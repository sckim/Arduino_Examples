#define BBOARD_LED 12
#define BUILTIN_LED 13
#define BUTTON 2

bool currentButtonState = false,
        lastButtonState = false;

int bCounter = 0,
    interval = 2;

int GetStringNumber();

void setup()
{
    int i;
    
    pinMode(BBOARD_LED,OUTPUT);
    pinMode(BUTTON,INPUT);
    Serial.begin(9600);
    Serial.println("Welcome to my State Changer Arduino demo!");
    i = atoi("123");
    Serial.println(i);
}

void loop()
{
    if(Serial.available() > 0)
    {
        interval = GetStringNumber();
        Serial.print("LED interval is now ");
        Serial.println(interval,DEC);
    }

    currentButtonState = digitalRead(BUTTON);
  
    if(currentButtonState != lastButtonState) //Is there any change in the button state?
    {
         if(currentButtonState == true)
         {
             bCounter++;
            
             Serial.println("down");
             Serial.print("Number of presses: ");
             Serial.println(bCounter,DEC);
            
             if(bCounter % interval == 0) //Has the button been pressed "interval" times?
             {
                 digitalWrite(BBOARD_LED,1);
                 Serial.println("LED lit");
             }
             else
             {
                 digitalWrite(BBOARD_LED,0);
                 Serial.println("LED unlit");
             }
         }
         else
             Serial.println("up");
    }
    
    lastButtonState = currentButtonState; //Updating button state  
}

int GetStringNumber()
{
    int value = 0;
    char temp[10];
    int  index=0;
    
    while(1)
    {
        if(Serial.available())  {
          /*Read a byte as it comes into the serial buffer*/
          char byteBuffer = Serial.read();
          Serial.print(byteBuffer);
          temp[index++] = byteBuffer;
         
        if(byteBuffer == '#') //Is the data a valid character?
          break;
      }
    }
    temp[index] ='\0';

   return atoi(temp);
}
