#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC4.h"

namespace {	
int	CurrentCHRBank;
FPPURead _ReadCHR;

void	Sync (void) {
	VRC4::syncPRG(0x1F, (VRC4::chr[CurrentCHRBank] &8) <<2);
	VRC4::syncCHR_RAM(0x07, 0x00);
	VRC4::syncMirror();
}

int	MAPINT	ReadCHR (int Bank, int Addr) {
	CurrentCHRBank =Bank;
	Sync();
	return _ReadCHR(Bank, Addr);
}

BOOL	MAPINT	Load (void) {
	iNES_SetSRAM();
	VRC4::load(Sync, 0x04, 0x08, NULL, true, 0);
	return TRUE;
}

void	MAPINT	Reset (RESET_TYPE ResetType) {
	VRC4::reset(ResetType);
	_ReadCHR =EMU->GetPPUReadHandler(0);
	for (int i =0; i <8; i++) EMU->SetPPUReadHandler(i, ReadCHR);
}

uint16_t MapperNum =520;
} // namespace

MapperInfo MapperInfo_520 = {
	&MapperNum,
	_T("Yu Yu Hakusho+Datach Dragon Ball Z multicart"),
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