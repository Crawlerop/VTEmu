/* Nintendulator - Win32 NES emulator written in C++
 * Copyright (C) 2002-2011 QMT Productions
 *
 * $URL: svn+ssh://quietust@svn.code.sf.net/p/nintendulator/code/nintendulator/trunk/src/APU.h $
 * $Id: APU.h 1322 2016-05-31 14:22:53Z quietust $
 */

#pragma once

#include <mmsystem.h>
#define DIRECTSOUND_VERSION 0x0800
#include <dsound.h>

namespace Sound {
extern short	*buffer;
extern unsigned long	LockSize;
extern unsigned long	MHz;
extern int	buflen;
extern int	Cycles;
extern BOOL	isEnabled;
extern BOOL	VTxx_Secondary_APU;
extern BOOL	VTxx_Primary_APU;
extern BOOL			APU1_Channel1;
extern BOOL			APU1_Channel2;
extern BOOL			APU1_Channel3;
extern BOOL			APU1_Channel4;
extern BOOL			APU1_Channel5;
extern BOOL			APU2_Channel1;
extern BOOL			APU2_Channel2;
extern BOOL			APU2_Channel3;
extern BOOL			APU2_Channel4;
extern BOOL			VT32_Channel1;
extern BOOL			VT32_Channel2;
extern BOOL			VT369_Channel1;
extern BOOL			VT369_Channel2;
extern BOOL			VT369_Channel3;
extern BOOL			VT369_Channel4;

void	Init		(void);
void	Destroy		(void);
void	Start		(void);
void	Stop		(void);
void	SoundOFF	(void);
void	SoundON		(void);
void	Config		(HWND);
void	Run		(void);
void	SetRegion	(void);
} // namespace Sound
