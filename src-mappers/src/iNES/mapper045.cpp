#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

#define prgAND (~reg[3] &0x3F)
#define chrAND (0xFF >>(~reg[2] &0xF))
//#define prgOR  (reg[1] | reg[2] <<2 &0x300)
#define chrOR  (reg[0] | reg[2] <<4 &0xF00)
#define locked (reg[3] &0x40)

/*	Menu selection in (10MG-D) 18-in-1:
	Check which PRG lines (A19,20,21,22) are soldered together
								check	Y=0	Y=1	Y=2	Y=3	Y=4
	F8 7E 70 BF, C000=78 D8? +1: +0		xx 40 60 xx	0111	0	OB	PRG	PRG	PRG	PRG
	F8 FE 30 BF, C000=78 D8? +1: +0		xx C0 20 xx	1101	1	OB	OB	PRG	PRG	PRG
	F8 BE 70 BF, C000=78 D8? +1: +0		xx 80 60 xx	1011	2	OB	OB	OB	PRG	PRG
	F8 FE 50 BF, C000=78 D8? +1: +0		xx C0 40 xx	1110	3	OB	OB	OB	OB	PRG	
	result at 061C/0632
	if not 4  F8 3E 10 BF (0000)
	otherwise F8 FE 50 BF (1110, the last one) 
	
	Menu selection in (NC-64B) 64 in 1 (8000 in 1 on Cartridge):
	88 30 4A B0, DFE0=AA? ->1
	88 B0 0A B0, DFEO=AA? ->2
	
	PRG A19=A
	PRG A20=B
	PRG A21=C
	PRG A22=D
	
	D C B A		0
	D C B-A		1
	D C-B A		2
	D C-B-A		3
	D-C B A		4
	
	
*/
namespace {
uint8_t		index;
uint8_t		reg[4];

void	sync (void) {
	int prgOR =reg[1] | reg[2] <<2 &0x300;
	if (ROM->dipValueSet && ROM->dipValue &0x01) prgOR |=prgOR &0x0C0? 0x0C0: 0x000; // PRG A20-A19 connected
	if (ROM->dipValueSet && ROM->dipValue &0x02) prgOR |=prgOR &0x140? 0x140: 0x000; // PRG A21-A19 connected
	if (ROM->dipValueSet && ROM->dipValue &0x04) prgOR |=prgOR &0x180? 0x180: 0x000; // PRG A21-A20 connected
	if (ROM->dipValueSet && ROM->dipValue &0x08) prgOR |=prgOR &0x240? 0x240: 0x000; // PRG A22-A19 connected
	if (ROM->dipValueSet && ROM->dipValue &0x10) prgOR |=prgOR &0x280? 0x280: 0x000; // PRG A22-A20 connected
	if (ROM->dipValueSet && ROM->dipValue &0x20) prgOR |=prgOR &0x300? 0x300: 0x000; // PRG A22-A21 connected
	
	MMC3::syncWRAM();
	MMC3::syncPRG(prgAND, prgOR);

	if (ROM->CHRROMSize || ROM->CHRRAMSize >8192)
		MMC3::syncCHR(chrAND, chrOR &~chrAND);
	else
		EMU->SetCHR_RAM8(0x0, 0);
	MMC3::syncMirror();
	
/*	uint8_t highLines =reg[1] >>4 &0xC | reg[2] >>5 &0x3;
	if ((index &3) ==0 && ROM->dipValueSet && (highLines ==0x7 || highLines ==0xB || highLines ==0xD || highLines ==0xE)) { // solder pad reading mode: three of four high lines are 1
		int compareValue =highLines ==0x7? 0: highLines ==0xD? 1: highLines ==0xB? 2: highLines ==0xE? 3: 4;
		if (compareValue >=ROM->dipValue)
			for (int bank =0x8; bank<=0xF; bank++) EMU->SetPRG_OB4(bank);
		else
			MMC3::syncPRG(0x00, 0x3E);
	}*/
}

int	MAPINT	readDIP (int bank, int addr) {
	return (~ROM->dipValue &addr)? 1: 0;
}

void	MAPINT	writeReg (int bank, int addr, int val) {
	MMC3::wramWrite(bank, addr, val);
	if (!locked) {		
		reg[index++ &3] =val;
		sync();
	}
}

BOOL	MAPINT	load (void) {
	MMC3::load(sync);
	return TRUE;
}

void	MAPINT	reset (RESET_TYPE resetType) {
	index =0;
	reg[0] =0x00;
	reg[1] =0x00;
	reg[2] =0x0F;
	reg[3] =0x00;
	MMC3::reset(resetType);

	if (ROM->dipValueSet) EMU->SetCPUReadHandler(0x5, readDIP);
	for (int bank =0x6; bank<=0x7; bank++) EMU->SetCPUWriteHandler(bank, writeReg);
}

int	MAPINT	saveLoad (STATE_TYPE stateMode, int offset, unsigned char *data) {
	offset =MMC3::saveLoad(stateMode, offset, data);
	SAVELOAD_BYTE(stateMode, offset, data, index);
	for (auto& r: reg) SAVELOAD_BYTE(stateMode, offset, data, r);
	if (stateMode ==STATE_LOAD) sync();
	return offset;
}

uint16_t mapperNum045 =45;
} // namespace

MapperInfo MapperInfo_045 ={
	&mapperNum045,
	_T("GA23C/SFC-011B"),
	COMPAT_FULL,
	load,
	reset,
	NULL,
	MMC3::cpuCycle,
	MMC3::ppuCycle,
	saveLoad,
	NULL,
	NULL
};
