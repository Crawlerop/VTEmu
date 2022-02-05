#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

/*	Reg			0	1	2	PRG	CHR
	Astrosmash		60	00	76	32	16
	Beach Volleyball	00	00	06	32	16
	Crown of Kings		00	B7	00	64	32
	Deadly Discs		78	00	46	32	16
	Frog Bog		08	00	16	32	16
	Long Drive Golf		10	00	26	32	24
	Maze Shoot		20	00	36	32	32
	Space Armada		40	00	86	32	32
	Space Gunner		58	00	62	16	16
	Tennis			50	00	56	32	16	
*/

#define nrom      !!(reg[2] &0x02)
#define nrom256   !!(reg[2] &0x04)
#define prg         (reg[2] >>3)
#define prgAND      (0x3F &~(reg[1] <<3 &0x38))
#define prgOR       (reg[1] >>2 &0x3E)
#define chr         (reg[0] >>2)
namespace {
uint8_t		reg[4];

void	sync (void) {
	if (nrom) {
		EMU->SetPRG_ROM16(0x8, prg &~(1*nrom256));
		EMU->SetPRG_ROM16(0xC, prg |  1*nrom256 );
		EMU->SetCHR_ROM8(0x0, chr);
	} else {
		MMC3::syncPRG(prgAND, prgOR &~prgAND);
		MMC3::syncCHR(0x7F, reg[1] &0x80);
	}
		
	MMC3::syncMirror();
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	reg[addr &3] =val;
	sync();
}

BOOL	MAPINT	load (void) {
	MMC3::load(sync);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	for (auto& r: reg) r =0x00;
	MMC3::reset(RESET_HARD);
	MMC3::setWRAMCallback(NULL, writeReg);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =MMC3::saveLoad(stateMode, offset, data);
	for (auto& r: reg) SAVELOAD_BYTE(stateMode, offset, data, r);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum =412;
} // namespace

MapperInfo MapperInfo_412 = {
	&mapperNum,
	_T("Intellivision"),
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
