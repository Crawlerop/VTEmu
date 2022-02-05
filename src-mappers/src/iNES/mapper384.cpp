#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC4.h"

namespace {
uint8_t		outerBank;

void	sync (void) {
	VRC4::syncPRG(0x0F, outerBank <<4);
	VRC4::syncCHR(0x7F, outerBank <<7);
	VRC4::syncMirror();
}

void	MAPINT	writeOuterBank (int bank, int addr, int val) {
	VRC4::writeWRAM(bank, addr, val);
	if (addr &0x800 && ~outerBank &0x08) {
		outerBank =val;
		sync();
	}
}

BOOL	MAPINT	load (void) {
	VRC4::load(sync, 0x04, 0x08, NULL, false, 0);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE ResetType) {
	outerBank =0;
	VRC4::reset(ResetType);
	EMU->SetCPUWriteHandler(0x6, writeOuterBank);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =VRC4::saveLoad(stateMode, offset, data);
	SAVELOAD_BYTE(stateMode, offset, data, outerBank);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t MapperNum =384;
} // namespace

MapperInfo MapperInfo_384 = {
	&MapperNum,
	_T("L1A16"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	VRC4::cpuCycle,
	NULL,
	VRC4::saveLoad,
	NULL,
	NULL
};