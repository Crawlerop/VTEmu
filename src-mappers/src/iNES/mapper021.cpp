#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC4.h"

namespace {
void	sync (void) {
	VRC4::syncPRG(0x1F, 0x00);
	VRC4::syncCHR(0x1FF, 0x000);
	VRC4::syncMirror();
}

BOOL	MAPINT	Load (void) {
	iNES_SetSRAM();
	switch(ROM->INES2_SubMapper) {
		case 1:  VRC4::load(sync, 0x02, 0x04, NULL, true, 0);
			 MapperInfo_021.Description = _T("Konami 352398");
			 break;
		case 2:  VRC4::load(sync, 0x40, 0x80, NULL, true, 0);
			 MapperInfo_021.Description = _T("Konami 352889");
			 break;
		default: VRC4::load(sync, 0x42, 0x84, NULL, true, 0);
                         MapperInfo_021.Description = _T("Konami VRC4a/VRC4c");
			 break;
	}
	return TRUE;
}

uint16_t mapperNum =21;
} // namespace

MapperInfo MapperInfo_021 = {
	&mapperNum,
	_T("Konami VRC4a/VRC4c"),
	COMPAT_FULL,
	Load,
	VRC4::reset,
	NULL,
	VRC4::cpuCycle,
	NULL,
	VRC4::saveLoad,
	NULL,
	NULL
};