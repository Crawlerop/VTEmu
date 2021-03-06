/* Nintendulator Mapper DLLs
 * Copyright (C) 2002-2011 QMT Productions
 *
 * $URL: https://nintendulator.svn.sourceforge.net/svnroot/nintendulator/mappers/trunk/src/Hardware/Sound/s_SUN5.cpp $
 * $Id: s_SUN5.cpp 1102 2011-01-03 20:44:43Z quietust $
 */

#include	"..\..\interface.h"
#include	"s_SUN5.h"

// Sunsoft 5, based on the AY-8910
namespace SUN5sound
{
struct	SUN5sqr
{
	union
	{
		struct
		{
			unsigned freq    :12;
			unsigned         : 4;
			unsigned volume  : 4;
			unsigned envmode : 1;
			unsigned         : 3;
		};
		struct
		{
			unsigned byte0 : 8;
			unsigned byte1 : 8;
			unsigned byte2 : 8;
		};
	};
	uint8_t CurP;
	int32 LCtr;

	int	Generate (int Cycles)
	{
		LCtr -= Cycles;
		while (LCtr <= 0)
		{
			CurP++;
			CurP &= 0x1F;
			LCtr += freq + 1;
		}
		return volume * ((CurP & 0x10) ? 3 : -3);
	}
} Sqr[3];

static union
{
	struct
	{
		unsigned tone      : 3;
		unsigned           : 3;
		unsigned           : 2;
		unsigned envelope  :16;
		unsigned envhold   : 1;
		unsigned envaltr   : 1;
		unsigned envattk   : 1;
		unsigned envcont   : 1;
		unsigned           : 4;
	};
	struct
	{
		unsigned byte7 : 8;
		unsigned byteB : 8;
		unsigned byteC : 8;
		unsigned byteD : 8;
	};
};
uint8_t select;

void	Load (void)
{
	ZeroMemory(Sqr, sizeof(Sqr));
	byte7 = byteB = byteC = byteD = 0;
	select = 0;
}

void	Reset (RESET_TYPE ResetType)
{
	Sqr[0].LCtr = 1;
	Sqr[1].LCtr = 1;
	Sqr[2].LCtr = 1;
}

void	Unload (void)
{
}

void	Write (int Addr, int Val)
{
	switch (Addr & 0xE000)
	{
	case 0xC000:	select = Val & 0xF;	break;	
	case 0xE000:	switch (select)
			{
			case 0x0:	Sqr[0].byte0 = Val;	break;
			case 0x1:	Sqr[0].byte1 = Val;	break;
			case 0x2:	Sqr[1].byte0 = Val;	break;
			case 0x3:	Sqr[1].byte1 = Val;	break;
			case 0x4:	Sqr[2].byte0 = Val;	break;
			case 0x5:	Sqr[2].byte1 = Val;	break;
			case 0x7:	byte7 = Val;	break;
			case 0x8:	Sqr[0].byte2 = Val;	break;
			case 0x9:	Sqr[1].byte2 = Val;	break;
			case 0xA:	Sqr[2].byte2 = Val;	break;
			case 0xB:	byteB = Val;	break;
			case 0xC:	byteC = Val;	break;
			case 0xD:	byteD = Val;	break;
			}				break;
	}
}

int	MAPINT	Get (int Cycles)
{
	int z = 0;
	if (!(tone & 1))	z += Sqr[0].Generate(Cycles);
	if (!(tone & 2))	z += Sqr[1].Generate(Cycles);
	if (!(tone & 4))	z += Sqr[2].Generate(Cycles);
	return z *40;
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data)
{
	SAVELOAD_BYTE(mode, offset, data, select);
	SAVELOAD_BYTE(mode, offset, data, Sqr[0].byte0);
	SAVELOAD_BYTE(mode, offset, data, Sqr[0].byte1);
	SAVELOAD_BYTE(mode, offset, data, Sqr[0].byte2);
	SAVELOAD_BYTE(mode, offset, data, Sqr[0].CurP);
	SAVELOAD_LONG(mode, offset, data, Sqr[0].LCtr);
	SAVELOAD_BYTE(mode, offset, data, Sqr[1].byte0);
	SAVELOAD_BYTE(mode, offset, data, Sqr[1].byte1);
	SAVELOAD_BYTE(mode, offset, data, Sqr[1].byte2);
	SAVELOAD_BYTE(mode, offset, data, Sqr[1].CurP);
	SAVELOAD_LONG(mode, offset, data, Sqr[1].LCtr);
	SAVELOAD_BYTE(mode, offset, data, Sqr[2].byte0);
	SAVELOAD_BYTE(mode, offset, data, Sqr[2].byte1);
	SAVELOAD_BYTE(mode, offset, data, Sqr[2].byte2);
	SAVELOAD_BYTE(mode, offset, data, Sqr[2].CurP);
	SAVELOAD_LONG(mode, offset, data, Sqr[2].LCtr);
	SAVELOAD_BYTE(mode, offset, data, byte7);
	SAVELOAD_BYTE(mode, offset, data, byteB);
	SAVELOAD_BYTE(mode, offset, data, byteC);
	SAVELOAD_BYTE(mode, offset, data, byteD);
	return offset;
}
} // namespace SUN5sound