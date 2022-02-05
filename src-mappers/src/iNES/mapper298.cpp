#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC4.h"

namespace {

void	Sync (void) {
	VRC4::syncPRG(0x1F, 0x00);
	VRC4::syncCHR(0x1FF, 0x00);
	VRC4::syncMirror();
}

BOOL	MAPINT	Load (void) {
	iNES_SetSRAM();
	VRC4::load(Sync, 0x02, 0x01, NULL, false, 0);
	return TRUE;
}

uint16_t MapperNum =298;
} // namespace

MapperInfo MapperInfo_298 = {
	&MapperNum,
	_T("NTDEC 1201"),
	COMPAT_FULL,
	Load,
	VRC4::reset,
	NULL,
	VRC4::cpuCycle,
	NULL,
	VRC4::saveLoad,
	NULL,
	NULL
};