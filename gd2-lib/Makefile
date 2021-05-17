all: terminal.run

terminal.run: GD2.cpp GD2Terminal.cpp
	m68k-elf-g++  -O3 -fno-exceptions -fomit-frame-pointer -Wall -m68000 -g -O GD2.cpp GD2Terminal.cpp -o terminal.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -Xlinker -Map=terminal.map

clean:
	$(RM) terminal.run terminal.map


distclean: clean


