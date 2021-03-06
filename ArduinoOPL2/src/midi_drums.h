/**
 * This file contains MIDI instrument defenitions for use with the OPL2 Audio Board library. These were converted from
 * the General MIDI timbres by The Fat Man(TM). This file contains the drum instrments only. Notice that these are not
 * rhythm mode 
 *
 * Instrument definition is based on Adlib instrument bank format.
 *  0 - Transpose
 *		Tells the number of semi-tones a note that is played using this instrument should be pitched up or down. For
 *		drum instruments that are played in melodic mode this sets the absolute note to be played for the drum sound.
 *
 *  1 - Channel c, operator 1, register 0x20
 *		Tremolo(1) | Vibrato(1) | Sustain(1) | KSR(1) | Frequency multiplier (4)
 *
 *  2 - Channel c, operator 1, register 0x40
 *		Key scale level(2) | Output level(6)
 *
 *  3 - Channel c, operator 1, register 0x60
 *		Attack(4) | Decay(4)
 *
 *  4 - Channel c, operator 1, register 0x80
 *		Sustain(4) | Release(4)
 *
 *  5 - Channel c, register 0xC0
 *		Undefined(4) | Modulation feedback factor(3) | Synth type(1)
 *
 *  6 - Channel c, operator 2, register 0x20
 *  7 - Channel c, operator 2, register 0x40
 *  8 - Channel c, operator 2, register 0x60
 *  9 - Channel c, operator 2, register 0x80
 *
 * 10 - Channel c, operators 1 + 2, register 0xE0
 *		OP1 WaveForm(3) | OP2 Waveform(3)
 */

#ifndef _MIDI_DRUM2OP_H_
	#define _MIDI_DRUM2OP_H_
	#undef PROGMEM
	#define PROGMEM

	const unsigned char DRUMINS_CLAP2[11]     PROGMEM = { 0x30, 0x3E, 0x00, 0x9F, 0x0F, 0x00, 0x30, 0x00, 0x87, 0xFA, 0x0F };
	const unsigned char DRUMINS_SCRATCH1[11]  PROGMEM = { 0x30, 0x01, 0x00, 0x78, 0x97, 0x00, 0x02, 0x00, 0x88, 0x98, 0x39 };
	const unsigned char DRUMINS_SCRATCH2[11]  PROGMEM = { 0x30, 0x01, 0x00, 0x78, 0x97, 0x00, 0x02, 0x00, 0x88, 0x98, 0x39 };
	const unsigned char DRUMINS_RIMSHOT2[11]  PROGMEM = { 0x30, 0x16, 0x08, 0xF1, 0xFB, 0x00, 0x11, 0x00, 0xF9, 0x69, 0x01 };
	const unsigned char DRUMINS_HIQ[11]       PROGMEM = { 0x30, 0x00, 0x00, 0xF8, 0x6C, 0x00, 0x0E, 0x80, 0xE8, 0x4A, 0x01 };
	const unsigned char DRUMINS_WOODBLOK[11]  PROGMEM = { 0x30, 0x25, 0x1B, 0xFA, 0xF2, 0x00, 0x12, 0x00, 0xF6, 0x9A, 0x01 };
	const unsigned char DRUMINS_GLOCK[11]     PROGMEM = { 0x30, 0x06, 0x03, 0xF4, 0x44, 0x01, 0x01, 0x1B, 0xF2, 0x34, 0x00 };
	const unsigned char DRUMINS_BASS_DR2[11]  PROGMEM = { 0x30, 0x00, 0x00, 0xF9, 0xF3, 0x00, 0x01, 0x00, 0xF7, 0x8A, 0x05 };
	const unsigned char DRUMINS_BASS_DR1[11]  PROGMEM = { 0x30, 0x01, 0x07, 0xFA, 0xFD, 0x00, 0x01, 0x00, 0xF6, 0x47, 0x05 };
	const unsigned char DRUMINS_RIMSHOT[11]   PROGMEM = { 0x30, 0x16, 0x08, 0xF1, 0xFB, 0x00, 0x11, 0x00, 0xF9, 0x69, 0x01 };
	const unsigned char DRUMINS_SNARE_AC[11]  PROGMEM = { 0x30, 0x24, 0x00, 0xFF, 0x0F, 0x00, 0x02, 0x00, 0xF7, 0xA9, 0x0F };
	const unsigned char DRUMINS_CLAP[11]      PROGMEM = { 0x30, 0x3E, 0x00, 0x9F, 0x0F, 0x00, 0x30, 0x00, 0x87, 0xFA, 0x0F };
	const unsigned char DRUMINS_SNARE_EL[11]  PROGMEM = { 0x30, 0x24, 0x00, 0xFF, 0x0F, 0x00, 0x02, 0x00, 0xF7, 0xA9, 0x0F };
	const unsigned char DRUMINS_LO_TOMS[11]   PROGMEM = { 0x30, 0x06, 0x0A, 0xFA, 0x1F, 0x00, 0x11, 0x00, 0xF5, 0xF5, 0x0C };
	const unsigned char DRUMINS_HIHAT_CL[11]  PROGMEM = { 0x30, 0x2C, 0x00, 0xF2, 0xFE, 0x00, 0x02, 0x06, 0xB8, 0xD8, 0x37 };
	const unsigned char DRUMINS_HI_TOMS[11]   PROGMEM = { 0x30, 0x06, 0x0A, 0xFA, 0x1F, 0x00, 0x11, 0x00, 0xF5, 0xF5, 0x0C };
	const unsigned char DRUMINS_HIHAT_PL[11]  PROGMEM = { 0x30, 0x2C, 0x00, 0xF2, 0xFE, 0x00, 0x02, 0x06, 0xB8, 0xD8, 0x37 };
	const unsigned char DRUMINS_LOW_TOM[11]   PROGMEM = { 0x30, 0x06, 0x0A, 0xFA, 0x1F, 0x00, 0x11, 0x00, 0xF5, 0xF5, 0x0C };
	const unsigned char DRUMINS_HIHAT_OP[11]  PROGMEM = { 0x30, 0x2E, 0x00, 0x82, 0xF6, 0x00, 0x04, 0x10, 0x74, 0xF8, 0x35 };
	const unsigned char DRUMINS_LTOM_MID[11]  PROGMEM = { 0x30, 0x06, 0x0A, 0xFA, 0x1F, 0x00, 0x11, 0x00, 0xF5, 0xF5, 0x0C };
	const unsigned char DRUMINS_HTOM_MID[11]  PROGMEM = { 0x30, 0x06, 0x0A, 0xFA, 0x1F, 0x00, 0x11, 0x00, 0xF5, 0xF5, 0x0C };
	const unsigned char DRUMINS_CRASH[11]     PROGMEM = { 0x30, 0x2C, 0x00, 0x9F, 0x0F, 0x02, 0x0E, 0x05, 0xC5, 0xD4, 0x3F };
	const unsigned char DRUMINS_TOM_HIGH[11]  PROGMEM = { 0x30, 0x06, 0x0A, 0xFA, 0x1F, 0x00, 0x11, 0x00, 0xF5, 0xF5, 0x0C };
	const unsigned char DRUMINS_RIDE_CY[11]   PROGMEM = { 0x30, 0x29, 0x10, 0x94, 0x0F, 0x00, 0x04, 0x04, 0xF9, 0x44, 0x3F };
	const unsigned char DRUMINS_TAMBOUR[11]   PROGMEM = { 0x30, 0x2C, 0x00, 0x9F, 0x0F, 0x02, 0x0E, 0x05, 0xC5, 0xD4, 0x3F };
	const unsigned char DRUMINS_CYMBAL[11]    PROGMEM = { 0x30, 0x29, 0x10, 0x94, 0x0F, 0x00, 0x04, 0x04, 0xF9, 0x44, 0x3F };
	const unsigned char DRUMINS_TAMBOU2[11]   PROGMEM = { 0x30, 0x2E, 0x09, 0xF5, 0xF1, 0x00, 0x06, 0x03, 0x87, 0xF7, 0x31 };
	const unsigned char DRUMINS_SPLASH[11]    PROGMEM = { 0x30, 0x2C, 0x00, 0x9F, 0x0F, 0x02, 0x0E, 0x05, 0xC5, 0xD4, 0x3F };
	const unsigned char DRUMINS_COWBELL[11]   PROGMEM = { 0x30, 0x37, 0x14, 0xF7, 0xA1, 0x01, 0x03, 0x00, 0xF6, 0x28, 0x09 };
	const unsigned char DRUMINS_CRASH2[11]    PROGMEM = { 0x30, 0x2C, 0x00, 0x9F, 0x0F, 0x02, 0x0E, 0x05, 0xC5, 0xD4, 0x3F };
	const unsigned char DRUMINS_VIBRASLA[11]  PROGMEM = { 0x30, 0x80, 0x00, 0xFF, 0x0F, 0x01, 0x00, 0x00, 0xF5, 0xF7, 0x1D };
	const unsigned char DRUMINS_RIDE2[11]     PROGMEM = { 0x30, 0x29, 0x10, 0x94, 0x0F, 0x00, 0x04, 0x04, 0xF9, 0x44, 0x3F };
	const unsigned char DRUMINS_HI_BONGO[11]  PROGMEM = { 0x30, 0x25, 0xC4, 0xFA, 0xFA, 0x00, 0x03, 0x00, 0x99, 0xF9, 0x01 };
	const unsigned char DRUMINS_LO_BONGO[11]  PROGMEM = { 0x30, 0x21, 0x03, 0xFB, 0xFA, 0x01, 0x02, 0x00, 0xA8, 0xF7, 0x01 };
	const unsigned char DRUMINS_MUTECONG[11]  PROGMEM = { 0x30, 0x25, 0xC4, 0xFA, 0xFA, 0x00, 0x03, 0x00, 0x99, 0xF9, 0x01 };
	const unsigned char DRUMINS_OPENCONG[11]  PROGMEM = { 0x30, 0x24, 0x18, 0xF9, 0xFA, 0x02, 0x03, 0x00, 0xA6, 0xF6, 0x0F };
	const unsigned char DRUMINS_LOWCONGA[11]  PROGMEM = { 0x30, 0x24, 0x18, 0xF9, 0xFA, 0x02, 0x03, 0x00, 0xA6, 0xF6, 0x0F };
	const unsigned char DRUMINS_HI_TIMBA[11]  PROGMEM = { 0x30, 0x05, 0x14, 0xF5, 0xF5, 0x02, 0x03, 0x00, 0xF6, 0x36, 0x27 };
	const unsigned char DRUMINS_LO_TIMBA[11]  PROGMEM = { 0x30, 0x05, 0x14, 0xF5, 0xF5, 0x02, 0x03, 0x00, 0xF6, 0x36, 0x27 };
	const unsigned char DRUMINS_HI_AGOGO[11]  PROGMEM = { 0x30, 0x1C, 0x0C, 0xF9, 0x31, 0x01, 0x15, 0x00, 0x96, 0xE8, 0x1F };
	const unsigned char DRUMINS_LO_AGOGO[11]  PROGMEM = { 0x30, 0x1C, 0x0C, 0xF9, 0x31, 0x01, 0x15, 0x00, 0x96, 0xE8, 0x1F };
	const unsigned char DRUMINS_CABASA[11]    PROGMEM = { 0x30, 0x0E, 0x00, 0xFF, 0x01, 0x00, 0x0E, 0x02, 0x79, 0x77, 0x3F };
	const unsigned char DRUMINS_MARACAS[11]   PROGMEM = { 0x30, 0x0E, 0x00, 0xFF, 0x01, 0x00, 0x0E, 0x02, 0x79, 0x77, 0x3F };
	const unsigned char DRUMINS_S_WHISTL[11]  PROGMEM = { 0x30, 0x20, 0x15, 0xAF, 0x07, 0x01, 0x0E, 0x00, 0xA5, 0x2B, 0x25 };
	const unsigned char DRUMINS_L_WHISTL[11]  PROGMEM = { 0x30, 0x20, 0x18, 0xBF, 0x07, 0x01, 0x0E, 0x00, 0x93, 0x3B, 0x21 };
	const unsigned char DRUMINS_S_GUIRO[11]   PROGMEM = { 0x30, 0x20, 0x00, 0xF0, 0xF7, 0x00, 0x08, 0x01, 0x89, 0x3B, 0x3B };
	const unsigned char DRUMINS_L_GUIRO[11]   PROGMEM = { 0x30, 0x20, 0x00, 0xF3, 0xFA, 0x00, 0x08, 0x0A, 0x53, 0x2B, 0x29 };
	const unsigned char DRUMINS_CLAVES[11]    PROGMEM = { 0x30, 0x15, 0x21, 0xF8, 0x9A, 0x01, 0x13, 0x00, 0xF6, 0x89, 0x09 };
	const unsigned char DRUMINS_HI_WDBLK[11]  PROGMEM = { 0x30, 0x25, 0x1B, 0xFA, 0xF2, 0x00, 0x12, 0x00, 0xF6, 0x9A, 0x01 };
	const unsigned char DRUMINS_LO_WDBLK[11]  PROGMEM = { 0x30, 0x25, 0x1B, 0xFA, 0xF2, 0x00, 0x12, 0x00, 0xF6, 0x9A, 0x01 };
	const unsigned char DRUMINS_MU_CUICA[11]  PROGMEM = { 0x30, 0x20, 0x01, 0x5F, 0x07, 0x00, 0x08, 0x00, 0x87, 0x4B, 0x11 };
	const unsigned char DRUMINS_OP_CUICA[11]  PROGMEM = { 0x30, 0x25, 0x12, 0x57, 0xF7, 0x01, 0x03, 0x00, 0x78, 0x67, 0x11 };
	const unsigned char DRUMINS_MU_TRNGL[11]  PROGMEM = { 0x30, 0x22, 0x2F, 0xF1, 0xF0, 0x00, 0x27, 0x02, 0xF8, 0xFC, 0x07 };
	const unsigned char DRUMINS_OP_TRNGL[11]  PROGMEM = { 0x30, 0x26, 0x44, 0xF1, 0xF0, 0x00, 0x27, 0x40, 0xF5, 0xF5, 0x07 };
	const unsigned char DRUMINS_SHAKER[11]    PROGMEM = { 0x30, 0x0E, 0x00, 0xFF, 0x01, 0x00, 0x0E, 0x02, 0x79, 0x77, 0x3F };
	const unsigned char DRUMINS_TRIANGL1[11]  PROGMEM = { 0x30, 0x26, 0x44, 0xF1, 0xFF, 0x00, 0x27, 0x40, 0xF5, 0xF5, 0x07 };
	const unsigned char DRUMINS_TRIANGL2[11]  PROGMEM = { 0x30, 0x26, 0x44, 0xF1, 0xFF, 0x00, 0x27, 0x40, 0xF5, 0xF5, 0x07 };
	const unsigned char DRUMINS_RIMSHOT3[11]  PROGMEM = { 0x30, 0x16, 0x08, 0xF1, 0xFB, 0x00, 0x11, 0x00, 0xF9, 0x69, 0x01 };
	const unsigned char DRUMINS_RIMSHOT4[11]  PROGMEM = { 0x30, 0x16, 0x08, 0xF1, 0xFB, 0x00, 0x11, 0x00, 0xF9, 0x69, 0x01 };
	const unsigned char DRUMINS_TAIKO[11]     PROGMEM = { 0x30, 0x02, 0x1D, 0xF5, 0x93, 0x00, 0x00, 0x00, 0xC6, 0x45, 0x01 };

	// MIDI note number of the first drum sound.
	const unsigned char DRUM_NOTE_BASE = 27;
	const unsigned char NUM_MIDI_DRUMS = 60;

	// Instrument pointer array to access instruments by MIDI program.
	const unsigned char *midiDrums[] = {
		DRUMINS_CLAP2,    DRUMINS_SCRATCH1, DRUMINS_SCRATCH2, DRUMINS_RIMSHOT2, DRUMINS_HIQ,      DRUMINS_WOODBLOK,
		DRUMINS_GLOCK,    DRUMINS_BASS_DR2, DRUMINS_BASS_DR1, DRUMINS_RIMSHOT,  DRUMINS_SNARE_AC, DRUMINS_CLAP,
		DRUMINS_SNARE_EL, DRUMINS_LO_TOMS,  DRUMINS_HIHAT_CL, DRUMINS_HI_TOMS,  DRUMINS_HIHAT_PL, DRUMINS_LOW_TOM,
		DRUMINS_HIHAT_OP, DRUMINS_LTOM_MID, DRUMINS_HTOM_MID, DRUMINS_CRASH,    DRUMINS_TOM_HIGH, DRUMINS_RIDE_CY,
		DRUMINS_TAMBOUR,  DRUMINS_CYMBAL,   DRUMINS_TAMBOU2,  DRUMINS_SPLASH,   DRUMINS_COWBELL,  DRUMINS_CRASH2,
		DRUMINS_VIBRASLA, DRUMINS_RIDE2,    DRUMINS_HI_BONGO, DRUMINS_LO_BONGO, DRUMINS_MUTECONG, DRUMINS_OPENCONG,
		DRUMINS_LOWCONGA, DRUMINS_HI_TIMBA, DRUMINS_LO_TIMBA, DRUMINS_HI_AGOGO, DRUMINS_LO_AGOGO, DRUMINS_CABASA,
		DRUMINS_MARACAS,  DRUMINS_S_WHISTL, DRUMINS_L_WHISTL, DRUMINS_S_GUIRO,  DRUMINS_L_GUIRO,  DRUMINS_CLAVES,
		DRUMINS_HI_WDBLK, DRUMINS_LO_WDBLK, DRUMINS_MU_CUICA, DRUMINS_OP_CUICA, DRUMINS_MU_TRNGL, DRUMINS_OP_TRNGL,
		DRUMINS_SHAKER,   DRUMINS_TRIANGL1, DRUMINS_TRIANGL2, DRUMINS_RIMSHOT3, DRUMINS_RIMSHOT4, DRUMINS_TAIKO
	};

#endif
