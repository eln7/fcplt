#include "app4.h"

APP4_DATA app4Data;

stSysValue g_stValue[] = {
    [0] = {.m_iDefault = 0, .m_iCurrent = 4, .m_iSet = 8, .m_iMin = 0, .m_iMax = 100, "%d"},
    [1] = {.m_iDefault = 1, .m_iCurrent = 5, .m_iSet = 9, .m_iMin = 0, .m_iMax = 100, "%d"},
    [2] = {.m_iDefault = 2, .m_iCurrent = 6, .m_iSet = 10, .m_iMin = 0, .m_iMax = 100, "%d"},
    [3] = {.m_fDefault = 1.14, .m_fCurrent = 2.14, .m_fSet = 3.14, .m_fMin = 0.001, .m_iMax = 49.009, "%.03f"}
};

MenuItem subMenuItems1[] = {
      {NULL, "(back)", &mainMenu, &Activate_Menu_Item}, 
      {&g_stValue[3], "Sub2 Item 1"},
      {NULL, "Sub1 Item 2"},
      {NULL, "Sub1 Item 3"},
      {NULL, "Sub1 Item 4"},
      {NULL, "Sub1 Item 5"},
      {NULL, "Sub1 Item 6"},
      {NULL, "Sub1 Item 7"},
      {NULL, "Sub1 Item 8"}
};


MenuItem subMenuItems2[] = {
    {NULL, "(back)", &mainMenu, &Activate_Menu_Item}, 
    {&g_stValue[2], "Sub2 Item 1"},
    {NULL, "Sub2 Item 2"},
    {NULL, "Sub2 Item 3"},
    {NULL, "Sub2 Item 4"},
    {NULL, "Sub2 Item 5"},
    {NULL, "Sub2 Item 6"}
};

MenuItem mainMenuItems[] = {
      {NULL, "(back)", NULL, &Activate_Menu_Item_State,  APP4_STATE_SERVICE_TASKS}, 
      {NULL, "Main Item 1", &subMenu1, &Activate_Menu_Item}, 
      {NULL, "Main Item 2", &subMenu2, &Activate_Menu_Item}, 
      {NULL, "File System Info", NULL, &Activate_Menu_Item_State, APP4_STATE_RENDER_FS_INFO}, 
      {&g_stValue[0], "Main Item 4", NULL}, 
      {&g_stValue[1], "Main Item 5", NULL}, 
      {NULL, "Main Item 6", NULL}, 
      {NULL, "Main Item 7", NULL}, 
      {NULL, "Main Item 8", NULL}, 
      {NULL, "Main Item 9", NULL}, 
      {NULL, "Main Item 10", NULL}, 
      {NULL, "Main Item 11", NULL}, 
      {NULL, "Version", NULL}, 
      {NULL, "Reset", NULL, &Active_Menu_Item_Reset}, 
};

Menu subMenu1  = { 
    .pager = 0,
    .index = 0,
    .items = subMenuItems1,
    .maxIndex = sizeof(subMenuItems1) / sizeof(MenuItem) - 1
} ;

Menu subMenu2 = { 
    .pager = 0,
    .index = 0,
    .items = subMenuItems2,
    .maxIndex = sizeof(subMenuItems2) / sizeof(MenuItem) - 1
} ;

Menu mainMenu = { 
    .pager = 0,
    .index = 0,
    .items = mainMenuItems,
    .maxIndex = sizeof(mainMenuItems) / sizeof(MenuItem) - 1
};


void activateMenu( Menu * m ){

}

void APP4_Initialize ( void )
{
    //uint32_t value = ADC_ResultGet(ADC_INPUT_POSITIVE_AN0);
    //srand(value);

    app4Data.state = APP4_STATE_INIT;
    app4Data.count0 = 0;
    app4Data.count1 = 0;
    app4Data.count2 = ~0;
    app4Data.count3 = 0;
    app4Data.count4 = 0;
    app4Data.erase_screen = ((unsigned int)rand() % 50) + 10;
    app4Data.downBtn = 0;
    app4Data.active_func = &LCD_Render;
    app4Data.lcdRows= 3;
    app4Data.menu = &mainMenu;
  
    //PMP_Setup();
}

void APP4_Tasks ( void )
{
    switch ( app4Data.state ){
        /* Application's initial state. */
        case APP4_STATE_INIT:{
            //vTaskDelay(2000);
            //PMADDRCLR = 1 << 14; 
            //ADC_Disable();
            //SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "LCD Setup\r\n");
            //LCD_Setup();
            LCD_Setup();
            srand(ADC_ResultGet(1));
            OCMP2_Enable();
            //app4Data.menuMutex = xSemaphoreCreateMutex();
            //app4Data.state = APP4_STATE_RENDER_MENU;
            app4Data.state = APP4_STATE_SERVICE_TASKS;
            break;
        }

        case APP4_STATE_SERVICE_TASKS:{
            (*app4Data.active_func)();
            break;
        }
        case APP4_STATE_RENDER_MENU:{
            Render_Menu();
            break;
        }
        case APP4_STATE_RENDER_FS_INFO:
            Render_File_System_Info();
            break;
        default:{
            break;
        }
    }
}

void LCD_Render( void )
{
    //unsigned int Start, Wait, Stop;

    char buf[128];

    //LCD_Home();
    //sprintf( buf, "xAxBxCxDxExFxGxHx");
    //LCD_Move(1,0);
    //LCD_WriteString(buf);
    //vTaskDelay(100);
    //LCD_Clear();
    
    //LCD_Home();
    /*
    LCD_Move(1,0);
    sprintf( buf, "%c", app4Data.count0++);
    LCD_WriteString(buf);
   
    if(app4Data.count0 > 256 ){
        LCD_Clear();
        vTaskDelay(200);
        app4Data.count0 = 0;
    }else{
            vTaskDelay(120);
    }
     * */

    if(app4Data.downBtn){
            app4Data.state = APP4_STATE_RENDER_MENU;
            app4Data.downBtn = 0;
            return;
    }

    app4Data.count0 = (unsigned int)rand() % 1150000;
    
    if(app4Data.count0 > app4Data.count1 )
        app4Data.count1 = app4Data.count0;
    
    if(app4Data.count0 < app4Data.count2)
        app4Data.count2 = app4Data.count0;
    
    app4Data.count3 = (unsigned int)rand() % 1150000;
 
    char buff[64];
    time_t current_time = time(NULL);
    
    strftime(buff, sizeof (buff), "%H:%M:%S", gmtime(&current_time));

    LCD_Move(0,0);
    sprintf( buf, "%s ",buff);
    LCD_WriteString(buf);
    
    LCD_Move(1,0);
    sprintf( buf, "Max: %u ",app4Data.count1);
    LCD_WriteString(buf);

    LCD_Move(2,0);
    sprintf( buf, "Min: %u, C:%02u",app4Data.count2, app4Data.erase_screen );
    LCD_WriteString(buf);
    
    /*uint32_t value_a5 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN5);*/
    /*uint32_t value_a12 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN12);*/
/*
    uint32_t value_a0 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN0);value_a0 = value_a0;
    uint32_t value_a1 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN1);value_a1 = value_a1;
    uint32_t value_a2 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN2);value_a2 = value_a2;
    uint32_t value_a3 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN3);value_a3 = value_a3;
    uint32_t value_a4 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN4);value_a4 = value_a4;
    uint32_t value_a5 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN5);value_a5 = value_a5;
    uint32_t value_a6 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN6);value_a6 = value_a6;
    uint32_t value_a7 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN7);value_a7 = value_a7;
    uint32_t value_a8 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN8);value_a8 = value_a8;
    uint32_t value_a9 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN9);value_a9 = value_a9;
    uint32_t value_a10 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN10);value_a10 = value_a10;
    uint32_t value_a11 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN11);value_a11 = value_a11;
    uint32_t value_a12 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN12);value_a12 = value_a12;
*/

    LCD_Move(3,0);
    //uint32_t value_a0 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN0);
    uint32_t value_a1 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN1);
    //uint32_t value_a13 = ADC_ResultGet(ADC_INPUT_POSITIVE_AN13);
    sprintf( buf, "A0:%05u, V:%05d", value_a1, app4Data.menu->index);
    LCD_WriteString(buf);
    
//    int i = 0;

    //printf("$%u %u;", value_a0*20, value_a13 );
    //printf("$%u %d;", value_a1, app4Data.count4 );
    
    /*printf("$");
    for( i=0; i < 16; i++){
        printf("%d%c", ADC_ResultGet(i), (i<15)?' ':';');
    }*/
    //printf("\n");
    
    OCMP2_CompareSecondaryValueSet(5000);

/*    if(!(app4Data.erase_screen--)){
        LCD_Clear();
        //app4Data.erase_screen = ((unsigned int)rand() % 50 ) + 1;
        app4Data.erase_screen = 99;
        
    }*/
    vTaskDelay(10);
}

void renderItems(Menu *menu){
    char buf[64];
    char buf1[64];
    uint32_t i = 0;

    for (i = 0; i <= app4Data.lcdRows; i++) {
        LCD_Move(i, 0);
        sprintf(buf, "%s%s", 
                (i ==  menu->index -  menu->pager)? ">": "",
                menu->items[menu->pager+i].label 
        );
        sprintf(buf1, "%-20s",  buf );
        LCD_WriteString(buf1);
    }    
}

void renderMenu(Menu *menu) {

    if(menu->index < 0)
        menu->index = 0;
    
    if(menu->index > menu->maxIndex)
        menu->index = menu->maxIndex;

    if ((menu->index - menu->pager) > app4Data.lcdRows) {
        menu->pager = (menu->index - app4Data.lcdRows);
    } else
    if((menu->index - menu->pager) < 0 ) {
        menu->pager = menu->index;
    }

    renderItems(menu);

    if(app4Data.downBtn){
        if(menu->items[menu->index].activate_func)
            menu->items[menu->index].activate_func( &menu->items[menu->index] );
        app4Data.downBtn = 0;
    }
}

void  Render_Menu() {
    renderMenu(app4Data.menu);
}

void Activate_Menu_Item(MenuItem * item){
    // TODO: perform checks
    app4Data.menu = item->subMenu; 
}

void Activate_Menu_Item_State(MenuItem * item){
    // TODO: perform checks
    app4Data.state = item->state;
}

void Active_Menu_Item_Reset(MenuItem *item){
    SYS_RESET_SoftwareReset();
}

void Render_File_System_Info(){
    char CACHE_ALIGN  buffer[256] = {0,};
    uint8_t CACHE_ALIGN work[512] = {0,};
    SYS_FS_FORMAT_PARAM opt = { 0, };
    
    if(app4Data.downBtn){
            app4Data.state = APP4_STATE_RENDER_MENU;
            app4Data.downBtn = 0;
            return;
    }
    
    if(SYS_FS_RES_SUCCESS == SYS_FS_CurrentDriveGet(buffer))
        printf("SYS_FS_CurrentDriveGet: %s\n", buffer);
    else
        printf("SYS_FS_CurrentDriveGet Failed: %u\n", SYS_FS_Error());
    
    if(SYS_FS_RES_SUCCESS == SYS_FS_CurrentWorkingDirectoryGet(buffer, sizeof(buffer)))
        printf("SYS_FS_CurrentWorkingDirectoryGet: %s\n", buffer);
    else{
        printf("SYS_FS_CurrentDriveGet Failed: %u\n", SYS_FS_Error());
        return;
    }

    opt.fmt = SYS_FS_FORMAT_FAT;
    opt.au_size = 0;

    if(SYS_FS_RES_FAILURE == SYS_FS_DriveFormat(buffer, &opt, (void *)work, sizeof(work))) {
        printf("SYS_FS_DriveFormat: %u\n", SYS_FS_Error());
    }else
    {
        printf("SYS_FS_DriveFormat succeeded\n");
    }
    
    uint32_t totalSectors = 0;
    uint32_t freeSectors = 0;

    if(SYS_FS_RES_FAILURE == SYS_FS_DriveSectorGet( buffer,   &totalSectors,  &freeSectors  ) ) {
        printf("SYS_FS_DriveSectorGet failed: %u\n", SYS_FS_Error());
    }
    else{
        printf("Total: %u Kb, Free: %u Kb\nSectors: %d(total), %d(free)\n", totalSectors*512/1024, freeSectors*512/1024, totalSectors, freeSectors);
    }

    if(SYS_FS_RES_FAILURE == SYS_FS_DirectoryMake( "hello" ) ) {
       printf("SYS_FS_DirectoryMake failed: %u\n", SYS_FS_Error());
    }
    
    SYS_FS_HANDLE fh = SYS_FS_DirOpen(buffer);

    if(SYS_FS_HANDLE_INVALID == fh)
        printf("SYS_FS_DirOpen failed: %u\n", SYS_FS_Error());
    else
        printf("SYS_FS_DirOpen success\n");

    SYS_FS_FSTAT stat;

    stat.lfname = buffer;
    stat.lfsize = sizeof(buffer);
   
    if(SYS_FS_RES_SUCCESS != SYS_FS_DirRead(fh, &stat)){
        printf("SYS_FS_DirRead failed: %u\n", SYS_FS_Error());
    }

    printf("Directory read:%s (%u)\n", *stat.lfname==0?stat.fname:stat.lfname, stat.fsize);
    
    //SYS_FS_HANDLE SYS_FS_DirOpen(const char* path);

/*
    
    SYS_FS_HANDLE fh = SYS_FS_DirOpen(buffer);

    if(SYS_FS_HANDLE_INVALID == fh)
        printf("SYS_FS_DirOpen failed: %u\n", SYS_FS_Error());
    else
        printf("SYS_FS_DirOpen success\n");

    SYS_FS_FSTAT stat;
    
    if(SYS_FS_RES_SUCCESS ==  SYS_FS_DirRead(fh, &stat)){
        printf("SYS_FS_DirRead succeeded\n");
    }else{
        printf("SYS_FS_DirRead failed: %u\n", SYS_FS_Error());
    }

        if(SYS_FS_RES_SUCCESS == SYS_FS_CurrentWorkingDirectoryGet(buffer, sizeof(buffer)))
        printf("SYS_FS_CurrentWorkingDirectoryGet: %s\n", buffer);
    else
        printf("SYS_FS_CurrentWorkingDirectoryGet Failed!!!\n"); 

    uintptr_t  handle;

    if(SYS_FS_RES_SUCCESS ==  FATFS_opendir(handle, buffer) ){
        printf("FATFS_opendir\n");
    }
    else
    {
        printf("FATFS_opendir Failed!!!\n");
    }
 */
}

void Active_Free_Sectors(MenuItem * item){
    char CACHE_ALIGN  buffer[256] = {0,};
    uint8_t CACHE_ALIGN work[512] = {0,};
    SYS_FS_FORMAT_PARAM opt = { 0, };

    if(SYS_FS_RES_SUCCESS == SYS_FS_CurrentDriveGet(buffer))
        printf("SYS_FS_CurrentDriveGet: %s\n", buffer);
    else
        printf("SYS_FS_CurrentDriveGet Failed: %u\n", SYS_FS_Error());

    opt.fmt = SYS_FS_FORMAT_FAT;
    opt.au_size = 0;

    if(SYS_FS_RES_FAILURE == SYS_FS_DriveFormat(buffer, &opt, (void *)work, sizeof(buffer))) {
        printf("SYS_FS_DriveFormat: %u\n", SYS_FS_Error());
    }else
    {
        printf("SYS_FS_DriveFormat succeeded\n");
    }
    
    uint32_t totalSectors = 0;
    uint32_t freeSectors = 0;

    if(SYS_FS_RES_FAILURE == SYS_FS_DriveSectorGet( buffer,   &totalSectors,  &freeSectors  ) ) {
        printf("SYS_FS_DriveSectorGet failed: %u\n", SYS_FS_Error());
    }
    else{
        printf("Sectors: %d(total), %d(free)\n", totalSectors, freeSectors);
    }
    
    if(SYS_FS_RES_SUCCESS == SYS_FS_CurrentWorkingDirectoryGet(buffer, sizeof(buffer)))
        printf("SYS_FS_CurrentWorkingDirectoryGet: %s\n", buffer);
    else
        return;
    
    if(SYS_FS_RES_FAILURE == SYS_FS_DirectoryMake( "hello" ) ) {
       printf("SYS_FS_DirectoryMake failed: %u\n", SYS_FS_Error());
    }
    
    SYS_FS_HANDLE fh = SYS_FS_DirOpen(buffer);

    if(SYS_FS_HANDLE_INVALID == fh)
        printf("SYS_FS_DirOpen failed: %u\n", SYS_FS_Error());
    else
        printf("SYS_FS_DirOpen success\n");

    SYS_FS_FSTAT stat;
    
    stat.lfname = buffer;
    stat.fsize = sizeof(buffer);
   
    if(SYS_FS_RES_SUCCESS != SYS_FS_DirRead(fh, &stat)){
        printf("SYS_FS_DirRead failed: %u\n", SYS_FS_Error());
    }

    printf("Directory read:%s (%u)\n", stat.lfname, stat.fsize);
    
/*
    
    if(SYS_FS_RES_FAILURE == SYS_FS_DriveSectorGet( buffer,   &totalSectors,  &freeSectors  ) ) {
        printf("SYS_FS_DriveSectorGet failed: %u\n", SYS_FS_Error());
    }
    else{
        printf("Sectors: %d(total), %d(free)\n", totalSectors, freeSectors);
    }
    
    if(SYS_FS_RES_FAILURE == SYS_FS_DirectoryChange( buffer ) ) {
        printf("SYS_FS_DirectoryChange failed: %u\n", SYS_FS_Error());
    }
    else{
        printf("Sectors: %d(total), %d(free)\n", totalSectors, freeSectors);
    }


        if(SYS_FS_RES_SUCCESS == SYS_FS_CurrentWorkingDirectoryGet(buffer, sizeof(buffer)))
        printf("SYS_FS_CurrentWorkingDirectoryGet: %s\n", buffer);
    else
        printf("SYS_FS_CurrentWorkingDirectoryGet Failed!!!\n"); 

    uintptr_t  handle;

    if(SYS_FS_RES_SUCCESS ==  FATFS_opendir(handle, buffer) ){
        printf("FATFS_opendir\n");
    }
    else
    {
        printf("FATFS_opendir Failed!!!\n");
    }
 */
}