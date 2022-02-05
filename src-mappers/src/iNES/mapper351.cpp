#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"
#include	"..\Hardware\h_MMC1.h"
#include	"..\Hardware\h_VRC4.h"

#define mapper   (reg[0] &0x03)
#define M_MMC3   0x00
#define M_MMC1   0x02
#define M_VRC4   0x03
#define nrom   !!(reg[2] &0x80)
#define prg128 !!(reg[2] &0x04)
#define chr8   !!(reg[2] &0x40)
#define chr128 !!(reg[2] &0x20)
#define chr32  !!(reg[2] &0x10)

#define prgAND (prg128? 0x0F: 0x1F)
#define chrAND (chr32? 0x1F: chr128? 0x7F: 0xFF)

namespace {
uint8_t		reg[4];

void	sync (void) {
	if (nrom) {
		EMU->SetPRG_ROM16(0x8, reg[1] >>2 &~!prg128);
		EMU->SetPRG_ROM16(0xC, reg[1] >>2 | !prg128);
	} else
	switch(mapper) {
		case M_MMC1: MMC1::syncPRG(prgAND >>1, (reg[1] >>1 &~prgAND) >>1); break;
		default:
		case M_MMC3: MMC3::syncPRG(prgAND, reg[1] >>1 &~prgAND); break;
		case M_VRC4: VRC4::syncPRG(prgAND, reg[1] >>1 &~prgAND); break;
	}
	
	if (chr8)
		EMU->SetCHR_ROM8(0x0, reg[0] >>2);
	else
	switch(mapper) {		
		case M_MMC1: MMC1::syncCHR_ROM(chrAND >>2, (reg[0] <<1 &~chrAND) >>2); break;
		default:
		case M_MMC3: MMC3::syncCHR_ROM(chrAND, reg[0] <<1 &~chrAND); break;
		case M_VRC4: VRC4::syncCHR_ROM(chrAND, reg[0] <<1 &~chrAND); break;
	}
	
	switch(mapper) {
		case M_MMC1: MMC1::syncMirror(); break;
		default:
		case M_MMC3: MMC3::syncMirror(); break;
		case M_VRC4: VRC4::syncMirror(); break;
	}
}

void	applyMode (void) {
	switch(mapper) {
		case M_MMC1:
			EMU->SetIRQ(1);
			for (int bank =0x8; bank<=0xF; bank++) EMU->SetCPUWriteHandler(bank, MMC1::write);
			break;
		default:
		case M_MMC3:
			EMU->SetCPUWriteHandler(0x8, MMC3::writeReg);
			EMU->SetCPUWriteHandler(0x9, MMC3::writeReg);
			EMU->SetCPUWriteHandler(0xA, MMC3::writeMirroringWRAM);
			EMU->SetCPUWriteHandler(0xB, MMC3::writeMirroringWRAM);
			EMU->SetCPUWriteHandler(0xC, MMC3::writeIRQConfig);
			EMU->SetCPUWriteHandler(0xD, MMC3::writeIRQConfig);
			EMU->SetCPUWriteHandler(0xE, MMC3::writeIRQEnable);
			EMU->SetCPUWriteHandler(0xF, MMC3::writeIRQEnable);
			break;
		case M_VRC4:
			EMU->SetIRQ(1);
			EMU->SetCPUWriteHandler(0x8, VRC4::writePRG);
			EMU->SetCPUWriteHandler(0x9, VRC4::writeMisc);
			EMU->SetCPUWriteHandler(0xA, VRC4::writePRG);
			EMU->SetCPUWriteHandler(0xB, VRC4::writeCHR);
			EMU->SetCPUWriteHandler(0xC, VRC4::writeCHR);
			EMU->SetCPUWriteHandler(0xD, VRC4::writeCHR);
			EMU->SetCPUWriteHandler(0xE, VRC4::writeCHR);
			EMU->SetCPUWriteHandler(0xF, VRC4::writeIRQ);
			break;
	}
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	reg[addr &3] =val;	
	if ((addr &3) ==0) applyMode();
	sync();
}

BOOL	MAPINT	load (void) {
	VRC4::load(sync, 0x04, 0x08, NULL, true, 0);
	MMC1::load(sync, MMC1B);
	MMC3::load(sync);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	for (auto& c: reg) c =0;
	MMC1::reset(RESET_HARD);
	MMC3::reset(RESET_HARD);
	VRC4::reset(RESET_HARD);
	EMU->SetCPUWriteHandler(0x5, writeReg);
	applyMode();
	sync();
}

void	MAPINT	cpuCycle (void) {
	switch(mapper) {
		case M_MMC1: MMC1::cpuCycle(); break;
		default:
		case M_MMC3: MMC3::cpuCycle(); break;
		case M_VRC4: VRC4::cpuCycle(); break;
	}
}

void	MAPINT	ppuCycle (int addr, int scanline, int cycle, int isRendering) {
	if (mapper ==M_MMC3) MMC3::ppuCycle(addr, scanline, cycle, isRendering);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =MMC3::saveLoad(stateMode, offset, data);
	offset =MMC1::saveLoad(stateMode, offset, data);
	offset =VRC4::saveLoad(stateMode, offset, data);
	for (auto& c: reg) SAVELOAD_BYTE(stateMode, offset, data, c);
	if (stateMode ==STATE_LOAD) {
		applyMode();
		sync();
	}
	return offset;
}

uint16_t mapperNum =351;
} // namespace

MapperInfo MapperInfo_351 ={
	&mapperNum,
	_T("Techline XB"),
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
