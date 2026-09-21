#include <Keypad.h>

#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

// notes to play, corresponding to the 3 sensors:
int notes[] = {
  NOTE_A4, NOTE_B4, NOTE_C5
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {11,10,9,8}; //Rows 0 to 3
byte colPins[numCols]= {7,6,5,4}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup()
{
  	pinMode(13, OUTPUT);
  	pinMode(3, OUTPUT);

	Serial.begin(9600);
}

//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
void loop()
{
	char keypressed = myKeypad.getKey();
	if (keypressed != NO_KEY)	{
		Serial.println(keypressed);

        tone(3, notes[keypressed%3], 50);
        digitalWrite(13, HIGH);
      	delay(200);
      	digitalWrite(13, LOW);
	}
}
