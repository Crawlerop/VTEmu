/* Nintendulator - Win32 NES emulator written in C++
 * Copyright (C) 2002-2011 QMT Productions
 *
 * $URL: svn+ssh://quietust@svn.code.sf.net/p/nintendulator/code/nintendulator/trunk/src/States.h $
 * $Id: States.h 1298 2014-03-21 18:38:07Z quietust $
 */

#pragma once

#define	STATES_CUR_VERSION	1100	// current savestate version
#define	STATES_MIN_VERSION	950	// minimum supported savestate version

namespace States
{
extern TCHAR BaseFilename[MAX_PATH];
extern int SelSlot;

void	Init (void);
void	SetFilename (TCHAR *name);
void	SetSlot (int Slot);
int	SaveData (FILE *);
BOOL	LoadData (FILE *, int len, int ver);
void	SaveNumberedState (void);
void	LoadNumberedState (void);
void	SaveNamedState (void);
void	LoadNamedState (void);
void	SaveState (const TCHAR*, const TCHAR*);
void	LoadState (const TCHAR*, const TCHAR*);
void	SaveVersion (FILE *, int ver);
int	LoadVersion (FILE *);
} // namespace States
