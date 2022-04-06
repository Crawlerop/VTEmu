#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_SerialDevice.h"
#include	"..\Hardware\h_Latch.h"
#include	"..\Hardware\h_MMC1.h"
#include	"..\Hardware\h_MMC2.h"
#include	"..\Hardware\h_MMC3.h"
#include	"..\Hardware\h_MMC4.h"
#include	"..\Hardware\h_VRC24.h"

class SerialLatch: public SerialDevice {
	uint8_t  command;
	uint8_t* rom;
public:
	         SerialLatch(uint8_t*);
	void     setPins(bool, bool, bool);
};
SerialLatch::SerialLatch(uint8_t* _rom):
	rom(_rom) {
}
void SerialLatch::setPins(bool select, bool newClock, bool newData) {
	if (select)
		state =0;
	else
	if (!clock && newClock) {
		if (state <8) {
			command =command <<1 | newData*1;
			if (++state ==8 && (command &0xF0) !=0x50 && (command &0xF0) !=0xA0) state =0;
		} else {
			int mask =1 <<(15 -state);
			int address =command &0x0F;
			if ((command &0xF0) ==0xA0)
				rom[address] =rom[address] &~mask | newData*mask;
			else
			if ((command &0xF0) ==0x50)
				output =!!(rom[address] &mask);
			if (++state ==16) state =0;
		}
	}
	clock =newClock;
}

namespace {
uint8_t		scratchData[16];
SerialLatch	scratchROM(scratchData);
uint16_t	reg[8];
int		prgAND;
int		prgOR;
bool		pa09;
bool		pa13;

void		dummySync(void) { }
FSync		mapperSync;
void	(MAPINT	*mapperCPUCycle) (void);
void	(MAPINT	*mapperPPUCycle) (int, int, int, int);
FCPURead	cartRead;
FCPUWrite	cartWrite;
FPPURead	dummyPPU;

void	sync (void) {
	prgOR =reg[6] <<1 &0x2000 | reg[7] >>3 &0x1FE0 | reg[7] <<4 &0x0010;
	EMU->SetPRG_RAM8(0x6, 0);
	mapperSync();
}

void	syncMMC1 (void) {
	prgOR =prgOR >>1 | reg[7] &0x0006;
	MMC1::syncPRG(prgAND, prgOR &~prgAND);
	MMC1::syncCHR(0x1F, 0x00);
	MMC1::syncMirror();
}
void	syncSUROM (void) {
	prgOR >>=1;
	MMC1::syncPRG(0x0F, MMC1::getCHRBank(0) &0x10 | prgOR &~0x1F);
	MMC1::syncCHR(0x01, 0x00);
	MMC1::syncMirror();
}
void	syncMMC2 (void) {
	MMC2::syncPRG(prgAND, prgOR &~prgAND);
	MMC2::syncCHR(0x1F, 0x00);
	MMC2::syncMirror();
}
void	syncMMC3 (void) {
	MMC3::syncPRG(prgAND, prgOR &~prgAND);
	MMC3::syncCHR(reg[7] &0x10? 0xFF: 0x7F, 0x00);
	MMC3::syncMirror();
}
void	syncMMC3_OneScreenMirroring (void) {
	MMC3::syncPRG(prgAND, prgOR &~prgAND);
	MMC3::syncCHR(0x7F, 0x00);
	MMC3::syncMirrorA17();
}
void	syncMMC4 (void) {
	prgOR >>=1;
	MMC4::syncPRG(prgAND, prgOR &~prgAND);
	MMC4::syncCHR(0x1F, 0x00);
	MMC4::syncMirror();
}
void	syncVRC24 (void) {
	VRC24::syncPRG(prgAND, prgOR &~prgAND);
	VRC24::syncCHR(0xFF, 0x00);
	VRC24::syncMirror();
}
void	syncUNROM (void) {
	prgOR >>=1;
	EMU->SetPRG_ROM16(0x8, Latch::data &prgAND | prgOR &~prgAND);
	EMU->SetPRG_ROM16(0xC,              prgAND | prgOR &~prgAND);
	EMU->SetCHR_RAM8(0x0, 0);
	if (reg[7] &0x4)
		EMU->Mirror_H();
	else
		EMU->Mirror_V();
}
void	syncIF12(void) {
	prgOR >>=1;
	EMU->SetPRG_ROM16(0x8, reg[2] &prgAND | prgOR &~prgAND);
	EMU->SetPRG_ROM16(0xC,         prgAND | prgOR &~prgAND);
	EMU->SetCHR_RAM8(0x0, reg[0] >>1 &0xF);
	if (reg[0] &0x01)
		EMU->Mirror_H();
	else
		EMU->Mirror_V();
}
void	syncANROM (void) {
	prgOR >>=2;
	EMU->SetPRG_ROM32(0x8, Latch::data &prgAND | prgOR &~prgAND);
	EMU->SetCHR_RAM8(0x0, 0);
	if (Latch::data &0x10)
		EMU->Mirror_S1();
	else
		EMU->Mirror_S0();
}
void	syncBNROM (void) {
	prgOR >>=2;
	EMU->SetPRG_ROM32(0x8, Latch::data &prgAND | prgOR &~prgAND);
	EMU->SetCHR_RAM8(0x0, 0);
	if (reg[7] &0x4)
		EMU->Mirror_H();
	else
		EMU->Mirror_V();
}
void	syncCNROM (void) {
	if (reg[7] &0x2) {
		prgOR &=~0xF;
		EMU->SetPRG_ROM16(0x8, reg[2] <<1 &0xE | reg[7] &0x1 | prgOR >>1 &~0xF);
		EMU->SetPRG_ROM16(0xC, reg[2] <<1 &0xE | reg[7] &0x1 | prgOR >>1 &~0xF);
		EMU->SetCHR_RAM8(0x0, 0);
	} else {
		EMU->SetPRG_ROM32(0x8, reg[2] &0x7 | prgOR >>2);
		EMU->SetCHR_RAM8(0x0, reg[0] &15);
	}
	if (reg[7] &0x8) {
		if (reg[7] &0x4)
			EMU->Mirror_H();
		else
			EMU->Mirror_V();
	} else {
		if (reg[1] &0x10)
			EMU->Mirror_S1();
		else
			EMU->Mirror_S0();
	}
}
void	syncGNROM (void) {
	prgOR  =prgOR >>2 | (reg[7] &4? 2: 0);
	EMU->SetPRG_ROM32(0x8, Latch::data >>4 &prgAND | prgOR &~prgAND);
	EMU->SetCHR_RAM8(0x0, Latch::data &15);
	if (reg[7] &0x10)
		EMU->Mirror_H();
	else
		EMU->Mirror_V();
}
void	syncColorDreams (void) {
	prgOR  =prgOR >>2 | (reg[7] &4? 2: 0);
	EMU->SetPRG_ROM32(0x8, Latch::data &prgAND | prgOR &~prgAND);
	EMU->SetCHR_RAM8(0x0, Latch::data >>4 &15);
	if (reg[7] &0x10)
		EMU->Mirror_H();
	else
		EMU->Mirror_V();
}
void	syncNanjing (void) {
	EMU->SetPRG_ROM32(0x8, reg[2] <<4 &0x30 | reg[0] &0x0F | (reg[3] &4? 0x00: 0x03) | prgOR >>2);
	EMU->SetCHR_RAM8(0x0, 0);	
	if (reg[7] &0x4)
		EMU->Mirror_H();
	else
		EMU->Mirror_V();
}
void	syncSMB2J(void) {
	prgOR |=reg[7] &8;			
	EMU->SetPRG_ROM8(0x8, 4         | prgOR);
	EMU->SetPRG_ROM8(0xA, 5         | prgOR);
	EMU->SetPRG_ROM8(0xC, reg[2] &7 | prgOR);
	EMU->SetPRG_ROM8(0xE, 7         | prgOR);
	EMU->SetCHR_RAM8(0x0, 0);	
	if (reg[7] &0x4)
		EMU->Mirror_H();
	else
		EMU->Mirror_V();
}
void	MAPINT	writeCNROM_CHR (int bank, int addr, int val) {
	reg[0] =val;
	sync();
}
void	MAPINT	writeCNROM_Mirroring (int bank, int addr, int val) {
	reg[1] =val;
	sync();
}
void	MAPINT	writeCNROM_PRG (int bank, int addr, int val) {
	reg[2] =val;
	sync();
}
void	MAPINT	writeIF12_CHR (int bank, int addr, int val) {
	reg[0] =val;
	sync();
}
void	MAPINT	writeIF12_PRG (int bank, int addr, int val) {
	reg[2] =val;
	sync();
}
void	MAPINT	writeSMB2J_IRQ (int bank, int addr, int val) {
	reg[0] =!!(bank &2);
	sync();
}
void	MAPINT	writeSMB2J_PRG (int bank, int addr, int val) {
	reg[2] =val;
	sync();
}

void	MAPINT	cpuCycle_SMB2J (void) {
	if (reg[0]) {
		EMU->SetIRQ(++reg[1] &0x1000? 0: 1);
	} else {
		EMU->SetIRQ(1);
		reg[1] =0;
	}
}

void	checkCHRSplit (int bank, int addr) { // Nanjing
	// During rising edge of PPU A13, PPU A9 is latched.
	bool pa13new =!!(bank &8);
	if (!pa13 && pa13new) pa09 =!!(addr &0x200);
	pa13 =pa13new;
}

int	MAPINT	interceptPPURead (int bank, int addr) { // Nanjing
	checkCHRSplit(bank, addr);
	if (reg[0] &0x80 && !pa13)
		return dummyPPU(bank &3 | (pa09? 4: 0), addr);
	else
		return dummyPPU(bank, addr);
}

void	applyMapper () {
	for (int bank =0x6; bank <=0xF; bank++) EMU->SetCPUReadHandler(bank, cartRead);
	for (int bank =0x6; bank <=0xF; bank++) EMU->SetCPUWriteHandler(bank, cartWrite);
	for (int bank =0x0; bank <=0x7; bank++) EMU->SetPPUReadHandler(bank, dummyPPU);

	mapperCPUCycle =NULL;
	mapperPPUCycle =NULL;
	uint8_t fusemap =ROM->INES2_SubMapper <<4 | reg[7] >>4 &0xF;
	uint8_t flags =reg[7] &0xF;
	switch(fusemap) {
		case 0x00: case 0x01:	/* SxROM, SUROM */
			prgAND =flags &2? (flags &8? (flags &4? 0x03: 0x01): 0x07): 0x0F;
			mapperSync =fusemap &0x01? syncSUROM: syncMMC1;
			mapperCPUCycle =MMC1::cpuCycle;
			MMC1::reset(RESET_HARD);
			break;
		case 0x0A:	/* PNROM */
			prgAND =0x0F;
			mapperSync =syncMMC2;
			MMC2::reset(RESET_HARD);
			break;
		default:
			EMU->DbgOut(L"Unknown fusemap %02X", fusemap);
		case 0x10: case 0x11: case 0x12:	/* TxROM, TxLROM */
			prgAND =flags &4? (flags &2? 0x0F: 0x1F): 0x3F;
			mapperSync =fusemap ==0x12? syncMMC3_OneScreenMirroring: syncMMC3;
			mapperCPUCycle =MMC3::cpuCycle;
			mapperPPUCycle =MMC3::ppuCycle;
			MMC3::reset(RESET_HARD);
			break;
		case 0x08: /* FxROM */
			prgAND =flags &2? 0x07: 0x0F;
			mapperSync =syncMMC4;
			MMC4::reset(RESET_HARD);
			break;
		case 0x09: case 0x0B: case 0x17:  /* UxROM */
			prgAND =fusemap ==0x0B? 0x1F: reg[7] &2? 0x07: 0x0F;
			if (flags &8) {
				mapperSync =syncUNROM;
				Latch::reset(RESET_HARD);
			} else { /* Holy Diver */
				mapperSync =syncIF12;
				for (int bank =0x8; bank <=0xB; bank++) EMU->SetCPUWriteHandler(bank, writeIF12_CHR);
				for (int bank =0xC; bank <=0xF; bank++) EMU->SetCPUWriteHandler(bank, writeIF12_PRG);
			}
			break;
		case 0x04: case 0x06: case 0x14: /* AxROM, BxROM */
			prgAND =fusemap ==0x06? 0x0F: flags &2? 0x03: 0x07;
			mapperSync =flags &8? syncBNROM: syncANROM;
			Latch::reset(RESET_HARD);
			break;
		case 0x05: case 0x15: /* NROM, CNROM, BF9097 */
			for (int bank =0x8; bank <=0xD; bank++) EMU->SetCPUWriteHandler(bank, writeCNROM_CHR);
			for (int bank =0xE; bank <=0xF; bank++) EMU->SetCPUWriteHandler(bank, writeCNROM_PRG);
			mapperSync =syncCNROM;
			if (!flags) EMU->SetCPUWriteHandler(0x9, writeCNROM_Mirroring);
			reg[0] =reg[1] =reg[2] =0;
			break;
		case 0x0C: case 0x0D: case 0x1C: case 0x1D: /* GNROM/Color Dreams */
			prgAND =flags &8? 1: 3;
			mapperSync =reg[6] &0x1000 && fusemap &~0x10? syncGNROM: syncColorDreams;
			Latch::reset(RESET_HARD);
			break;
		case 0x20: case 0x21: case 0x22: case 0x23: /* Konami VRC2/4 */
			prgAND =flags &2? 0x0F: 0x1F;
			VRC24::A0 =fusemap &2? 2: 1;
			VRC24::A1 =fusemap &2? 1: 2;
			VRC24::vrc4 =!!(fusemap &1);
			mapperCPUCycle =VRC24::cpuCycle;
			mapperSync =syncVRC24;
			VRC24::reset(RESET_HARD);
			break;
		case 0x0E: /* Nanjing */
			reg[0] =reg[1] =reg[2] =reg[3] =0;
			mapperSync =syncNanjing;
			for (int bank =0; bank <12; bank++) {
				EMU->SetPPUReadHandler(bank, interceptPPURead);
				EMU->SetPPUReadHandlerDebug(bank, dummyPPU);
			}
			break;			
		case 0x07: /* SMB2J */
			for (int bank =0x8; bank <=0xB; bank++) EMU->SetCPUWriteHandler(bank, writeSMB2J_IRQ);
			for (int bank =0xE; bank <=0xF; bank++) EMU->SetCPUWriteHandler(bank, writeSMB2J_PRG);
			reg[0] =reg[1] =reg[2] =0;
			mapperCPUCycle =cpuCycle_SMB2J;
			mapperSync =syncSMB2J;
			break;
	}
}

int	MAPINT	readReg (int bank, int addr) {
	if ((addr &0x701) ==0x301)
		return scratchROM.getData()*0x80 | *EMU->OpenBus &~0x80;
	else
		return *EMU->OpenBus;
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	int index =addr >>8 &7;
	if (addr &1)
		reg[index] =reg[index] &0x00FF | val <<8;
	else
		reg[index] =reg[index] &0xFF00 | val &0xFF;
	if (index ==7 && ~addr &1) applyMapper();
	if (index ==3) scratchROM.setPins(!!(reg[3] &0x0400), !!(reg[3] &0x0200), !!(reg[3] &0x0100));	
	sync();
}

BOOL	MAPINT	load (void) {
	iNES_SetSRAM();
	MMC1::load(sync, MMC1Type::MMC1B);
	MMC2::load(sync);
	MMC3::load(sync);
	MMC4::load(sync);
	VRC24::load(sync, true, 1, 2, NULL, true, 0);
	Latch::load(sync, false);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	reg[6] =0x0000;
	reg[7] =0xFF0F;

	cartRead =EMU->GetCPUReadHandler(0x8);
	cartWrite =EMU->GetCPUWriteHandler(0x8);
	dummyPPU =EMU->GetPPUReadHandler(0x0);
	EMU->SetCPUReadHandler(0x5, readReg);
	EMU->SetCPUWriteHandler(0x5, writeReg);

	applyMapper();
	sync();
}

void	MAPINT	cpuCycle (void) {
	if (mapperCPUCycle) mapperCPUCycle();
}

void	MAPINT	ppuCycle (int addr, int scanline, int cycle, int isRendering) {
	if (mapperPPUCycle) mapperPPUCycle(addr, scanline, cycle, isRendering);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	for (auto& c: reg)         SAVELOAD_WORD(stateMode, offset, data, c);
	for (auto& c: scratchData) SAVELOAD_BYTE(stateMode, offset, data, c);
	if (stateMode ==STATE_LOAD) applyMapper();
	offset =MMC1::saveLoad(stateMode, offset, data);
	offset =MMC2::saveLoad(stateMode, offset, data);
	offset =MMC3::saveLoad(stateMode, offset, data);
	offset =MMC4::saveLoad(stateMode, offset, data);
	offset =VRC24::saveLoad(stateMode, offset, data);
	offset =Latch::saveLoad_AD(stateMode, offset, data);	
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum =468;
} // namespace

MapperInfo MapperInfo_468 ={
	&mapperNum,
	_T("BlazePro FPGA"),
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