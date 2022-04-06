#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace {
void	sync (void) {
	if (Latch::data &0x40)
		EMU->SetPRG_ROM32(0x8, Latch::data >>1);
	else {
		EMU->SetPRG_ROM16(0x8, Latch::data);
		EMU->SetPRG_ROM16(0xC, Latch::data |7);
	}
	EMU->SetCHR_RAM8(0, 0);
	if (Latch::data &0x20)
		EMU->Mirror_H();
	else
		EMU->Mirror_V();
}

BOOL	MAPINT	load (void) {
	Latch::load(sync, FALSE);
	return TRUE;
}

uint16_t mapperNum =764;
} // namespace

MapperInfo MapperInfo_764 ={
	&mapperNum,
	_T("118-in-1"),
	COMPAT_FULL,
	load,
	Latch::resetHard,
	NULL,
	NULL,
	NULL,
	Latch::saveLoad_D,
	NULL,
	NULL
};