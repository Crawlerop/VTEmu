/* Nintendulator - Win32 NES emulator written in C++
 * Copyright (C) 2002-2011 QMT Productions
 *
 * $URL: svn+ssh://quietust@svn.code.sf.net/p/nintendulator/code/nintendulator/trunk/src/AVI.h $
 * $Id: AVI.h 1257 2012-02-14 04:11:05Z quietust $
 */

#pragma once

DECLARE_HANDLE(HAVI);

namespace AVI
{
extern HAVI handle;

void	Init		(void);
void	Start		(void);
void	AddVideo	(void);
void	AddAudio	(void);
void	End		(void);
} // namespace AVI
