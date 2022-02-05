#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace {
void	Sync (void) {
	EMU->SetPRG_ROM32(0x8, Latch::addr >>8);
	EMU->SetCHR_ROM8(0, Latch::addr >>8);
	if (Latch::addr &0x200)
		EMU->Mirror_H();
	else
		EMU->Mirror_V();
}

BOOL	MAPINT	Load (void) {
	Latch::load(Sync, TRUE);
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType) {
	Latch::reset(ResetType);
}

uint16_t MapperNum =341;
} // namespace

MapperInfo MapperInfo_341 = {
	&MapperNum,
	_T("TJ-03"),
	COMPAT_FULL,
	Load,
	Reset,
	NULL,
	NULL,
	NULL,
	Latch::saveLoad_A,
	NULL,
	NULL
};