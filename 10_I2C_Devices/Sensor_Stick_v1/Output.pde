void printdata(void)
{    
      Serial.print("!");

      #if 0
      Serial.print("ANG:");
      Serial.print(ToDeg(roll));
      Serial.print(",");
      Serial.print(ToDeg(pitch));
      Serial.print(",");
      Serial.print(ToDeg(yaw));
      #endif      
      #if 1
      Serial.print("Data:");
      Serial.print(accel_x);
      Serial.print (",");
      Serial.print(accel_y);
      Serial.print (",");
      Serial.print(accel_z);
      Serial.print(",");
      Serial.print(gyro_x);  //(int)read_adc(0)
      Serial.print(",");
      Serial.print(gyro_y);
      Serial.print(",");
      Serial.print(gyro_z);  
      /*
      Serial.print(",");
      Serial.print(magnetom_x);
      Serial.print (",");
      Serial.print(magnetom_y);
      Serial.print (",");
      Serial.print(magnetom_z);      
      */
      Serial.print(",");
      Serial.println(Button_pressed);
      #endif
      
      #if 0
      Serial.print (",DCM:");
      Serial.print(convert_to_dec(DCM_Matrix[0][0]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[0][1]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[0][2]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[1][0]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[1][1]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[1][2]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[2][0]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[2][1]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[2][2]));
      #endif
}

long convert_to_dec(float x)
{
  return x*10000000;
}

