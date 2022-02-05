#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC2.h"
#include	"..\Hardware\h_VRC4.h"

namespace {
void	sync (void) {
	EMU->SetPRG_RAM8(0x6, 0);
	EMU->SetPRG_ROM8(0x8 ^VRC4::prgFlip, VRC4::prg[0]);
	EMU->SetPRG_ROM8(0xA               , VRC4::prg[1]);
	EMU->SetPRG_ROM8(0xC ^VRC4::prgFlip, ROM->INES_PRGSize*2 -2);
	EMU->SetPRG_ROM8(0xE               , ROM->INES_PRGSize*2 -1);	
	VRC4::syncCHR(0x1FF, 0x000);
	VRC4::syncMirror();
}

BOOL	MAPINT	load (void) {
	iNES_SetSRAM();
	VRC4::load(sync, 0x05, 0x0A, NULL, true, 0);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	VRC4::reset(resetType);
	if (ROM->MiscROMData && ROM->MiscROMSize) for (unsigned int i =0; i <ROM->MiscROMSize; i++) ROM->PRGRAMData[i +0x1000] =ROM->MiscROMData[i];
}

uint16_t mapperNum =563;
} // namespace

MapperInfo MapperInfo_563 = {
	&mapperNum,
	_T("Bad mapper 23 homebrew"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	VRC4::cpuCycle,
	NULL,
	VRC4::saveLoad,
	NULL,
	NULL
};