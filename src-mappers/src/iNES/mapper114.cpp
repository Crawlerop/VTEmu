#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

#define prg     override &0x0F
#define	nrom    override &0x80
#define	nrom256 override &0x20

namespace {
uint8_t		override;
uint8_t		chr;
uint8_t		outer;

void	sync (void) {
	if (nrom) {
		uint8_t bank =(outer >>1) |prg;
		EMU->SetPRG_ROM16(0x8, nrom256? bank &~1: bank);
		EMU->SetPRG_ROM16(0xC, nrom256? bank | 1: bank);
	} else
		MMC3::syncPRG(0x1F, outer);
	MMC3::syncCHR_ROM(0xFF, chr <<8);
	MMC3::syncMirror();
}

int	MAPINT	readDIP (int bank, int addr) {
	if ((addr &3) ==2)
		return ROM->dipValue &7 | *EMU->OpenBus &~7;
	else
		return *EMU->OpenBus;
}

void	MAPINT	writeExtra (int bank, int addr, int val) {
	switch(addr &3) {
		case 0:	override =val;
			break;
		case 1:	chr =val;
			break;
		case 3:	outer =val &~0x1F;
			break;
	}
	sync();
}

void	MAPINT	writeASIC (int bank, int addr, int val) {
	static const uint16_t addressLUT[4][8] ={
		{ 0xA001, 0xA000, 0x8000, 0xC000, 0x8001, 0xC001, 0xE000, 0xE001 }, // 0 The Lion King, Aladdin
		{ 0xA001, 0x8001, 0x8000, 0xC001, 0xA000, 0xC000, 0xE000, 0xE001 }, // 1 Boogerman
		{ 0xC001, 0x8000, 0x8001, 0xA000, 0xA001, 0xE001, 0xE000, 0xC000 }, // 2 2-in-1 The Lion King/Bomber Boy
		{ 0x8000, 0x8001, 0xA000, 0xA001, 0xC000, 0xC001, 0xE000, 0xE001 }  // 3 -
	};
	static const uint8_t dataLUT[4][8] ={
		{ 0, 3, 1, 5, 6, 7, 2, 4 }, // 0 The Lion King, Aladdin
		{ 0, 2, 5, 3, 6, 1, 7, 4 }, // 1 Boogerman
		{ 0, 6, 3, 7, 5, 2, 4, 1 }, // 2 2-in-1 The Lion King/Bomber Boy
		{ 0, 1, 2, 3, 4, 5, 6, 7 }  // 3 -
	};
	if (bank ==0xE && addr ==0) override =0xA0;
	
	int lutValue =addressLUT[ROM->INES2_SubMapper &3][bank &6 | addr &1];
	if (lutValue ==0x8000) val =val &0xC0 | dataLUT[ROM->INES2_SubMapper &3][val &7];
	MMC3::write(lutValue >>12, lutValue &1, val);
}

BOOL	MAPINT	load (void) {
	MMC3::load(sync);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	if (resetType ==RESET_HARD) {
		override =0x00;
		chr =0x00;
		outer =0xE0;
	}
	MMC3::reset(resetType);
	for (int i =0x6; i<=0x7; i++) {
		EMU->SetCPUReadHandler(i, readDIP);
		EMU->SetCPUReadHandlerDebug(i, readDIP);
		EMU->SetCPUWriteHandler(i, writeExtra);
	}
	for (int i =0x8; i<=0xF; i++) EMU->SetCPUWriteHandler(i, writeASIC);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =MMC3::saveLoad(stateMode, offset, data);
	SAVELOAD_BYTE(stateMode, offset, data, override);
	SAVELOAD_BYTE(stateMode, offset, data, chr);
	SAVELOAD_BYTE(stateMode, offset, data, outer);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum114 =114;
uint16_t mapperNum182 =182;
} // namespace

MapperInfo MapperInfo_114 ={
	&mapperNum114,
	_T("6122"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	MMC3::cpuCycle,
	MMC3::ppuCycle_MMC3A,
	saveLoad,
	NULL,
	NULL
};
MapperInfo MapperInfo_182 ={
	&mapperNum182,
	_T("YH-001"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	MMC3::cpuCycle,
	MMC3::ppuCycle_MMC3A,
	saveLoad,
	NULL,
	NULL
};