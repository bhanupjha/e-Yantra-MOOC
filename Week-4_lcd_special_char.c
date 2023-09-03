/*! \mainpage Week-4 Challenge Activity 1: Display custom characters on LCD
 *
 * @author     e-Yantra Team
 * @date       2020/04/01
 *
 * \subsection Aim
 * to display custom characters on LCD.
 *
 * \subsection Connections (Proteus Project)
 * LCD Connections:        <br>
 *   LCD Pins   Micro-controller Pins     <br>
 *     RS  --> PB0      <br>
 *     RW  --> PB2      <br>
 *     EN  --> PB1      <br>
 *     DB7 --> PD7      <br>
 *     DB6 --> PD6      <br>
 *     DB5 --> PD5      <br>
 *     DB4 --> PD4      <br>
 *
 */

//---------------------------------- HEADER FILES -----------------------------------------------------

#include "firebird_simulation.h"  // Header file included that contains macro definitions essential for Firebird V robot and Simulation
#include <util/delay.h>     // Standard AVR Delay Library
#include "lcd.h"      // LCD Header file included that contains function definitions essential to deal with LCD

//------------------------------------ Global Variables ---------------------------------------------------

unsigned char pattern_e[32] = {
 0b00011111,      
 0b00010001,
 0b00010011,
 0b00010110,
 0b00011100,
 0b00010000,
 0b00011111,
 0b00000000
};

unsigned char pattern_a[32] = {
 0b00000011,0b00000100,0b00001000,0b00010000,0b00000000,0b00000000,0b00000000,0b00000000, //for left side of positive sine wave
 0b00011000,0b00000100,0b00000010,0b00000001,0b00000000,0b00000000,0b00000000,0b00000000, //for right side of positive sine wave
 0b00000000,0b00000000,0b00000000,0b00000000,0b00010000,0b00001000,0b00000111,0b00000000, //for left side of negative sine wave
 0b00000000,0b00000000,0b00000000,0b00000000,0b00000001,0b00000010,0b00011100,0b00000000 //for right side of negative sine wave
};

//------------------------------------ FUNCTIONS ---------------------------------------------------

/**
* @brief      Store the custom characters at CGRAM location.<br>
*         
* @details    This function stores the 8 byte pattern at the CGRAM memort.<br>
*
* @param[in]  loc     The address of CGRAM 1 - 7
*      *pattern   Base address of array where the pattern is stored
*/

//<< NOTE >>: You should not change this function in order to get the required output
void lcd_custom_char (unsigned char loc, unsigned char *pattern)
{
 /*
 << TODO >> :
  Command 0x40 and onwards to force the device to point CGRAM address
     Write 8 byte for generation of the custom character 
 */ 
 lcd_wr_command(0x40 + (loc * 8)); // Command 0x40 and onwards to force the device to point CGRAM address
 for (unsigned char i = 0; i < 8; i++) {
  lcd_wr_char(loc,i,pattern[i]);
 }
}


/**
* @brief      Display the logo "e" using custom character.<br>
*         
* @details    This function displays the pattern "e".<br>
*
*/  
void Display_logo()
{
 lcd_string(1,3,"e-Yantra Logo");
 _delay_ms(2000);
 lcd_clear();      // Clear the LCD
 /*
 << TODO >> :
  displays the logo on LCD 
  Use the binary pattern stored in pattern_e array<br> 
*  and pass the base address of array to the lcd_custom_char function.
 */
 // Display the custom character 'e' on the LCD
 lcd_custom_char(0, pattern_e);
 lcd_home(); // Move the cursor to the first row first column of LCD
 lcd_wr_char(2,8,0x00);
}

/**
* @brief      Display the sine wave.<br>
*         
* @details    This function displays the sine wave on LCD.<br>
*
*/

// Define the array to store the binary patterns for each step of the sine wave
unsigned char sine_wave[4][8] = {
	{0b00000011, 0b00000100, 0b00001000, 0b00010000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00011000, 0b00000100, 0b00000010, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00010000, 0b00001000, 0b00000111, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b00000010, 0b00011100, 0b00000000}
};
  
void Display_sine_wave()
{
	int i;
	lcd_string(1,3,"Sine Wave");
	_delay_ms(2000);
	lcd_clear();						// Clear the LCD
	lcd_custom_char(0, sine_wave[0]);		// Build Character1 at position 1
	lcd_custom_char(1, sine_wave[1]);		// Build Character1 at position 1
	lcd_custom_char(2, sine_wave[2]);		// Build Character1 at position 1
	lcd_custom_char(3, sine_wave[3]);		// Build Character1 at position 1
	for(i=0;i<16;i++)
	lcd_wr_char(1,i+1,(i%4));
	for(i=0;i<16;i++)
	lcd_wr_char(2,i+1,(i%4));
}



//---------------------------------- MAIN ----------------------------------------------------------------
/**
 * @brief      Main Function
 *
 * @details    First Initializes the LCD
 *      and displays the different patterns on LCD on by one. 
 */
 int main(void)
{
 lcd_port_config();     // Initialize the LCD port
 lcd_init();       // Initialize the LCD
 lcd_clear();      // Clear the LCD
    
 Display_logo();
 _delay_ms(2000);
 lcd_clear();      // Clear the LCD
 Display_sine_wave();
 _delay_ms(2000);
 lcd_clear();      // Clear the LCD
 
 while(1);
}