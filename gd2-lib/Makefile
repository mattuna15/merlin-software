all: terminal.run

terminal.run: GD2.cpp  term.cpp
	m68k-elf-g++  -O3 -fno-exceptions -fomit-frame-pointer -Wall -m68000 -g -O GD2.cpp term.cpp -o terminal.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld  -L../FatFs -lMerlinFat -Xlinker -Map=terminal.map

clean:
	$(RM) terminal.run terminal.map


distclean: clean


