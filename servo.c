#include "servo.h"

const uint32_t servo_pwm_min  = 500;
const uint32_t servo_pwm_stop = 1500;
const uint32_t servo_pwm_max  = 2500;

const uint32_t servo_max_angle = 360;
const uint32_t servo_max_speed = 100;

void servo_init(servo_t *s)
{
    HAL_TIM_PWM_Start(s->htim, s->channel);

    if (s->type == servo_rotation) {
        s->servo_pwm = servo_pwm_stop;
        servo_stop(s);
    } else {
        s->servo_pwm = servo_pwm_min;
        servo_pos_move(s, 0.0f);
    }
}

void servo_stop(servo_t *s)
{
    if (s->type != servo_rotation)
        return;

    s->servo_pwm = servo_pwm_stop;
    __HAL_TIM_SET_COMPARE(s->htim, s->channel, s->servo_pwm);
}

void servo_pos_move(servo_t *s, float angle)
{
    if (s->type != servo_position)
        return;

    if (angle < 0.0f){
        angle = 0.0f;
    }

    if (angle > servo_max_angle){
        angle = servo_max_angle;
    }

    s->servo_pwm = servo_pwm_min + (uint32_t)((angle / servo_max_angle) * (servo_pwm_max - servo_pwm_min));

    __HAL_TIM_SET_COMPARE(s->htim, s->channel, s->servo_pwm);

}

void servo_rot_move(servo_t *s, float speed)
{
    if (s->type != servo_rotation)
        return;

    if (speed < 0.0f){
        speed = 0.0f;
    }

    if (speed > servo_max_speed){
        speed = servo_max_speed;
    }

    uint32_t offset = (uint32_t)((speed / servo_max_speed) * (servo_pwm_max - servo_pwm_stop));

    if (s->servo_dir) {
        // CW
        s->servo_pwm = servo_pwm_stop + offset;
    } else {
        // CCW
        s->servo_pwm = servo_pwm_stop - offset;
    }

    __HAL_TIM_SET_COMPARE(s->htim, s->channel, s->servo_pwm);
}
