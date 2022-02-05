#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

namespace {
uint8_t		reg;
#define	locked  !!(reg &0x80)
#define	prgOR     (reg <<4 &0x70)
#define	chrOR     (reg <<3 &0x180 | reg <<7 &0x200)
#define	prgAND    (reg &0x08? 0x0F: 0x1F)
#define	chrAND    (reg &0x40? 0x7F: 0xFF)

void	sync (void) {
	MMC3::syncWRAM();
	MMC3::syncPRG(prgAND, prgOR &~prgAND);
	if (ROM->INES2_SubMapper ==13 && reg ==0x8B)
		EMU->SetCHR_RAM8(0x0, 0);
	else
		MMC3::syncCHR(chrAND, chrOR &~chrAND);
	MMC3::syncMirror();
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	if (!locked) {
		reg =val;
		sync();
	} else
		MMC3::wramWrite(bank, addr, val);
}

BOOL	MAPINT	load (void) {
	MMC3::load(sync);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	reg =0x00;
	MMC3::reset(resetType);
	MMC3::setWRAMCallback(NULL, writeReg);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =MMC3::saveLoad(stateMode, offset, data);
	SAVELOAD_BYTE(stateMode, offset, data, reg);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum =52;
} // namespace

MapperInfo MapperInfo_052 ={
	&mapperNum,
	_T("Realtec 8213"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	MMC3::cpuCycle,
	MMC3::ppuCycle,
	saveLoad,
	NULL,
	NULL
};