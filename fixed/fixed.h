#ifndef FIXED_H

#define FIXED_H

#include <stdint.h>

// Fixed-point configuration
#define INT_WIDTH 8
#define FRACT_WIDTH 24
#define DATA_WIDTH (INT_WIDTH + FRACT_WIDTH)    // Q8.24 fixed-point
#define ROUND_VALUE (1LL << (FRACT_WIDTH - 1))
// Fixed-point data type
typedef int32_t fixed_point_t;
typedef int64_t fixed_point_product_t;

// Function prototypes
fixed_point_t FixedMul(fixed_point_t a, fixed_point_t b);
fixed_point_t FloatToFixed(double a);
double FixedToFloat(fixed_point_product_t a);

#endif // FIXED_H