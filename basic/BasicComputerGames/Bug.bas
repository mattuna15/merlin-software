10 PRINT TAB(34);"BUG"
20 PRINT TAB(15);"CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY"
30 PRINT:PRINT:PRINT
40 REM
50 A=0: B=0: H=0: L=0: N=0: P=0: Q=0: R=0: S=0: T=0: U=0: V=0: Y=0
60 PRINT "THE GAME BUG"
70 PRINT "I HOPE YOU ENJOY THIS GAME."
80 PRINT
90 PRINT "DO YOU WANT INSTRUCTIONS";
100 INPUT Z$
110 IF Z$="NO" THEN 300
120 PRINT "THE OBJECT OF BUG IS TO FINISH YOUR BUG BEFORE I FINISH"
130 PRINT "MINE. EACH NUMBER STANDS FOR A PART OF THE BUG BODY."
140 PRINT "I WILL ROLL THE DIE FOR YOU, TELL YOU WHAT I ROLLED FOR YOU"
150 PRINT "WHAT THE NUMBER STANDS FOR, AND IF YOU CAN GET THE PART."
160 PRINT "IF YOU CAN GET THE PART I WILL GIVE IT TO YOU."
170 PRINT "THE SAME WILL HAPPEN ON MY TURN."
180 PRINT "IF THERE IS A CHANGE IN EITHER BUG I WILL GIVE YOU THE"
190 PRINT "OPTION OF SEEING THE PICTURES OF THE BUGS."
200 PRINT "THE NUMBERS STAND FOR PARTS AS FOLLOWS:"
210 PRINT "NUMBER","PART","NUMBER OF PART NEEDED"
220 PRINT "1","BODY","1"
230 PRINT "2","NECK","1"
240 PRINT "3","HEAD","1"
250 PRINT "4","FEELERS","2"
260 PRINT "5","TAIL","1"
270 PRINT "6","LEGS","6"
280 PRINT
290 PRINT
300 IF Y>0 THEN 2480
310 Z=INT(6*RND(0)+1)
320 C=1
330 PRINT "YOU ROLLED A";Z;"."
340 ON Z GOTO 350,430,540,650,760,870
350 PRINT "1=BODY"
360 IF B=1 THEN 410
370 PRINT "YOU NOW HAVE A BODY."
380 B=1
390 C=0
400 GOTO 970
410 PRINT "YOU DO NOT NEED A BODY."
420 GOTO 970
430 PRINT "2=NECK"
440 IF N=1 THEN 500
450 IF B=0 THEN 520
460 PRINT "YOU NOW HAVE A NECK."
470 N=1
480 C=0
490 GOTO 970
500 PRINT "YOU DO NOT NEED A NECK."
510 GOTO 970
520 PRINT "YOU DO NOT HAVE A BODY."
530 GOTO 970
540 PRINT "3=HEAD"
550 IF N=0 THEN 610
560 IF H=1 THEN 630
570 PRINT "YOU NEEDED A HEAD."
580 H=1
590 C=0
600 GOTO 970
610 PRINT "YOU DO NOT HAVE A NECK."
620 GOTO 970
630 PRINT "YOU HAVE A HEAD."
640 GOTO 970
650 PRINT "4=FEELERS"
660 IF H=0 THEN 740
670 IF A=2 THEN 720
680 PRINT "I NOW GIVE YOU A FEELER."
690 A=A+1
700 C=0
710 GOTO 970
720 PRINT "YOU HAVE TWO FEELERS ALREADY."
730 GOTO 970
740 PRINT "YOU DO NOT HAVE A HEAD."
750 GOTO 970
760 PRINT "5=TAIL"
770 IF B=0 THEN 830
780 IF T=1 THEN 850
790 PRINT "I NOW GIVE YOU A TAIL."
800 T=T+1
810 C=0
820 GOTO 970
830 PRINT "YOU DO NOT HAVE A BODY."
840 GOTO 970
850 PRINT "YOU ALREADY HAVE A TAIL."
860 GOTO 970
870 PRINT "6=LEG"
880 IF L=6 THEN 940
890 IF B=0 THEN 960
900 L=L+1
910 C=0
920 PRINT "YOU NOW HAVE";L;" LEGS."
930 GOTO 970
940 PRINT "YOU HAVE 6 FEET ALREADY."
950 GOTO 970
960 PRINT "YOU DO NOT HAVE A BODY."
970 X=INT(6*RND(0)+1)
971 PRINT
975 FOR DELAY=1 TO 2000:NEXT DELAY
980 PRINT "I ROLLED A";X;"."
990 ON X GOTO 1000,1080,1190,1300,1410,1520
1000 PRINT "1=BODY"
1010 IF P=1 THEN 1060
1020 PRINT "I NOW HAVE A BODY."
1030 C=0
1040 P=1
1050 GOTO 1630
1060 PRINT "I DO NOT NEED A BODY."
1070 GOTO 1630
1080 PRINT "2=NECK"
1090 IF Q=1 THEN 1150
1100 IF P=0 THEN 1170
1110 PRINT "I NOW HAVE A NECK."
1120 Q=1
1130 C=0
1140 GOTO 1630
1150 PRINT "I DO NOT NEED A NECK."
1160 GOTO 1630
1170 PRINT "I DO NOT HAVE A BODY."
1180 GOTO 1630
1190 PRINT "3=HEAD"
1200 IF Q=0 THEN 1260
1210 IF R=1 THEN 1280
1220 PRINT "I NEEDED A HEAD."
1230 R=1
1240 C=0
1250 GOTO 1630
1260 PRINT "I DO NOT HAVE A NECK."
1270 GOTO 1630
1280 PRINT "I DO NOT NEED A HEAD."
1290 GOTO 1630
1300 PRINT "4=FEELERS"
1310 IF R=0 THEN 1390
1320 IF S=2 THEN 1370
1330 PRINT "I GET A FEELER."
1340 S=S+1
1350 C=0
1360 GOTO 1630
1370 PRINT "I HAVE 2 FEELERS ALREADY."
1380 GOTO 1630
1390 PRINT "I DO NOT HAVE A HEAD."
1400 GOTO 1630
1410 PRINT "5=TAIL"
1420 IF P=0 THEN 1480
1430 IF U=1 THEN 1500
1440 PRINT "I NOW HAVE A TAIL."
1450 U=1
1460 C=0
1470 GOTO 1630
1480 PRINT "I DO NOT HAVE A BODY."
1490 GOTO 1630
1500 PRINT "I DO NOT NEED A TAIL."
1510 GOTO 1630
1520 PRINT "6=LEGS"
1530 IF V=6 THEN 1590
1540 IF P=0 THEN 1610
1550 V=V+1
1560 C=0
1570 PRINT "I NOW HAVE";V;" LEGS."
1580 GOTO 1630
1590 PRINT,"I HAVE 6 FEET."
1600 GOTO 1630
1610 PRINT "I DO NOT HAVE A BODY."
1620 GOTO 1630
1630 IF A=2 AND T=1 AND L=6 THEN 1650
1640 GOTO 1670
1650 PRINT "YOUR BUG IS FINISHED."
1660 Y=Y+1
1670 IF S=2 AND P=1 AND V=6 THEN 1690
1680 GOTO 1710
1690 PRINT "MY BUG IS FINISHED."
1700 Y=Y+2
1710 IF C=1 THEN 300
1720 PRINT "DO YOU WANT THE PICTURES";
1730 INPUT Z$
1740 IF Z$="NO" THEN 300
1750 PRINT "*****YOUR BUG*****"
1760 PRINT
1770 PRINT
1780 IF A=0 THEN 1860
1790 FOR Z=1 TO 4
1800 FOR X=1 TO A
1810 PRINT TAB(10);
1820 PRINT "A ";
1830 NEXT X
1840 PRINT
1850 NEXT Z
1860 IF H=0 THEN 1880
1870 GOSUB 2470
1880 IF N=0 THEN 1920
1890 FOR Z=1 TO 2
1900 PRINT "          N N"
1910 NEXT Z
1920 IF B=0 THEN 2000
1930 PRINT "     BBBBBBBBBBBB"
1940 FOR Z=1 TO 2
1950 PRINT "     B          B"
1960 NEXT Z
1970 IF T<>1 THEN 1990
1980 PRINT "TTTTTB          B"
1990 PRINT "     BBBBBBBBBBBB"
2000 IF L=0 THEN 2080
2010 FOR Z=1 TO 2
2020 PRINT TAB(5);
2030 FOR X=1 TO L
2040 PRINT " L";
2050 NEXT X
2060 PRINT
2070 NEXT Z
2080 FOR Z=1 TO 4
2090 PRINT
2100 NEXT Z
2110 PRINT "*****MY BUG*****"
2120 PRINT
2130 PRINT
2140 PRINT
2150 IF S=0 THEN 2230
2160 FOR Z=1 TO 4
2170 PRINT TAB(10);
2180 FOR X=1 TO S
2190 PRINT "F ";
2200 NEXT X
2210 PRINT
2220 NEXT Z
2230 IF R<>1 THEN 2250
2240 GOSUB 2470
2250 IF Q=0 THEN 2280
2260 PRINT "          N N"
2270 PRINT "          N N"
2280 IF P=0 THEN 2360
2290 PRINT "     BBBBBBBBBBBB"
2300 FOR Z=1 TO 2
2310 PRINT "     B          B"
2320 NEXT Z
2330 IF U<>1 THEN 2350
2340 PRINT "TTTTTB          B"
2350 PRINT "     BBBBBBBBBBBB"
2360 IF V=0 THEN 2450
2370 FOR Z=1 TO 2
2380 PRINT TAB(5);
2390 FOR X=1 TO V
2400 PRINT " L";
2410 NEXT X
2420 PRINT
2430 NEXT Z
2450 IF Y<>0 THEN 2540
2460 GOTO 300
2470 PRINT "        HHHHHHH"
2480 PRINT "        H     H"
2490 PRINT "        H O O H"
2500 PRINT "        H     H"
2510 PRINT "        H  V  H"
2520 PRINT "        HHHHHHH"
2530 RETURN
2540 PRINT "I HOPE YOU ENJOYED THE GAME, PLAY IT AGAIN SOON!!"
2550 END
