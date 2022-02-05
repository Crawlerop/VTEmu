#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace {
void	sync (void) {
	bool writeEnable =false;
	for (int bank =0x6; bank<=0x7; bank++) EMU->SetPRG_OB4(bank);
	switch (Latch::addr &7) {
		case 0: case 4:
			EMU->SetPRG_ROM32(0x8, Latch::data >>1);
			break;
		case 1:	EMU->SetPRG_ROM16(0x8, Latch::data);
			EMU->SetPRG_ROM16(0xC, Latch::data | 7);
			writeEnable =true;
			break;
		case 2:	case 6:
			EMU->SetPRG_ROM8(0x8, Latch::data <<1 | Latch::data >>7);
			EMU->SetPRG_ROM8(0xA, Latch::data <<1 | Latch::data >>7);
			EMU->SetPRG_ROM8(0xC, Latch::data <<1 | Latch::data >>7);
			EMU->SetPRG_ROM8(0xE, Latch::data <<1 | Latch::data >>7);
			writeEnable =true;
			break;
		case 3:	case 7:
			EMU->SetPRG_ROM16(0x8, Latch::data);
			EMU->SetPRG_ROM16(0xC, Latch::data);
			break;
		case 5:	EMU->SetPRG_ROM8 (0x6, Latch::data <<1 | Latch::data >>7);
			EMU->SetPRG_ROM32(0x8, Latch::data >>1 | 3);
			writeEnable =true;
			break;
	}
	EMU->SetCHR_RAM8(0, 0);
	for (int bank =0; bank <8; bank++) EMU->SetCHR_Ptr1(bank, EMU->GetCHR_Ptr1(bank), writeEnable);
	
	if (Latch::data &0x40)
		EMU->Mirror_H();
	else	
		EMU->Mirror_V();
}

BOOL	MAPINT	load (void) {
	Latch::load(sync, FALSE);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	FCPUWrite writeNothing =EMU->GetCPUWriteHandler(0x8);
	Latch::reset(RESET_HARD);
	for (int bank =0x8; bank<=0xE; bank++) EMU->SetCPUWriteHandler(bank, writeNothing); // Only responds in the $F000-$FFFF range
}

uint16_t MapperNum =354;
} // namespace

MapperInfo MapperInfo_354 ={
	&MapperNum,
	_T("FAM250"),
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