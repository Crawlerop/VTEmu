#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace {
void	Sync (void) {
	if (Latch::addr &0x20) {
		EMU->SetPRG_ROM16(0x8, Latch::addr);
		EMU->SetPRG_ROM16(0xC, Latch::addr);
	} else {
		EMU->SetPRG_ROM16(0x8, Latch::addr | Latch::data);
		EMU->SetPRG_ROM16(0xC, Latch::addr | 7);
	}
	EMU->SetCHR_RAM8(0, 0);
	if ((Latch::addr &0x25) ==0x25)
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

uint16_t MapperNum =340;
} // namespace

MapperInfo MapperInfo_340 = {
	&MapperNum,
	_T("K-3036"),
	COMPAT_FULL,
	Load,
	Reset,
	NULL,
	NULL,
	NULL,
	Latch::saveLoad_AD,
	NULL,
	NULL
};