#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

#define nrom    !!(reg[0] &0x40) && !(reg[0] &0x20)
#define nrom256 !!(reg[0] &0x02)
#define prgA17  !!(reg[1] &0x08)
#define prgA18  !!(reg[1] &0x40)
#define chrA17  !!(reg[1] &0x04)
#define chrA18  !!(reg[0] &0x10)
#define prg       (reg[0] &1 | reg[0] >>2 &2 | reg[0] &4 | (prgA17? 8: 0) | (prgA18? 16: 0))
#define large   !!(reg[1] &0x02)

namespace {
uint8_t		reg[2];

void	sync (void) {
	if (nrom) {
		if (nrom256)
			EMU->SetPRG_ROM32(0x8, prg >>1);
		else {
			EMU->SetPRG_ROM16(0x8, prg);
			EMU->SetPRG_ROM16(0xC, prg);
		}
	} else {
		MMC3::syncPRG(large? 0x1F: 0x0F, (prgA17? 0x10: 0x00) | (prgA18? 0x20: 0x00));
	}
	MMC3::syncCHR(large? 0xFF: 0x7F, (chrA17? 0x80: 0x00) | (chrA18? 0x100: 0x000));
	MMC3::syncMirror();
	MMC3::syncWRAM();
}

void	MAPINT	write5 (int bank, int addr, int val) {
	reg[addr &1] =val;
	sync();
}

BOOL	MAPINT	load (void) {
	MMC3::load(sync);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	reg[0] =0x80;
	reg[1] =0x82; // Must boot up in 256 KiB mode
	
	MMC3::reset(resetType);
	EMU->SetCPUWriteHandler(0x5, write5);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =MMC3::saveLoad(stateMode, offset, data);
	for (auto& c: reg) SAVELOAD_BYTE(stateMode, offset, data, c);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum =411;
} // namespace

MapperInfo MapperInfo_411 ={
	&mapperNum,
	_T("A88S-1"),
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