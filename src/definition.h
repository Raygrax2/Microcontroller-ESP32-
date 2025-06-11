#ifndef __DEFINITION_H__
#define __DEFINITION_H__
#include <Ultrasonic.h>
#include <esp_task_wdt.h>
#include <esp_timer.h>
#include <SimplePWM.h>
#include <SimpleADC.h>
#include <SimpleLCD.h>
#include <SimpleGPIO.h>
#include <stdio.h>
#include <SimpleUART.h>

uint64_t current_time, previous_time;

const uint8_t echo = 19; // GPIO pin for echo
const uint8_t trig = 18; // GPIO pin for trigger
const uint8_t ch_trig = 0;
const uint8_t LCellPin = 34; // Channel for echo
const uint8_t PIN_MOTOR_A_IN1 = 17;
const uint8_t PIN_MOTOR_A_IN2 = 5;
const uint8_t PIN_MOTOR_B_IN1 = 21;
const uint8_t PIN_MOTOR_B_IN2 = 22;
const uint8_t PIN_PWM_A = 18;
const uint8_t PIN_STBY = 16;
const uint8_t PIN_LOAD_CELL = 34;
const uint8_t PIN_LED_Green = 4;
const uint8_t PIN_LED_RED = 15;
TimerConfig US_config{
    .timer = LEDC_TIMER_3,
    .frequency = 40,
    .bit_resolution = LEDC_TIMER_14_BIT,
    .mode = LEDC_LOW_SPEED_MODE};

#endif