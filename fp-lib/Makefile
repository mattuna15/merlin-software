all: float-test.run

float-test.run: ieee754.c float-test.c

	m68k-elf-gcc -Wall -m68000 -g -O  \
			-Wl,--wrap=__muldf3 \
			-Wl,--wrap=__divdf3 \
			-Wl,--wrap=__subdf3 \
			-Wl,--wrap=__adddf3 \
			-Wl,--wrap=sqrt \
			ieee754.c float-test.c \
			-o float-test.run \
			-lm -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -Xlinker -Map=float.map

clean:
	$(RM) *.o *.a *.run


distclean: clean


