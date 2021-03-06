/* Nintendulator Mapper DLLs
 * Copyright (C) 2002-2011 QMT Productions
 *
 * $URL: svn+ssh://quietust@svn.code.sf.net/p/nintendulator/code/mappers/trunk/src/Dll/d_NSF.cpp $
 * $Id: d_NSF.cpp 1144 2011-01-18 01:27:25Z quietust $
 */

#include	"d_NSF.h"

HWND			hWnd;
HINSTANCE		hInstance;
const EmulatorInterface	*EMU;
ROMInfo		*ROM;

namespace
{
void	MAPINT	UnloadMapper (void)
{
	ROM = NULL;
}

MapperInfo	*MAPINT	LoadMapper (ROMInfo *_ROM)
{
	ROM = _ROM;
	if (ROM->ROMType == ROM_UNDEFINED)	/* Allow enumerating mappers */
	{
		unsigned int i = (unsigned int)ROM->Filename;
		if (i >= 1)
		{
			UnloadMapper();
			return NULL;
		}
		((ROMInfo *)ROM)->ROMType = ROM_NSF;
		return &MapperInfo_NSF;
	}
	if (ROM->ROMType != ROM_NSF)
	{
		UnloadMapper();
		return NULL;
	}
	return &MapperInfo_NSF;
}

DLLInfo	DLL_Info =
{
	_T("NSF.DLL by Quietust"),
	0x20100102,
	0x00040002,
	LoadMapper,
	UnloadMapper
};
} // namespace

extern "C" __declspec(dllexport)	void	MAPINT	UnloadMapperDLL (void)
{
	EMU = NULL;
	hWnd = NULL;
}

extern "C" __declspec(dllexport)	DLLInfo	*MAPINT	LoadMapperDLL (HWND hWndEmu, const EmulatorInterface *_EMU, int VersionRequired)
{
	hWnd = hWndEmu;
	EMU = _EMU;
	if (VersionRequired != CurrentMapperInterface)
	{
		UnloadMapperDLL();
		return NULL;
	}
	return &DLL_Info;
}

BOOL	WINAPI	DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	hInstance = hinstDLL;
	return TRUE;
}