#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC2.h"
#include	"..\Hardware\h_VRC4.h"

namespace {
void	syncVRC2 (void) {
	VRC2::syncPRG(0x1F, 0x00);
	VRC2::syncCHR_ROM(0x0FF, 0x000);
	VRC2::syncMirror();
}

void	syncVRC4 (void) {
	VRC4::syncPRG(0x1F, 0x00);
	VRC4::syncCHR(0x1FF, 0x000);
	VRC4::syncMirror();
}

BOOL	MAPINT	load (void) {
	iNES_SetSRAM();
	MapperInfo_023.Reset =VRC4::reset;
	MapperInfo_023.CPUCycle =VRC4::cpuCycle;
	MapperInfo_023.SaveLoad =VRC4::saveLoad;
	switch(ROM->INES2_SubMapper) {
		case 1:  VRC4::load(syncVRC4, 0x01, 0x02, NULL, true, 0);
			 MapperInfo_023.Description = _T("Konami VRC4 (A0/A1)");
			 break;
		case 2:  VRC4::load(syncVRC4, 0x04, 0x08, NULL, true, 0);
			 MapperInfo_023.Description = _T("Konami 352396");
			 break;
		case 3:  VRC2::load(syncVRC2, 0x01, 0x02);
			 MapperInfo_023.Description = _T("Konami 350603/350636/350926/351179");
			 MapperInfo_023.Reset =VRC2::reset;
			 MapperInfo_023.CPUCycle =NULL;
			 MapperInfo_023.SaveLoad =VRC2::saveLoad;
			 break;
		default: VRC4::load(syncVRC4, 0x05, 0x0A, NULL, true, 0);
			 MapperInfo_023.Description = _T("Konami VRC2b/VRC4e/VRC4f");
			 break;
	}
	return TRUE;
}

uint16_t mapperNum =23;
} // namespace

MapperInfo MapperInfo_023 = {
	&mapperNum,
	_T("Konami VRC2b/VRC4e/VRC4f"),
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