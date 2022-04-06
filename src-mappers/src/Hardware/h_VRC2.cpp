#include	"h_VRC2.h"

namespace VRC2 {
FSync		sync;
int		A0, A1;
uint8_t		prg[2];
uint16_t	chr[8];
uint8_t		mirroring;
uint8_t		latch;

void	MAPINT	syncPRG (int AND, int OR) {
	EMU->SetPRG_RAM8(0x6, 0);
	EMU->SetPRG_ROM8(0x8, prg[0] &AND |OR);
	EMU->SetPRG_ROM8(0xA, prg[1] &AND |OR);
	EMU->SetPRG_ROM8(0xC, 0xFE   &AND |OR);
	EMU->SetPRG_ROM8(0xE, 0xFF   &AND |OR);
}

void	MAPINT	syncCHR (int AND, int OR) {
	if (ROM->CHRROMSize)
		syncCHR_ROM(AND, OR);
	else
		syncCHR_RAM(AND, OR);
}

void	MAPINT	syncCHR_ROM (int AND, int OR) {
	for (int bank =0; bank <8; bank++) EMU->SetCHR_ROM1(bank, chr[bank] &AND |OR);
}

void	MAPINT	syncCHR_ROM (int AND, int OR0, int OR2, int OR4, int OR6) {
	EMU->SetCHR_ROM1(0x0, chr[0] &AND |OR0);
	EMU->SetCHR_ROM1(0x1, chr[1] &AND |OR0);
	EMU->SetCHR_ROM1(0x2, chr[2] &AND |OR2);
	EMU->SetCHR_ROM1(0x3, chr[3] &AND |OR2);
	EMU->SetCHR_ROM1(0x4, chr[4] &AND |OR4);
	EMU->SetCHR_ROM1(0x5, chr[5] &AND |OR4);
	EMU->SetCHR_ROM1(0x6, chr[6] &AND |OR6);
	EMU->SetCHR_ROM1(0x7, chr[7] &AND |OR6);
}

void	MAPINT	syncCHR_RAM (int AND, int OR) {
	for (int bank =0; bank <8; bank++) EMU->SetCHR_RAM1(bank, chr[bank] &AND |OR);
}

void	MAPINT	syncMirror() {
	switch (mirroring &1) {
		case 0:	EMU->Mirror_V(); break;
		case 1:	EMU->Mirror_H(); break;
	}
}

int	MAPINT	readLatch (int bank, int addr) {
	return *EMU->OpenBus &~1 | latch &1;
}

void	MAPINT	writeLatch (int bank, int addr, int val) {
	latch =val;
}

void	MAPINT	writePRG (int bank, int addr, int val) {
	prg[bank >>1 &1] =val;
	sync();
}

void	MAPINT	writeMirroring (int bank, int addr, int val) {
	mirroring =val;
	sync();
}

void	MAPINT  writeCHR (int bank, int addr, int val) {
	int reg =((bank -0xB) <<1) | (addr &A1? 1: 0);
	if (addr &A0)
		chr[reg] = chr[reg] &0x00F | val <<4;
	else
		chr[reg] = chr[reg] &0xFF0 | val &0xF;
	sync();	
}

void	MAPINT	load (FSync _sync, uint8_t _A0, uint8_t _A1) {
	sync =_sync;
	A0 =_A0;
	A1 =_A1;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	if (resetType ==RESET_HARD) {
		prg[0] =0;
		prg[1] =1;
		for (int bank =0; bank <8; bank++) chr[bank] =bank;
	}
	sync();

	if (ROM->INES_Version >=2 && ROM->INES2_PRGRAM ==0) {
		EMU->SetCPUReadHandler(0x6, readLatch);
		EMU->SetCPUReadHandlerDebug(0x6, readLatch);
		EMU->SetCPUWriteHandler(0x6, writeLatch);
	}
	for (int bank =0x8; bank<=0xA; bank +=2) EMU->SetCPUWriteHandler(bank, writePRG);
	EMU->SetCPUWriteHandler(0x9, writeMirroring);
	for (int bank =0xB; bank<=0xE; bank++) EMU->SetCPUWriteHandler(bank, writeCHR);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	SAVELOAD_BYTE(stateMode, offset, data, latch);
	SAVELOAD_BYTE(stateMode, offset, data, mirroring);
	for (auto& c: prg) SAVELOAD_BYTE(stateMode, offset, data, c);
	for (auto& c: chr) SAVELOAD_WORD(stateMode, offset, data, c);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}
} // namespace VRC2