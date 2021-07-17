all: demotune.run

demotune.run: DemoTune.cpp
	m68k-elf-g++ -fno-exceptions -fomit-frame-pointer -Wall  -O3  -m68000 -g -O DemoTune.cpp -o demotune.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -L. -lm -L../../gd2-lib -lGD2 -L../../FatFs -lMerlinFat -L../ -lOPL -Xlinker -Map=demo.map

lib: libOPL.a

libOPL.a: OPL2.cpp OPL3.cpp OPL3Duo.cpp TuneParser.cpp
	m68k-elf-g++ -O3 -fno-exceptions -fomit-frame-pointer -Wall -m68000 -c OPL2.cpp OPL3.cpp OPL3Duo.cpp TuneParser.cpp
	m68k-elf-ar rcs ../libOPL.a *.o 

clean:
	$(RM) *.o *.a *.run


distclean: clean


