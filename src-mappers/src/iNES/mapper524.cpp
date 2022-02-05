#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC2.h"

namespace {
uint8_t	IRQEnabled;
uint16_t IRQCounter;

void	Sync (void) {
	VRC2::syncPRG(0x1F, 0x00);
	VRC2::syncCHR_ROM(0xFF, 0x00);
	VRC2::syncMirror();
}

void	MAPINT	WriteIRQ (int Bank, int Addr, int Val) {
	switch(Addr &0xC) {
		case 0x8: IRQEnabled =1; break;
		case 0xC: IRQEnabled =0; IRQCounter =0; EMU->SetIRQ(1); break;
	}
}

BOOL	MAPINT	Load (void) {
	VRC2::load(Sync, 0x01, 0x02);
	return TRUE;
}

void	MAPINT	Reset (RESET_TYPE ResetType) {
	if (ResetType ==RESET_HARD) IRQEnabled =IRQCounter =0;
	VRC2::reset(ResetType);
	EMU->SetCPUWriteHandler(0xF, WriteIRQ);
	EMU->SetIRQ(1);
}

void	MAPINT	CPUCycle (void) {
	if (IRQEnabled && ++IRQCounter &1024) EMU->SetIRQ(0);
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data) {
	offset = VRC2::saveLoad(mode, offset, data);
	SAVELOAD_BYTE(mode, offset, data, IRQEnabled);
	SAVELOAD_WORD(mode, offset, data, IRQCounter);
	if (mode == STATE_LOAD) Sync();
	return offset;
}

uint16_t MapperNum =524;
} // namespace

MapperInfo MapperInfo_524 = {
	&MapperNum,
	_T("900218"),
	COMPAT_FULL,
	Load,
	Reset,
	NULL,
	CPUCycle,
	NULL,
	VRC2::saveLoad,
	NULL,
	NULL
};