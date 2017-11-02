#include <SoftwareSerial.h>

//To flash onto ATTiny45 with Arduino as the ISP:
//Arduino Pin 10 -> ATTiny Reset
//Arduino Pin 11 -> ATTiny Pin 0 (MOSI)
//Arduino Pin 12 -> ATTiny Pin 1 (MISO)
//Arduino Pin 13 -> ATTiny Pin 2 (SCK)

//To use Arduino as a USB - Serial Interface
//Arduino TX -> ATTiny TX (Pin 3) as defined below
//Arduino RX -> ATTiny RX (Pin 4)
//Arduino Reset -> Arduino GND
//ATTiny LED Left Output -> ATTiny Pin 0
//ATTiny LED Right Output -> ATTiny Pin 1


char readString[6+1];
SoftwareSerial TinySerial(3,4);

void setup() {
  TinySerial.begin(9600);
  pinMode(0, OUTPUT); 
  pinMode(1, OUTPUT);
}

void loop() {
    if (TinySerial.available())  {
    byte size = TinySerial.readBytes(readString, 6);

    readString[size] = 0; //Pad string with zero

    //String format L,200!R,200! <- [LED Position, PWM (0-255) !]
    char* command = strtok(readString, "!");
    while (command != 0){
      //Split by comma   
      char* separator = strchr(command, ',');
      if(separator != 0){
        *separator = 0;
        char letter = *command;
        //TinySerial.println(letter);
        ++separator;
        int pwmVal = atoi(separator);
        TinySerial.println(pwmVal);

        if (letter == 'L'){
          analogWrite(0,pwmVal);          
          //TinySerial.println("L" + '\n');
        }
        else if (letter == 'R'){
          analogWrite(1,pwmVal);
          //TinySerial.println("R" + '\n');
        }
        else if (letter == 'B'){
          analogWrite(0,pwmVal);
          analogWrite(1,pwmVal);
          //TinySerial.println("B" + '\n');
        }
      }
      command = strtok(0,"!"); 
      delay(100);
    }
  }
}

    
   



