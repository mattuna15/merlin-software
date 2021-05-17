1,2c1,2
< 	.file	"test.cc"
< | GNU C++14 (GCC) version 9.3.1 20210510 (m68k-elf)
---
> 	.file	"test.c"
> | GNU C17 (GCC) version 9.3.1 20210510 (m68k-elf)
6,7c6,7
< | options passed:  -imultilib m68000 test.cc -mcpu=68000
< | -auxbase-strip test.run -g -O -Wall -fverbose-asm
---
> | options passed:  -imultilib m68000 test.c -mcpu=68000
> | -auxbase-strip test2.run -g -O -Wall -fverbose-asm
12,13c12,13
< | -fexceptions -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse
< | -fgcse-lm -fgnu-runtime -fgnu-unique -fguess-branch-probability -fident
---
> | -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse -fgcse-lm
> | -fgnu-runtime -fgnu-unique -fguess-branch-probability -fident
40a41
> 	.cfi_sections	.debug_frame
46,47c47,48
< 	.file 1 "test.cc"
< 	.loc 1 4 12 view -0
---
> 	.file 1 "test.c"
> 	.loc 1 1 12 view -0
49,51c50
< 	.loc 1 7 5 view .LVU1
< | test.cc:8:          "   jsr 0xE00D44 \n\t");
< 	.loc 1 8 33 is_stmt 0 view .LVU2
---
> 	.loc 1 4 5 view .LVU1
53c52
< | 8 "test.cc" 1
---
> | 4 "test.c" 1
58,59c57,58
< | test.cc:11: }
< 	.loc 1 11 1 view .LVU3
---
> | test.c:8: }
> 	.loc 1 8 1 is_stmt 0 view .LVU2
75c74
< 	.byte	0x4
---
> 	.byte	0xc
84c83
< 	.byte	0x4
---
> 	.byte	0x1
170,172c169,171
< 	.string	"GNU C++14 9.3.1 20210510 -mcpu=68000 -g -O"
< .LASF3:
< 	.string	"main"
---
> 	.string	"GNU C17 9.3.1 20210510 -mcpu=68000 -g -O"
> .LASF1:
> 	.string	"test.c"
175,176c174,175
< .LASF1:
< 	.string	"test.cc"
---
> .LASF3:
> 	.string	"main"
