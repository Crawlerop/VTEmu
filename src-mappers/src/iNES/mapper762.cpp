#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace {
void	sync (void) {
	if (Latch::addr &0x0200)
		EMU->SetPRG_ROM32(0x8, Latch::addr);
	else {
		EMU->SetPRG_ROM16(0x8,(Latch::addr <<1) | (Latch::addr &0x0100? 1: 0));
		EMU->SetPRG_ROM16(0xC,(Latch::addr <<1) | (Latch::addr &0x0100? 1: 0));
	}
	EMU->SetCHR_RAM8(0x0, 0);
	if (Latch::addr &0x0080)
		EMU->Mirror_H();
	else
		EMU->Mirror_V();
}

BOOL	MAPINT	load (void) {
	Latch::load(sync, FALSE);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	Latch::reset(RESET_HARD);
}

/*
	F23A: 8K bank @E000 := $EB/16K: $75/$3A
	
	Arabian: F411	: 88000 /4000 =22
*/
uint16_t MapperNum =762;
} // namespace

MapperInfo MapperInfo_762 ={
	&MapperNum,
	_T("90-in-1"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	NULL,
	NULL,
	Latch::saveLoad_A,
	NULL,
	NULL
};