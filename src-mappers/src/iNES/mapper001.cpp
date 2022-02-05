#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC1.h"

#define isMMC1A !!(ROM->INES_MapperNum ==155 || ROM->INES2_SubMapper ==3)
#define is32K   !!(ROM->INES2_SubMapper ==5)

namespace {
void	sync (void) {	
	switch (ROM->INES2_PRGRAM) {
		case 0x77: // SOROM (CHR-RAM)/SZROM (CHR-ROM)
			MMC1::syncWRAM( MMC1::getCHRBank(0) &(ROM->CHRROMSize? 0x10: 0x08)? 0: 1);
			break;
		case 0x09:
		case 0x90:
			MMC1::syncWRAM((MMC1::getCHRBank(0) &0x0C) >>2);
			break;
		default:
			MMC1::syncWRAM(isMMC1A? MMC1::getPRGBank(0) >>3 &1: 0);
	}
	
	if (is32K) // SEROM/SHROM/SH1ROM
		EMU->SetPRG_ROM32(0x8, 0);
	else
		MMC1::syncPRG(0x0F, MMC1::getCHRBank(0) &0x10);
	
	MMC1::syncCHR(0x1F, 0x00);
	
	if (CART_VRAM) // For Vs. Hogan's Alley conversion
		EMU->Mirror_4();
	else
		MMC1::syncMirror();
}

BOOL	MAPINT	load (void) {
	iNES_SetSRAM();
	TCHAR** Description =(ROM->INES_MapperNum ==155)? &MapperInfo_155.Description: &MapperInfo_001.Description;
	if (ROM->INES_CHRSize ==0) {
		if (ROM->INES_Version <2) {
			if (ROM->INES_PRGSize ==512/16)
				*Description = _T("Nintendo SUROM/SXROM");
			else
			if (ROM->INES_PRGSize ==256/16)
				*Description = _T("Nintendo SGROM/SMROM/SNROM/SOROM/SXROM");
			else
				*Description = _T("Nintendo SGROM/SNROM/SOROM/SXROM");
		} else {
			if (ROM->INES2_PRGRAM ==0x00)
				*Description = _T("Nintendo SGROM/SMROM");
			else
			if (ROM->INES2_PRGRAM ==0x07 || ROM->INES2_PRGRAM ==0x70)
				*Description = (ROM->INES_PRGSize ==512/16)? _T("Nintendo SUROM"): _T("Nintendo SNROM");
			else
			if (ROM->INES2_PRGRAM ==0x77 || ROM->INES2_PRGRAM ==0x08)
				*Description = _T("Nintendo SOROM");
			else
			if (ROM->INES2_PRGRAM ==0x09 || ROM->INES2_PRGRAM ==0x90)
				*Description = _T("Nintendo SXROM");
		}
	} else {
		if (ROM->INES_Version <2) {
			if (ROM->INES_PRGSize ==64/16 && ROM->INES_CHRSize <128/8)
				*Description = _T("Nintendo SAROM/SBROM");
			else
			if (ROM->INES_PRGSize ==64/16 && ROM->INES_CHRSize>=128/8)
				*Description = _T("Nintendo SCROM");
			else
			if (ROM->INES_PRGSize ==32/16 && ROM->INES_CHRSize <128/8)
				*Description = _T("Nintendo SEROM/SIROM");
			else
			if (ROM->INES_PRGSize ==32/16 && ROM->INES_CHRSize>=128/8)
				*Description = _T("Nintendo SHROM");
			else
			if                              (ROM->INES_CHRSize <128/8)
				*Description = _T("Nintendo SFROM/SJROM");
			else
			if (CART_BATTERY)
				*Description = _T("Nintendo SKROM");
			else
				*Description = _T("Nintendo SKROM/SLROM");
		} else {
			if (ROM->INES2_PRGRAM) {
				if (ROM->INES_PRGSize ==64/16)
					*Description = _T("Nintendo SAROM");
				else
				if (ROM->INES_PRGSize ==32/16)
					*Description = _T("Nintendo SIROM");
				else
				if                              (ROM->INES_CHRSize <128/8)
					*Description = (ROM->INES2_PRGRAM ==0x77)? _T("Nintendo SZROM"): _T("Nintendo SJROM");
				else
					*Description = _T("Nintendo SKROM");
			} else {
				if (ROM->INES_PRGSize ==64/16 && ROM->INES_CHRSize <128/8)
					*Description = _T("Nintendo SBROM");
				else
				if (ROM->INES_PRGSize ==64/16 && ROM->INES_CHRSize>=128/8)
					*Description = _T("Nintendo SCROM");
				else
				if (ROM->INES_PRGSize ==32/16 && ROM->INES_CHRSize <128/8)
					*Description = _T("Nintendo SEROM");
				else
				if (ROM->INES_PRGSize ==32/16 && ROM->INES_CHRSize>=128/8)
					*Description = _T("Nintendo SHROM");
				else
				if                              (ROM->INES_CHRSize <128/8)
					*Description = _T("Nintendo SFROM");
				else
					*Description = _T("Nintendo SLROM");
			}
		}
	}
	MMC1::load(sync, isMMC1A? MMC1A: MMC1B);
	return TRUE;
}

int	MAPINT	readSwitch (int bank, int addr) {
	return ROM->dipValue;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	MMC1::reset(resetType);
	if (ROM->dipValueSet) EMU->SetCPUReadHandler(0x1, readSwitch); // For NES Test Station
}

uint16_t mapperNum001 =1;
uint16_t mapperNum155 =155;
} // namespace

MapperInfo MapperInfo_001 ={
	&mapperNum001,
	_T("Nintendo SxROM (MMC1B+)"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	MMC1::cpuCycle,
	NULL,
	MMC1::saveLoad,
	NULL,
	NULL
};
MapperInfo MapperInfo_155 ={
	&mapperNum155,
	_T("Nintendo SxROM (MMC1A)"),
	COMPAT_FULL,
	load,
	MMC1::reset,
	NULL,
	MMC1::cpuCycle,
	NULL,
	MMC1::saveLoad,
	NULL,
	NULL
};
