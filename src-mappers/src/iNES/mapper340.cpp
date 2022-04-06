#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace {
void	sync (void) {
	if (Latch::addr &0x20) {
		EMU->SetPRG_ROM16(0x8, Latch::addr >>2 &0x20 | Latch::addr &0x1F);
		EMU->SetPRG_ROM16(0xC, Latch::addr >>2 &0x20 | Latch::addr &0x1F);
	} else {
		EMU->SetPRG_ROM16(0x8, Latch::addr >>2 &0x20 | Latch::addr | Latch::data);
		EMU->SetPRG_ROM16(0xC, Latch::addr >>2 &0x20 | Latch::addr | 7);
	}
	EMU->SetCHR_RAM8(0, 0);
	if (Latch::addr &0x40 || Latch::addr &0x20 && Latch::addr &0x04)
		EMU->Mirror_H();
	else
		EMU->Mirror_V();
}

BOOL	MAPINT	load (void) {
	Latch::load(sync, true);
	return TRUE;
}

uint16_t mapperNum =340;
} // namespace

MapperInfo MapperInfo_340 = {
	&mapperNum,
	_T("K-3036"),
	COMPAT_FULL,
	load,
	Latch::resetHard,
	NULL,
	NULL,
	NULL,
	Latch::saveLoad_AD,
	NULL,
	NULL
};