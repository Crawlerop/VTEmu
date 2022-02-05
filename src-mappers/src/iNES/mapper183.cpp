#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC4.h"

namespace {
uint8_t PRG[4];

void	Sync (void) {
	EMU->SetPRG_ROM8(0x6, PRG[0]);
	EMU->SetPRG_ROM8(0x8, PRG[1]);
	EMU->SetPRG_ROM8(0xA, PRG[2]);
	EMU->SetPRG_ROM8(0xC, PRG[3]);
	EMU->SetPRG_ROM8(0xE, 0xFF);
	VRC4::syncCHR_ROM(0x1FF, 0x00);
	VRC4::syncMirror();
}

void	MAPINT	Write (int Bank, int Addr, int Val) {
	if (Bank ==0x9 && Addr &0x800) VRC4::writeMisc(0x9, 0x0, Val); else
	if (Bank ==0x6 && Addr &0x800) PRG[0] =Addr &0x3F; else
	if (Bank ==0x8 && Addr &0x800) PRG[1] =Val; else
	if (Bank ==0xA && Addr &0x800) PRG[2] =Val; else
	if (Bank ==0xA &&~Addr &0x800) PRG[3] =Val;
	Sync();
}

BOOL	MAPINT	Load (void) {
	VRC4::load(Sync, 0x04, 0x08, NULL, true, 0);
	return TRUE;
}

void	MAPINT	Reset (RESET_TYPE ResetType) {
	VRC4::reset(ResetType);
	for (int i =0x6; i<=0xA; i++) EMU->SetCPUWriteHandler(i, Write);
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data) {
	for (int i =0; i <4; i++) SAVELOAD_BYTE(mode, offset, data, PRG[i]);
	offset =VRC4::saveLoad(mode, offset, data);
	return offset;
}

uint16_t MapperNum =183;
} // namespace

MapperInfo MapperInfo_183 = {
	&MapperNum,
	_T("Shui Guan Pipe"),
	COMPAT_FULL,
	Load,
	Reset,
	NULL,
	VRC4::cpuCycle,
	NULL,
	VRC4::saveLoad,
	NULL,
	NULL
};