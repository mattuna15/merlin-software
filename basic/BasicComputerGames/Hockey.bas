2 PRINT TAB(33);"HOCKEY"
4 PRINT TAB(15);"CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY"
6 PRINT:PRINT:PRINT
10 REM ROBERT PUOPOLO ALG. 1 140 MCCOWAN 6/7/73 HOCKEY
30 LET X=1
40 PRINT:PRINT:PRINT
50 PRINT "WOULD YOU LIKE THE INSTRUCTIONS";:INPUT C$
55 PRINT
60 IF C$="NO" THEN 90
65 IF C$="YES" THEN 80
70 PRINT "ANSWER YES OR NO!!":GOTO 50
80 GOTO 1720
90 DIM A$(7),B$(7),H(20),T(5),T1(5),T2(5),T3(5)
100 PRINT "ENTER THE TWO TEAMS";:INPUT A$(7),B$(7)
105 PRINT
110 PRINT "ENTER THE NUMBER OF MINUTES IN A GAME";:INPUT T6
115 PRINT
120 IF T6<1 THEN 110:PRINT
130 PRINT "WOULD THE " A$(7) " COACH ENTER HIS TEAM"
135 PRINT
140 FOR I=1 TO 6:PRINT "PLAYER"I;CHR$(8);:INPUT A$(I):NEXT I:PRINT
150 PRINT "WOULD THE " B$(7) " COACH DO THE SAME"
155 PRINT
160 FOR T=1 TO 6:PRINT "PLAYER"T;:INPUT B$(T):NEXT T:PRINT
170 PRINT "INPUT THE REFEREE FOR THIS GAME";:INPUT R$
180 PRINT:PRINT TAB(10);A$(7) " STARTING LINEUP"
190 FOR T=1 TO 6:PRINT A$(T):NEXT T
200 PRINT:PRINT TAB(10);B$(7)" STARTING LINEUP"
210 FOR T=1 TO 6:PRINT B$(T):NEXT T:PRINT
220 PRINT "WE'RE READY FOR TONIGHTS OPENING FACE-OFF."
230 PRINT R$ " WILL DROP THE PUCK BETWEEN " A$(2) " AND " B$(2)
240 FOR L=1 TO T6:IF L=1 THEN 260
250 PRINT "AND WE'RE READY FOR THE FACE-OFF"
260 C=INT(2*RND(0))+1:ON C GOTO 270,280
270 PRINT A$(7) " HAS CONTROL OF THE PUCK":GOTO 290
280 PRINT B$(7) " HAS CONTROL."
290 PRINT "PASS";:INPUT P:FOR N=1 TO 3:H(N)=0:NEXT N
300 IF P<0 THEN 290
305 IF P>3 THEN 290
310 FOR J=1 TO (P+2)
320 H(J)=INT(5*RND(0))+1
330 NEXT J:IF H(J-1)=H(J-2) THEN 310
331 IF P+2<3 THEN 350
335 IF H(J-1)=H(J-3) THEN 310
340 IF H(J-2)=H(J-3) THEN 310
350 IF P=0 THEN 360
355 GOTO 490
360 INPUT "SHOT";S:IF S<1 THEN 360
365 IF S>4 THEN 360
370 ON C GOTO 380,480
380 PRINT A$(H(J-1));:G=H(J-1):G1=0:G2=0
390 ON S GOTO 400,420,440,460
400 PRINT " LET'S A BOOMER GO FROM THE RED LINE!!"
410 Z=10:GOTO 890
420 PRINT " FLIPS A WRISTSHOT DOWN THE ICE"
440 PRINT " BACKHANDS ONE IN ON THE GOALTENDER"
450 Z=25:GOTO 890
460 PRINT " SNAPS A LONG FLIP SHOT"
470 Z=17:GOTO 890
480 PRINT B$(H(J-1));:G1=0:G2=0:G=H(J-1):GOTO 390
490 ON C GOTO 500,640
500 ON P GOTO 510,540,570
510 PRINT A$(H(J-2)) " LEADS " A$(H(J-1)) " WITH A PERFECT PASS."
520 PRINT A$(H(J-1)) " CUTTING IN!!!"
530 G=H(J-1):G1=H(J-2):G2=0:Z1=3:GOTO 770
540 PRINT A$(H(J-2)) " GIVES TO A STREAKING " A$(H(J-1))
550 PRINT A$(H(J-3)) " COMES DOWN ON " B$(5) " AND " B$(4)
560 G=H(J-3):G1=H(J-1):G2=H(J-2):Z1=2:GOTO 770
570 PRINT "OH MY GOD!! A ' 4 ON 2 ' SITUATION"
580 PRINT A$(H(J-3)) " LEADS " A$(H(J-2))
590 PRINT A$(H(J-2)) " IS WHEEELING THROUGH CENTER."
600 PRINT A$(H(J-2)) " GIVES AND GOES WITH " A$(H(J-1))
610 PRINT "PRETTY PASSING!"
620 PRINT A$(H(J-1)) " DROPS IT TO " A$(H(J-4))
630 G=H(J-4):G1=J(J-1):G2=H(J-2):Z1=1:GOTO 770
640 ON P GOTO 650,670,720
650 PRINT B$(H(J-1)) " HITS " B$(H(J-2)) " FLYING DOWN THE LEFT SIDE"
660 G=H(J-2):G1=H(J-1):G2=0:Z1=3:GOTO 770
670 PRINT "IT'S A ' 3 ON 2 '!"
680 PRINT "ONLY " A$(4) " AND " A$(5) " ARE BACK."
690 PRINT B$(H(J-2)) " GIVES OFF TO " B$(H(J-1))
700 PRINT B$(H(J-1)) " DROPS TO " B$(H(J-3))
710 G=H(J-3):G1=H(J-1):G2=H(J-2):Z1=2:GOTO 770
720 PRINT " A ' 3 ON 2 ' WITH A ' TRAILER '!"
730 PRINT B$(H(J-4)) " GIVES TO " B$(H(J-2)) " WHO SHUFFLES IT OFF TO"
740 PRINT B$(H(J-1)) " WHO FIRES A WING TO WING PASS TO "
750 PRINT B$(H(J-3)) " AS HE CUTS IN ALONE!!"
760 G=H(J-3):G1=H(J-1):G2=H(J-2):Z1=1:GOTO 770
770 PRINT "SHOT";:INPUT S:IF S>4 THEN 770:IF S<1 THEN 770
780 ON C GOTO 790,880
790 PRINT A$(G);:ON S GOTO 800,820,840,860
800 PRINT " LET'S A BIG SLAP SHOT GO!!"
810 Z=4:Z=Z+Z1:GOTO 890
820 PRINT " RIPS A WRIST SHOT OFF"
830 Z=2:Z=Z+Z1:GOTO 890
840 PRINT " GETS A BACKHAND OFF"
850 Z=3:Z=Z+Z1:GOTO 890
860 PRINT " SNAPS OFF A SNAP SHOT"
870 Z=2:Z=Z+Z1:GOTO 890
880 PRINT B$(G);:ON S GOTO 800,820,840,860
890 PRINT "AREA";:INPUT A:IF A<1 THEN 890
895 IF A>4 THEN 890
900 ON C GOTO 910,920
910 S2=S2+1:GOTO 930
920 S3=S3+1
930 A1=INT(4*RND(0))+1:IF A<>A1 THEN 1200
940 H(20)=INT(100*RND(0))+1
950 IF INT(H(20)/Z)=H(20)/Z THEN 1160
960 ON C GOTO 970,980
970 PRINT "GOAL " A$(7):H(9)=H(9)+1:GOTO 990
980 PRINT "SCORE " B$(7):H(8)=H(8)+1
990 FOR B1=1 TO 25:PRINT CHR$(7);:NEXT B1:PRINT
1000 PRINT "SCORE: ";:IF H(8)>H(9) THEN 1020
1010 PRINT A$(7)":";H(9),B$(7)":";H(8):GOTO 1030
1020 PRINT B$(7)":";H(8),A$(7)":";H(9)
1030 ON C GOTO 1040,1100
1040 PRINT "GOAL SCORED BY: " A$(G):IF G1=0 THEN 1070
1050 IF G2=0 THEN 1080
1060 PRINT " ASSISTED BY: " A$(G1) " AND " A$(G2):GOTO 1090
1070 PRINT " UNASSISTED.":GOTO 1090
1080 PRINT " ASSISTED BY: " A$(G1)
1090 T(G)=T(G)+1:T1(G1)=T1(G1)+1:T1(G2)=T1(G2)+1:GOTO 1540
1100 PRINT "GOAL SCORED BY: " B$(G);
1110 IF G1=0 THEN 1130
1115 IF G2=0 THEN 1140
1120 PRINT " ASSISTED BY: " B$(G1) " AND " B$(G2):GOTO 1150
1130 PRINT " UNASSISTED":GOTO 1150
1140 PRINT " ASSISTED BY: " B$(G1):GOTO 1150
1150 T2(G)=T2(G)+1:T3(G1)=T3(G1)+1:T3(G2)=T3(G2)+1:GOTO 1540
1160 A2=INT(100*RND(0))+1:IF INT(A2/4)=A2/4 THEN 1170
1165 GOTO 1200
1170 ON C GOTO 1180,1190
1180 PRINT "SAVE " B$(6) " --  REBOUND":GOTO 940
1190 PRINT "SAVE " A$(6) " --  FOLLOW UP":GOTO 940
1200 S1=INT(6*RND(0))+1
1210 ON C GOTO 1220,1380
1220 ON S1 GOTO 1230,1260,1290,1300,1330,1350
1230 PRINT "KICK SAVE AND A BEAUTY BY " B$(6)
1240 PRINT "CLEARED OUT BY " B$(3)
1250 GOTO 260
1260 PRINT "WHAT A SPECTACULAR GLOVE SAVE BY " B$(6)
1270 PRINT "AND " B$(6) " GOLFS IT INTO THE CROWD"
1280 GOTO 1540
1290 PRINT "SKATE SAVE ON A LOW STEAMER BY " B$(6):GOTO 260
1300 PRINT "PAD SAVE BY " B$(6) " OFF THE STICK"
1310 PRINT "OF "A$(G) " AND " B$(6) " COVERS UP"
1320 GOTO 1540
1330 PRINT "WHISTLES ONE OVER THE HEAD OF " B$(6)
1340 GOTO 260
1350 PRINT B$(6) " MAKES A FACE SAVE!! AND HE IS HURT"
1360 PRINT "THE DEFENSEMAN " B$(5) " COVERS UP FOR HIM"
1370 GOTO 1540
1380 ON S1 GOTO 1390,1410,1440,1470,1490,1520
1390 PRINT "STICK SAVE BY " A$(6)
1400 PRINT "AND CLEARED OUT BY " A$(4):GOTO 260
1410 PRINT "OH MY GOD!! " B$(G) " RATTLES ONE OFF THE POST"
1420 PRINT "TO THE RIGHT OF " A$(6) " AND " A$(6) " COVERS ";
1430 PRINT "ON THE LOOSE PUCK!":GOTO 1540
1440 PRINT "SKATE SAVE BY " A$(6)
1450 PRINT A$(6) " WHACKS THE LOOSE PUCK INTO THE STANDS"
1460 GOTO 1540
1470 PRINT "STICK SAVE BY " A$(6) " AND HE CLEARS IT OUT HIMSELF"
1480 GOTO 260
1490 PRINT "KICKED OUT BY " A$(6)
1500 PRINT "AND IT REBOUNDS ALL THE WAY TO CENTER ICE"
1510 GOTO 260
1520 PRINT "GLOVE SAVE " A$(6) " AND HE HANGS ON"
1530 GOTO 1540
1540 NEXT L:FOR N=1 TO 30:PRINT CHR$(7);:NEXT N:PRINT "THAT'S THE SIREN"
1550 PRINT:PRINT TAB(15);"FINAL SCORE:"
1560 IF H(8)>H(9) THEN 1580
1570 PRINT A$(7)":";H(9),B$(7)":";H(8):GOTO 1590
1580 PRINT B$(7)":";H(8),A$(7)":";H(9)
1590 PRINT: PRINT TAB(10);"SCORING SUMMARY":PRINT
1600 PRINT TAB(25);A$(7)
1610 PRINT TAB(5);"NAME";TAB(20);"GOALS";TAB(35);"ASSISTS"
1620 PRINT TAB(5);"----";TAB(20);"-----";TAB(35);"-------"
1630 FOR I=1 TO 5:PRINT TAB(5);A$(I);TAB(21);T(I);TAB(36);T1(I)
1640 NEXT I:PRINT
1650 PRINT TAB(25);B$(7)
1660 PRINT TAB(5);"NAME";TAB(20);"GOALS";TAB(35);"ASSISTS"
1670 PRINT TAB(5);"----";TAB(20);"-----";TAB(35);"-------"
1680 FOR T=1 TO 5:PRINT TAB(5);B$(T);TAB(21);T2(T);TAB(36);T3(T)
1690 NEXT T:PRINT
1700 PRINT "SHOTS ON NET":PRINT A$(7)":";S2:PRINT B$(7)":";S3
1710 END
1720 PRINT: PRINT "THIS IS A SIMULATED HOCKEY GAME."
1730 PRINT "QUESTION     RESPONSE"
1740 PRINT "PASS         TYPE IN THE NUMBER OF PASSES YOU WOULD"
1750 PRINT "             LIKE TO MAKE, FROM 0 TO 3."
1760 PRINT "SHOT         TYPE THE NUMBER CORRESPONDING TO THE SHOT"
1770 PRINT "             YOU WANT TO MAKE.  ENTER:"
1780 PRINT "             1 FOR A SLAPSHOT"
1790 PRINT "             2 FOR A WRISTSHOT"
1800 PRINT "             3 FOR A BACKHAND"
1810 PRINT "             4 FOR A SNAP SHOT"
1820 PRINT "AREA         TYPE IN THE NUMBER CORRESPONDING TO"
1830 PRINT "             THE AREA YOU ARE AIMING AT.  ENTER:"
1840 PRINT "             1 FOR UPPER LEFT HAND CORNER"
1850 PRINT "             2 FOR UPPER RIGHT HAND CORNER"
1860 PRINT "             3 FOR LOWER LEFT HAND CORNER"
1870 PRINT "             4 FOR LOWER RIGHT HAND CORNER"
1880 PRINT
1890 PRINT "AT THE START OF THE GAME, YOU WILL BE ASKED FOR THE NAMES"
1900 PRINT "OF YOUR PLAYERS.  THEY ARE ENTERED IN THE ORDER: "
1910 PRINT "LEFT WING, CENTER, RIGHT WING, LEFT DEFENSE,"
1920 PRINT "RIGHT DEFENSE, GOALKEEPER.  ANY OTHER INPUT REQUIRED WILL"
1930 PRINT "HAVE EXPLANATORY INSTRUCTIONS."
1940 GOTO 90
1950 END
