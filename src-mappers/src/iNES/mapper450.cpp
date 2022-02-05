#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC2.h"

namespace {
uint8_t		reg;

void	sync (void) {
	VRC2::syncPRG(0x0F, reg <<4);
	VRC2::syncCHR_ROM(0x7F, reg <<7);
	VRC2::syncMirror();
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	reg =val;
	sync();
}

BOOL	MAPINT	load (void) {
	VRC2::load(sync, 0x01, 0x02);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	reg =0;
	VRC2::reset(resetType);
	for (int bank =0x6; bank <=0x7; bank++) EMU->SetCPUWriteHandler(bank, writeReg);
}

uint16_t MapperNum =450;
} // namespace

MapperInfo MapperInfo_450 = {
	&MapperNum,
	_T("晶太 YY841157C"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	NULL,
	NULL,
	VRC2::saveLoad,
	NULL,
	NULL
};