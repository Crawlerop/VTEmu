#include	"..\DLL\d_iNES.h"

namespace {
void	MAPINT	unload (void);
}

#include	"mapper004-TxROM.h"
#include	"mapper004-HKROM.h"

namespace {
BOOL	MAPINT	load (void) {
	if (ROM->INES2_SubMapper ==1)
		memcpy(&MapperInfo_004, &HKROM::MapperInfo_HKROM, sizeof(MapperInfo));
	else
		memcpy(&MapperInfo_004, &TxROM::MapperInfo_TxROM, sizeof(MapperInfo));
	return MapperInfo_004.Load();
}

void	MAPINT	unload (void) {
	MapperInfo_004.Load =load;
}

uint16_t mapperNum =4;
} // namespace

MapperInfo MapperInfo_004 ={
	&mapperNum,
	_T("Nintendo TxROM/HKROM"),
	COMPAT_FULL,
	load,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};