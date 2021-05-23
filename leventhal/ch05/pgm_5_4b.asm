DATA     EQU     $6000
PROGRAM  EQU     $4000

         ORG     DATA
LENGTH   DS.W    1               NUMBER OF DATA ELEMENTS
START    DS.L    1               ADDRESS OF DATA ELEMENTS
MAXNUM   DS.W    1               MAXIMUM NUMBER IN SERIES

         ORG     PROGRAM

PGM_5_4B MOVEA.L START,A0        INITIALIZE POINTER REGISTER
         MOVEQ   #0,D0           MAX := 0
         MOVE.W  LENGTH,D1       INITIALIZE ELEMENT COUNT

         BEQ.S   DONE            IF LENGTH = 0 THEN DONE

LOOP     CMP.W   (A0)+,D0        COMPARE DATA ELEMENT WITH MAX
         BCC.S   LOOPTEST        IF MAX > OR = TEMP GOTO LOOPTEST

         MOVE.W  -2(A0),D0       ...ELSE NEW MAX, MAX := TEMP

LOOPTEST SUBQ.W  #1,D1             UPDATE ELEMENT COUNT
         BNE     LOOP            IF COUNT NOT ZERO THEN GOTO LOOP

DONE     MOVE.W  D0,MAXNUM       STORE MAXIMUM NUMBER IN SERIES

         RTS

         END     PGM_5_4B
