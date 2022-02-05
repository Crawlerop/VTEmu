#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

namespace {
uint8_t		reg[4];
FCPURead	readCart;

void	sync (void) {
	int prgAND = reg[0] &0x40? 0x0F: 0x1F;
	int prgOR  =(reg[0] <<4 &0x70 | reg[0] <<3 &0x180) &~prgAND;
	switch(reg[3] &3) {
		case 0: MMC3::syncPRG(prgAND, prgOR); break;
		case 1:
		case 2: EMU->SetPRG_ROM16(0x8, (MMC3::getPRGBank(0) &prgAND |prgOR) >>1);
			EMU->SetPRG_ROM16(0xC, (MMC3::getPRGBank(0) &prgAND |prgOR) >>1);
		        break;
		case 3: EMU->SetPRG_ROM32(0x8, (MMC3::getPRGBank(0) &prgAND |prgOR) >>2);
			break;
	}
	MMC3::wram =0x80; // WRAM always enabled
	MMC3::syncWRAM();

	int chrAND = reg[0] &0x80? 0x7F: 0xFF;
	int chrOR;
	if (ROM->INES_MapperNum ==126)
		chrOR =(reg[0] <<4 &0x080 | reg[0] <<3 &0x100 | reg[0] <<5 &0x200) &~chrAND;
	else
		chrOR =reg[0] <<4 &0x380 &~chrAND;
	
	if (reg[3] &0x10)
		iNES_SetCHR_Auto8(0x0, reg[2] &(chrAND >>3) | chrOR >>3);
	else
		MMC3::syncCHR(chrAND, chrOR);
	MMC3::syncMirror();
	
	*EMU->multiCanSave =TRUE;
	if (reg[3] &0x10) {
		*EMU->multiCHRStart =EMU->GetCHR_Ptr1(0x0);
		*EMU->multiCHRSize  =8192;
		*EMU->multiMirroring =MMC3::mirroring &1;
	} else {
		*EMU->multiCHRStart =(chrOR <<10 &(ROM->CHRROMSize-1)) +(ROM->CHRROMSize? ROM->CHRROMData: ROM->CHRRAMData);
		*EMU->multiCHRSize  =(chrAND +1) *1024;
		*EMU->multiMirroring =1;
	}
	if (reg[3] &0x03) {
		*EMU->multiPRGStart =EMU->GetPRG_Ptr4(0x8);
		*EMU->multiPRGSize  =reg [3] &0x02? 32768: 16384;
	} else {
		*EMU->multiPRGStart =(reg[0] &0x7)*131072 +ROM->PRGROMData;
		*EMU->multiPRGSize  = reg[0] &0x40? 131072: 262144;
	}
}

int	MAPINT	interceptCartRead (int bank, int addr) {
	if (reg[1] &0x01)
		return (ROM->dipValue &0x03) | (*EMU->OpenBus &~0x03);
	else
		return readCart(bank, addr);
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	MMC3::wramWrite(bank, addr, val);
	if (~reg[3] &0x80) {
		reg[addr &3] =val;
		sync();
	} else
	if ((addr &3) ==2) {
		int mask =reg[2] &0x10? 1: 3;
		reg[2] =reg[2] &~mask | val &mask;
		sync();
	}
}

void	MAPINT	interceptIRQWrite (int bank, int addr, int val) {
	MMC3::writeIRQConfig(bank, addr, val ^0xFF);
	sync();
}

BOOL	MAPINT	load (void) {
	MMC3::load(sync);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	for (auto& r: reg) r =0x00;
	MMC3::reset(RESET_HARD);
	readCart =EMU->GetCPUReadHandler(0x8);
	for (int bank =0x8; bank <=0xF; bank++) EMU->SetCPUReadHandler(bank, interceptCartRead);
	EMU->SetCPUWriteHandler(0x6, writeReg);
	if (ROM->INES_MapperNum ==534) {
		EMU->SetCPUWriteHandler(0xC, interceptIRQWrite);
		EMU->SetCPUWriteHandler(0xD, interceptIRQWrite);
	}
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =MMC3::saveLoad(stateMode, offset, data);
	for (auto& r: reg) SAVELOAD_BYTE(stateMode, offset, data, r);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum126 =126;
uint16_t mapperNum534 =534;
} // namespace

MapperInfo MapperInfo_126 = {
	&mapperNum126,
	_T("SuperJoy"),
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
MapperInfo MapperInfo_422 = {
	&mapperNum534,
	_T("BS-400"),
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
MapperInfo MapperInfo_534 = {
	&mapperNum534,
	_T("NC019A/南晶 NJ064"),
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