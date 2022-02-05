#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

#define	mirrorH !!(Latch::data &0x0001)
#define	nrom128 !!(Latch::data &0x0002)
#define	last      (Latch::data &0x0004)
#define	nrom256 !!(Latch::data &0x0008)
#define wramBank  (Latch::data >>3 &6 |8)

namespace {
void	sync (void) {
	if (nrom128) {
		EMU->SetPRG_ROM8(0x8, Latch::addr >>1);
		EMU->SetPRG_ROM8(0xA, Latch::addr >>1);
		EMU->SetPRG_ROM8(0xC, Latch::addr >>1);
		EMU->SetPRG_ROM8(0xE, Latch::addr >>1);
		EMU->SetPRG_RAM8(wramBank ^4, 0);
	} else
	if (nrom256) {
		EMU->SetPRG_ROM8(0x8, Latch::addr >>1 |0);
		EMU->SetPRG_ROM8(0xA, Latch::addr >>1 |1);
		EMU->SetPRG_ROM8(0xC, Latch::addr >>1 |2);
		EMU->SetPRG_ROM8(0xE, Latch::addr >>1 |3 |last);
	} else {
		EMU->SetPRG_ROM16(0x8, Latch::addr >>2);
		EMU->SetPRG_ROM16(0xC,               0);
	}
	EMU->SetPRG_RAM8(wramBank, 0);
	EMU->SetCHR_RAM8(0x0, 0);	
	if (mirrorH)
		EMU->Mirror_H();
	else	
		EMU->Mirror_V();
}

BOOL	MAPINT	load (void) {
	Latch::load(sync, false);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	FCPUWrite cartWrite =EMU->GetCPUWriteHandler(0xE);
	Latch::reset(RESET_HARD);
	for (int bank =0xE; bank<=0xF; bank++) EMU->SetCPUWriteHandler(bank, cartWrite); // Latch does not respond at E000-FFFF; WRAM may be mapped there
}

uint16_t mapperNum =452;
} // namespace

MapperInfo MapperInfo_452 ={
	&mapperNum,
	_T("DS-9-27"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	NULL,
	NULL,
	Latch::saveLoad_AD,
	NULL,
	NULL
};