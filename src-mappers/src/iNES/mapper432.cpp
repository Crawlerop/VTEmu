#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

namespace {
uint8_t	Reg;

void	Sync (void) {
	if (Reg &0x04) {
		MMC3::syncPRG(0x0F, Reg <<4 &0x10 | Reg <<1 &0x20);
		MMC3::syncCHR(0x7F, Reg <<7 &0x80 | Reg <<5 &0x100);
	} else {
		MMC3::syncPRG(0x1F,                 Reg <<1 &0x20);
		MMC3::syncCHR(0xFF, Reg <<5 &0x100);
	}
	MMC3::syncWRAM();
	MMC3::syncMirror();
}

void	MAPINT	WriteReg (int Bank, int Addr, int Val) {
	Reg =Val &0xFF;
	Sync();
}

BOOL	MAPINT	Load (void) {
	MMC3::load(Sync);
	return TRUE;
}

void	MAPINT	Reset (RESET_TYPE ResetType) {
	Reg =0;
	MMC3::reset(ResetType);
	MMC3::setWRAMCallback(NULL, WriteReg);
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data) {
	offset = MMC3::saveLoad(mode, offset, data);
	SAVELOAD_BYTE(mode, offset, data, Reg);
	if (mode ==STATE_LOAD) Sync();
	return offset;
}

uint16_t MapperNum =432;
} // namespace

MapperInfo MapperInfo_432 = {
	&MapperNum,
	_T("Realtec 8090"),
	COMPAT_FULL,
	Load,
	Reset,
	NULL,
	MMC3::cpuCycle,
	MMC3::ppuCycle,
	SaveLoad,
	NULL,
	NULL
};