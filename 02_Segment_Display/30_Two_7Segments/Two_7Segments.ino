#include <Arduino.h>

unsigned char SEG[10] = {0b11000000, 0b11111001,
                         0b10100100, 0b10110000,
                         0b10011001, 0b10010010,
                         0b10000010, 0b11111000,
                         0b10000000, 0b10010000};
unsigned char num = 0;

void setup()
{
    for (int i = 0; i < 8; i++)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);
    }
    pinMode(8, OUTPUT); // 1의 자리 선택 핀
    pinMode(9, OUTPUT); // 10의 자리 선택 핀
}

void dispSeg(unsigned char ch, unsigned char digit)
{
    digitalWrite(8, digit == 0); // 1의 자리 활성화 (LOW 활성화 가정)
    digitalWrite(9, digit == 1); // 10의 자리 활성화

    for (int i = 0; i < 8; i++)
    {
        digitalWrite(i, (SEG[ch] & (1 << i)) ? HIGH : LOW);
    }
}

int duration = 0;

void loop()
{
    unsigned char tens = num / 10; // 10의 자리
    unsigned char ones = num % 10; // 1의 자리

    dispSeg(ones, 0); // 1의 자리 출력
    delay(10);
    dispSeg(tens, 1); // 10의 자리 출력
    delay(10);

    duration++;
    if (duration % 50 == 0)
    {
        num++;
        if (num > 99)
            num = 0;
    }
}
