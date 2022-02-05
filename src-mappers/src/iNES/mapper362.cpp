#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC4.h"

namespace {	
uint8_t		currentCHRBank;
uint8_t		game;
FPPURead	readCHR;

void	sync (void) {
	if (game ==0) {
		VRC4::syncPRG(0x0F, (VRC4::chr[currentCHRBank] &0x180) >>3);
		VRC4::syncCHR(0x7F, VRC4::chr[currentCHRBank] &0x180);
	} else {
		VRC4::syncPRG(0x0F, 0x40);
		VRC4::syncCHR(0x1FF, 0x200);
	}
	VRC4::syncMirror();
}

int	MAPINT	trapCHRRead (int bank, int addr) {
	currentCHRBank =bank;
	sync();
	return readCHR(bank, addr);
}

BOOL	MAPINT	load (void) {
	iNES_SetSRAM();
	VRC4::load(sync, 0x01, 0x02, NULL, false, 0);
	if (ROM->PRGROMSize <=512*1024)
		MapperInfo_362.Description =_T("晶太 830506C");
	else
		MapperInfo_362.Description =_T("晶太 830529C");
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	if (resetType ==RESET_HARD || ROM->PRGROMSize <=512*1024)
		game =0;
	else
		game ^=1;
	VRC4::reset(resetType);
	
	if (game ==0) {
		readCHR =EMU->GetPPUReadHandler(0x0);
		for (int bank =0; bank <8; bank++) {
			EMU->SetPPUReadHandler(bank, trapCHRRead);
			EMU->SetPPUReadHandlerDebug(bank, readCHR);
		}
	}
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =VRC4::saveLoad(stateMode, offset, data);
	if (ROM->PRGROMSize ==768*1024 && ROM->CHRROMSize ==768*1024) SAVELOAD_BYTE(stateMode, offset, data, game);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t MapperNum =362;
} // namespace

MapperInfo MapperInfo_362 = {
	&MapperNum,
	_T("晶太 830506C"),
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