#include "h_EEPROM_93C66.h"

static constexpr uint8_t
	Opcode_misc =0,
	Opcode_write =1,
	Opcode_read =2,
	Opcode_erase =3,
	Opcode_writeDisable =10,
	Opcode_writeAll =11,
	Opcode_eraseAll =12,
	Opcode_writeEnable =13
;
static constexpr uint8_t
	State_standBy =0,
	State_startBit =1,
	State_opcode =3,
	State_address =12,
	State_data =20,
	State_finished =99
;	

EEPROM_93C66A::EEPROM_93C66A (uint8_t* buffer) {
	storage =buffer;
	address =0;
	state =State_standBy;
	lastCLK =false;
	writeEnabled =false;
}

void EEPROM_93C66A::write (bool CS, bool CLK, bool DAT) {
	if (!CS && state <=State_address)
		state =State_standBy;
	else
	if (state ==State_standBy && CS ==true && CLK ==true) {
		state =State_startBit;
		opcode =0;
		address =0;
		output =true;
	} else if (CLK && !lastCLK) {
		if (state >=State_startBit && state <State_opcode)  opcode  =(opcode  <<1) | DAT*1; else
		if (state >=State_opcode   && state <State_address) address =(address <<1) | DAT*1; else

		if (state >=State_address  && state <State_data) {
			if (opcode ==Opcode_write || opcode ==Opcode_writeAll) data =(data <<1) | DAT*1; else
			if (opcode ==Opcode_read) {
				output =!!(data &0x80);
				data =data <<1;
			}
		}

		state++;
		if (state ==State_address) {
			switch (opcode) {
				case Opcode_misc:
					opcode =(address >>7) +10;
					switch (opcode) {
						case Opcode_writeDisable: writeEnabled =false;
						                           state =State_finished;
									   break;
						case Opcode_writeEnable:  writeEnabled =true;
						                           state =State_finished;
									   break;
						case Opcode_eraseAll:     if (writeEnabled) for (int i =0; i <512; i++) storage[i] =0xFF;
						                           state =State_finished;
									   break;
						case Opcode_writeAll:	   address =0;
									   break;
					}
					break;
				case Opcode_erase:
					if (writeEnabled) storage[address] =0xFF;
					state =State_finished;
					break;
				case Opcode_read:
					data =storage[address++];
					break;
			}
		} else
		if (state ==State_data) {
			if (opcode ==Opcode_write) {
				EMU->StatusOut(L"Written byte %d", address);
				storage[address++] =data;
				state =State_finished;
			} else
			if (opcode ==Opcode_writeAll) {
				storage[address++] =data;
				state =(CS && (address <512))? State_address: State_finished;
			} else
			if (opcode ==Opcode_read) {
				if (address <512) data =storage[address];
				state =(CS && (++address <=512))? State_address: State_finished;
			}
		}
		
		if (state ==State_finished) {
			output =false;
			state =State_standBy;
		}
	}
	//EMU->DbgOut(L"state %d, opcode %d, address %02X, data %02X", state, opcode, address, data);
	lastCLK =CLK;
}

bool EEPROM_93C66A::read (void) {
	return output;
}

int MAPINT EEPROM_93C66A::saveLoad (STATE_TYPE stateMode, int offset, unsigned char *stateData) {
	SAVELOAD_BYTE(stateMode, offset, stateData, opcode);
	SAVELOAD_BYTE(stateMode, offset, stateData, data);
	SAVELOAD_WORD(stateMode, offset, stateData, address);
	SAVELOAD_BOOL(stateMode, offset, stateData, lastCLK);
	SAVELOAD_BOOL(stateMode, offset, stateData, writeEnabled);
	SAVELOAD_BOOL(stateMode, offset, stateData, output);
	return offset;
}

