#include	"..\DLL\d_iNES.h" 

namespace {
uint8_t		reg;
bool		irq;
uint16_t	counter;

void	sync (void) {
	EMU->SetPRG_ROM8(0x6, 6);
	EMU->SetPRG_ROM8(0x8, 4);
	EMU->SetPRG_ROM8(0xA, 5);
	EMU->SetPRG_ROM8(0xC, reg &7);
	EMU->SetPRG_ROM8(0xE, 7);
	iNES_SetCHR_Auto8(0x0, reg >>3);
	iNES_SetMirroring();
}

void	MAPINT	writeIRQ (int bank, int addr, int val) {
	irq =!!(bank &2);
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	reg =val;
	sync();
}

void	MAPINT	reset (RESET_TYPE resetType) {
	if (resetType ==RESET_HARD) reg =0;
	sync();
	irq =false;
	counter =0;
	EMU->SetIRQ(1);
	
	for (int bank =0x8; bank<=0xB; bank++) EMU->SetCPUWriteHandler(bank, writeIRQ);
	for (int bank =0xE; bank<=0xF; bank++) EMU->SetCPUWriteHandler(bank, writeReg);
}

void	MAPINT	cpuCycle (void) {
	if (irq)
		EMU->SetIRQ(++counter &0x1000? 0: 1);
	else {
		EMU->SetIRQ(1);
		counter =0;
	}
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	SAVELOAD_BYTE(stateMode, offset, data, reg);
	SAVELOAD_BOOL(stateMode, offset, data, irq);
	SAVELOAD_WORD(stateMode, offset, data, counter);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum =40;
} // namespace

MapperInfo MapperInfo_040 ={
	&mapperNum,
	_T("NTDEC 2722"),
	COMPAT_FULL,
	NULL,
	reset,
	NULL,
	cpuCycle,
	NULL,
	saveLoad,
	NULL,
	NULL
};