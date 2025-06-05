#include <definition.h>
extern "C" void app_main()
{
    esp_task_wdt_deinit();
    /*    // Uncomment the following code to use the Ultrasonic sensor
    // Ultrasonic sensor part
    Ultrasonic usonic;
    
    usonic.setup(echo, trig, ch_trig, US_config);
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
            
            
        }
    */
    
}