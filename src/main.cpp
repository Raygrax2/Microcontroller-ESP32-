#include <definition.h>
void lcdPrint(SimpleLCD &lcdDisplay, const char *str)
{
    lcdDisplay.writeCommand(CMD_CLEAR);
    lcdDisplay.writeCommand(CMD_HOME);
    while (*str)
    {
        if (*str == '\n')
        {
            lcdDisplay.writeCommand(CMD_SECOND_LINE);
            str++;
        }
        else
            lcdDisplay.print(*str++);
    }
}
typedef enum {
    STATE_IDLE,
    STATE_MOVING_FORWARD,
    STATE_TURNING_LEFT,
    STATE_TURNING_RIGHT,
    STATE_STOPPED,
    STATE_COLLISION_DETECTED
} AGVState;
extern "C" void app_main()
{
    esp_task_wdt_deinit();
    SimpleLCD lcd;
    Ultrasonic usonic;
    uint8_t pinArrayLCD[11] = {4, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27};
    //setups
    lcd.setup(pinArrayLCD);
    usonic.setup(echo, trig, ch_trig, US_config);
    char buffer[100];
    sprintf(buffer, "This is a Test");
    lcdPrint(lcd, buffer);
    

    //codigo provisional para motores
    SimpleGPIO motorA_ini1, motorA_ini2, MotorB_ini1, MotorB_ini2, pwmA, stby;
    SimpleGPIO motorA_ini2; // Declare motorA_ini2
    pwmA.setup(18, GPO);
    motorA_ini2.setup(5, GPO);
    motorA_ini1.setup(17, GPO);
    MotorB_ini1.setup(21, GPO);
    MotorB_ini2.setup(22, GPO);
    stby.setup(16, GPO);
    stby.set(1); // Enable the motor driver
    AGVState state = STATE_IDLE; // Initialize state
    while (1)
    {
        current_time = esp_timer_get_time();
        motorA_ini1.set(1); // Set motor 1 to high
        motorA_ini2.set(0); // Set motor 2 to high
        MotorB_ini1.set(1); // Set motor 3 to high
        MotorB_ini2.set(0); // Set motor 4 to high
        SimplePWM pwm;
        pwm.setup(18, 0, &US_config, false); // Setup PWM on pin 18
        pwm.setDigitalLevel(1000); // Set PWM duty cycle to 1000 (out of 4095)
        // pwm.setDuty(0.5); // Set PWM duty cycle to 50%
        // wait 2 sec
        

           // ...existing code...
            if (current_time - previous_time >= 1000000)
            { // 1 second
                previous_time = current_time;
    
                // --- Collision detection logic ---
                float dist = usonic.getDistance() / 10;
                if (dist > 40)
                {
                    // Not valid distance, it will be ignored
                    fprintf(stdout, "Distance is too far, ignoring...\n");
                }
                else if (dist < 20)
                {
                    printf("Collision imminent!\n");
                    state = STATE_COLLISION_DETECTED;
                }
                else
                {
                    fprintf(stdout, "Distance: %.2f cm\n", dist);
                }
                // --- End collision detection logic ---
    
                switch (state)
                {
                case STATE_IDLE:
                    /* code */
                    break;
                case STATE_MOVING_FORWARD:
                    // Move forward
                    motorA_ini1.set(1); // Set motor 1 to high
                    motorA_ini2.set(0); // Set motor 2 to high
                    MotorB_ini1.set(1); // Set motor 3 to high
                    MotorB_ini2.set(0); // Set motor 4 to high
                    pwm.setDigitalLevel(1000); // Set PWM duty cycle to 1000 (out of 4095)
                    break;
                case STATE_TURNING_LEFT:
                    // Considering the motor a is on the left side and motor b is on the right side
                    motorA_ini1.set(1); // Set motor 1 to high
                    motorA_ini2.set(0); // Set motor 2 to high
                    MotorB_ini1.set(0); // Set motor 3 to high
                    MotorB_ini2.set(0); // Set motor 4 to high
                    pwm.setDigitalLevel(1000); // Set PWM duty cycle to 1000 (out of 4095)
                    break;
                case STATE_TURNING_RIGHT:
                // Considering the motor a is on the left side and motor b is on the right side
                    motorA_ini1.set(0); // Set motor 1 to high
                    motorA_ini2.set(0); // Set motor 2 to high
                    MotorB_ini1.set(1); // Set motor 3 to high
                    MotorB_ini2.set(0); // Set motor 4 to high
                    pwm.setDigitalLevel(1000); // Set PWM duty cycle to 1000 (out of 4095)
                    break;
                case STATE_STOPPED:
                    // Stop both motors
                    motorA_ini1.set(0); // Set motor 1 to high
                    motorA_ini2.set(0); // Set motor 2 to high
                    MotorB_ini1.set(0); // Set motor 3 to high
                    MotorB_ini2.set(0); // Set motor 4 to high
                    pwm.setDigitalLevel(0); // Set PWM duty cycle to 0 (stop)
                    // if the ultrasonic sensor changes to not detect a collision, change state to moving forward
                    if (dist > 20) {
                        state = STATE_MOVING_FORWARD; // Change state to moving forward
                    }
                    break;
                case STATE_COLLISION_DETECTED:
                    // Collision detected, stop both motors
                    motorA_ini1.set(0); // Set motor 1 to low
                    motorA_ini2.set(0); // Set motor 2 to low
                    pwm.setDigitalLevel(0); // Set PWM duty cycle to 0 (stop)
                    
                    state = STATE_STOPPED; // Change state to stopped
                    break;
                
                default:
                    break;
                }
            }
    // ...existing code...
    }
}
