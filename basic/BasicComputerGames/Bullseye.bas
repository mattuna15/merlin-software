5 PRINT TAB(32);"BULLSEYE"
10 PRINT TAB(15);"CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY"
20 PRINT:PRINT:PRINT
30 PRINT "IN THIS GAME, UP TO 20 PLAYERS THROW DARTS AT A TARGET"
40 PRINT "WITH 10, 20, 30, AND 40 POINT ZONES.  THE OBJECTIVE IS"
50 PRINT "TO GET 200 POINTS.": PRINT
60 PRINT "THROW",TAB(20);"DESCRIPTION";TAB(45);"PROBABLE SCORE"
70 PRINT" 1";TAB(20);"FAST OVERARM";TAB(45);"BULLSEYE OR COMPLETE MISS"
80 PRINT" 2";TAB(20);"CONTROLLED OVERARM";TAB(45);"10, 20 OR 30 POINTS"
90 PRINT" 3";TAB(20);"UNDERARM";TAB(45);"ANYTHING":PRINT
100 DIM A$(20),S(20),W(10): M=0: R=0: FOR I=1 TO 20: S(I)=0: NEXT I
110 INPUT "HOW MANY PLAYERS";N: PRINT
120 FOR I=1 TO N
130 PRINT "NAME OF PLAYER #";I;:INPUT A$(I)
140 NEXT I
150 R=R+1: PRINT: PRINT "ROUND";R:PRINT "---------"
160 FOR I=1 TO N
170 PRINT: PRINT A$(I)"'S THROW";: INPUT T
180 IF T<0 OR T>3 THEN PRINT "INPUT 1, 2, OR 3!": GOTO 170
190 ON T GOTO 200, 210, 200
200 P1=.65: P2=.55: P3=.5: P4=.5: GOTO 230
210 P1=.99: P2=.77: P3=.43: P4=.01: GOTO 230
220 P1=.95: P2=.75: P3=.45: P4=.05
230 U=RND(0)
240 IF U>=P1 THEN PRINT "BULLSEYE!!  40 POINTS!":B=40: GOTO 290
250 IF U>=P2 THEN PRINT "30-POINT ZONE!":B=30: GOTO 290
260 IF U>=P3 THEN PRINT "20-POINT ZONE":B=20: GOTO 290
270 IF U>=P4 THEN PRINT "WHEW!  10 POINTS.":B=10: GOTO 290
280 PRINT "MISSED THE TARGET!  TOO BAD.": B=0
290 S(I)=S(I)+B: PRINT "TOTAL SCORE =";S(I): NEXT I
300 FOR I=1 TO N
310 IF S(I)>=200 THEN M=M+1: W(M)=I
320 NEXT I
330 IF M=0 THEN 150
340 PRINT: PRINT "WE HAVE A WINNER!!": PRINT
350 FOR I=1 TO M: PRINT A$(W(I));" SCORED";S(W(I));" POINTS.": NEXT I
360 PRINT: PRINT "THANKS FOR THE GAME.": END
