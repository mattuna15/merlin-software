5 PRINT TAB(33);"PIZZA"
10 PRINT TAB(15);"CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY"
15 PRINT: PRINT: PRINT
20 DIM S$(16),M$(4),A(10)
30 PRINT "PIZZA DELIVERY GAME": PRINT
50 INPUT "WHAT IS YOUR FIRST NAME";N$: PRINT
80 PRINT "HI, ";N$;".  IN THIS GAME YOU ARE TO TAKE ORDERS"
90 PRINT "FOR PIZZAS.  THEN YOU ARE TO TELL A DELIVERY BOY"
100 PRINT "WHERE TO DELIVER THE ORDERED PIZZAS.": PRINT: PRINT
140 FOR I=1 TO 16
150 READ S$(I)
160 NEXT I
170 FOR I=1 TO 4
180 READ M$(I)
190 NEXT I
200 DATA "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O"
210 DATA "P","1","2","3","4"
230 PRINT "MAP OF THE CITY OF HYATTSVILLE": PRINT
250 PRINT " -----1-----2-----3-----4-----"
260 K=4
270 FOR I=1 TO 4
280 PRINT "-": PRINT "-": PRINT"-": PRINT "-"
320 PRINT M$(K);
330 S1=16-4*I+1
340 PRINT "     ";S$(S1);"     ";S$(S1+1);"     ";S$(S1+2);"     ";
350 PRINT S$(S1+3);"     ";M$(K)
380 K=K-1
390 NEXT I
400 PRINT "-": PRINT "-": PRINT "-": PRINT "-"
440 PRINT " -----1-----2-----3-----4-----": PRINT
460 PRINT "THE OUTPUT IS A MAP OF THE HOMES WHERE"
470 PRINT "YOU ARE TO SEND PIZZAS.": PRINT
490 PRINT "YOUR JOB IS TO GIVE A TRUCK DRIVER"
500 PRINT "THE LOCATION OR COORDINATES OF THE"
510 PRINT "HOME ORDERING THE PIZZA.": PRINT
520 INPUT "DO YOU NEED MORE DIRECTIONS";A$
530 IF A$="YES" THEN 590
540 IF A$="NO" THEN 750
550 PRINT "'YES' OR 'NO' PLEASE, NOW THEN,": GOTO 520
590 PRINT: PRINT "SOMEBODY WILL ASK FOR A PIZZA TO BE"
600 PRINT "DELIVERED.  THEN A DELIVERY BOY WILL"
610 PRINT "ASK YOU FOR THE LOCATION.":PRINT "     EXAMPLE:"
620 PRINT "THIS IS J.  PLEASE SEND A PIZZA."
640 PRINT "DRIVER TO ";N$;".  WHERE DOES J LIVE?"
650 PRINT "YOUR ANSWER WOULD BE 2,3": PRINT
660 INPUT "UNDERSTAND";A$
670 IF A$="YES" THEN 690
680 PRINT "THIS JOB IS DEFINITELY TOO DIFFICULT FOR YOU. THANKS ANYWAY"
685 GOTO 999
690 PRINT "GOOD.  YOU ARE NOW READY TO START TAKING ORDERS.": PRINT
700 PRINT "GOOD LUCK!!": PRINT
750 FOR I=1 TO 5
760 S=INT(RND(0)*16+1): PRINT
770 PRINT "HELLO ";N$;"'S PIZZA.  THIS IS ";S$(S);".";
775 PRINT "  PLEASE SEND A PIZZA."
780 PRINT "  DRIVER TO ";N$;":  WHERE DOES ";S$(S);" LIVE";
790 INPUT A(1),A(2)
870 T=A(1)+(A(2)-1)*4
880 IF T=S THEN 920
890 PRINT "THIS IS ";S$(T);".  I DID NOT ORDER A PIZZA."
900 PRINT "I LIVE AT ";A(1);",";A(2)
910 GOTO 780
920 PRINT "HELLO "N$;".  THIS IS ";S$(S);", THANKS FOR THE PIZZA."
930 NEXT I
940 PRINT: INPUT "DO YOU WANT TO DELIVER MORE PIZZAS";A$
960 IF A$="YES" THEN 750
970 PRINT: PRINT "O.K. ";N$;", SEE YOU LATER!":PRINT
999 END