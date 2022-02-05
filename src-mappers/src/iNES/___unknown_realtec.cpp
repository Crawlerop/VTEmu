/* used by nesdev */
#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

namespace {
uint8_t		reg[2];
#define	prgAND    (reg[1] &0x10? 0x0F: 0x1F)
#define	prgOR     (reg[1] <<4 &0x030)
#define	chrOR     (reg[1] <<5 &0x180)
#define nrom    !!(reg[1] &0x40 && ~reg[1] &0x10)
#define nrom128 !!(reg[1] &0x40)

void	sync (void) {
	if (reg[1] ==0x83) {
		MMC3::syncPRG(0x0F, 0x10);
		MMC3::syncCHR(0x7F, 0x000);
	} else
	if (reg[1] ==0x86) {
		MMC3::syncPRG(0x0F, 0x00);
		MMC3::syncCHR(0x7F, 0x000);
	} else
	if (nrom) {
		MMC3::syncPRG_GNROM_67(nrom128? 0: 1, 0x3F, 0x00);
		MMC3::syncCHR(0x0FF, chrOR &0x100);
	} else {
		MMC3::syncPRG(prgAND, prgOR &~prgAND);
		MMC3::syncCHR(0x0FF, chrOR);
	}
	MMC3::syncMirror();
	MMC3::syncWRAM();
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	MMC3::wramWrite(bank, addr, val);
//	if (!locked) {
		reg[addr &1] =val;
		sync();
//	}
}

BOOL	MAPINT	load (void) {
	MMC3::load(sync);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	for (auto& r: reg) r =0x00;
	MMC3::reset(resetType);
	MMC3::setWRAMCallback(NULL, writeReg);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =MMC3::saveLoad(stateMode, offset, data);
	for (auto& r: reg) SAVELOAD_BYTE(stateMode, offset, data, r);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum =429;
} // namespace

MapperInfo MapperInfo_429 ={
	&mapperNum,
	_T("Realtec ????"),
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