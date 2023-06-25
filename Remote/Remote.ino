// timers for the sub-main loop
unsigned long currentMillis;
long previousMillis = 0;
float loopTime = 20;


float stickLVert;
float stickLHorz;
float stickRVert;
float stickRHorz;

int but1;
int but2;
int but3;
int but4;
int but1out;
int but2out;
int but3out;
int but4out;

void setup() {
  Serial.begin(57600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}

void loop() {
  currentMillis = millis();
    if (currentMillis - previousMillis >= loopTime) {  // run a loop every 10ms          
        previousMillis = currentMillis;          // reset the clock to time it
        stickLVert = analogRead(A2);
        stickLHorz = analogRead(A3);
        stickRVert = analogRead(A0);
        stickRHorz = analogRead(A1);
     
        //remove the offsets. Adjust the middle number for accuracy
        stickLVert = stickLVert - 0 - 512;
        stickLVert = deadzone(stickLVert) * -1; //reverse the sign for wiring on this stick;
        stickLHorz = stickLHorz - 0 - 512;
        stickLHorz = deadzone(stickLHorz) * -1; //reverse the sign for wiring on this stick;
       
        stickRVert = stickRVert - 0 - 512;
        stickRVert = deadzone(stickRVert);
        stickRHorz = stickRHorz - 0 - 512;
        stickRHorz = deadzone(stickRHorz) * -1; //reverse the sign for wiring on this stick;
     
        but1 = digitalRead(2);
        but2 = digitalRead(3);
        but3 = digitalRead(4);
        but4 = digitalRead(5);
        // invert buttons as they are pullup
     
        but1out = invButtons(but1);
        but2out = invButtons(but2);
        but3out = invButtons(but3);
        but4out = invButtons(but4);
       
       
        Serial.print(stickLVert);
        Serial.print(",");
        Serial.print(stickLHorz);
        Serial.print(",");
        Serial.print(stickRVert);
        Serial.print(",");
        Serial.print(stickRHorz);
        Serial.print(",");
        Serial.print(but1out);
        Serial.print(",");
        Serial.print(but2out);
        Serial.print(",");
        Serial.print(but3out);
        Serial.print(",");
        Serial.println(but4out);
    }

}


float deadzone(float value) {
     if (value > 40) {
        value = value - 40;
     }
     else if (value < -40) {
      value = value + 40;
     }
     else {
      value = 0;
     }
     value = value / 500;   // scale so that we get 0.0 ~ 1.0
     return value;  
}

int invButtons(int value) {
 
    if (value == 0) {
      value = 1;
    }
    else if (value == 1) {
      value = 0;
    }
    return value;
}
