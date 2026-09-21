unsigned int pre_1;
unsigned int pre_2;
unsigned int pre_3;
unsigned int pre_4;
unsigned int pre_5;
int press_1[100];
int press_2[100];
int press_3[100];
int press_4[100];
int press_5[100];

int index=0;
int avg_press_1(int taps)
{
  int i;
  long sum_pre;
  
  press_1[index++] = analogRead(0);
  index = index % taps;  
 
  sum_pre = 0;
  for(i=0; i<taps; i++)
    sum_pre += press_1[i];

  return map(sum_pre/taps,65,190,0,25);
}
int avg_press_2(int taps)
{
  int i;
  long sum_pre;
  
  press_2[index++] = analogRead(1);
  index = index % taps;  
 
  sum_pre = 0;
  for(i=0; i<taps; i++)
    sum_pre += press_2[i];
 
  return map(sum_pre/taps,65,183,0,25);
}
int avg_press_3(int taps)
{
  int i;
  long sum_pre;
  
  press_3[index++] = analogRead(2);
  index = index % taps;  
 
  sum_pre = 0;
  for(i=0; i<taps; i++)
    sum_pre += press_3[i];
 
  return map(sum_pre/taps,65,180,0,25);
}
int avg_press_4(int taps)
{
  int i;
  long sum_pre;
  
  press_4[index++] = analogRead(3);
  index = index % taps;  
 
  sum_pre = 0;
  for(i=0; i<taps; i++)
    sum_pre += press_4[i];
 
  
  return map(sum_pre/taps,65,180,0,25);
}
int avg_press_5(int taps)
{
  int i;
  long sum_pre;
  
  press_5[index++] = analogRead(4);
  index = index % taps;  
 
  sum_pre = 0;
  for(i=0; i<taps; i++)
    sum_pre += press_5[i];
 
  
  return map(sum_pre/taps,65,200,0,25);
}
void setup()
{
  Serial.begin(9600);
}

void loop()
{
//  pre=map(pre,335,500,0,25);

  pre_1=avg_press_1(50);
  pre_2=avg_press_2(50);
  pre_3=avg_press_3(50);
  pre_4=avg_press_4(50);
  pre_5=avg_press_5(50);
  
 /*pre_1=analogRead(0);
  pre_2=analogRead(1);
  pre_3=analogRead(2);
  pre_4=analogRead(3);
  pre_5=analogRead(4);*/


  Serial.print(pre_1);
  Serial.print("  ");
  Serial.print(pre_2);
  Serial.print("  ");
  Serial.print(pre_3);
  Serial.print("  ");
  Serial.print(pre_4); 
  Serial.print("  ");
  Serial.println(pre_5);
}
