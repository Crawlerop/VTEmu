#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace {
uint8_t		reg[2];
uint8_t		mirroring;

void	sync (void) {
	if (reg[1] !=0xF0) mirroring =Latch::data;
	EMU->SetPRG_ROM16(0x8, reg[0] >>1 &~7 | Latch::data &7);
	EMU->SetPRG_ROM16(0xC, reg[0] >>1 &~7 |              7);
	EMU->SetCHR_RAM8(0x0, 0);
	if (mirroring &0x80)
		EMU->Mirror_H();
	else
		EMU->Mirror_V();
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	reg[addr &1] =val;
	sync();
}

BOOL	MAPINT	load (void) {
	Latch::load(sync, FALSE);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	reg[0] =0xF0;
	reg[1] =0x00;
	mirroring =0x00;
	Latch::reset(RESET_HARD);
	for (int bank =0x6; bank<=0x7; bank++) EMU->SetCPUWriteHandler(bank, writeReg);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =Latch::saveLoad_D(stateMode, offset, data);
	for (auto c: reg) SAVELOAD_BYTE(stateMode, offset, data, c);
	SAVELOAD_BYTE(stateMode, offset, data, mirroring);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum =439;
} // namespace

MapperInfo MapperInfo_439 ={
	&mapperNum,
	_T("YS2309"),
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