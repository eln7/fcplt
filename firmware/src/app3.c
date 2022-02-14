#include "app3.h"
#include "definitions.h"

APP3_DATA app3Data;

void APP3_Initialize ( void )
{
    app3Data.state = APP3_STATE_INIT;
    app3Data.delay = 1;
}

volatile static int _prevValueAB = 0;
volatile static int _prevValueBtn = 1;

void APP3_Tasks ( void )
{
    switch ( app3Data.state ) {
        case APP3_STATE_INIT:
        {
            bool appInitialized = true;

            if (appInitialized){
                app3Data.state = APP3_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP3_STATE_SERVICE_TASKS:
        {
            //char buff[64];
            //time_t current_time;

            int _currValueAB = GPIO_PinRead(GPIO_PIN_RG7) << 1;
            _currValueAB |= GPIO_PinRead(GPIO_PIN_RG8);

            switch ((_prevValueAB | _currValueAB)) {
                case 0b1000: case 0b1100:
                    app4Data.menu->index++;
                break;
                case 0b1101: case 0b1001:
                    app4Data.menu->index--;
                break;
            }
            _prevValueAB = _currValueAB << 2;

            if(_prevValueBtn == 0 && GPIO_PinRead(GPIO_PIN_RG6) )
                app4Data.downBtn = 1;

            _prevValueBtn = GPIO_PinRead(GPIO_PIN_RG6);

            //current_time = time(NULL);
            //strftime(buff, sizeof (buff), "%H:%M:%S", gmtime(&current_time));
            //printf("%s %02u %02u %02u %03d\n", buff, _prevValueAB, _currValueAB, _prevValueAB | _currValueAB, app4Data.menu.index);

            vTaskDelay(app3Data.delay);
            break;
        }
        default:
        {
            break;
        }
    }
}