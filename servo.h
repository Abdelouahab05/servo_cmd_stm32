#ifndef SERVO_H
#define SERVO_H

#include "stm32f4xx_hal.h"

// Struct

typedef enum {
    servo_position,
    servo_rotation
} servo_type_t;

typedef struct {

    TIM_HandleTypeDef *htim;
    uint32_t channel;
    uint32_t servo_dir;
    uint32_t servo_pwm ;  
    servo_type_t type;

} servo_t;

// Functions

void servo_init(servo_t *s);
void servo_stop(servo_t *s);

// Positional servo functions 
void servo_pos_move(servo_t *s, float angle);

// Continuous rotation servo functions 
void servo_rot_move(servo_t *s, float speed);


#endif
