
        #include "../gd2-lib/GD-c.h"
        #include "../gd2-lib/GD2.h"

        #include <stdio.h>

        XDEF main

*****************
* vars
**************
points ds.l  1
shape_x ds.w 1
shape_y ds.w 1
shape_scale ds.w 1
level ds.l 1


main:

        pea welcome
        jsr printf
        addq.l #4,sp

        *************************************************
        * start

        jsr game_start

        *************************************************
        * loop

        move.l #1,level

game_loop:

        move.w #1024,shape_scale
        move.w #100,shape_x
        move.w #100,shape_y

        move.l level,d4

        jsr ast_start

        jsr gd_swap

        jmp end


*************************************************
** draw 4 asteroids


ast_start:
        lea.l rocks,a3 * pointer

ast_loop:
        moveq #12,d2 * 13 points on a rock.

        sub.l d3,d3
        move.w shape_x,d3
        swap d3
        move.w shape_y,d3

        jsr shape_start

        add.w #100,shape_x
        add.w #100,shape_y

        dbra d4,ast_loop

        rts

*************************************************
* Draw shapes.
* d2 - number of points
* d3 - starting coord - x,y
* 

shape_start:

        move.l d3,points
        pea points
        jsr beginLine
        addq.l #4,sp


draw_shape:
        move.w shape_scale,d3
        move.b (a3)+,d3
        swap d3
        move.w (a3)+,d3

        move.l d3,points
        pea points
        jsr addPoint
        addq.l #4,sp

        dbra d2,draw_shape

        rts

end:
        jmp $e00bc0

welcome:
        dc.b 13,10,'Asteroid Demo',13,10,0

rocks:
    rock1: 
        dc.b 0,0,4,7,4,4,7,4,-4,7,-2,-4,7,2,-4,8,-6,-4,8,-6,0,7,-4,4,7,0,8,7,4,4,7,4,-4,0,0,0,0,0,0
    rock2: 
        dc.b 0,4,2,7,4,2,7,-4,4,7,-4,-2,7,-4,2,7,-4,-4,7,2,-4,7,-2,-4,7,4,-4,7,2,2,8,6,-2,8,4,6,7,-4,4
    rock3: 
        dc.b 0,-4,0,7,-4,-2,7,4,-6,7,4,6,7,0,-6,7,4,0,7,4,6,7,0,4,7,-4,6,7,-6,0,7,-6,-6,7,4,-2,0,0,0
    rock4: 
        dc.b 0,2,0,7,6,2,6,0,2,7,-6,4,7,-6,0,6,2,-4,7,-6,0,7,0,-6,7,4,-6,7,6,2,6,2,-2,6,4,4,7,-6,4


  
  




