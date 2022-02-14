/*
    LCD Display problem from Kino in Microchip Forum
    https://www.microchip.com/forums/FindPost/1161411  

 * Using PMP peripheral in PIC32MX795 for communication with a Character Liquid Crystal Display. 
 */

// wait for the peripheral master port (PMP) to be ready
// should be called before every read and write operation
void waitPMP(void);

// wait for the LCD to finish its command.
// We check this by reading from the LCD
void waitLCD(void);

// set up the parallel master port (PMP) to control the LCD 
// pins RE0 - RE7 (PMD0 - PMD7) connect to LCD pins D0 - D7
// pin RD4 (PMENB) connects to LCD pin E
// pin RD5 (PMRD/PMWR) Connects to LCD pin R/W
// pin RB13 (PMA10) Connects to RS.
// interrupts will be disabled while this function executes
void PMP_Setup(void);
void LCD_Setup(void);

// Clears the display and returns to the home position (0,0)
void LCD_Clear(void);

// Return the cursor and display to the home position (0,0)
void LCD_Home(void);

// Issue the LCD entry mode set command
// This tells the LCD what to do after writing a character
// id : 1 increment cursor, 0 decrement cursor
// s : 1 shift display right, 0 don't shift display
void LCD_Entry(int id, int s);

// Issue the LCD Display command
// Changes display settings
// d : 1 display on, 0 display off
// c : 1 cursor on, 0 cursor off
// b : 1 cursor blinks, 0 cursor doesn't blink
void LCD_Display(int d, int c, int b);

// Issue the LCD display shift command
// Move the cursor or the display right or left
// sc : 0 shift cursor, 1 shift display
// rl : 0 to the left, 1 to the right
void LCD_Shift(int sc, int rl);

// Issue the LCD Functions set command
// This controls some LCD settings
// You may want to clear the screen after calling this
// n : 0 one line, 1 two lines
// f : 0 small font, 1 large font (only if n == 0)
void LCD_Function(int n, int f);

// Move the cursor to the desired line and column
// Does this by issuing a DDRAM Move instruction
// line : line 0 or line 1
// col  : the desired column
void LCD_Move(int line, int col);

// Sets the CGRAM address, used for creating custom
// characters
// addr address in the CGRAM to make current
void LCD_CMove(unsigned char addr);

// Writes the character to the LCD at the current position
void LCD_WriteChar(char c);

// Write a string to the LCD starting at the current cursor
void LCD_WriteString(const char *str);

// Make val a custom character.  This only implements 
// The small font version
// val : between 0 and 7
// data : 7 character array.  The first 5 bits of each character
//        determine whether that pixel is on or off
void LCD_CustomChar(unsigned char val, const char * data);

// Write data to the LCD and wait for it to finish by checking the busy flag. 
// rs : the value of the RS signal, 0 for an instruction 1 for data
// data : the byte to send
void LCD_Write(int rs, unsigned char data);

// read data from the LCD.  
// rs : the value of the RS signal 0 for instructions status, 1 for data
unsigned char LCD_Read(int rs);