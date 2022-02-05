#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC2.h"
#include	"..\Hardware\h_VRC4.h"

namespace {
void	syncVRC2 (void) {
	VRC2::syncPRG(0x1F, 0x00);
	VRC2::syncCHR_ROM(0xFFF, 0x000);
	VRC2::syncMirror();
}

void	syncVRC4 (void) {
	VRC4::syncPRG(0x1F, 0x00);
	VRC4::syncCHR(0xFFF, 0x000);
	VRC4::syncMirror();
}

BOOL	MAPINT	load (void) {
	iNES_SetSRAM();
	MapperInfo_025.Reset =VRC4::reset;
	MapperInfo_025.CPUCycle =VRC4::cpuCycle;
	MapperInfo_025.SaveLoad =VRC4::saveLoad;
	switch(ROM->INES2_SubMapper) {
		case 1:  VRC4::load(syncVRC4, 0x02, 0x01, NULL, true, 0);
			 MapperInfo_025.Description = _T("Konami 351406");
			 break;
		case 2:  VRC4::load(syncVRC4, 0x08, 0x04, NULL, true, 0);
			 MapperInfo_025.Description = _T("Konami 352400");
			 break;
		case 3:  VRC2::load(syncVRC2, 0x02, 0x01);
			 MapperInfo_025.Description = _T("Konami 351948");
			 MapperInfo_025.Reset =VRC2::reset;
			 MapperInfo_025.CPUCycle =NULL;
			 MapperInfo_025.SaveLoad =VRC2::saveLoad;
			 break;
		default: VRC4::load(syncVRC4, 0x0A, 0x05, NULL, true, 0);
			 MapperInfo_025.Description = _T("Konami VRC2c/VRC4b/VRC4d");
			 break;
	}
	return TRUE;
}

uint16_t mapperNum =25;
} // namespace

MapperInfo MapperInfo_025 = {
	&mapperNum,
	_T("Konami VRC2c/VRC4b/VRC4d"),
	COMPAT_FULL,
	load,
	VRC4::reset,
	NULL,
	VRC4::cpuCycle,
	NULL,
	VRC4::saveLoad,
	NULL,
	NULL
};