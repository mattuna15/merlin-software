DATA     EQU     $6000
PROGRAM  EQU     $4000

         ORG     DATA
START1   DS.L    1               ADDRESS OF FIRST STRING
START2   DS.L    1               ADDRESS OF SECOND STRING
MATCH    DS.W    1               MATCH FLAG

         ORG     PROGRAM

PGM_6_5A MOVEA.L START1,A0       POINTER TO FIRST STRING
         MOVEA.L START2,A1       POINTER TO SECOND STRING
         MOVEQ   #-1,D1          ASSUME NO MATCH
         MOVEQ   #0,D0           LENGHT COUNTER := 0
         MOVE.B  (A0)+,D0        INITIALIZE LENGTH COUNTER
         CMP.B   (A1)+,D0        STRING LENGTH EQUAL?
         BNE.S   DONE            IF NOT = THEN NO MATCH

         TST.B   D0              STRING LENGTH = 0?
         BEQ.S   SAME            IF = 0 THEN STRINGS MATCH

         SUBQ.W  #1,D0           ADJUST COUNTER FOR DBNE

LOOP     CMPM.B  (A0)+,(A1)+     COMPARE CURRENT STRING ELEMENTS
         DBNE    D0,LOOP         IF MATCH AND NOT END OF STRING-CONT

         BNE.S   DONE            IF NO MATCH AND END THEN DONE

SAME     NOT.W   D1              STRING MATCH

DONE     MOVE.W  D1,MATCH        SAVE MATCH STATE

         RTS

         END     PGM_6_5A
