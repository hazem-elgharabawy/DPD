#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <stdint.h>
#include "..\fixed\fixed.h"

// Actuator structure
typedef struct {
    fixed_point_t in_r, in_i;               // Input values
    fixed_point_t a10_r, a10_i;             // Coefficients for linear term
    fixed_point_t a30_r, a30_i;             // Coefficients for cubic term
    fixed_point_t a50_r, a50_i;             // Coefficients for quintic term
    fixed_point_t out_r, out_i;             // Output values
} Actuator_S;

// Function prototypes
void actuator_step(Actuator_S *act);

#endif // ACTUATOR_H
