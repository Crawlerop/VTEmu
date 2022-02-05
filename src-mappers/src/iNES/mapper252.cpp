#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC4.h"

namespace {
FPPUWrite	writeCHR;
uint8_t		maskCHRBank;
uint8_t		maskCompare;

void	sync (void) {
	VRC4::syncPRG(0x1F, 0x00);
	
	for (int bank =0x0; bank <0x8; bank++) {
		int val =VRC4::chr[bank];
		if ((val &maskCHRBank) ==maskCompare)
			EMU->SetCHR_RAM1(bank, val);
		else
			EMU->SetCHR_ROM1(bank, val);
	}
	VRC4::syncMirror();
}

void	MAPINT	interceptCHRWrite (int bank, int addr, int val) {
	switch(VRC4::chr[bank]) {
		case 0x88: maskCHRBank =0xFC; maskCompare =0x4C; break;
		case 0xC2: maskCHRBank =0xFE; maskCompare =0x7C; break;
		case 0xC8: maskCHRBank =0xFE; maskCompare =0x04; break;
	}
	writeCHR(bank, addr, val);
}

BOOL	MAPINT	load (void) {
	iNES_SetSRAM();
	VRC4::load(sync, 0x4, 0x8, NULL, true, 1);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	if (resetType ==RESET_HARD) {
		if (ROM->INES_MapperNum ==252) {
			maskCHRBank =0xFE;
			maskCompare =0x06;
		} else { // Actual later board starts with FC/28, but earlier board is fixed to FE/04
			maskCHRBank =0xFE;
			maskCompare =0x04;
		}
	}
	VRC4::reset(resetType);
	writeCHR =EMU->GetPPUWriteHandler(0x0);
	for (int bank =0x0; bank<=0x7; bank++) EMU->SetPPUWriteHandler(bank, interceptCHRWrite);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =VRC4::saveLoad(stateMode, offset, data);
	SAVELOAD_BYTE(stateMode, offset, data, maskCHRBank);
	SAVELOAD_BYTE(stateMode, offset, data, maskCompare);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum252 =252;
uint16_t mapperNum253 =253;
} // namespace

MapperInfo MapperInfo_252 ={
	&mapperNum252,
	_T("外星 FS???"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	VRC4::cpuCycle,
	NULL,
	saveLoad,
	NULL,
	NULL
};
MapperInfo MapperInfo_253 ={
	&mapperNum253,
	_T("外星 FS???"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	VRC4::cpuCycle,
	NULL,
	saveLoad,
	NULL,
	NULL
};