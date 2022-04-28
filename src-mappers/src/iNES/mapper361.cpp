#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

namespace {
uint8_t OuterBank;

void	Sync (void) {
	MMC3::syncMirror();
	MMC3::syncPRG(0x0F, OuterBank &~0x0F);
	MMC3::syncCHR_ROM(0x7F, (OuterBank &~0x0F) <<3);
	MMC3::syncWRAM();
}

BOOL	MAPINT	Load (void) {
	MMC3::load(Sync);
	return TRUE;
}

void	MAPINT	WriteOuterBank (int Bank, int Addr, int Val) {
	OuterBank =Val;
	Sync();
}

void	MAPINT	Reset (RESET_TYPE ResetType) {	
	if (ResetType ==RESET_HARD) OuterBank =0;
	MMC3::reset(ResetType);
	EMU->SetCPUWriteHandler(0x7, WriteOuterBank);
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data) {
	SAVELOAD_BYTE(mode, offset, data, OuterBank);
	offset = MMC3::saveLoad(mode, offset, data);
	if (mode == STATE_LOAD)	Sync();
	return offset;
}

uint16_t MapperNum =361;
} // namespace

MapperInfo MapperInfo_361 ={
	&MapperNum,
	_T("晶太 YY841101C"),
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