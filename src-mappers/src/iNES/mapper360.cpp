#include	"..\DLL\d_iNES.h"

namespace {
void	Sync (void) {
	if (ROM->dipValue <2)
		EMU->SetPRG_ROM32(0x8, ROM->dipValue >>1);
	else {
		EMU->SetPRG_ROM16(0x8, ROM->dipValue);
		EMU->SetPRG_ROM16(0xC, ROM->dipValue);
	}
	EMU->SetCHR_ROM8(0x0, ROM->dipValue);
	if (ROM->dipValue & 0x10)
		EMU->Mirror_H();
	else
		EMU->Mirror_V();
}

void	MAPINT	Reset (RESET_TYPE ResetType) {
	Sync();
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data) {
	if (mode ==STATE_LOAD) Sync();
	return offset;
}

uint16_t MapperNum =360;
} // namespace

MapperInfo MapperInfo_360 ={
	&MapperNum,
	_T("普澤 P3150"),
	COMPAT_FULL,
	NULL,
	Reset,
	NULL,
	NULL,
	NULL,
	SaveLoad,
	NULL,
	NULL
};
