  const int dotLength = 150; // in Milliseconds
  const int dashLength = dotLength * 3;
  const int letterPause = dotLength;
  const int wordPause = dotLength * 3;
 // const int dashLength = dotLength * 5;
 // const int letterPause = dotLength * 3;
 // const int wordPause = dotLength * 7;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(21, OUTPUT);  
}

void loop() {
  // put your main code here, to run repeatedly
  shortBeep();
  shortBeep();
  shortBeep();
  delay(letterPause);
  longBeep();
  longBeep();
  longBeep();
  delay(letterPause);
  shortBeep();
  shortBeep();
  shortBeep();
  delay(wordPause);
}

void shortBeep(void) {
  digitalWrite(21, HIGH);
  delay(dotLength);
  digitalWrite(21, LOW);
  delay(dotLength);
}

void longBeep(void) {
  digitalWrite(21, HIGH);
  delay(dashLength);
  digitalWrite(21, LOW);
  delay(dashLength);
}
