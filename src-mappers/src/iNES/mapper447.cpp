#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC4.h"

namespace {
uint8_t		reg;
FCPURead	readROM;

int	MAPINT	interceptRead (int bank, int addr);
void	sync (void) {
	if (reg &4) {
		int A14 =~reg &2;
		EMU->SetPRG_ROM8(0x8, (VRC4::prg[0] &~A14) &0x0F | reg <<4);
		EMU->SetPRG_ROM8(0xA, (VRC4::prg[1] &~A14) &0x0F | reg <<4);
		EMU->SetPRG_ROM8(0xC, (VRC4::prg[0] | A14) &0x0F | reg <<4);
		EMU->SetPRG_ROM8(0xE, (VRC4::prg[1] | A14) &0x0F | reg <<4);
	} else
		VRC4::syncPRG(0x0F, reg <<4);
	VRC4::syncCHR(0x7F, reg <<7);
	VRC4::syncMirror();

	for (int bank =0x8; bank <=0xF; bank++) EMU->SetCPUReadHandler(bank, ROM->dipValueSet && reg &8? interceptRead: readROM);
}

int	MAPINT	interceptRead (int bank, int addr) {
	return readROM(bank, addr &~3 | ROM->dipValue &3);
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	VRC4::writeWRAM(bank, addr, val);
	if (VRC4::wramEnable && ~reg &1) reg =addr &0xFF;
	sync();
}

BOOL	MAPINT	load (void) {
	iNES_SetSRAM();
	VRC4::load(sync, 0x04, 0x08, NULL, true, 0);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	readROM =EMU->GetCPUReadHandler(0x8);

	reg =0;
	VRC4::reset(resetType);
	for (int bank =0x6; bank <=0x7; bank++) EMU->SetCPUWriteHandler(bank, writeReg);
}

uint16_t MapperNum =447;
} // namespace

MapperInfo MapperInfo_447 = {
	&MapperNum,
	_T("KL-06"),
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