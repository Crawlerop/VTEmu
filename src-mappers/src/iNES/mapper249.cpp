#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

namespace {
uint8_t	AlternateMapping;

static const uint8_t bitOrder[2][8] = {
	{ 7, 6, 5, 2, 1, 3, 4, 0 },
	{ 5, 4, 2, 6, 7, 3, 1, 0 },
};

uint8_t	ReorderBits(const uint8_t input, const uint8_t pattern) {
	uint8_t output =0;
	for (int i =0; i <8; i++) {
		output = (output <<1) | ((input >>bitOrder[pattern][i]) &1);
	}
	return output;
}
uint8_t	ReorderBitsPRG(const uint8_t input) {
	return input <0x20? ReorderBits(input, 0): ReorderBits(input -0x20, 1);
}

void	Sync (void) {
	if (AlternateMapping) {
		for (int bank =0; bank <4; bank++) EMU->SetPRG_ROM8(0x8 +bank*2, ReorderBitsPRG(MMC3::getPRGBank(bank)   ));
		for (int bank =0; bank <8; bank++) EMU->SetCHR_ROM1(       bank, ReorderBits   (MMC3::getCHRBank(bank), 1));
	} else {
		MMC3::syncPRG(0x3F, 0x00);
		MMC3::syncCHR_ROM(0xFF, 0x00);
	}
	MMC3::syncWRAM();
	MMC3::syncMirror();
}

void	MAPINT	Write5 (int Bank, int Addr, int Val) {
	AlternateMapping =!!(Val &2);
}

BOOL	MAPINT	Load (void) {
	MMC3::load(Sync);
	iNES_SetSRAM();
	return TRUE;
}

void	MAPINT	Reset (RESET_TYPE ResetType) {
	if (ResetType ==RESET_HARD) AlternateMapping =0;
	MMC3::reset(ResetType);
	EMU->SetCPUWriteHandler(0x5, Write5);
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data) {
	offset = MMC3::saveLoad(mode, offset, data);
	SAVELOAD_BYTE(mode, offset, data, AlternateMapping);
	if (mode == STATE_LOAD) Sync();
	return offset;
}

uint16_t MapperNum =249;
} // namespace

MapperInfo MapperInfo_249 ={
	&MapperNum,
	_T("Waixing MMC3"),
	COMPAT_FULL,
	Load,
	Reset,
	NULL,
	MMC3::cpuCycle,
	MMC3::ppuCycle,
	SaveLoad,
	NULL,
	NULL,
};