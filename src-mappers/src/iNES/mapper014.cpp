#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"
#include	"..\Hardware\h_VRC2.h"

#define	modeMMC3 mode &2
namespace {
uint8_t		mode;
FCPUWrite	writeNothing;

void	sync (void) {
	if (modeMMC3) {
		MMC3::syncPRG(0x3F, 0);
		MMC3::syncCHR_ROM(0xFF, mode <<5 &0x100, mode <<5 &0x100, mode <<3 &0x100, mode <<1 &0x100);
		MMC3::syncMirror();
	} else {
		VRC2::syncPRG(0x1F, 0x00);
		VRC2::syncCHR_ROM(0xFF, mode <<5 &0x100, mode <<5 &0x100, mode <<3 &0x100, mode <<1 &0x100);
		VRC2::syncMirror();
	}
}

void	applyMode (void) {
	if (modeMMC3) {
		EMU->SetCPUWriteHandler(0x8, MMC3::writeReg);
		EMU->SetCPUWriteHandler(0x9, MMC3::writeReg);
		EMU->SetCPUWriteHandler(0xB, MMC3::writeMirroringWRAM);
		EMU->SetCPUWriteHandler(0xC, MMC3::writeIRQConfig);
		EMU->SetCPUWriteHandler(0xD, MMC3::writeIRQConfig);
		EMU->SetCPUWriteHandler(0xE, MMC3::writeIRQEnable);
		EMU->SetCPUWriteHandler(0xF, MMC3::writeIRQEnable);
	} else	{
		EMU->SetCPUWriteHandler(0x8, VRC2::writePRG);
		EMU->SetCPUWriteHandler(0x9, VRC2::writeMirroring);
		EMU->SetCPUWriteHandler(0xB, VRC2::writeCHR);
		EMU->SetCPUWriteHandler(0xC, VRC2::writeCHR);
		EMU->SetCPUWriteHandler(0xD, VRC2::writeCHR);
		EMU->SetCPUWriteHandler(0xE, VRC2::writeCHR);
		EMU->SetCPUWriteHandler(0xF, writeNothing);
		EMU->SetIRQ(1);
	}
}

void	MAPINT	writeMode (int bank, int addr, int val) {
	if (addr ==0x131) {
		mode =val;
		applyMode();
		sync();
	} else
	if (modeMMC3)
		MMC3::writeMirroringWRAM(bank, addr, val);
	else
		VRC2::writePRG(bank, addr, val);
}

BOOL	MAPINT	load (void) {
	iNES_SetSRAM();
	MMC3::load(sync);
	VRC2::load(sync, 0x01, 0x02);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType){
	if (resetType ==RESET_HARD) {
		mode =0;
		applyMode();
	}
	sync();

	writeNothing =EMU->GetCPUWriteHandler(0xF);
	MMC3::reset(resetType);
	VRC2::reset(resetType);
	EMU->SetCPUWriteHandler(0xA, writeMode);
}

void	MAPINT	cpuCycle (void) {
	if (modeMMC3) MMC3::cpuCycle();
}

void	MAPINT	ppuCycle (int addr, int scanline, int cycle, int isRendering) {
	if (modeMMC3) MMC3::ppuCycle(addr, scanline, cycle, isRendering);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =VRC2::saveLoad(stateMode, offset, data);
	offset =MMC3::saveLoad(stateMode, offset, data);
	SAVELOAD_BYTE(stateMode, offset, data, mode);
	if (stateMode ==STATE_LOAD) {
		applyMode();
		sync();
	}
	return offset;
}

uint16_t mapperNum =14;
} // namespace

MapperInfo MapperInfo_014 ={
	&mapperNum,
	_T("哥德 SL-1632"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	cpuCycle,
	ppuCycle,
	saveLoad,
	NULL,
	NULL
};