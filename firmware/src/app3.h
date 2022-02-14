#ifndef _APP3_H
#define _APP3_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

typedef enum
{
    APP3_STATE_INIT=0,
    APP3_STATE_SERVICE_TASKS,
} APP3_STATES;

typedef struct
{
    APP3_STATES state;
    unsigned int delay;
} APP3_DATA;

void APP3_Initialize ( void );
void APP3_Tasks( void );

#ifdef __cplusplus
}
#endif

#endif /* _APP3_H */