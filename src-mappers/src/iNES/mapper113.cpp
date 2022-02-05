#include	"..\DLL\d_iNES.h"

namespace {
FCPUWrite	writeAPU;
uint8_t		reg;

void	sync (void) {
	EMU->SetPRG_ROM32(0x8, reg >>3 &0x7);
	EMU->SetCHR_ROM8(0, reg &0x7 | reg >>3 &0x8);
	if (reg &0x80)
		EMU->Mirror_V();
	else	
		EMU->Mirror_H();
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	if (bank ==0x4) writeAPU(bank, addr, val);
	if (addr &0x100) {
		reg =val;
		sync();
	}
}

void	MAPINT	reset (RESET_TYPE resetType) {
	if (resetType ==RESET_HARD) reg =0;
	sync();

	writeAPU =EMU->GetCPUWriteHandler(0x4);
	for (int bank =0x4; bank <=0x5; bank++) EMU->SetCPUWriteHandler(bank, writeReg);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	SAVELOAD_BYTE(stateMode, offset, data, reg);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum =113;
} // namespace

MapperInfo MapperInfo_113 ={
	&mapperNum,
	_T("HES 4-in-1"),
	COMPAT_FULL,
	NULL,
	reset,
	NULL,
	NULL,
	NULL,
	saveLoad,
	NULL,
	NULL
};
