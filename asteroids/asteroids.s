
        #include "../gd2-lib/GD-c.h"
        #include "../gd2-lib/GD2.h"

        #include <stdio.h>

        XDEF main

*****************
* vars generic
**************
points ds.b  1
shape_scale ds.l 1
level ds.l 1
random ds.w 1
velocity ds.w 1
heading ds.w 1


*******************************
* ship
*******************************

ship_x ds.w 1
ship_y ds.w 1
ship_angle ds.w 1
ship_velocity ds.w 1
ship_old_heading ds.w 1
ship_old_velocity ds.w 1
ship_heading ds.w 1
ship_thrust_count ds.b 1
ship_firing_count ds.b 1
ship_lives ds.b 1
ship_scale ds.w 1
ship_hs_count ds.b 1

*******************************
* lasers
*******************************

ship_laser_count ds.b 1

ship_laser_x ds.w 4
ship_laser_y ds.w 4
ship_laser_angle ds.w 4
ship_laser_velocity ds.w 4
ship_laser_age ds.b 4

ufo_laser_count ds.b 1

ufo_laser_x ds.w 4
ufo_laser_y ds.w 4
ufo_laser_angle ds.w 4
ufo_laser_velocity ds.w 4
ufo_laser_age ds.b 4

*******************************
* asteroids array
*******************************

asteroids_count ds.b 1
ast_velocity ds.w 20
ast_heading ds.w 20
ast_x ds.w 20
ast_y ds.w 20
ast_shape ds.b 20
ast_scale ds.l 20
ast_dead ds.b 20

*******************************
* ufo array
*******************************

ufo_x ds.w 1
ufo_y ds.w 1
ufo_velocity ds.w 1
ufo_heading ds.w 1
ufo_thrust ds.b 1
ufo_firing_count ds.b 1
ufo_lives ds.b 1
ufo_scale ds.l 1
ufo_active ds.b 1

rand_max ds.w 1

main:

        pea welcome
        jsr printf
        addq.l #4,sp

        *************************************************
        * start

        jsr game_start

        *************************************************
        * initialise randomiser

        jsr gd_seed

        *************************************************
        * start

        move.l #4,level

***********************************
** ship initial setting
*
        move.w #500,ship_x
        move.w #100,ship_y
        move.w #256,ship_scale
        clr.b  ship_firing_count
        move.w #0,ship_angle
        move.w #$8000,ship_heading
        move.w #0,ship_velocity
        move.b #3,ship_lives
        move.b #3,ship_hs_count

****************************
** ufo setting
*
        clr.w ufo_x
        jsr random_y
        move.w d0,ufo_y
        move.l #256,ufo_scale
        move.w #3,ufo_velocity

*********************************************
** asteroid settings randomise start locations
*

        move.l level,d4
        lea.l ast_velocity,a4
        lea.l ast_heading,a5
astspeed:
        move.w #10,rand_max
        pea rand_max
        jsr gd_rand
        addq #4,sp

        cmp.w #0,d0
        bne rand_head

        move.w #2,d0

rand_head:
        move.w d0,(a4)+
        move.w #65535,rand_max
        pea rand_max
        jsr gd_rand
        addq #4,sp
        move.w d0,(a5)+

        dbra d4,astspeed

        move.l level,d4
        lea.l ast_x,a4
        lea.l ast_y,a5
randomxy:
        move.w #1280,rand_max
        pea rand_max
        jsr gd_rand
        addq #4,sp
        move.w d0,(a4)+

        move.w #720,rand_max
        pea rand_max
        jsr gd_rand
        addq #4,sp
        move.w d0,(a5)+
        
        dbra d4,randomxy

*************************************************
** loop
*

game_loop:

        jsr gd_clear

*************************************************
* reduce thrust count

        cmp.b #0,ship_thrust_count
        beq keyb

        sub.b #1,ship_thrust_count

*************************************************
** get keyboard press
*buttons:   * left, right, fire, thrust hyperspace quit - , . z x space q      
*  dc.b $2C,$2E,$5A,$58,$20,$51
keyb:

        btst.b #0,$f20003
        bne.s getKeyb

        jmp draw_shapes

getKeyb:
        move.b $f20001,d0 * return key ascii value into d0
        lea.l buttons,a0
         
cmpbuttons:

        cmp.b (a0)+,d0 * check for x and then quit
        beq left

        cmp.b (a0)+,d0 * check for x and then quit
        beq right

        cmp.b (a0)+,d0 * check for x and then quit
        beq fire

        cmp.b (a0)+,d0 * check for x and then quit
        beq thrust

        cmp.b (a0)+,d0 * check for x and then quit
        beq hyperspace

        cmp.b (a0),d0 * check for x and then quit
        beq end

        bra draw_shapes

left:
        sub.w #1,ship_angle

        cmp.w #0,ship_angle
        bge set_heading

        move.w #7,ship_angle
        bra set_heading

right:

        add.w #1,ship_angle

        cmp.w #7,ship_angle
        ble set_heading

        move.w #0,ship_angle

set_heading: *  only do this if we are boosting - convert to furmans for the polar setting,

        cmp.b #0,ship_thrust_count
        beq draw_shapes

        lea ship_heading,a0
        lea furmans,a1

        move.w (a0),ship_old_heading

        move.w ship_angle,d0
        mulu #2,d0
        adda d0,a1
        move.w (a1),(a0)

        bra draw_shapes

fire:
        addq #1,ship_firing_count
        cmp.b #4,ship_firing_count
        blt draw_shapes

        move.w #3,ship_firing_count
        bra draw_shapes

thrust:     * make sure that the heading is reset at thrust press

        lea ship_velocity,a0
        move.w (a0),ship_old_velocity
        sub.w #1,ship_old_velocity

        cmp.b #0,ship_old_velocity
        beq set_thrust
        move.w #0,ship_velocity

set_thrust:
        cmp.b #0,ship_thrust_count   * already thrust
        bgt set_heading

        move.b #3,ship_thrust_count *reset
        add.w #1,ship_velocity *speed up

        cmp.w #5,ship_velocity *max
        ble set_heading

        move.w #5,ship_velocity * no more
        bra set_heading

hyperspace:

        cmp.b #0,ship_hs_count
        beq draw_shapes

        sub.b #1,ship_hs_count
        move.w #1280,rand_max
        pea rand_max
        jsr gd_rand
        addq #4,sp
        move.w d0,ship_x

        move.w #720,rand_max
        pea rand_max
        jsr gd_rand
        addq #4,sp
        move.w d0,ship_y

check_collision:

************************
* draw ship/asteroids/ufo
*
draw_shapes:
        jsr draw_vectors

****************************
* swap frame buffer for EVE double buffer

        jsr gd_swap

*******************
** back to start        

        bra game_loop


*************************************************
** back to mon

end:
        jmp $e00bc0

*************************************************
** draw ship 

draw_vectors:

        pea ship_old_heading
        pea ship_old_velocity
        pea ship_heading
        pea ship_velocity
        jsr polar_ship
        add #16,sp

        add.w d0,ship_x

        cmp.w #0,ship_x
        bge chks_max_x

        move.w #1280,ship_x

chks_max_x:
        cmp.w #1280,ship_x
        ble chks_min_y

        move.w #0,ship_x

chks_min_y:

        swap d0   * x/y is stored in d0 from GD library

        add.w d0,ship_y

        cmp.w #0,ship_y
        bge set_ship_y

        move.w #720,ship_y

set_ship_y:        
        cmp.w #720,ship_y
        ble draw_ship

        move.w #0,ship_y

draw_ship:

** check for active thrust

        cmp.b #0,ship_thrust_count
        beq no_thrust

**** ship with rocket

        move.w ship_angle,d0
        mulu #30,d0
        lea.l ship_t,a3 * pointer
        adda d0,a3

        moveq #9,d2 * 10 points on a ship with thrust
        bra set_ship_points

no_thrust:    * no rocket

        move.w ship_angle,d0
        mulu #18,d0
        lea.l ship,a3 * pointer
        adda d0,a3

        moveq #5,d2 * 6 points on a ship.

set_ship_points:

        move.w ship_x,d3
        swap d3
        move.w ship_y,d3

        move.l #256,shape_scale

        jsr shape_start

*************************************************
** draw asteroids


ast_start:
        lea.l rocks,a3 * pointer
        move.l level,d4

        move.l #1024,shape_scale

        lea.l ast_heading,a1
        lea.l ast_velocity,a2
        lea.l ast_x,a4
        lea.l ast_y,a5

ast_loop:
        lea.l rocks,a3 * pointer
        moveq #12,d2 * 13 points on a rock.

        move.w (a1)+,heading
        move.w (a2)+,velocity

        pea heading
        pea velocity
        jsr polar
        addq #8,sp

        add.w d0,(a4)
        cmp.w #0,(a4)
        bge chk_max_x

        move.w #1280,(a4)
        bra.s chk_ast_y

chk_max_x:        
        cmp.w #1280,(a4)
        ble chk_ast_y

        move.w #0,(a4)

chk_ast_y:
        swap d0
        add.w d0,(a5)

        cmp.w #0,(a5)
        bge chk_max_y

        move.w #720,(a5)
        bra.s draw_ast

chk_max_y:
        cmp.w #720,(a5)
        ble draw_ast

        move.w #0,(a5)

draw_ast:

        move.w (a4)+,d3
        swap d3
        move.w (a5)+,d3

        jsr shape_start

        dbra d4,ast_loop

*************************************************
** draw ufo

ufo_start:

        add #5,ufo_x
        cmp.w #1280,ufo_x
        ble draw_ufo

        move.w #0,ufo_x
        jsr random_y

draw_ufo:
        move.l ufo_scale,shape_scale
        lea.l ufo,a3 * pointer

        moveq #11,d2 * 12 points on a ufo.

        move.w ufo_x,d3
        swap d3
        move.w ufo_y,d3

        jsr shape_start

        rts

random_y:
        move.w #720,rand_max
        pea rand_max
        jsr gd_rand
        addq #4,sp

        move.w d0,ufo_y

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

        move.l shape_scale,d3
        move.b (a3)+,d3
        swap d3
        move.w (a3)+,d3

        move.l d3,points
        pea points
        jsr addPoint
        addq.l #4,sp

        dbra d2,draw_shape

        rts


********************************
* Strings

welcome:
        dc.b 13,10,'Asteroid Demo',13,10,0

number:
        dc.b 13,10,'Heading: ',37,'X',13,10,0

************************************
* Shape vectors
*

* 6 points for a ship with no thrust
ship:
        dc.b 0,4,6,7,-8,0,7,-4,4,7,8,-24,7,8,24,7,-4,-4
        dc.b 0,-1,7,7,-6,-6,7,-6,0,7,23,-11,7,-11,23,7,0,-6
        dc.b 0,-6,4,7,0,-8,7,-4,-4,7,24,8,7,-24,8,7,4,-4
        dc.b 0,-7,-1,7,6,-6,7,0,-6,7,11,23,7,-23,-11,7,6,0
        dc.b 0,-4,-6,7,8,0,7,4,-4,7,-8,24,7,-8,-24,7,4,4
        dc.b 0,1,-7,7,6,6,7,6,0,7,-23,11,7,11,-23,7,0,6
        dc.b 0,6,-4,7,0,8,7,4,4,7,-24,-8,7,24,-8,7,-4,4
        dc.b 0,7,1,7,-6,6,7,0,6,7,-11,-23,7,23,11,7,-6,0

* 10 points for a ship with thrust
ship_t:
        dc.b 0,4,6,12,-4,8,12,-4,-8,12,4,8,12,4,-8,7,-8,0,7,-4,4,7,8,-24,7,8,24,7,-4,-4
        dc.b 0,-1,7,12,-8,3,12,3,-8,12,-3,8,12,8,-3,7,-6,-6,7,-6,0,7,23,-11,7,-11,23,7,0,-6
        dc.b 0,-6,4,12,-8,-4,12,8,-4,12,-8,4,12,8,4,7,0,-8,7,-4,-4,7,24,8,7,-24,8,7,4,-4
        dc.b 0,-7,-1,12,-3,-8,12,8,3,12,-8,-3,12,3,8,7,6,-6,7,0,-6,7,11,23,7,-23,-11,7,6,0
        dc.b 0,-4,-6,12,4,-8,12,4,8,12,-4,-8,12,-4,8,7,8,0,7,4,-4,7,-8,24,7,-8,-24,7,4,4
        dc.b 0,1,-7,12,8,-3,12,-3,8,12,3,-8,12,-8,3,7,6,6,7,6,0,7,-23,11,7,11,-23,7,0,6
        dc.b 0,6,-4,12,8,4,12,-8,4,12,8,-4,12,-8,-4,7,0,8,7,4,4,7,-24,-8,7,24,-8,7,-4,4
        dc.b 0,7,1,12,3,8,12,-8,-3,12,8,3,12,-3,-8,7,-6,6,7,0,6,7,-11,-23,7,23,11,7,-6,0

* 13 points per rock
rocks:
    rock1: 
        dc.b 0,0,-4,7,4,-4,7,4,4,7,-2,4,7,2,4,8,-6,4,8,-6,0,7,-4,-4,7,0,-8,7,4,-4,7,4,4,0,0,0,0,0,0
    rock2: 
        dc.b 0,4,-2,7,4,-2,7,-4,-4,7,-4,2,7,-4,-2,7,-4,4,7,2,4,7,-2,4,7,4,4,7,2,-2,8,6,2,8,4,-6,7,-4,-4
    rock3: 
        dc.b 0,-4,0,7,-4,2,7,4,6,7,4,-6,7,0,6,7,4,0,7,4,-6,7,0,-4,7,-4,-6,7,-6,0,7,-6,6,7,4,2,0,0,0
    rock4: 
        dc.b 0,2,0,7,6,-2,6,0,-2,7,-6,-4,7,-6,0,6,2,4,7,-6,0,7,0,6,7,4,6,7,6,-2,6,2,2,6,4,-4,7,-6,-4

* 12 points
ufo:
        dc.b 0,4,-2,12,-8,0,0,-6,4,13,20,0,13,-6,4,12,-8,0,13,-6,-4,13,6,-4,12,2,-4,12,4,0,12,2,4,13,6,4

buttons:   * left, right, fire, thrust hyperspace quit - , . z x space q        
        dc.b $2C,$2E,$5A,$58,$20,$51

furmans:
        dc.w $8000,$a000,$c000,$e000,0,$2000,$4000,$6000



  
  




