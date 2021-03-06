#include "stdafx.h"
#include "Nintendulator.h"
#include "resource.h"
#include "Settings.h"
#include "Controllers.h"
#include "MapperInterface.h"
#include "NES.h"
#include "GFX.h"
#include "PPU.h"

namespace Settings {	
// General
int	plugThruDevice			=0;
BOOL	AutoCorrect			=FALSE;
BOOL	AutoRun				=TRUE;
BOOL	dbgVisible			=FALSE;
Region	DefaultRegion			=REGION_NTSC;
int	SizeMult			=2;
BOOL	FixAspect			=TRUE;
BOOL	FastLoad			=FALSE;
int	PosX				=0;
int	PosY				=0;
CommitMode	CommitMode35		=COMMIT_APPDATA;
BOOL	HardGameSaver			=FALSE;
// CPU
int	RAMInitialization		=0x00;
// APU
BOOL	BootWithDisabledFrameIRQ	=FALSE;
int	ExpansionAudioVolume		=80;
int	LowPassFilterAPU		=0;
BOOL	LowPassFilterOneBus		=TRUE;
BOOL	NonlinearMixing			=TRUE;
BOOL	SoundEnabled			=TRUE;
BOOL	VTxx_APU1 = TRUE;
BOOL	VTxx_APU2 = TRUE;
BOOL	APU1_CH1 = TRUE;
BOOL	APU1_CH2 = TRUE;
BOOL	APU1_CH3 = TRUE;
BOOL	APU1_CH4 = TRUE;
BOOL	APU1_CH5 = TRUE;
BOOL	APU2_CH1 = TRUE;
BOOL	APU2_CH2 = TRUE;
BOOL	APU2_CH3 = TRUE;
BOOL	APU2_CH4 = TRUE;
BOOL	VT32_CH1 = TRUE;
BOOL	VT32_CH2 = TRUE;
BOOL	VT369_CH1 = TRUE;
BOOL	VT369_CH2 = TRUE;
BOOL	VT369_CH3 = TRUE;
BOOL	VT369_CH4 = TRUE;
BOOL	VT369_60hz_Sound = FALSE;
BOOL	VT369_60hz_Sound_Alt = FALSE;
BOOL	VT369_APU_Force_FullSpeed = FALSE;
int		VTxx_Rom_Type = 0;
BOOL	SwapDutyCycles			=FALSE;
BOOL	SwapAllDutyCycles = FALSE;
BOOL	BootlegExpansionAudio		=TRUE;
BOOL	CleanN163			=TRUE;
BOOL	PreventWaveformClash		=FALSE;
BOOL	RemoveDPCMBuzz			=FALSE;
BOOL	RemoveDPCMPops			=FALSE;
BOOL	ReverseDPCM			=FALSE;
BOOL	DisablePeriodicNoise		=FALSE;
BOOL	VT369SoundHLE                   =TRUE;
// PPU
BOOL	DisableEmphasis			=FALSE;
BOOL	IgnoreRaceCondition		=FALSE;
int	VSDualScreens			=2;
BOOL	VSync				=FALSE;
int	VT03Palette			=0;
BOOL    VT32RemoveBlueishCast           =TRUE;
BOOL	PPUSoftReset			=TRUE;
BOOL	PPUNeverClip			=FALSE;
BOOL	Dendy60Hz			=FALSE;
BOOL	DendyNTSCAspect			=FALSE;
BOOL	DisableOAMData			=FALSE;
BOOL	NoSpriteLimit			=FALSE;
BOOL	ScrollGlitch			=FALSE;
BOOL	upByOne				=FALSE;
// GFX
BOOL	aFSkip				=FALSE;
int	FSkip				=0;
BOOL	NTSCsRGB			=TRUE;
int	NTSCHue				=0;
int	NTSCAxis			=0;
BOOL	NTSCNormalize			=TRUE;
int	NTSCSaturation			=50;
BOOL	PALsRGB				=TRUE;
BOOL	PALNormalize			=TRUE;
int	PALSaturation			=50;
PALETTE Palette[PALREGION_MAX]		={ PALETTE_NTSC, PALETTE_NTSC, PALETTE_PAL, PALETTE_PAL, PALETTE_RGB, PALETTE_RGB };
BOOL	RGBsRGB				=TRUE;
BOOL	Scanlines			=FALSE;
int	Xstart				=0;
int	Xend				=255;
int	Ystart				=0;
int	Yend				=239;
// Paths and filenames
TCHAR	CustPalette[PALREGION_MAX][MAX_PATH];
TCHAR	Path_ROM[MAX_PATH];
TCHAR	Path_NMV[MAX_PATH];
TCHAR	Path_AVI[MAX_PATH];
TCHAR	Path_PAL[MAX_PATH];
TCHAR	Path_BMP[MAX_PATH];
TCHAR	Path_NST[MAX_PATH];
TCHAR	Path_CopyNES[MAX_PATH];

PALETTE DefaultPalette[PALREGION_MAX] ={ PALETTE_NTSC, PALETTE_NTSC, PALETTE_PAL, PALETTE_PAL, PALETTE_RGB, PALETTE_RGB };

void	SaveSettings (void) {
	HKEY SettingsBase;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Nintendulator\\"), 0, KEY_ALL_ACCESS, &SettingsBase)) RegCreateKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Nintendulator\\"), 0, _T("NintendulatorClass"), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &SettingsBase, NULL);
	
	#define SAVE_SETTING(x) RegSetValueEx(SettingsBase, _T(#x), 0, REG_DWORD, (LPBYTE) &x, sizeof(x))
	SAVE_SETTING(plugThruDevice);
//	SAVE_SETTING(AutoCorrect);
	SAVE_SETTING(AutoRun);
	SAVE_SETTING(dbgVisible);
	SAVE_SETTING(DefaultRegion);
	SAVE_SETTING(SizeMult);
	SAVE_SETTING(FixAspect);
	SAVE_SETTING(FastLoad);
	SAVE_SETTING(CommitMode35);
	SAVE_SETTING(HardGameSaver);
	SAVE_SETTING(RAMInitialization);
	SAVE_SETTING(BootWithDisabledFrameIRQ);
	SAVE_SETTING(ExpansionAudioVolume);
	SAVE_SETTING(LowPassFilterAPU);
	SAVE_SETTING(LowPassFilterOneBus);
	SAVE_SETTING(NonlinearMixing);
	SAVE_SETTING(SoundEnabled);
	SAVE_SETTING(VTxx_APU1);
	SAVE_SETTING(VTxx_APU2);
	SAVE_SETTING(APU1_CH1);
	SAVE_SETTING(APU1_CH2);
	SAVE_SETTING(APU1_CH3);
	SAVE_SETTING(APU1_CH4);
	SAVE_SETTING(APU1_CH5);
	SAVE_SETTING(APU2_CH1);
	SAVE_SETTING(APU2_CH2);
	SAVE_SETTING(APU2_CH3);
	SAVE_SETTING(APU2_CH4);
	SAVE_SETTING(VT32_CH1);
	SAVE_SETTING(VT32_CH2);
	SAVE_SETTING(VT369_CH1);
	SAVE_SETTING(VT369_CH2);
	SAVE_SETTING(VT369_CH3);
	SAVE_SETTING(VT369_CH4);
	SAVE_SETTING(VT369_60hz_Sound);
	SAVE_SETTING(VT369_60hz_Sound_Alt);
	SAVE_SETTING(VT369_APU_Force_FullSpeed);
	SAVE_SETTING(VTxx_Rom_Type);
	SAVE_SETTING(SwapDutyCycles);
	SAVE_SETTING(SwapAllDutyCycles);
	SAVE_SETTING(BootlegExpansionAudio);
	SAVE_SETTING(CleanN163);
	SAVE_SETTING(RemoveDPCMBuzz);
	SAVE_SETTING(RemoveDPCMPops);
	SAVE_SETTING(ReverseDPCM);
	SAVE_SETTING(DisablePeriodicNoise);
	SAVE_SETTING(VT369SoundHLE);
	SAVE_SETTING(DisableEmphasis);
	SAVE_SETTING(IgnoreRaceCondition);
	SAVE_SETTING(VSDualScreens);
	SAVE_SETTING(VSync);
	SAVE_SETTING(NoSpriteLimit);
	SAVE_SETTING(ScrollGlitch);
	SAVE_SETTING(upByOne);
	SAVE_SETTING(VT03Palette);
	SAVE_SETTING(VT32RemoveBlueishCast);
	SAVE_SETTING(PPUSoftReset);
	SAVE_SETTING(PPUNeverClip);
	SAVE_SETTING(Dendy60Hz);
	SAVE_SETTING(DendyNTSCAspect);
	SAVE_SETTING(DisableOAMData);
	SAVE_SETTING(aFSkip);
	SAVE_SETTING(FSkip);
	SAVE_SETTING(NTSCsRGB);
	SAVE_SETTING(NTSCHue);
	SAVE_SETTING(NTSCAxis);
	SAVE_SETTING(NTSCNormalize);
	SAVE_SETTING(NTSCSaturation);
	SAVE_SETTING(PALsRGB);
	SAVE_SETTING(PALNormalize);
	SAVE_SETTING(PALSaturation);
	SAVE_SETTING(RGBsRGB);
	SAVE_SETTING(Scanlines);
	SAVE_SETTING(Xstart);
	SAVE_SETTING(Xend);
	SAVE_SETTING(Ystart);
	SAVE_SETTING(Yend);
	#undef SAVE_SETTING
	RegSetValueEx(SettingsBase, _T("PaletteNTSC"),  0, REG_DWORD, (LPBYTE) &Palette[PALREGION_NTSC],  sizeof(int));
	RegSetValueEx(SettingsBase, _T("PalettePAL"),   0, REG_DWORD, (LPBYTE) &Palette[PALREGION_PAL],   sizeof(int));
	RegSetValueEx(SettingsBase, _T("PaletteDendy"), 0, REG_DWORD, (LPBYTE) &Palette[PALREGION_DENDY], sizeof(int));
	RegSetValueEx(SettingsBase, _T("PaletteVS"),    0, REG_DWORD, (LPBYTE) &Palette[PALREGION_VS],    sizeof(int));
	RegSetValueEx(SettingsBase, _T("PalettePC10"),  0, REG_DWORD, (LPBYTE) &Palette[PALREGION_PC10],  sizeof(int));

	GetWindowPosition();
	RegSetValueEx(SettingsBase, _T("PosX"),         0, REG_DWORD, (LPBYTE) &PosX, sizeof(int));
	RegSetValueEx(SettingsBase, _T("PosY"),         0, REG_DWORD, (LPBYTE) &PosY, sizeof(int));
	
	RegSetValueEx(SettingsBase, _T("Path_ROM"),         0, REG_SZ,    (LPBYTE)  Path_ROM,                     sizeof(TCHAR) *_tcslen(Path_ROM));
	RegSetValueEx(SettingsBase, _T("Path_NMV"),         0, REG_SZ,    (LPBYTE)  Path_NMV,                     sizeof(TCHAR) *_tcslen(Path_NMV));
	RegSetValueEx(SettingsBase, _T("Path_AVI"),         0, REG_SZ,    (LPBYTE)  Path_AVI,                     sizeof(TCHAR) *_tcslen(Path_AVI));
	RegSetValueEx(SettingsBase, _T("Path_PAL"),         0, REG_SZ,    (LPBYTE)  Path_PAL,                     sizeof(TCHAR) *_tcslen(Path_PAL));
	RegSetValueEx(SettingsBase, _T("Path_BMP"),         0, REG_SZ,    (LPBYTE)  Path_BMP,                     sizeof(TCHAR) *_tcslen(Path_BMP));
	RegSetValueEx(SettingsBase, _T("Path_NST"),         0, REG_SZ,    (LPBYTE)  Path_NST,                     sizeof(TCHAR) *_tcslen(Path_NST));
	RegSetValueEx(SettingsBase, _T("Path_CopyNES"),     0, REG_SZ,    (LPBYTE)  Path_CopyNES,                 sizeof(TCHAR) *_tcslen(Path_CopyNES));
	RegSetValueEx(SettingsBase, _T("CustPaletteNTSC"),  0, REG_SZ,    (LPBYTE)  CustPalette[PALREGION_NTSC],  sizeof(TCHAR) *_tcslen(CustPalette[PALREGION_NTSC]));
	RegSetValueEx(SettingsBase, _T("CustPalettePAL"),   0, REG_SZ,    (LPBYTE)  CustPalette[PALREGION_PAL],   sizeof(TCHAR) *_tcslen(CustPalette[PALREGION_PAL]));
	RegSetValueEx(SettingsBase, _T("CustPaletteDendy"), 0, REG_SZ,    (LPBYTE)  CustPalette[PALREGION_DENDY], sizeof(TCHAR) *_tcslen(CustPalette[PALREGION_DENDY]));
	RegSetValueEx(SettingsBase, _T("CustPaletteVS"),    0, REG_SZ,    (LPBYTE)  CustPalette[PALREGION_VS],    sizeof(TCHAR) *_tcslen(CustPalette[PALREGION_VS]));
	RegSetValueEx(SettingsBase, _T("CustPalettePC10"),  0, REG_SZ,    (LPBYTE)  CustPalette[PALREGION_PC10],  sizeof(TCHAR) *_tcslen(CustPalette[PALREGION_PC10]));

	Controllers::SaveSettings(SettingsBase);
	RegCloseKey(SettingsBase);
}

void	LoadSettings (void) {
	DWORD Size;
	HKEY SettingsBase;
	RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Nintendulator\\"), 0, KEY_ALL_ACCESS, &SettingsBase);

	#define LOAD_SETTING(x) Size =sizeof(int); RegQueryValueEx(SettingsBase, _T(#x), 0, NULL, (LPBYTE) &x, &Size)
	LOAD_SETTING(plugThruDevice);
//	LOAD_SETTING(AutoCorrect);
	LOAD_SETTING(AutoRun);
	LOAD_SETTING(dbgVisible);
	LOAD_SETTING(DefaultRegion);
	LOAD_SETTING(SizeMult);
	LOAD_SETTING(FixAspect);
	LOAD_SETTING(FastLoad);
	LOAD_SETTING(CommitMode35);
	LOAD_SETTING(HardGameSaver);
	LOAD_SETTING(RAMInitialization);
	LOAD_SETTING(BootWithDisabledFrameIRQ);
	LOAD_SETTING(ExpansionAudioVolume);
	LOAD_SETTING(LowPassFilterAPU);
	LOAD_SETTING(LowPassFilterOneBus);
	LOAD_SETTING(NonlinearMixing);
	LOAD_SETTING(SoundEnabled);
	LOAD_SETTING(VTxx_APU1);
	LOAD_SETTING(VTxx_APU2);
	LOAD_SETTING(APU1_CH1);
	LOAD_SETTING(APU1_CH2);
	LOAD_SETTING(APU1_CH3);
	LOAD_SETTING(APU1_CH4);
	LOAD_SETTING(APU1_CH5);
	LOAD_SETTING(APU2_CH1);
	LOAD_SETTING(APU2_CH2);
	LOAD_SETTING(APU2_CH3);
	LOAD_SETTING(APU2_CH4);
	LOAD_SETTING(VT32_CH1);
	LOAD_SETTING(VT32_CH2);
	LOAD_SETTING(VT369_CH1);
	LOAD_SETTING(VT369_CH2);
	LOAD_SETTING(VT369_CH3);
	LOAD_SETTING(VT369_CH4);
	LOAD_SETTING(VT369_60hz_Sound);
	LOAD_SETTING(VT369_60hz_Sound_Alt);
	LOAD_SETTING(VT369_APU_Force_FullSpeed);
	LOAD_SETTING(VTxx_Rom_Type);
	LOAD_SETTING(SwapDutyCycles);
	LOAD_SETTING(SwapAllDutyCycles);
	LOAD_SETTING(BootlegExpansionAudio);
	LOAD_SETTING(CleanN163);
	LOAD_SETTING(RemoveDPCMBuzz);
	LOAD_SETTING(RemoveDPCMPops);
	LOAD_SETTING(ReverseDPCM);
	LOAD_SETTING(DisablePeriodicNoise);
	LOAD_SETTING(VT369SoundHLE);
	LOAD_SETTING(DisableEmphasis);
	LOAD_SETTING(IgnoreRaceCondition);
	LOAD_SETTING(VSDualScreens);
	LOAD_SETTING(VSync);
	LOAD_SETTING(NoSpriteLimit);
	LOAD_SETTING(ScrollGlitch);
	LOAD_SETTING(upByOne);
	LOAD_SETTING(VT03Palette);
	LOAD_SETTING(VT32RemoveBlueishCast);
	LOAD_SETTING(PPUSoftReset);
	LOAD_SETTING(PPUNeverClip);
	LOAD_SETTING(Dendy60Hz);
	LOAD_SETTING(DendyNTSCAspect);
	LOAD_SETTING(DisableOAMData);
	LOAD_SETTING(aFSkip);
	LOAD_SETTING(FSkip);
	LOAD_SETTING(NTSCsRGB);
	LOAD_SETTING(NTSCHue);
	LOAD_SETTING(NTSCAxis);
	LOAD_SETTING(NTSCNormalize);
	LOAD_SETTING(NTSCSaturation);
	LOAD_SETTING(PALsRGB);
	LOAD_SETTING(PALNormalize);
	LOAD_SETTING(PALSaturation);
	LOAD_SETTING(RGBsRGB);
	LOAD_SETTING(Scanlines);
	LOAD_SETTING(Xstart);
	LOAD_SETTING(Xend);
	LOAD_SETTING(Ystart);
	LOAD_SETTING(Yend);
	#undef LOAD_SETTING
	Size =sizeof(int); RegQueryValueEx(SettingsBase, _T("PaletteNTSC"),  0, NULL, (LPBYTE) &Palette[PALREGION_NTSC],  &Size);
	Size =sizeof(int); RegQueryValueEx(SettingsBase, _T("PalettePAL"),   0, NULL, (LPBYTE) &Palette[PALREGION_PAL],   &Size);
	Size =sizeof(int); RegQueryValueEx(SettingsBase, _T("PaletteDendy"), 0, NULL, (LPBYTE) &Palette[PALREGION_DENDY], &Size);
	Size =sizeof(int); RegQueryValueEx(SettingsBase, _T("PaletteVS"),    0, NULL, (LPBYTE) &Palette[PALREGION_VS],    &Size);
	Size =sizeof(int); RegQueryValueEx(SettingsBase, _T("PalettePC10"),  0, NULL, (LPBYTE) &Palette[PALREGION_PC10],  &Size);
	Palette[PALREGION_VS] =PALETTE_RGB; // Vs. games may only use RGB palette

	Size =sizeof(int); RegQueryValueEx(SettingsBase, _T("PosX"), 0, NULL, (LPBYTE) &PosX, &Size);
	Size =sizeof(int); RegQueryValueEx(SettingsBase, _T("PosY"), 0, NULL, (LPBYTE) &PosY, &Size);
	SetWindowPosition();

	Path_ROM[0] =Path_NMV[0] =Path_AVI[0] =Path_PAL[0] =CustPalette[REGION_NTSC][0] =CustPalette[REGION_PAL][0] =CustPalette[REGION_DENDY][0] ='\0';
	Size =MAX_PATH *sizeof(TCHAR); RegQueryValueEx(SettingsBase, _T("Path_ROM"),         0, NULL, (LPBYTE) &Path_ROM,                     &Size);
	Size =MAX_PATH *sizeof(TCHAR); RegQueryValueEx(SettingsBase, _T("Path_NMV"),         0, NULL, (LPBYTE) &Path_NMV,                     &Size);
	Size =MAX_PATH *sizeof(TCHAR); RegQueryValueEx(SettingsBase, _T("Path_AVI"),         0, NULL, (LPBYTE) &Path_AVI,                     &Size);
	Size =MAX_PATH *sizeof(TCHAR); RegQueryValueEx(SettingsBase, _T("Path_PAL"),         0, NULL, (LPBYTE) &Path_PAL,                     &Size);
	Size =MAX_PATH *sizeof(TCHAR); RegQueryValueEx(SettingsBase, _T("Path_BMP"),         0, NULL, (LPBYTE) &Path_BMP,                     &Size);
	Size =MAX_PATH *sizeof(TCHAR); RegQueryValueEx(SettingsBase, _T("Path_NST"),         0, NULL, (LPBYTE) &Path_NST,                     &Size);
	Size =MAX_PATH *sizeof(TCHAR); RegQueryValueEx(SettingsBase, _T("Path_CopyNES"),     0, NULL, (LPBYTE) &Path_CopyNES,                 &Size);
	Size =MAX_PATH *sizeof(TCHAR); RegQueryValueEx(SettingsBase, _T("CustPaletteNTSC"),  0, NULL, (LPBYTE) &CustPalette[PALREGION_NTSC],  &Size);
	Size =MAX_PATH *sizeof(TCHAR); RegQueryValueEx(SettingsBase, _T("CustPalettePAL"),   0, NULL, (LPBYTE) &CustPalette[PALREGION_PAL],   &Size);
	Size =MAX_PATH *sizeof(TCHAR); RegQueryValueEx(SettingsBase, _T("CustPaletteDendy"), 0, NULL, (LPBYTE) &CustPalette[PALREGION_DENDY], &Size);
	Size =MAX_PATH *sizeof(TCHAR); RegQueryValueEx(SettingsBase, _T("CustPaletteVS"),    0, NULL, (LPBYTE) &CustPalette[PALREGION_VS],    &Size);
	Size =MAX_PATH *sizeof(TCHAR); RegQueryValueEx(SettingsBase, _T("CustPalettePC10C"), 0, NULL, (LPBYTE) &CustPalette[PALREGION_PC10],  &Size);

	Controllers::LoadSettings(SettingsBase);
	RegCloseKey(SettingsBase);

	ApplySettingsToMenu();
	if (dbgVisible) ShowWindow(hDebug, SW_SHOW);
	UpdateInterface();
}

void	ApplySettingsToMenu(void) {
	if (plugThruDevice <ID_PLUG_NONE || plugThruDevice >ID_PLUG_MAX) plugThruDevice =ID_PLUG_NONE;
	for (int i =ID_PLUG_NONE; i <=ID_PLUG_MAX; i++) CheckMenuItem(hMenu, i, plugThruDevice ==i? MF_CHECKED: MF_UNCHECKED); // CheckMenuRadioItem does not like that the items are in different sub-menus
	CheckMenuItem(hMenu, ID_FILE_AUTOCORRECT,          AutoCorrect?              MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_FILE_AUTORUN,              AutoRun?                  MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_DEBUG_STATWND,             dbgVisible?               MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_PPU_SIZE_ASPECT,           FixAspect?                MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_FASTLOAD,                  FastLoad?                 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_CPU_BOOT_DISABLE_FRAMEIRQ, BootWithDisabledFrameIRQ? MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_SOUND_LPF_ONEBUS,          LowPassFilterOneBus?      MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_NONLINEAR_MIXING,          NonlinearMixing?          MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_SOUND_ENABLED,             SoundEnabled?             MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_SOUND_VTXXAPU1,            VTxx_APU1?                MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_SOUND_VTXXAPU2,            VTxx_APU2?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_APU1_CH1,				   APU1_CH1?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_APU1_CH2,				   APU1_CH2?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_APU1_CH3,				   APU1_CH3?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_APU1_CH4,				   APU1_CH4?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_APU1_CH5,				   APU1_CH5?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_APU2_CH1,				   APU2_CH1?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_APU2_CH2,				   APU2_CH2?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_APU2_CH3,				   APU2_CH3?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_APU2_CH4,				   APU2_CH4?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_VT32_CH1,				   VT32_CH1?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_VT32_CH2,				   VT32_CH2?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_VT369_CH1,				   VT369_CH1?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_VT369_CH2,				   VT369_CH2?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_VT369_CH3,				   VT369_CH3?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_VT369_CH4,				   VT369_CH4?				 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_SOUND_VTXXAPUDETUNE,	   VT369_60hz_Sound?		 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_SOUND_VTXXAPUDETUNE2,	   VT369_60hz_Sound_Alt?	 MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_SOUND_ALWAYSMAKEAPUFULLSPEED, VT369_APU_Force_FullSpeed? MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_SOUND_SWAPDUTY,            SwapDutyCycles?           MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_SOUND_SWAPDUTYCYCLES_ALL,  SwapAllDutyCycles?           MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_SOUND_EXPAUDIO_BOOTLEG,    BootlegExpansionAudio?    MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_SOUND_CLEAN_N163,          CleanN163?                MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_SOUND_REMOVE_BUZZ,         RemoveDPCMBuzz?           MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_SOUND_REMOVE_POPS,         RemoveDPCMPops?           MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_REVERSE_DPCM,              ReverseDPCM?              MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_PPU_DISABLE_EMPHASIS,      DisableEmphasis?          MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_IGNORE_RACE_CONDITION,     IgnoreRaceCondition?      MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_PPU_SCANLINES,             Scanlines?                MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_PPU_VSYNC,                 VSync?                    MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_PPU_NO_SPRITE_LIMIT,       NoSpriteLimit?            MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_PPU_SCROLL_GLITCH,         ScrollGlitch?             MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_PPU_UP_BY_ONE,             upByOne?                  MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_PPU_SOFT_RESET,            PPUSoftReset?             MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_PPU_NEVER_CLIP,            PPUNeverClip?             MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_DENDY_NTSC_ASPECT,         DendyNTSCAspect?          MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_DENDY_60_HZ,               Dendy60Hz?                MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_PPU_SHOW_BG,               PPU::showBG?              MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_PPU_SHOW_OBJ,	           PPU::showOBJ?             MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_VT32_REMOVE_BLUE_CAST,	   VT32RemoveBlueishCast?    MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_DISABLE_PERIODIC_NOISE,	   DisablePeriodicNoise?     MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_PPU_DISABLE_OAMDATA,	   DisableOAMData?           MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_HARD_GAME_SAVER,    	   HardGameSaver?            MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_VT369_SOUND_HLE,    	   VT369SoundHLE?            MF_CHECKED: MF_UNCHECKED);
	
	switch (VTxx_Rom_Type) {
		default:
			VTxx_Rom_Type = 0;
		case 0:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_VT02, MF_BYCOMMAND);
			break;
		case 1:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_WAIXINGVT02, MF_BYCOMMAND);
			break;
		case 2:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_JUNGLETACVT02, MF_BYCOMMAND);
			break;
		case 3:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_VT09, MF_BYCOMMAND);
			break;
		case 4:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_VT32, MF_BYCOMMAND);
			break;
		case 5:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_VT369, MF_BYCOMMAND);
			break;
		case 6:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_VT369_1, MF_BYCOMMAND);
			break;
		case 7:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_VT369_2, MF_BYCOMMAND);
			break;
		case 8:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_VT369_3, MF_BYCOMMAND);
			break;
		case 9:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_VT369_4, MF_BYCOMMAND);
			break;
		case 10:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_VT369_5, MF_BYCOMMAND);
			break;
		case 11:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_MULTICARTA, MF_BYCOMMAND);
			break;
		case 12:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_MULTICARTB, MF_BYCOMMAND);
			break;
		case 13:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_MULTICARTC, MF_BYCOMMAND);
			break;
		case 14:
			CheckMenuRadioItem(hMenu, ID_VTXXROMSYSTEMTYPE_VT02, ID_VTXXROMSYSTEMTYPE_MULTICARTD, ID_VTXXROMSYSTEMTYPE_MULTICARTD, MF_BYCOMMAND);
			break;
	}
	switch (LowPassFilterAPU) {
		default:LowPassFilterAPU =0;
		case 0:	CheckMenuRadioItem(hMenu, ID_SOUND_LPF_NONE, ID_SOUND_LPF_RF, ID_SOUND_LPF_NONE,  MF_BYCOMMAND); break;
		case 1:	CheckMenuRadioItem(hMenu, ID_SOUND_LPF_NONE, ID_SOUND_LPF_RF, ID_SOUND_LPF_PULSE, MF_BYCOMMAND); break;
		case 2:	CheckMenuRadioItem(hMenu, ID_SOUND_LPF_NONE, ID_SOUND_LPF_RF, ID_SOUND_LPF_APU,   MF_BYCOMMAND); break;
		case 3:	CheckMenuRadioItem(hMenu, ID_SOUND_LPF_NONE, ID_SOUND_LPF_RF, ID_SOUND_LPF_RF,    MF_BYCOMMAND); break;
	}
	switch (VT03Palette) {
		case 0:	CheckMenuRadioItem(hMenu, ID_VT03_NTSC, ID_VT03_MIXED, ID_VT03_NTSC,   MF_BYCOMMAND); break;
		case 1:	CheckMenuRadioItem(hMenu, ID_VT03_NTSC, ID_VT03_MIXED, ID_VT03_PAL,    MF_BYCOMMAND); break;
		default:VT03Palette =2;
		case 2:	CheckMenuRadioItem(hMenu, ID_VT03_NTSC, ID_VT03_MIXED, ID_VT03_MIXED,  MF_BYCOMMAND); break;
	}
	switch (NES::CurRegion) {
		case REGION_PAL:   CheckMenuRadioItem(hMenu, ID_PPU_MODE_NTSC, ID_PPU_MODE_DENDY, ID_PPU_MODE_PAL,   MF_BYCOMMAND); break;
		case REGION_DENDY: CheckMenuRadioItem(hMenu, ID_PPU_MODE_NTSC, ID_PPU_MODE_DENDY, ID_PPU_MODE_DENDY, MF_BYCOMMAND); break;
		default:           NES::CurRegion =REGION_NTSC;
		case REGION_NTSC:  CheckMenuRadioItem(hMenu, ID_PPU_MODE_NTSC, ID_PPU_MODE_DENDY, ID_PPU_MODE_NTSC,  MF_BYCOMMAND); break;
	}
	switch (DefaultRegion) {
		case REGION_PAL:   CheckMenuRadioItem(hMenu, ID_DEFAULT_NTSC, ID_DEFAULT_DENDY, ID_DEFAULT_PAL,   MF_BYCOMMAND); break;
		case REGION_DENDY: CheckMenuRadioItem(hMenu, ID_DEFAULT_NTSC, ID_DEFAULT_DENDY, ID_DEFAULT_DENDY, MF_BYCOMMAND); break;
		default:           DefaultRegion =REGION_NTSC;
		case REGION_NTSC:  CheckMenuRadioItem(hMenu, ID_DEFAULT_NTSC, ID_DEFAULT_DENDY, ID_DEFAULT_NTSC,  MF_BYCOMMAND); break;
	}
	switch (SizeMult) {
		case 1:  CheckMenuRadioItem(hMenu, ID_PPU_SIZE_1X, ID_PPU_SIZE_4X, ID_PPU_SIZE_1X, MF_BYCOMMAND); break;
		default: SizeMult =2;
		case 2:	 CheckMenuRadioItem(hMenu, ID_PPU_SIZE_1X, ID_PPU_SIZE_4X, ID_PPU_SIZE_2X, MF_BYCOMMAND); break;
		case 3:	 CheckMenuRadioItem(hMenu, ID_PPU_SIZE_1X, ID_PPU_SIZE_4X, ID_PPU_SIZE_3X, MF_BYCOMMAND); break;
		case 4:	 CheckMenuRadioItem(hMenu, ID_PPU_SIZE_1X, ID_PPU_SIZE_4X, ID_PPU_SIZE_4X, MF_BYCOMMAND); break;
	}
	switch (RAMInitialization) {
		case 0x00: CheckMenuRadioItem(hMenu, ID_RAMFILL_00, ID_RAMFILL_RANDOM, ID_RAMFILL_00,     MF_BYCOMMAND); break;
		case 0xFF: CheckMenuRadioItem(hMenu, ID_RAMFILL_00, ID_RAMFILL_RANDOM, ID_RAMFILL_FF,     MF_BYCOMMAND); break;
		default:   CheckMenuRadioItem(hMenu, ID_RAMFILL_00, ID_RAMFILL_RANDOM, ID_RAMFILL_RANDOM, MF_BYCOMMAND); break;
	}
	switch (ExpansionAudioVolume) {
		case  0:  CheckMenuRadioItem(hMenu, ID_EXPAUDIO_NONE, ID_EXPAUDIO_LATER, ID_EXPAUDIO_NONE,   MF_BYCOMMAND); break;
		case 75:  CheckMenuRadioItem(hMenu, ID_EXPAUDIO_NONE, ID_EXPAUDIO_LATER, ID_EXPAUDIO_ORIG,   MF_BYCOMMAND); break;
		default:  ExpansionAudioVolume =80;
		case 80:  CheckMenuRadioItem(hMenu, ID_EXPAUDIO_NONE, ID_EXPAUDIO_LATER, ID_EXPAUDIO_MIDDLE, MF_BYCOMMAND); break;
		case 133: CheckMenuRadioItem(hMenu, ID_EXPAUDIO_NONE, ID_EXPAUDIO_LATER, ID_EXPAUDIO_LATER,  MF_BYCOMMAND); break;
	}
	switch (VSDualScreens) {
		case 0:  CheckMenuRadioItem(hMenu, ID_VSDUAL_LEFT, ID_VSDUAL_BOTH, ID_VSDUAL_LEFT,  MF_BYCOMMAND); break;
		case 1:  CheckMenuRadioItem(hMenu, ID_VSDUAL_LEFT, ID_VSDUAL_BOTH, ID_VSDUAL_RIGHT, MF_BYCOMMAND); break;
		default: VSDualScreens =2;
		case 2:  CheckMenuRadioItem(hMenu, ID_VSDUAL_LEFT, ID_VSDUAL_BOTH, ID_VSDUAL_BOTH,  MF_BYCOMMAND); break;
	}
	switch (CommitMode35) {
		case COMMIT_DISCARD: CheckMenuRadioItem(hMenu, ID_COMMIT35_DISCARD, ID_COMMIT35_DIRECTLY, ID_COMMIT35_DISCARD,  MF_BYCOMMAND); break;
		default:CommitMode35 =COMMIT_APPDATA;
		case COMMIT_APPDATA: CheckMenuRadioItem(hMenu, ID_COMMIT35_DISCARD, ID_COMMIT35_DIRECTLY, ID_COMMIT35_APPDATA,  MF_BYCOMMAND); break;
		case COMMIT_DIRECTLY:CheckMenuRadioItem(hMenu, ID_COMMIT35_DISCARD, ID_COMMIT35_DIRECTLY, ID_COMMIT35_DIRECTLY, MF_BYCOMMAND); break;
	}
	GFX::LoadPalette(PALETTE_MAX);
}

void GetWindowPosition() {
	if (!GFX::Fullscreen) {
		RECT WindowPosition;
		GetWindowRect(hMainWnd, &WindowPosition);
		PosX =WindowPosition.left;
		PosY =WindowPosition.top;
	}
}

void SetWindowPosition() {
	if (!GFX::Fullscreen) {
		RECT WindowPosition;
		GetWindowRect(hMainWnd, &WindowPosition);
		WindowPosition.left =PosX;;
		WindowPosition.top =PosY;
		SetWindowPos(hMainWnd, HWND_TOP, PosX, PosY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
}

} // namespace Settings