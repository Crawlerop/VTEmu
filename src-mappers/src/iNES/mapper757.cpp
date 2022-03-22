#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

namespace {
uint8_t		reg;

void	sync (void) {
	if (reg &0x20) {
		EMU->SetPRG_ROM32(0x8, reg &0x1F);
		if (reg &0x80)
			EMU->Mirror_H();
		else
			EMU->Mirror_V();
	} else
		MMC3::syncPRG(0x0F, reg <<2 &~0x0F);
		
	if (reg &0x80 && ROM->dipValue &1)
		for (int bank =0x8; bank <=0xF; bank++) EMU->SetPRG_OB4(bank);
	else
	if (reg &0x20)
		MMC3::syncPRG_GNROM_67(reg &0x10? 2: 0, 0x0F, reg <<4);
	else
		MMC3::syncPRG(0x0F, reg <<4);
	
	if (reg &0x04) {
		EMU->SetCHR_ROM2(0x0, MMC3::getCHRBank(0));
		EMU->SetCHR_ROM2(0x2, MMC3::getCHRBank(1));
		EMU->SetCHR_ROM2(0x4, MMC3::getCHRBank(4));
		EMU->SetCHR_ROM2(0x6, MMC3::getCHRBank(7));
	} else
		EMU->SetCHR_RAM8(0x0, 0);
	MMC3::syncMirror();
}

BOOL	MAPINT	load (void) {
	MMC3::load(sync);
	return TRUE;
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	reg =val;		
	sync();
}

void	MAPINT	reset (RESET_TYPE resetType) {
	reg =0;
	MMC3::reset(resetType);	
	for (int bank =0x9; bank <=0xF; bank+=2) EMU->SetCPUWriteHandler(bank, writeReg);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =MMC3::saveLoad(stateMode, offset, data);
	SAVELOAD_BYTE(stateMode, offset, data, reg);
	if (stateMode ==STATE_LOAD) MMC3::sync();
	return offset;
}

uint16_t mapperNum =757;
} // namespace

MapperInfo MapperInfo_757 ={
	&mapperNum,
	_T("FC-29-40/K-3101"),
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