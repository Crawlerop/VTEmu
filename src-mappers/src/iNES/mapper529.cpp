#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC4.h"
#include	"..\Hardware\h_EEPROM.h"

namespace {
EEPROM_I2C	*eeprom =NULL;

void	sync (void) {
	EMU->SetPRG_ROM16(0x8, VRC4::prg[1]);
	EMU->SetPRG_ROM16(0xC, 0xFF);
	VRC4::syncCHR(0x1FF, 0x00);
	VRC4::syncMirror();
}

int	MAPINT	readEEPROM (int bank, int addr) {
	return 0x01;
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	if (addr &0x800) {
		
	} else switch(bank) {
		case 0x8: case 0xA:
			VRC4::writePRG(bank, addr, val);
			break;
		case 0x9:
			VRC4::writeMisc(bank, addr, val);
			break;
		case 0xB: case 0xC: case 0xD: case 0xE:
			VRC4::writeCHR(bank, addr, val);
			break;
		case 0xF:
			VRC4::writeIRQ(bank, addr, val);
			break;
	}
}

BOOL	MAPINT	load (void) {
	VRC4::load(sync, 0x04, 0x08, NULL, true, 0);
	size_t sizeSave =(ROM->INES2_PRGRAM &0xF0)? (64 << (ROM->INES2_PRGRAM >> 4)): 0;
	
	if (sizeSave ==256) {
		iNES_SetSRAM();
		eeprom =new EEPROM_24C02(0, ROM->PRGRAMData);
		MapperInfo_529.Description =ROM->CHRROMSize? _T("YY0807"): _T("J-2148");
	} else
		MapperInfo_529.Description =_T("T-230");
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	VRC4::reset(resetType);
	if (eeprom) {
		EMU->SetCPUReadHandler(0x5, readEEPROM);
		for (int bank =0x8; bank<=0xF; bank++) EMU->SetCPUWriteHandler(bank, writeReg);
	}
}

void	MAPINT	unload (void) {
	if (eeprom) {
		delete eeprom;
		eeprom =NULL;
	}
}

uint16_t mapperNum =529;
} // namespace

MapperInfo MapperInfo_529 = {
	&mapperNum,
	_T("YY0807/J-2148/T-230"),
	COMPAT_FULL,
	load,
	reset,
	unload,
	VRC4::cpuCycle,
	NULL,
	VRC4::saveLoad,
	NULL,
	NULL
};