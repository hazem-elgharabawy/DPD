#include "actuator.h"
#include "..\fixed\fixed.h"
#include <stdio.h>



// Actuator computation function
void actuator_func(Actuator_S *act) {

    //Y = H(1)*X + H(2)*X*|X|^2 + H(3)*X*|X|^4
    
    // H(1) = a10
    // H(2) = a30
    // H(3) = a50
    // Print the output values

    // Step 1: Compute the square of the input magnitude
    fixed_point_t abs_squared = FixedMul(act->in_r, act->in_r) +         // |X|^2
                                FixedMul(act->in_i, act->in_i);


    // Step 2: Compute the fourth power of the input magnitude
    fixed_point_t abs_pwr_four = FixedMul(abs_squared, abs_squared);       // |X|^4

    // Step 3: Compute intermediate results for cubic term
    fixed_point_t half_mul1_r = FixedMul(abs_squared, act->a30_r);         //H(2)*|X|^2
    fixed_point_t half_mul1_i = FixedMul(abs_squared, act->a30_i);

    // Step 4: Add linear term
    fixed_point_t add1_r = half_mul1_r + act->a10_r;                       // [ H(1) + H(2)*|X|^2 ]
    fixed_point_t add1_i = half_mul1_i + act->a10_i;

    // Step 5: Compute intermediate results for quintic term
    fixed_point_t half_mul2_r = FixedMul(abs_pwr_four, act->a50_r);        //H(3)*|X|^4
    fixed_point_t half_mul2_i = FixedMul(abs_pwr_four, act->a50_i);

    // Step 6: Add cubic and quintic terms
    fixed_point_t add2_r = half_mul2_r + add1_r;                           // [ H(1) + H(2)*|X|^2 + H(3)*|X|^4]
    fixed_point_t add2_i = half_mul2_i + add1_i;

    // Step 7: Compute the final output
    fixed_point_t mul1 = FixedMul(add2_r, act->in_r);                      // [ H(1) + H(2)*|X|^2 + H(3)*|X|^4] * X
    fixed_point_t mul2 = FixedMul(add2_i, act->in_i);
    fixed_point_t mul3 = FixedMul(add2_r, act->in_i);
    fixed_point_t mul4 = FixedMul(add2_i, act->in_r);

    act->out_r = mul1 - mul2;                                              //Y = H(1)*X + H(2)*X*|X|^2 + H(3)*X*|X|^4
    act->out_i = mul3 + mul4;

}
