#ifndef _APP4_H
#define _APP4_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "sys/time.h"
#include "configuration.h"
#include "definitions.h"


#ifdef __cplusplus

extern "C" {

#endif

typedef enum
{
    APP4_STATE_INIT=0,
    APP4_STATE_SERVICE_TASKS,
    APP4_STATE_RENDER_FS_INFO,
    APP4_STATE_RENDER_MAIN,
    APP4_STATE_RENDER_MENU,
} APP4_STATES;

typedef struct _tMenu Menu;
typedef struct _tMenuItem MenuItem;
typedef struct _tContextItem stContextItem;
typedef struct _tMenuCtrlSlider MenuCtrlSlider;
typedef struct _stContext stContext;

typedef void (*tActivateMenuItemFunc)(MenuItem * item);
typedef void (*pfnProcessContextFunc)(stContext * context);
typedef stContextItem * (*pfnGetContextItemsFunc)();

typedef struct _stSysValue {
    union {
        int m_iDefault;
        float m_fDefault;
    };
    union {
        int m_iCurrent;
        float m_fCurrent;
    };
    union {
        int m_iSet;
        float m_fSet;
    };
    union {
        int m_iMin;
        float m_fMin;
    };
    union {
        int m_iMax;
        float m_fMax;
    };
    char *m_szFmt;
} stSysValue, *pstSetValue;

typedef struct _tMenuItem {
  pstSetValue m_pstSysValue;
  const char *label;
  Menu * subMenu;
  tActivateMenuItemFunc activate_func;
  APP4_STATES state;
} MenuItem;

typedef struct _tMenuCtrlSlider {

} MenuCtrlSlider;

typedef struct _tMenu {
  int32_t index;
  int32_t pager;
  int32_t maxIndex;
  MenuItem * items;
} Menu;

typedef struct _stContext {
  int32_t index;
  int32_t pager;
  int32_t maxIndex;
  MenuItem * items;
  pfnProcessContextFunc pfnProcessContextFunc;
} stContext, * pstContext;

typedef void (*tActiveFunc)();

typedef struct
{
    APP4_STATES state;
    unsigned int count0;
    unsigned int count1;
    unsigned int count2;
    unsigned int count3;
    int count4;
    unsigned int erase_screen;
    tActiveFunc active_func;
    int32_t lcdRows;
    Menu * menu;
    int32_t downBtn;
    SemaphoreHandle_t menuMutex;
} APP4_DATA;

void APP4_Initialize ( void );
void APP4_Tasks( void );
void LCD_Render( void );
void Render_Main( void );
void Render_Menu( void );
void Render_File_System_Info( void );
void Activate_Menu_Item(MenuItem * item);
void Activate_Menu_Item_State(MenuItem * item);
void Active_Menu_Item_Reset(MenuItem * item);
void Active_Dir_Item(MenuItem * item);



APP4_DATA app4Data;

Menu mainMenu;
Menu subMenu1;
Menu subMenu2;

#ifdef __cplusplus
}
#endif

#endif 

