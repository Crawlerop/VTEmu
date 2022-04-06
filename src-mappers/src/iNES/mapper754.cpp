#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace {
void	sync (void) {
	EMU->SetPRG_ROM32(8, Latch::addr >>2);
	EMU->SetCHR_ROM8(0, Latch::addr &4 && ~Latch::addr &8? Latch::addr &7: Latch::addr >>2);
	iNES_SetMirroring();
}

BOOL	MAPINT	load (void) {
	Latch::load(sync, false);
	return TRUE;
}

uint16_t mapperNum =754;
} // namespace

MapperInfo MapperInfo_754 ={
	&mapperNum,
	_T("ET-150"),
	COMPAT_FULL,
	load,
	Latch::resetHard,
	NULL,
	NULL,
	NULL,
	Latch::saveLoad_AL,
	NULL,
	NULL
};