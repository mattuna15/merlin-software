DATA     EQU     $6000
PROGRAM  EQU     $4000

         ORG     DATA
LENGTH   DS.W    1               NUMBER OF DATA ELEMENTS
START    DS.L    1               ADDRESS OF DATA ELEMENTS
TOTAL    DS.W    1               SUM OF DATA ELEMENTS

         ORG     PROGRAM

PGM_5_1B MOVEA.L START,A0        INITIALIZE POINTER REGISTER
         MOVEQ   #0,D0           INITIALIZE SUM TO ZERO
         MOVE.W  LENGTH,D1       INITIALIZE ELEMENT COUNT

         BEQ.S   DONE            IF LENGTH = 0 THEN DONE

LOOP     ADD.W   (A0)+,D0        SUM NEXT ELEMENT
         SUBQ.W  #1,D1           UPDATE ELEMENT COUNT
         BNE     LOOP            IF COUNT NOT ZERO THEN GOTO LOOP

DONE     MOVE.W  D0,TOTAL        STORE SUMMATION

         RTS

         END     PGM_5_1B
