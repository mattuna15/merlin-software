
#include "ieee754.h"
#include <math.h>
#include <inttypes.h>

volatile uint64_t *opa = (uint64_t *)0xf50000;
volatile uint64_t *opb = (uint64_t *)0xf50008;
volatile uint64_t *fpu_res = (uint64_t *)0xf50010;
volatile uint32_t *fpu_res1 = (uint32_t *)0xf50010;
volatile uint32_t *fpu_res2 = (uint32_t *)0xf50014;

volatile uint8_t *fpu_ctl = (uint8_t *)0xf50019;
volatile uint8_t *fpu_sts = (uint8_t *)0xf5001b;

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL << (b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL << (b)))
#define BIT_CHECK(a, b) (!!((a) & (1ULL << (b)))) // '!!' to make sure this returns 0 or 1

#define ADD  0
#define SUB  0b00000010
#define MUL  0b00000100
#define DIV  0b00000110
#define SQRT 0b00001000
#define SDBL 0b00001010
#define DSGL 0b00001100
#define POW  0b00001110
#define EXP  0b00010000
#define COS  0b00010010
#define TAN  0b00010100
#define SIN  0b00010110

union FloatingPointIEEE754 op_a, op_b, resf;

union FloatingPointIEEE754f float_res;

// -- FPU Operations (fpu_op):
// --========================
// --	0 = add
// --	1 = sub
// --	2 = mul
// --	3 = div

// --Rounding Modes (rmode):
// --=======================
// --	0 = round_nearest_even
// --	1 = round_to_zero
// --	2 = round_up
// --	3 = round_down


//double
double __wrap___extendsfdf2(float a)
{

   //printf("\r\next: start\r\n");

  *fpu_ctl = SDBL;

  float_res.flt = a;

  *opa = (uint64_t)float_res.numf << 32;
  *opb = 0x0;

  BIT_SET(*fpu_ctl, 0); //enable
  BIT_CLEAR(*fpu_ctl, 0);

  while (!BIT_CHECK(*fpu_sts, 0) && !BIT_CHECK(*fpu_sts, 1))
  {
  }

  resf.num = *fpu_res; 

   //printf("\r\nnext: stop\r\n");


  return resf.dbl;
}

float __wrap___truncdfsf2(double a)
{

   //printf("\r\ntrunc: start\r\n");

  *fpu_ctl = DSGL;

  op_a.dbl = a;
  op_b.dbl = 0x0;

  *opa = op_a.num;
  *opb = 0x0;

  BIT_SET(*fpu_ctl, 0); //enable
    BIT_CLEAR(*fpu_ctl, 0);


  while (!BIT_CHECK(*fpu_sts, 0) && !BIT_CHECK(*fpu_sts, 1))
  {
  }

  float_res.numf = *fpu_res;


   //printf("\r\ntrunc: stop\r\n");

  return float_res.flt;
}

double __wrap___muldf3(double a, double b)
{

   

   //printf("\r\nmuldf3: start\r\n");

  *fpu_ctl = MUL;

  op_a.dbl = a;
  op_b.dbl = b;

  *opa = op_a.num;
  *opb = op_b.num;

  BIT_SET(*fpu_ctl, 0); //enable
    BIT_CLEAR(*fpu_ctl, 0);

  while (!BIT_CHECK(*fpu_sts, 0) )
  {
  }

   //printf("\r\nmuldf3: stop\r\n");

  resf.num = *fpu_res;

  return resf.dbl;
}


double __wrap___adddf3(double a, double b)
{

    

   //printf("\r\nadddf3: start\r\n");

  *fpu_ctl = ADD;

  op_a.dbl = a;
  op_b.dbl = b;

  *opa = op_a.num;
  *opb = op_b.num;

  BIT_SET(*fpu_ctl, 0); //enable
    BIT_CLEAR(*fpu_ctl, 0);

  while (!BIT_CHECK(*fpu_sts, 0)   && !BIT_CHECK(*fpu_sts, 1))
  {
  }



   //printf("\r\nadddf3: stop\r\n");

  resf.num = *fpu_res;

  return resf.dbl;


}

double __wrap___subdf3(double a, double b)
{
  
    

   //printf("\r\nsubdf3: start\r\n");

  *fpu_ctl = SUB;

  op_a.dbl = a;
  op_b.dbl = b;

  *opa = op_a.num;
  *opb = op_b.num;

  BIT_SET(*fpu_ctl, 0); //enable
    BIT_CLEAR(*fpu_ctl, 0);

  while (!BIT_CHECK(*fpu_sts, 0) && !BIT_CHECK(*fpu_sts, 1))
  {
  }


   //printf("\r\nsubdf3: stop\r\n");

  resf.num = *fpu_res;

  return resf.dbl;

}



double __wrap___divdf3(double a, double b)
{

   //printf("\r\ndivdf3: start\r\n");

  *fpu_ctl = DIV;

  op_a.dbl = a;
  op_b.dbl = b;

  *opa = op_a.num;
  *opb = op_b.num;

  BIT_SET(*fpu_ctl, 0); //enable
    BIT_CLEAR(*fpu_ctl, 0);

  while (!BIT_CHECK(*fpu_sts, 0) && !BIT_CHECK(*fpu_sts, 1))
  {
  }

   //printf("\r\ndivdf3: stop\r\n");

  resf.num = *fpu_res;

  return resf.dbl;

}

double __wrap_pow(double a, double b)
{

   //printf("\r\npow: start\r\n");

  *fpu_ctl = POW;

  op_a.dbl = a;
  op_b.dbl = b;

  *opa = op_a.num;
  *opb = op_b.num;

  BIT_SET(*fpu_ctl, 0); //enable

  while (!BIT_CHECK(*fpu_sts, 0))
  {
  }

   //printf("\r\npow: stop\r\n");

  resf.num = *fpu_res;

  return resf.dbl;

}

double __wrap_sqrt(double a)
{

   //printf("\r\nsqrt: start\r\n");

  *fpu_ctl = SQRT;

  op_a.dbl = a;
  op_b.dbl = 0x0;

  *opa = op_a.num;
  *opb = op_b.num;

  BIT_SET(*fpu_ctl, 0); //enable
    BIT_CLEAR(*fpu_ctl, 0);

  while (!BIT_CHECK(*fpu_sts, 0))
  {
  }

   //printf("\r\nsqrt: stop\r\n");

  resf.num = *fpu_res;

  return resf.dbl;

}

double __wrap_exp(double a)
{

   //printf("\r\nexp: start\r\n");

  *fpu_ctl = EXP;

  op_a.dbl = a;
  op_b.dbl = 0x0;

  *opa = op_a.num;
  *opb = op_b.num;

  BIT_SET(*fpu_ctl, 0); //enable

  while (!BIT_CHECK(*fpu_sts, 0) && !BIT_CHECK(*fpu_sts, 1))
  {
  }

  BIT_CLEAR(*fpu_ctl, 0);

   //printf("\r\nexp: stop\r\n");

  resf.num = *fpu_res;

  return resf.dbl;

}

double __wrap_sin(double a)
{

      

   //printf("\r\nsin: start\r\n");

  *fpu_ctl = SIN;

  op_a.dbl = a;
  op_b.dbl = 0x0;

  *opa = op_a.num;
  *opb = op_b.num;

  BIT_SET(*fpu_ctl, 0); //enable

  while (!BIT_CHECK(*fpu_sts, 0) && !BIT_CHECK(*fpu_sts, 1))
  {
  }

  BIT_CLEAR(*fpu_ctl, 0);

   //printf("\r\nsin: stop\r\n");

  resf.num = *fpu_res;

  return resf.dbl;

}
double __wrap_cos(double a)
{

   //printf("\r\ncos: start\r\n");

  *fpu_ctl = COS;

  op_a.dbl = a;
  op_b.dbl = 0x0;

  *opa = op_a.num;
  *opb = op_b.num;

  BIT_SET(*fpu_ctl, 0); //enable

  while (!BIT_CHECK(*fpu_sts, 0) && !BIT_CHECK(*fpu_sts, 1))
  {
  }

  BIT_CLEAR(*fpu_ctl, 0);

   //printf("\r\ncos: stop\r\n");

  resf.num = *fpu_res;

  return resf.dbl;

}
double __wrap_tan(double a)
{

      

   //printf("\r\ntan: start\r\n");

  *fpu_ctl = TAN;

  op_a.dbl = a;
  op_b.dbl = 0x0;

  *opa = op_a.num;
  *opb = op_b.num;

  BIT_SET(*fpu_ctl, 0); //enable

  while (!BIT_CHECK(*fpu_sts, 0) && !BIT_CHECK(*fpu_sts, 1))
  {
  }

  BIT_CLEAR(*fpu_ctl, 0);

   //printf("\r\ntan: stop\r\n");

  resf.num = *fpu_res;

  return resf.dbl;

}
