#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace {
uint8_t		outerBank;

void	sync (void) {
	if (outerBank ==0) outerBank =Latch::data &0xE0;
	if (outerBank &0x40) {
		EMU->SetPRG_ROM32(0x8, Latch::data &7 | outerBank >>3 &0x18);
		if (Latch::data &0x10)
			EMU->Mirror_S0();
		else
			EMU->Mirror_S1();
	} else {
		EMU->SetPRG_ROM16(0x8, Latch::data &7 | outerBank >>2 &0x38);
		EMU->SetPRG_ROM16(0xC,              7 | outerBank >>2 &0x38);
		if (outerBank &0x10)
			EMU->Mirror_H();
		else
			EMU->Mirror_V();
	}
	EMU->SetCHR_RAM8(0x0, 0x0);
}

BOOL	MAPINT	load (void) {
	Latch::load(sync, FALSE);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	outerBank =0;
	Latch::reset(RESET_HARD);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =Latch::saveLoad_D(stateMode, offset, data);
	SAVELOAD_BYTE(stateMode, offset, data, outerBank);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum =453;
} // namespace

MapperInfo MapperInfo_453 ={
	&mapperNum,
	_T("Realtec 8042"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	NULL,
	NULL,
	saveLoad,
	NULL,
	NULL
};