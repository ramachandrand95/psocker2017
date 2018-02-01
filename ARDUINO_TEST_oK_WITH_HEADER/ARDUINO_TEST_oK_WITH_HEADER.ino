/**
 * Generates a test signal of 'OK' with a header
 */
char signal[0x80];

void setup() {
  pinMode(13, OUTPUT); 

}

void loop() {
  char signal[160] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
              1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
              1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,
              1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
              1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
              1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
              1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
              1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,
              1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0};
              
  for(int x = 0; x < sizeof(signal); x++){
       digitalWrite(13,signal[x]);
       delayMicroseconds(500);
    }
    delay(1000);
  }


