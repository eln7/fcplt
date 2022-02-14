/*
    LCD Display problem from Kino in Microchip Forum
    https://www.microchip.com/forums/FindPost/1161411  
 * 
 *  Using PMP peripheral in PIC32MX795 for communication with a Character Liquid Crystal Display. 
 */
#include <xc.h>
#include "peripheral/pmp/plib_pmp.h"
#include "definitions.h"
#include "LCD.h"

#if __32MX795F512L
  #define PMABIT 10 // which PMA bit number to use for LCD Register Select (RS) signal pin. 
#elif __32MX110F016B
//  #define PMABIT  0
#elif __32MX150F128B
  #define PMABIT 14
#elif  __32MX695F512L
    #define PMABIT 14
#endif

// wait for the peripheral master port (PMP) to be ready
// should be called before every read and write operation
void waitPMP(void)
{
  while(PMMODEbits.BUSY) { ; }
}

// wait for the LCD to finish its command.
// We check this by reading from the LCD
void waitLCD() {
  volatile unsigned char val = 0x80;
  PMADDRCLR = 1 << PMABIT;			/* LCD Command RS = 0 */
  PMDIN;								/* Initiate a Read cycle. */
  while (val & 0x80) { // Read from the LCD until the Busy flag (BF, 7th bit) is 0
    waitPMP();                  // wait for the PMP to be ready
    val = PMDIN;
    waitPMP();
    //SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "LCD is Busy\r\n");
  }
}

// set up the parallel master port (PMP) to control the LCD 
// pins RE0 - RE7 (PMD0 - PMD7) connect to LCD pins D0 - D7
// pin RD4 (PMENB) connects to LCD pin E
// pin RD5 (PMRD/PMWR) Connects to LCD pin R/W
// pin RB13 (PMA10) Connects to RS.
// interrupts will be disabled while this function executes

void PMP_Setup() {
  IEC1bits.PMPIE = 0;    // disable PMP interrupts
  PMCON = 0;             // clear PMCON, like it is on reset
  PMCONbits.PTWREN = 1;  // PMENB strobe enabled
  PMCONbits.PTRDEN = 1;  // PMRD/PMWR enabled
  PMCONbits.WRSP = 1;    // Read/write strobe is active high
  PMCONbits.RDSP = 1;    // Read/write strobe is active high

  PMMODE = 0;            // clear PMMODE like it is on reset
  PMMODEbits.MODE = 0x3; // set master mode 1, which uses a single strobe

  // Set up wait states.  The LCD requires data to be held on its lines
  // for a minimum amount of time.
  // All wait states are given in peripheral bus clock
  // (PBCLK) cycles.  PBCLK of 80 MHz in our case
  // so one cycle is 1/80 MHz = 12.5 ns.
  // The timing controls asserting/clearing PMENB (RD4) which
  // is connected to the E pin of the LCD (we refer to the signal as E here)
  // The times required to wait can be found in the LCD controller's data sheet.
  // The cycle is started when reading from or writing to the PMDIN SFR.
  // Note that the wait states for writes start with minimum of 1 (except WAITE)
  // We add some extra wait states to make sure we meet the time and
  // account for variations in timing amongst different HD44780 compatible parts.
  // The timing we use here is for the KS066U which is faster than the HD44780.
  
  PMMODEbits.WAITB = 0x3;  // Tas in the LCD datasheet is 60 ns
  PMMODEbits.WAITM = 0x3;  // PWeh in the data sheet is 230 ns (we don't quite meet this)
  PMMODEbits.WAITE = 0x3;  // after E is low wait Tah (10ns)

  PMAEN |= 1 << PMABIT;    // PMA is an address line, to use for RS (Register Select) signal.
  PMAENSET =   _PMAEN_PTEN14_MASK;
  PMCONbits.ON = 1;        // enable the PMP peripheral
  waitPMP();
}

void LCD_Setup() {
  // perform the initialization sequence of the LCD Controller    
  /* Datasheet prescribe delay before and after Function Set, if Initialization by Command. */
  LCD_Function(1, 0);      // 2 line mode, small font
  /* DL=1 is 8 bit interface		   0b 0E0 0011 1000 */	
  /* LCD_Function cannot be used for Initialization by Command, Assume Power-on default Reset. */
  LCD_Display(1, 0, 0);    // Display control: display on, cursor off, blinking cursor off	/* 0b 0E0 0000 1100 */
  LCD_Clear();             // clear the LCD													/* 0b 0E0 0000 0001 */
  LCD_Entry(1, 0);         // Cursor moves left to right. do not shift the display.			/* 0b 0E0 0000 0110 */
}

// Clears the display and returns to the home position (0,0)
void LCD_Clear(void) {
  LCD_Write(0, 0x01); //clear the whole screen
}

// Return the cursor and display to the home position (0,0)
void LCD_Home(void) {
  LCD_Write(0, 0x02);
}

// Issue the LCD entry mode set command
// This tells the LCD what to do after writing a character
// id : 1 increment cursor, 0 decrement cursor
// s : 1 shift display right, 0 don't shift display
void LCD_Entry(int id, int s) {
  LCD_Write(0, 0x04 | (id << 1) | s);
}

// Issue the LCD Display command
// Changes display settings
// d : 1 display on, 0 display off
// c : 1 cursor on, 0 cursor off
// b : 1 cursor blinks, 0 cursor doesn't blink
void LCD_Display(int d, int c, int b) {
  LCD_Write(0, 0x08 | (d << 2) | (c << 1) | b);				/* 0b 0E0 0000 1100 */
}

// Issue the LCD display shift command
// Move the cursor or the display right or left
// sc : 0 shift cursor, 1 shift display
// rl : 0 to the left, 1 to the right
void LCD_Shift(int sc, int rl) {
  LCD_Write(0, 0x1 | (sc << 3) | (rl << 2));
}

// Issue the LCD Functions set command
// This controls some LCD settings
// You may want to clear the screen after calling this
// n : 0 one line, 1 two lines
// f : 0 small font, 1 large font (only if n == 0)
void LCD_Function(int n, int f) {
  LCD_Write(0, 0x30 | (n << 3) | (f << 2));					/* 0b 0E0 0011 1000 */
}

// Move the cursor to the desired line and column
// Does this by issuing a DDRAM Move instruction
// line : line 0 or line 1
// col  : the desired column
void LCD_Move(int line, int col) {
  unsigned int bases[] = {0x00, 0x40, 0x14, 0x54};
  LCD_Write(0, (0x80 | bases[line] ) + col);
}

// Sets the CGRAM address, used for creating custom
// characters
// addr address in the CGRAM to make current
void LCD_CMove(unsigned char addr) {
  LCD_Write(0, 0x40 | addr);
}

// Writes the character to the LCD at the current position
void LCD_WriteChar(char c) {
  LCD_Write(1, c);
}

// Write a string to the LCD starting at the current cursor
void LCD_WriteString(const char *str) {
  while(*str) {
    LCD_WriteChar(*str); // increment string pointer after char sent
    ++str;
  }
}

// Make val a custom character.  This only implements 
// The small font version
// val : between 0 and 7
// data : 7 character array.  The first 5 bits of each character
//        determine whether that pixel is on or off
void LCD_CustomChar(unsigned char val, const char * data) {
  int i = 0;
  for(i = 0; i < 7; ++i) {
    LCD_CMove(((val & 7) << 2) | i);
    LCD_Write(1, data[i]);
  }
}

// Write data to the LCD and wait for it to finish by checking the busy flag. 
// rs : the value of the RS signal, 0 for an instruction 1 for data
// data : the byte to send
void LCD_Write(int rs, unsigned char data) {
  waitLCD();           // wait for the LCD to be ready
    waitPMP();
  if(rs) { // 1 for data									/* 0b 0E1 0111 1000 */
    waitPMP();
    PMADDRSET = 1 << PMABIT;
    waitPMP();
  } else { // 0 for command
        waitPMP();
    PMADDRCLR = 1 << PMABIT;
    waitPMP();
  }
  //Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
  //Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
  waitPMP();           // Wait for the PMP to be ready	/* wait here? should not be be needed, Address Multiplexing? */
  PMDIN = data;        // send the data					/* 0b 0E0 1000 0000 */
  waitPMP();
}

// read data from the LCD.  
// rs : the value of the RS signal 0 for instructions status, 1 for data
unsigned char LCD_Read(int rs) {
  volatile unsigned char val = 0; // volatile so 1st read doesn't get optimized away
  if(rs) { // 1 to read data
    PMADDRSET = 1 << PMABIT;
      waitPMP();
  } else { // 0 to read command status
    PMADDRCLR = 1 << PMABIT;
      waitPMP();
  }
  // from the PIC32 reference manual, you must read twice to actually get the data
  waitPMP();                  // wait for the PMP to be ready
  val = PMDIN;
  waitPMP();
  val = PMDIN;
  return val;
}
