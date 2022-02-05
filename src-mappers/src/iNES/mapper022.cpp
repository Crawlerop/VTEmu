#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC2.h"

namespace {
void	sync (void) {
	VRC2::syncPRG(0x1F, 0x00);
	for (int i =0; i <8; i++) EMU->SetCHR_ROM1(i, VRC2::chr[i] >>1);
	VRC2::syncMirror();
}

BOOL	MAPINT	load (void) {
	iNES_SetSRAM();
	VRC2::load(sync, 0x02, 0x01);
	return TRUE;
}

uint16_t mapperNum =22;
} // namespace

MapperInfo MapperInfo_022 = {
	&mapperNum,
	_T("Konami 351618"),
	COMPAT_FULL,
	load,
	VRC2::reset,
	NULL,
	NULL,
	NULL,
	VRC2::saveLoad,
	NULL,
	NULL
};