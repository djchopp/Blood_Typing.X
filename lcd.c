#include <xc.h>
#include "lcd.h"
#include "lcd18f.h"

/*************LCD Methods*******************/
void lcdinit(){
  _displayfunction = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
}

void begin(){

  _numlines = 2;
  _currline = 0;

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
  __delay_us(5000);
  // Now we pull both RS and R/W low to begin commands
  RS = 0;
  EN = 0;

      // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46

    // we start in 8bit mode, try to set 4 bit mode
    write4bits(0x03);
    __delay_us(4500); // wait min 4.1ms

    // second try
    write4bits(0x03);
    __delay_us(4500); // wait min 4.1ms

    // third go!
    write4bits(0x03);
    __delay_us(150);

    // finally, set to 4-bit interface
    write4bits(0x02);

  // finally, set # lines, font size, etc.
  command(LCD_FUNCTIONSET | _displayfunction);

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  display();

  // clear it off
  clear();

  // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  command(LCD_ENTRYMODESET | _displaymode);

}

void clear(){
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  __delay_us(2000);  // this command takes a long time!
}

void home(){
  command(LCD_RETURNHOME);  // set cursor position to zero
  __delay_us(2000);  // this command takes a long time!
}

void scrollDisplayLeft() {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void scrollDisplayRight() {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void display(){
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void setCursor(uint8_t col, uint8_t row){
    int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    if ( row >= _numlines ) {
        row = _numlines-1;    // we count rows starting w/0
    }

  command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void command(uint8_t value){
    send(value, 0);
}

void prints(const char *message){	// Write message to LCD (C string type)
    //command(LCD_DISPLAYOFF); // disable display;
    while (*message){			// Look for end of string
        send(*message++,1);
    }
    //command(LCD_DISPLAYON); // enable display;
}

void send(uint8_t value, uint8_t mode){
   RS=mode;
   write4bits(value>>4);
   write4bits(value);
}

void write4bits(uint8_t value){
    data1 = (value >> 0) & 0x01;
    data2 = (value >> 1) & 0x01;
    data3 = (value >> 2) & 0x01;
    data4 = (value >> 3) & 0x01;
    pulseEnable();
}

void pulseEnable(){
  EN=0;
  __delay_us(1);
  EN=1;
  __delay_us(1);
  EN=0;
  __delay_us(100);
}


