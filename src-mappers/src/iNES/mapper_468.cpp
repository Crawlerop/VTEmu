#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC1.h"

#define locked     !!(reg[0] &0x80)
#define mirrorH    !!(reg[0] &0x01)
#define mapper        reg[4]
#define protectCHR !!(reg[5] &0x04)
#define prgOR        (reg[1] | reg[2] <<8)
#define prgAND        reg[3]
#define chr           reg[6]

#define MAPPER_NROM 0
#define MAPPER_MMC1 4

namespace {
uint8_t		reg[8];
FCPUWrite	dummy;

void	sync (void) {
	if (locked) switch(mapper) {
		case MAPPER_NROM:
			EMU->SetPRG_OB4(0x6);
			EMU->SetPRG_OB4(0x7);
			EMU->SetPRG_ROM8(0x8, 0 &~prgAND | prgOR);
			EMU->SetPRG_ROM8(0xA, 1 &~prgAND | prgOR);
			EMU->SetPRG_ROM8(0xC, 2 &~prgAND | prgOR);
			EMU->SetPRG_ROM8(0xE, 3 &~prgAND | prgOR);
			EMU->SetCHR_RAM8(0x0, chr);
			if (mirrorH)
				EMU->Mirror_H();
			else
				EMU->Mirror_V();
			break;
		case MAPPER_MMC1:
			MMC1::syncWRAM(0);
			MMC1::syncPRG(~prgAND >>1, prgOR >>1);
			MMC1::syncCHR(0x1F, chr >>2);
			MMC1::syncMirror();
			break;
	} else {
		EMU->SetPRG_ROM8(0x8, prgOR);
		EMU->SetPRG_ROM8(0xA, 0x3D);
		EMU->SetPRG_ROM8(0xC, 0x3E);
		EMU->SetPRG_ROM8(0xE, 0x3F);
		EMU->SetCHR_RAM8(0x0, chr);
		if (mirrorH)
			EMU->Mirror_H();
		else
			EMU->Mirror_V();		
	}
	if (protectCHR) protectCHRRAM();
}

void	applyMode ();
void	MAPINT	writeReg (int bank, int addr, int val) {
	reg[addr >>8 &7] =val;
	if (locked) applyMode();
	sync();
}

void	applyMode () {
	for (int bank =0x5; bank <=0xF; bank++) EMU->SetCPUWriteHandler(bank, dummy);
	if (locked) switch(mapper) {
		case MAPPER_MMC1:
			MMC1::reset(RESET_HARD);
			break;			
	} else
		EMU->SetCPUWriteHandler(0x5, writeReg);
}

BOOL	MAPINT	load (void) {
	iNES_SetSRAM();
	MMC1::load(sync, MMC1Type::MMC1B);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	for (auto& c: reg) c =0;
	dummy =EMU->GetCPUWriteHandler(0x8);
	applyMode();
	sync();
}

void	MAPINT	cpuCycle (void) {
	if (locked) switch(mapper) {
		case MAPPER_NROM:
			break;
		case MAPPER_MMC1:
			MMC1::cpuCycle();
			break;			
	}
}

void	MAPINT	ppuCycle (int addr, int scanline, int cycle, int isRendering) {
	if (locked) switch(mapper) {
		case MAPPER_NROM:
			break;
		case MAPPER_MMC1:
			break;			
	}
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	for (auto& c: reg) SAVELOAD_BYTE(stateMode, offset, data, c);
	if (stateMode ==STATE_LOAD) applyMode();
	offset =MMC1::saveLoad(stateMode, offset, data);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum =468;
} // namespace

MapperInfo MapperInfo_468 ={
	&mapperNum,
	_T("FDS"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	cpuCycle,
	ppuCycle,
	saveLoad,
	NULL,
	NULL
};