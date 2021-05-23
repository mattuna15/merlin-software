all: terminal.run

terminal.run: HardwareTest.cpp 
	m68k-elf-g++  -O3 -fno-exceptions -fomit-frame-pointer -Wall -m68000 -g -I../../../src -O ../../../src/OPL2.cpp ../../../src/OPL3.cpp ../../../src/OPL3Duo.cpp HardwareTest.cpp -o terminal.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -Xlinker -Map=terminal.map

clean:
	$(RM) terminal.run terminal.map


distclean: clean


