/**
 * This sketch tests if your OPL3 Duo board is functioning correctly. Open the serial terminal and follow the
 * instructions all tests indicate what you should hear when your board is functioning correctly.
 *
 * Code by Maarten Janssen, 2020-10-27
 * WWW.CHEERFUL.NL
 * Most recent version of the library can be found at my GitHub: https://github.com/DhrBaksteen/ArduinoOPL2
 */

#include <OPL3Duo.h>
#include <instruments.h>
#include <stdio.h>

OPL3Duo opl3Duo;
Instrument testInstrument;
Instrument testInstrument2;

void playTone(byte channel);

bool wasEnterPressed()
{

	uint8_t volatile *term = (uint8_t volatile *)0xf00009;
	uint8_t volatile *newchar = (uint8_t volatile *)0xf0000b;

	if (BIT_CHECK(*term, 0))
	{
		byte character = *newchar;
		return true;
	}
	else
		return false;
}

void setup()
{
	delay(1000);
	//Serial.begin(9600);
	opl3Duo.begin();
	testInstrument = opl3Duo.loadInstrument(INSTRUMENT_SYN1);
	testInstrument2 = opl3Duo.loadInstrument(INSTRUMENT_FLUTE);

	printf("This sketch tests the basic functions of the OPL3 Duo board.\r\n");
	printf("The expected test reulst is shown for each test.\r\n");
	printf("On each test press ENTER to advance to the next test.\r\n");
	printf("\r\n");
	printf("Press ENTER to begin...\r\n");
	while (!wasEnterPressed())
		;
	printf("\r\n");
}

void testSynthUnit1()
{
	printf("TEST 1: Synth unit 1...\r\n");
	printf("- You should hear a steady tone and a continuous scale through both speakers.\r\n");
	printf("\r\n");

	// Play a 250 Hz tone on channel 0 of synth unit 2.
	playTone(18);

	// Play a scale on all channels of synth unit 1.
	byte channel = 0;
	byte note = 0;
	while (!wasEnterPressed())
	{
		opl3Duo.setInstrument(channel, testInstrument);
		opl3Duo.playNote(channel, 5, note);
		delay(200000);
		opl3Duo.setKeyOn(channel, false);

		channel = (channel + 1) % 18;
		note = (note + 1) % 12;
	}

	// Stop background tone.
	opl3Duo.setKeyOn(18, false);
	delay(500);
}

void testUnit1Panning()
{
	printf("TEST 2: Synth unit 1 left channel...\r\n");
	printf("- You should hear a steady tone through the left speaker only.\r\n");
	printf("\r\n");

	opl3Duo.setInstrument(0, testInstrument2);
	opl3Duo.setPanning(0, true, false);
	opl3Duo.playNote(0, 4, NOTE_C);
	while (!wasEnterPressed())
		;
	opl3Duo.setKeyOn(0, false);

	delay(500);

	printf("Test 3: Synth unit 1 right channel...\r\n");
	printf("- You should hear a steady tone through the right speaker only.\r\n");
	printf("\r\n");

	opl3Duo.setPanning(0, false, true);
	opl3Duo.playNote(0, 4, NOTE_C);
	while (!wasEnterPressed())
		;
	opl3Duo.setKeyOn(0, false);

	opl3Duo.setPanning(0, true, true);
	delay(500);
}

void testSynthUnit2()
{
	printf("TEST 4: Synth unit 2...\r\n");
	printf("- You should hear a steady tone and a continuous scale through both speakers.\r\n");
	printf("\r\n");

	// Play a 250 Hz tone on channel 0 of synth unit 1.
	playTone(0);

	// Play a scale on all channels of synth unit 2.
	byte channel = 0;
	byte note = 0;
	while (!wasEnterPressed())
	{
		opl3Duo.setInstrument(18 + channel, testInstrument);
		opl3Duo.playNote(18 + channel, 5, note);
		delay(200000);
		opl3Duo.setKeyOn(18 + channel, false);

		channel = (channel + 1) % 18;
		note = (note + 1) % 12;
	}

	// Stop background tone.
	opl3Duo.setKeyOn(0, false);
	delay(500);
}

void testUnit2Panning()
{
	printf("TEST 5: Synth unit 2 left channel...\r\n");
	printf("- You should hear a steady tone through the left speaker only.\r\n");
	printf("\r\n");

	opl3Duo.setInstrument(18, testInstrument2);
	opl3Duo.setPanning(18, true, false);
	opl3Duo.playNote(18, 4, NOTE_C);
	while (!wasEnterPressed())
		;
	opl3Duo.setKeyOn(18, false);

	delay(500);
	printf("Test 6: Synth unit 2 right channel...\r\n");
	printf("- You should hear a steady tone through the right speaker only.\r\n");
	printf("\r\n");

	opl3Duo.setPanning(18, false, true);
	opl3Duo.playNote(18, 4, NOTE_C);
	while (!wasEnterPressed())
		;
	opl3Duo.setKeyOn(18, false);

	opl3Duo.setPanning(18, true, true);
	delay(500);
}

void testReset()
{
	printf("TEST 7: OPL3 Duo reset...\r\n");
	printf("- There should be no sound.\r\n");
	printf("\r\n");

	playTone(0);
	playTone(18);
	opl3Duo.reset();

	while (!wasEnterPressed())
		;
	delay(500);
}

/**
 * Play a tone of 250 Hz on the given channel.
 */
void playTone(byte channel)
{
	opl3Duo.setInstrument(channel, testInstrument2);
	opl3Duo.playNote(channel, 4, NOTE_C);
}

int main()
{

	setup();

	testSynthUnit1();
	opl3Duo.setOPL3Enabled(true);
	testUnit1Panning();
	opl3Duo.setOPL3Enabled(false);
	testSynthUnit2();
	opl3Duo.setOPL3Enabled(true);
	testUnit2Panning();
	opl3Duo.setOPL3Enabled(false);
	testReset();
	printf("Done.\r\n");
}
