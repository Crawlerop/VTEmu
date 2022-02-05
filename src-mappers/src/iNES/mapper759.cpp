#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

namespace {
void	sync (void) {
	MMC3::syncPRG(0x0F, MMC3::getPRGBank(1)     &~0x0F);
	MMC3::syncCHR(0x7F, MMC3::getPRGBank(1) <<3 &~0x7F);
	MMC3::syncWRAM();
	MMC3::syncMirror();
}

BOOL	MAPINT	load (void) {
	MMC3::load(sync);
	return TRUE;
}

uint16_t MapperNum =759;
} // namespace

MapperInfo MapperInfo_759 = {
	&MapperNum,
	_T("K-3043"),
	COMPAT_FULL,
	load,
	MMC3::reset,
	NULL,
	MMC3::cpuCycle,
	MMC3::ppuCycle,
	MMC3::saveLoad,
	NULL,
	NULL
};