#include	"..\interface.h"

namespace VRC4 {
extern	int		A0, A1;
extern	uint8_t		prgFlip;
extern	uint8_t		prg[2];
extern	uint16_t	chr[8];
extern	uint8_t		irq;
extern	uint8_t		counter;
extern	uint8_t 	latch;
extern	int16_t		cycles;
extern	bool		wramEnable;
void	MAPINT		syncPRG (int, int);
void	MAPINT		syncCHR (int, int);
void	MAPINT		syncCHR_ROM (int, int);
void	MAPINT		syncCHR_RAM (int, int);
void	MAPINT		syncMirror ();
void	MAPINT		write (int, int, int);
int	MAPINT		readWRAM (int, int);
void	MAPINT		writeWRAM (int, int, int);
void	MAPINT		writePRG (int, int, int);
void	MAPINT		writeMisc (int, int, int);
void	MAPINT  	writeCHR (int, int, int);
void	MAPINT		writeIRQ (int, int, int);
void	MAPINT		load (FSync, int, int, FCPUWrite, bool, uint8_t);
void	MAPINT		reset (RESET_TYPE);
void	MAPINT		cpuCycle (void);
int	MAPINT		saveLoad (STATE_TYPE, int, unsigned char *);
}
