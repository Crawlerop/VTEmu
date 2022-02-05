#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC2.h"

namespace {
void	Sync (void) {
	VRC2::syncPRG(0x1F, 0x00);
	VRC2::syncCHR_ROM(0xFFF, 0x000);
	VRC2::syncMirror();
	EMU->Mirror_Custom(VRC2::chr[0] >> 7, VRC2::chr[0] >> 7, VRC2::chr[1] >> 7, VRC2::chr[1] >> 7);
}

BOOL	MAPINT	Load (void) {
	iNES_SetSRAM();
	VRC2::load(Sync, 0x01, 0x02);
	return TRUE;
}

void	MAPINT	Reset (RESET_TYPE ResetType) {
	VRC2::reset(ResetType);
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data) {
	offset =VRC2::saveLoad(mode, offset, data);
	return offset;
}

uint16_t MapperNum =527;
} // namespace

MapperInfo MapperInfo_527 = {
	&MapperNum,
	_T("AX-40G"),
	COMPAT_FULL,
	Load,
	Reset,
	NULL,
	NULL,
	NULL,
	VRC2::saveLoad,
	NULL,
	NULL
};