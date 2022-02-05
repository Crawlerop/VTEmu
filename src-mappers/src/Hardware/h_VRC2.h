#include	"..\interface.h"

namespace VRC2 {
extern	uint16_t	chr[8];

void	MAPINT	syncPRG (int, int);
void	MAPINT	syncCHR_ROM (int, int);
void	MAPINT	syncCHR_ROM (int, int, int, int, int);
void	MAPINT	syncCHR_RAM (int, int);
void	MAPINT	syncMirror ();
void	MAPINT	writePRG (int, int, int);
void	MAPINT	writeMirroring (int, int, int);
void	MAPINT  writeCHR (int, int, int);
void	MAPINT	writeIRQ (int, int, int);
void	MAPINT	load (FSync, uint8_t, uint8_t);
void	MAPINT	reset (RESET_TYPE);
int	MAPINT	saveLoad (STATE_TYPE, int, unsigned char *);
}
