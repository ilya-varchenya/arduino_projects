#include <IRremote.h>

const int IR = 11;
const int OUT = 12;
const int BUTTON = 5;
const int SETUP_LED = 2;

boolean isButtonPressed;
String irVar = "0";
String oldVar;
boolean state = true;

IRrecv irrecv(IR);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(BUTTON, INPUT);
  pinMode(OUT, OUTPUT);
  pinMode(SETUP_LED, OUTPUT);
}

String getIRSignal() {
  String resultValue;
  if (irrecv.decode(&results)) {
    resultValue = String(results.value);
    irrecv.resume();
  }
  delay(500);
  return resultValue;
}

void setupIRVar() {
  Serial.println("Button is pressed");
  isButtonPressed = true;
  digitalWrite(SETUP_LED, 1);
  oldVar = irVar;
  while (isButtonPressed) {
    if (irrecv.decode(&results)) {
      irVar = String(results.value);
      irrecv.resume();
    }
    if (oldVar != irVar) {
      isButtonPressed = false;
      digitalWrite(SETUP_LED, 0);
    }
    
  }
  Serial.println("Setup irVar = " + irVar);
}

void loop() {
  if (digitalRead(BUTTON) == 1) {
    setupIRVar();
  }
  if (getIRSignal() == irVar) {
    digitalWrite(OUT, state);
    state = !state;
    Serial.println("state = " + String(state));
  }
}
