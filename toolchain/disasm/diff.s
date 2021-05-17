1d0
<  ORI.b     #$14,D0
3,18c2
<  BCHG      D0,$5200(PC)
<  ANDI      #$1801,SR
<  MOVE.b    A4,-(A5)
<  BTST      D7,D4
<  SUB.b     D1,D4
<  ORI.b     #$00,D0
<  ORI.b     #$00,(A0)
<  ORI.b     #$00,(A4)+
<  MOVEP.w   D0,($0000,A0)
<  ORI.b     #$00,A6
<  ORI.b     #$00,D0
<  ORI.b     #$7C,D0
< Warning: Invalid S bits in instruction (11), assuming word size.
< Warning: Invalid S bits in instruction (11), assuming word size.
< Warning: Invalid S bits in instruction (11), assuming word size.
<  ORI.w     #$FFFE,(A7)+
---
>  MOVEA.l   #$00DFFFFE,A0
20c4
<  BEQ       $00000040
---
>  BEQ       $00000014
23,24c7,8
<  MOVE.l    #$00000C80,D1
<  MOVE.l    #$00000CA0,D0
---
>  MOVE.l    #$00000C54,D1
>  MOVE.l    #$00000C78,D0
26c10
<  BEQ       $00000066
---
>  BEQ       $0000003A
31c15
<  DBF       D0,$0000005A
---
>  DBF       D0,$0000002E
34c18
<  BCC       $0000005A
---
>  BCC       $0000002E
37c21
<  BEQ       $00000076
---
>  BEQ       $0000004A
41c25
<  BEQ       $00000086
---
>  BEQ       $0000005A
43,45c27,29
<  MOVE.l    #$00000B74,(A7)
<  JSR       $000009B8
<  JSR       $00000B60
---
>  MOVE.l    #$00000B48,(A7)
>  JSR       $0000098C
>  JSR       $00000B34
47c31
<  PEA       $00000B84
---
>  PEA       $00000B58
50c34
<  JSR       $000009A8
---
>  JSR       $0000097C
52,55c36,39
<  JSR       $00000AAC
<  MOVE.l    #$00000C80,D0
<  CMPI.l    #$00000C80,D0
<  BEQ       $000000DC
---
>  JSR       $00000A80
>  MOVE.l    #$00000C54,D0
>  CMPI.l    #$00000C54,D0
>  BEQ       $000000B0
58,59c42,43
<  BEQ       $000000DC
<  PEA       $00000C80
---
>  BEQ       $000000B0
>  PEA       $00000C54
63,64c47,48
<  MOVE.l    #$00000C80,D0
<  SUBI.l    #$00000C80,D0
---
>  MOVE.l    #$00000C54,D0
>  SUBI.l    #$00000C54,D0
72c56
<  BEQ       $00000112
---
>  BEQ       $000000E6
75c59
<  BEQ       $00000112
---
>  BEQ       $000000E6
77c61
<  PEA       $00000C80
---
>  PEA       $00000C54
83,86c67,70
<  TST.b     $00000C80
<  BNE       $0000017E
<  MOVE.l    #$00000B5C,D2
<  SUBI.l    #$00000B50,D2
---
>  TST.b     $00000C54
>  BNE       $00000152
>  MOVE.l    #$00000B30,D2
>  SUBI.l    #$00000B24,D2
89,90c73,74
<  LEA       $00000B50,A2
<  MOVE.l    $00000C82,D0
---
>  LEA       $00000B24,A2
>  MOVE.l    $00000C56,D0
92c76
<  BLS       $0000015C
---
>  BLS       $00000130
94c78
<  MOVE.l    D0,$00000C82
---
>  MOVE.l    D0,$00000C56
99c83
<  MOVE.l    $00000C82,D0
---
>  MOVE.l    $00000C56,D0
101c85
<  BHI       $00000140
---
>  BHI       $00000114
105c89
<  BEQ       $00000176
---
>  BEQ       $0000014A
109c93
<  MOVE.b    #$01,$00000C80
---
>  MOVE.b    #$01,$00000C54
116,117c100,101
<  BEQ       $000001A2
<  PEA       $00000C86
---
>  BEQ       $00000176
>  PEA       $00000C5A
121c105
<  BRA       $000000DE
---
>  BRA       $000000B2
131c115
<  JSR       $000009D0
---
>  JSR       $000009A4
137c121
<  MOVEA.l   $00000B5C,A0
---
>  MOVEA.l   $00000B30,A0
140c124
<  BNE       $00000200
---
>  BNE       $000001D4
144c128
<  BEQ       $00000200
---
>  BEQ       $000001D4
148c132
<  BGE       $00000210
---
>  BGE       $000001E4
154c138
<  BEQ       $0000026C
---
>  BEQ       $00000240
157c141
<  BNE       $00000244
---
>  BNE       $00000218
160c144
<  BEQ       $00000208
---
>  BEQ       $000001DC
166c150
<  BEQ       $00000208
---
>  BEQ       $000001DC
181c165
<  BNE       $0000026C
---
>  BNE       $00000240
192c176
<  BRA       $0000020A
---
>  BRA       $000001DE
194c178
<  MOVEA.l   $00000B40,A0
---
>  MOVEA.l   $00000B14,A0
197,198c181,182
<  BEQ       $000002A6
<  LEA       $00000B40,A2
---
>  BEQ       $0000027A
>  LEA       $00000B14,A2
203c187
<  BNE       $0000029C
---
>  BNE       $00000270
216c200
<  BNE       $000002E0
---
>  BNE       $000002B4
241c225
<  BEQ       $00000332
---
>  BEQ       $00000306
258c242
<  ORI.b     #$90,D0
---
>  ORI.b     #$64,D0
260,261c244,245
<  JSR       $00000986
<  JSR       $00000A88
---
>  JSR       $0000095A
>  JSR       $00000A5C
265c249
<  JSR       $00000914
---
>  JSR       $000008E8
271c255
<  BCLR      D5,(A0)
---
>  BCHG      D5,-(A4)
