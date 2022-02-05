#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace {
void	Sync (void) {
	EMU->SetPRG_ROM16(0x8, Latch::data);
	EMU->SetPRG_ROM16(0xC, Latch::data |7);
	EMU->SetCHR_RAM8(0, 0);
}

BOOL	MAPINT	Load (void) {
	Latch::load(Sync, TRUE);
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType) {
	iNES_SetMirroring();
	Latch::reset(ResetType);
}

uint16_t MapperNum =336;
} // namespace

MapperInfo MapperInfo_336 = {
	&MapperNum,
	_T("K-3046"),
	COMPAT_FULL,
	Load,
	Reset,
	NULL,
	NULL,
	NULL,
	Latch::saveLoad_D,
	NULL,
	NULL
};