#include <definition.h>
void lcdPrint(SimpleLCD &lcdDisplay, const char* str) {
    lcdDisplay.writeCommand(CMD_CLEAR);
    lcdDisplay.writeCommand(CMD_HOME);
    while (*str) {
        if(*str == '\n') {
            lcdDisplay.writeCommand(CMD_SECOND_LINE);
            str++;
        }
        else
            lcdDisplay.print(*str++);
    }
}

extern "C" void app_main()
{
    esp_task_wdt_deinit();
    SimpleLCD lcd;
    uint8_t pinArrayLCD[11] = {4, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27};
    lcd.setup(pinArrayLCD);
    char buffer[100];
    sprintf(buffer, "This is a Test");
    lcdPrint(lcd, buffer);
    /*Ultrasonic usonic;
    usonic.setup(echo, trig, ch_trig, US_config);
    
    // Uncomment the following code to use the Ultrasonic sensor
    // Ultrasonic sensor part
    
    while (1)
    {
        current_time = esp_timer_get_time();
        if (current_time - previous_time >= 1000000)
        { // 1 second
            previous_time = current_time;
            float dist = usonic.getDistance() / 10;
            if (dist > 40){
                //Not valid distance, it will be ignored
                fprintf(stdout, "Distance is too far, ignoring...\n");
                break;
            }
            else{
                fprintf(stdout, "Distance: %.2f cm\n", dist);
                break;

            }
            }
           */
        //}

            // Uncoment for the linefollower part
            // Linefollower part supose 8 sensors
            /*
            uint8_t left_sensor = 34;   // GPIO pin for left sensor
            uint8_t right_sensor = 35;  // GPIO pin for right sensor
            SimpleGPIO left_sensor_gpio, rihgt_sensor_gpio;
            left_sensor_gpio.setup(left_sensor, GPI);
            rihgt_sensor_gpio.setup(right_sensor, GPO);
            */
       // }

}
