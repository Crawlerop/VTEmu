#pragma once
#include	"..\interface.h"

class EEPROM_93C66A {
	uint8_t*	storage;
	uint8_t		opcode;
	uint8_t		data;
	uint16_t 	address;
	uint8_t		state;
	bool		lastCLK;
	bool		writeEnabled;
	bool		output;
public:	
	EEPROM_93C66A	(uint8_t*);
	int		MAPINT	saveLoad (STATE_TYPE, int, uint8_t *);
	void		write (bool, bool, bool);
	bool		read (void);
};
