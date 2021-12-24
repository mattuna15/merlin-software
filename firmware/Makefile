all:  loader.run

loader.run: ../fp-lib/ieee754.c  loader.c
	m68k-elf-gcc -fno-exceptions -fomit-frame-pointer -Wall -m68000 -g -O loader.c ../fp-lib/ieee754.c -o loader.run  \
			-Wl,--wrap=__muldf3 \
			-Wl,--wrap=__divdf3 \
			-Wl,--wrap=__subdf3 \
			-Wl,--wrap=__adddf3 \
			 -I../fp-lib/ -T loader.ld -L../FatFs -lMerlinFat -L../gd2-lib -lGD2 -Xlinker -Map=firmware.map

clean:
	$(RM) *.o *.a *.run


distclean: clean


