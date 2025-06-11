#include <definition.h>
typedef enum
{
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
    Ultrasonic usonic;
    SimpleGPIO motorA_ini1, motorA_ini2, MotorB_ini1, MotorB_ini2, pwmA, stby;
    SimplePWM pwm;
    SimpleADC LCell;

    // setups
    usonic.setup(echo, trig, ch_trig, US_config);

    // Load cell for weight measurement
    LCell.setup(LCellPin); // Setup load cell on GPIO 34
    printf("Load cell setup complete.\n");

    pwm.setup(PIN_PWM_A, GPO, &US_config, false); // Setup PWM on pin 18
    motorA_ini1.setup(PIN_MOTOR_A_IN1, GPO);
    motorA_ini2.setup(PIN_MOTOR_A_IN2, GPO);
    MotorB_ini1.setup(PIN_MOTOR_B_IN1, GPO);
    MotorB_ini2.setup(PIN_MOTOR_B_IN2, GPO);
    stby.setup(PIN_STBY, GPO);
    stby.set(1); // Enable the motor driver
    // AGVState state = STATE_IDLE; // Initialize state
    current_time = esp_timer_get_time();
    motorA_ini1.set(1);                  // Set motor 1 to high
    motorA_ini2.set(0);                  // Set motor 2 to high
    MotorB_ini1.set(1);                  // Set motor 3 to high
    MotorB_ini2.set(0);                  // Set motor 4 to high
    pwm.setup(18, 0, &US_config, false); // Setup PWM on pin 18
    pwm.setDigitalLevel(1000);           // Set PWM duty cycle to 1000 (out of 4095)
    while (1)
    {
        float WEight = LCell.read(ADC_READ_RAW);
        printf("Load cell reading: %.2f \n", WEight);
        if (current_time - previous_time >= 1000000)
        { // 1 second
            previous_time = current_time;
            printf("Entro al if \n");
            /*// --- Collision detection logic ---
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
                state = STATE_STOPPED; // Change state to stopped
                break;

            default:
                break;
            }


        }
            */
        }
    }
}
