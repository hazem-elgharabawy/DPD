#include "fixed.h"

//  Functions definitions

fixed_point_t DoubleToFixed(double a){
    fixed_point_t result;
    result = (fixed_point_t) (a * (1<< FRACT_WIDTH) + 0.5);         // multiply by 2^FRACT_WIDTH
    return result;
}

double FixedToDouble(fixed_point_product_t a){
    double result;
    result = (double) a / (1 << FRACT_WIDTH);                  // divide by 2^FRACT_WIDTH
    return result;
}


fixed_point_t FixedMul(fixed_point_t a, fixed_point_t b) {
    fixed_point_product_t product = (fixed_point_product_t)a * (fixed_point_product_t)b;
    return (fixed_point_t)((product + ROUND_VALUE) >> FRACT_WIDTH); // Add rounding
}
