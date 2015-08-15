/*
mbkSerial1 allows you to control your Master Beta Kit over the serial port via the USB connected to the UNO.  
Syntax to send down the serial is identical to that of the Arduino language, and this allows the user
to use two commands: analogRead() and analogWrite()

analogRead(A0[or A1, etc]) reads the analog value from A0[or A1 etc], returning an integer between 0 and 1023  
Remember the knob is at A2, so to read the knob use for example
int knob = analogRead(A2);

analogWrite(pin,value) outputs an analog value to a pin.  Note that this must be one of the pins that allows for 
Pulse Width Modulation(PWM), which are marked by a little squiggle on the UNO board and consist of 
3,5,6,7,9,10, and 11. 

If you're using the Arduino IDE's Serial Monitor(the magnifying glass icon in the upper right), remember to 
check that baud rates are compatible.  This is also true for any other serial interface, just a reminder here.

Written August 2015 by Dr. X. Treme at Orgasmatronics. No rights reserverd or acknowledged.  Fuck all 
intellecutal property, both patents and copyrights.  No license referenced, as author of code does not believe
in the moral validity of the relevant laws that would apply to such licenses.  

No gods, no masters. Fuck the tech industry.

*/


void setup() {
  Serial.begin(9600);
}

void loop() {
  int x;  //generic analog value
  String stringOne = Serial.readString(); //read in a string from serial 

  if(stringOne.startsWith("analogRead")){  //analogRead command, same syntax as in Arduino language
    char analogChannel = stringOne.charAt(12); //assume that syntax is analogRead(A[N]), and find N
    if(analogChannel == '0'){
       x = analogRead(A0); 
    }
    if(analogChannel == '1'){
       x = analogRead(A1); 
    }
    if(analogChannel == '2'){
       x = analogRead(A2); 
    }
    if(analogChannel == '3'){
       x = analogRead(A3); 
    }
    if(analogChannel == '4'){
       x = analogRead(A4); 
    }
    if(analogChannel == '5'){
       x = analogRead(A5); 
    }
    Serial.print(x,DEC);
    Serial.println();
  } 
  if(stringOne.startsWith("analogWrite")){
    int pinLength = stringOne.indexOf(',') - stringOne.indexOf('(') - 1;
    int valueLength = stringOne.indexOf(')') - stringOne.indexOf(',') - 1;
    String pinString = stringOne.substring(12,12 + pinLength);
    int pin = pinString.toInt();
    String valueString = stringOne.substring(12 + pinLength + 1,12 + pinLength + valueLength + 1); 
    int value = valueString.toInt();
    analogWrite(pin,value); 
  }
}
