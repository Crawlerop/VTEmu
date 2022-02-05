#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace {
void	sync (void) {
	EMU->SetPRG_ROM32(8, Latch::addr);
	EMU->SetCHR_ROM8(0, Latch::addr);
	iNES_SetMirroring();
}

BOOL	MAPINT	load (void) {
	Latch::load(sync, FALSE);
	return TRUE;
}

uint16_t mapperNum =201;
} // namespace

MapperInfo MapperInfo_201 ={
	&mapperNum,
	_T("21-in-1"),
	COMPAT_FULL,
	load,
	Latch::reset,
	NULL,
	NULL,
	NULL,
	Latch::saveLoad_AL,
	NULL,
	NULL
};