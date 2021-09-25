#ifndef _i754_H_INCLUDED
#define _i754_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>


union FloatingPointIEEE754
{
  struct
  {
    unsigned int sign : 1;
    unsigned short int exponent : 11;
    long long mantissa : 52;
  } raw;
  uint32_t num32[2];
  uint64_t num;
  double dbl;
} ;

union FloatingPointIEEE754f
{
  struct
  {
    unsigned int sign : 1;
    unsigned short int exponent : 8;
    long long mantissa : 23;
  } raw;
  uint32_t numf;
  float flt;
} ;

double __wrap___extendsfdf2(float a);
float __wrap___truncdfsf2(double a);
double __wrap___muldf3(double a, double b);
double __wrap___adddf3(double a, double b);
double __wrap___subdf3(double a, double b);
double __wrap___divdf3(double a, double b);
double __wrap_pow(double a, double b);
double __wrap_sqrt(double a);
double __wrap_exp(double a);
double __wrap_cos(double a);
double __wrap_sin(double a);
double __wrap_tan(double a);

void double_to_string(double f, char *str, uint8_t precision);

#ifdef __cplusplus
}
#endif

 #endif