/*
      This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
      Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
      Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
      You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LASER_MODULE_H
#define LASER_MODULE_H

#include "libs/Module.h"
#include "libs/Pin.h"
#include "libs/Kernel.h"
#include "modules/communication/utils/Gcode.h"
#include "PwmOut.h" // mbed.h lib


#define laser_module_enable_checksum        CHECKSUM("laser_module_enable")
#define laser_module_pin_checksum           CHECKSUM("laser_module_pin")
#define laser_module_pwm_period_checksum    CHECKSUM("laser_module_pwm_period")
#define laser_module_max_power_checksum     CHECKSUM("laser_module_max_power")
#define laser_module_tickle_power_checksum  CHECKSUM("laser_module_tickle_power")
#define laser_coolant_sensor_pin            CHECKSUM("laser_coolant_sensor_pin")
#define laser_coolant_sensor_frequency      CHECKSUM("laser_coolant_sensor_frequency")

class Laser : public Module{
    public:
        Laser();
        virtual ~Laser() {};
        void on_module_loaded();
        void on_main_loop(void* argument);
        void on_block_end(void* argument);
        void on_block_begin(void* argument);
        void on_play(void* argument);
        void on_pause(void* argument);
        void on_gcode_execute(void* argument);
        void on_speed_change(void* argument);
        void set_proportional_power();
        uint32_t coolant_check(uint32_t dummy);

        mbed::PwmOut*    laser_pin;    // PWM output to regulate the laser power
        bool             laser_on;     // Laser status
        bool             laser_inverting; // stores whether the pwm period should be inverted
        float            laser_max_power; // maximum allowed laser power to be output on the pwm pin
        float            laser_tickle_power; // value used to tickle the laser on moves
        Pin              laser_coolant_pin;  // pin for missing pulse detector
        uint32_t         laser_coolant_freq; // missing pulse detector frequency, in Hz
    protected:
        uint32_t         coolant_good;   // count of consecutive periods with a pulse seen
        bool             coolant_paused; // currently paused due to missed pulse
        bool             coolant_msg_state; // if != _paused, a message needs to be sent
};

#endif
