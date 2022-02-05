/* Nintendulator - Win32 NES emulator written in C++
 * Copyright (C) 2002-2011 QMT Productions
 *
 * $URL: svn+ssh://quietust@svn.code.sf.net/p/nintendulator/code/nintendulator/trunk/src/Movie.h $
 * $Id: Movie.h 1286 2013-04-06 17:20:06Z quietust $
 */

#pragma once

#define	MOV_PLAY	0x01
#define	MOV_RECORD	0x02
#define	MOV_REVIEW	0x04

namespace Movie
{
extern unsigned char	Mode;
extern unsigned char	ControllerTypes[4];

void		ShowFrame	(void);
void		Play		(void);
void		Record		(void);
void		Stop		(void);
unsigned char	LoadInput	(void);
void		SaveInput	(unsigned char);
int		Save		(FILE *);
int		Load		(FILE *, int ver);
} // namespace Movie
