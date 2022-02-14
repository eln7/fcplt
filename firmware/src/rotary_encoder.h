#ifndef _ROTARY_ENCODER_H
#define _ROTARY_ENCODER_H 

#include "definitions.h"
//#include "eln_time.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EXAMPLE_CONSTANT 0

    typedef struct _example_struct_t {
        /* Describe structure member. */
        int some_number;


    } example_struct_t;

    volatile static int _prevValueAB = 0;

    static void rotary_encoder_handler(GPIO_PIN pin, uintptr_t context) {
        char buff[64];

        time_t current_time;

        //current_time = time(NULL);
        current_time = 0;

        int _currValueAB = GPIO_PinRead(GPIO_PIN_RG7) << 1;
        _currValueAB |= GPIO_PinRead(GPIO_PIN_RG8);
        
        // xSemaphoreTake(app4Data.menuMutex, portMAX_DELAY);
        
        switch ((_prevValueAB | _currValueAB)) {
            case 0b1000: case 0b1100:
                app4Data.menu->index--;
                break;
            case 0b1101: case 0b1001:
                app4Data.menu->index++;
                break;
        }
        // xSemaphoreGive(app4Data.menuMutex);
        _prevValueAB = _currValueAB << 2;

        Menu * menu = app4Data.menu;
        
        strftime(buff, sizeof (buff), "%H:%M:%S", gmtime(&current_time));
        printf("%s %02u %02u %02u %03d\n", buff, _prevValueAB, _currValueAB, _prevValueAB | _currValueAB, app4Data.menu->index);
    }

#ifdef __cplusplus
}
#endif

#endif