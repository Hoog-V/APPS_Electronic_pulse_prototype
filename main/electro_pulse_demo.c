/* Elektropulse demo

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/mcpwm.h"

#define ELECTRO_PULSE_GPIO        (18)   // GPIO connects to the PWM signal line of boost conv

#define PERIOD_FREQ 300

static inline int convert_duty_to_us(int duty){
    return ((duty*10e6)/(PERIOD_FREQ))/100;
}


void app_main(void)
{
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, ELECTRO_PULSE_GPIO); 
    mcpwm_config_t pwm_config = {
        .frequency = PERIOD_FREQ, 
        .cmpr_a = 0,   
        .counter_mode = MCPWM_UP_COUNTER,
        .duty_mode = MCPWM_DUTY_MODE_0,
    };
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
    mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, convert_duty_to_us(500));
}

