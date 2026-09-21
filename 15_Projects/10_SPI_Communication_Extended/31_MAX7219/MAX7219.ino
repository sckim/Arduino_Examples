#include "Arduino.h"
//We always have to include the library
#include "LedControl.h"

// Matrix code generator
// https://xantorohara.github.io/led-matrix-editor/#3810101010101810

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn
 pin 11 is connected to the CLK
 pin 10 is connected to LOAD
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(11,13,10,2);

uint64_t IMAGES[] = {
  0x1c08080808080c08,
  0x3e0408102020221c,
  0x1c2220201820221c,
  0x20203e2224283020,
  0x1c2220201e02023e,
  0x1c2222221e02221c,
  0x040404081020203e,
  0x1c2222221c22221c,
  0x1c22203c2222221c,
  0x1c2222222222221c
};
int IMAGES_LEN = sizeof(IMAGES)/8;

void displayImage(int addr, uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    lc.setRow(addr, 7-i, row);
//  or
//    for (int j = 0; j < 8; j++) {
//      lc.setLed(addr, i, j, bitRead(row, j));
//    }
  }
}

/* we always wait a bit between updates of the display */
unsigned long delaytime=1000;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  lc.shutdown(1,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  lc.setIntensity(1,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

//void show(int addr, byte *a)
//{
//	for(int i=0; i<8; i++)
//		lc.setRow(addr, 7-i, a[i]);
//}
/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix.
 (you need at least 5x7 leds to see the whole chars)
 */
//void writeArduinoOnMatrix() {
//  /* here is the data for the characters */
//  byte a[5]={B01111110,B10001000,B10001000,B10001000,B01111110};
//  byte r[5]={B00111110,B00010000,B00100000,B00100000,B00010000};
//  byte d[5]={B00011100,B00100010,B00100010,B00010010,B11111110};
//  byte u[5]={B00111100,B00000010,B00000010,B00000100,B00111110};
//  byte i[5]={B00000000,B00100010,B10111110,B00000010,B00000000};
//  byte n[5]={B00111110,B00010000,B00100000,B00100000,B00011110};
//  byte o[5]={B00011100,B00100010,B00100010,B00100010,B00011100};
//
//  /* now display them one by one with a small delay */
//  show(0, a);
//  delay(delaytime);
//  show(0, r);
//  delay(delaytime);
//  show(0, d);
//  delay(delaytime);
//  show(0, u);
//  delay(delaytime);
//  show(0, i);
//  delay(delaytime);
//  show(0, n);
//  delay(delaytime);
//  show(0, o);
//  delay(delaytime);
//}

/*
  This function lights up a some Leds in a row.
 The pattern will be repeated on every row.
 The pattern will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void rows() {
  for(int row=3;row<8;row++) {
    lc.setRow(0,row,B10100000);
    delay(delaytime);
//    lc.setRow(1,row,B10110000);
//    delay(delaytime);
//    lc.setRow(0,row,(byte)0);
//    for(int i=0;i<row;i++) {
//      delay(delaytime);
//      lc.setRow(0,row,B10100000);
//      delay(delaytime);
//      lc.setRow(0,row,(byte)0);
//    }
  }
}

/*
  This function lights up a some Leds in a column.
 The pattern will be repeated on every column.
 The pattern will blink along with the column-number.
 column number 4 (index==3) will blink 4 times etc.
 */
void columns() {
  for(int col=0;col<8;col++) {
    delay(delaytime);
    lc.setColumn(0,col,B10100000);
    delay(delaytime);
    lc.setColumn(0,col,(byte)0);
    for(int i=0;i<col;i++) {
      delay(delaytime);
      lc.setColumn(0,col,B10100000);
      delay(delaytime);
      lc.setColumn(0,col,(byte)0);
    }
  }
}

/*
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void single() {
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      delay(delaytime);
      lc.setLed(0,row,col,true);
      delay(delaytime);
      for(int i=0;i<col;i++) {
        lc.setLed(0,row,col,false);
        delay(delaytime);
        lc.setLed(0,row,col,true);
        delay(delaytime);
      }
    }
  }
}

void loop() {
  //writeArduinoOnMatrix();
  for(int i=0; i<IMAGES_LEN; i++) {
	  displayImage(0, IMAGES[i]);
      delay(delaytime);
  }
//  lc.clearDisplay(0);
//  rows();
//  lc.clearDisplay(0);
//  lc.clearDisplay(1);
//  columns();
//  single();
}
