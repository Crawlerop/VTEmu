#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_VRC4.h"
#include	"..\Hardware\h_Latch.h"

/*
Mermaid		6000	0000
DuckTales	6001	0001
Prince		6002	0010
Top Gun		6003	0011
Yuuyuu		6005	0101
Battletoads	600F	1111
*/

#define	outer   (reg &7)
#define uorom !!(reg &4)
#define bnrom !!(reg &8)
namespace {
uint8_t		reg;
FCPUWrite	writeWRAM;

void	sync (void) {
	if (bnrom) {
		EMU->SetPRG_ROM32(0x8, Latch::data &0x07 | outer <<2 &~4);
		if (Latch::data &0x10)
			EMU->Mirror_S1();
		else	
			EMU->Mirror_S0();
		for (int bank =0x8; bank <=0xF; bank++) EMU->SetCPUWriteHandler(bank, Latch::write);
	} else {
		if (uorom) {
			EMU->SetPRG_ROM16(0x8, VRC4::prg[0] &0x0F | outer <<3 &~8);
			EMU->SetPRG_ROM16(0xC,               0x0F | outer <<3 &~8);
		} else {
			EMU->SetPRG_ROM16(0x8, VRC4::prg[0] &0x07 | outer <<3);
			EMU->SetPRG_ROM16(0xC,               0x07 | outer <<3);
		}
		VRC4::syncMirror();
		for (int bank =0x8; bank <=0xF; bank++) EMU->SetCPUWriteHandler(bank, VRC4::write);
	}
	EMU->SetCHR_RAM8(0x0, 0);
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	if (VRC4::wramEnable) reg =addr &0xFF;
	writeWRAM(bank, addr, val);
	sync();
}

BOOL	MAPINT	load (void) {
	iNES_SetSRAM();
	Latch::load(sync, false);
	VRC4::load(sync, 0x04, 0x08, NULL, true, 0);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {

	reg =0;
	Latch::reset(RESET_HARD);
	VRC4::reset(resetType);
	writeWRAM =EMU->GetCPUWriteHandler(0x6);
	sync();
	
	for (int bank =0x6; bank <=0x7; bank++) EMU->SetCPUWriteHandler(bank, writeReg);
}

uint16_t MapperNum =448;
} // namespace

MapperInfo MapperInfo_448 = {
	&MapperNum,
	_T("830768C"),
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