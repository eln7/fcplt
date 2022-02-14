#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "definitions.h"

int main ( void )
{
    SYS_Initialize ( NULL );

    
    TMR1_Start();
    TMR2_Start();

    if (SYS_TIME_Status (sysObj.sysTime) == SYS_STATUS_READY){
        printf("\n\nTime system service is initialized and ready to accept new requests.\n");
    }
    
    printf( "%08x-%08x\n", (NVM_START_ADDRESS & ~(0x200-1)) & 0x1FFFFFFF, (((NVM_START_ADDRESS + 0x40000) & ~(0x200-1))-1)  & 0x1FFFFFFF );
    printf( " Flash Start(BMXPUPBA):%08x\n", BMXPUPBA);    
    printf( " Flash Size(BMXPFMSZ):%08x\n", BMXPFMSZ);

    printf("\nNVM %s", NVM_IsBusy()? "not Ready!!!\n": "is Ready\n");
    
    for(int i = 0; i < 10; i++){
            SYS_FS_MEDIA_GEOMETRY * geo = SYS_FS_MEDIA_MANAGER_GetMediaGeometry( i );
        if(geo){
            printf("Block Size: %u, Number of Block: %u\n", 
                    geo->geometryTable->blockSize,
                    geo->geometryTable->numBlocks
            );
        }
    }

    //GPIO_PinInterruptCallbackRegister( CN8_PIN, (GPIO_PIN_CALLBACK)rotary_encoder_handler, 0);
    //GPIO_PinInterruptEnable(CN8_PIN);
    
    //GPIO_PinInterruptCallbackRegister( CN9_PIN, (GPIO_PIN_CALLBACK)rotary_encoder_handler, 0);
    //GPIO_PinInterruptEnable(CN9_PIN);

    //GPIO_PinInterruptCallbackRegister( CN10_PIN, (GPIO_PIN_CALLBACK)rotary_encoder_handler, 0);
    //GPIO_PinInterruptEnable(CN10_PIN);

    while ( true )  {
        SYS_Tasks ( );
    }
    return ( EXIT_FAILURE );
}