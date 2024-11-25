

// relay pins

#define numButton 3
#define numRels 4
#define WAITINTERVAL 250

const int Rels[numRels] = {4, 7, 8, 12};
const int buttonPin[numButton] = {3, 2, 5};

bool buttonState[numButton];
bool lastButtonState[numButton];

bool valveState = LOW;

void setup() {
  // Start serial communication for debugging (optional)
  Serial.begin(9600);

  // Relay pins
  for (int j = 0; j < numRels; j++) {
    pinMode(Rels[j], OUTPUT);
    digitalWrite(Rels[j], HIGH);
    // setting all relays to open
    delay(WAITINTERVAL);
    digitalWrite(Rels[j], LOW);
  }
  delay(WAITINTERVAL);
  // tactile
  for (int i = 0; i < numButton; i++) {
    pinMode(buttonPin[i], INPUT);
    buttonState[i] = LOW;
    lastButtonState[i] = LOW;
  }
  //Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < numButton; i++) {
    // Read the state of the button
    lastButtonState[i] = buttonState[i];
    buttonState[i] = digitalRead(buttonPin[i]);
  }
  if ((buttonState[0] == LOW) && (lastButtonState[0] == HIGH)) {
    Serial.print("valveState");
    Serial.print(" = ");
    Serial.println(valveState);
    valveState = !(valveState);
    setValveState();
    Serial.print("valveState");
    Serial.print(" = ");
    Serial.println(valveState);

  }
  if ((buttonState[1] == LOW) && (lastButtonState[1] == LOW)) {
    openBothValves();
  }
  if ((buttonState[1] == HIGH) && (lastButtonState[1] == LOW)) {
    setValveState();
  }
  if ((buttonState[2] == LOW) && (lastButtonState[2] == LOW)) {
    closeBothValves();
  }
  if ((buttonState[2] == HIGH) && (lastButtonState[2] == LOW)) {
    setValveState();
  }
  delay(10);
}


void setValveState() {
  if (valveState == LOW) {
    digitalWrite(Rels[0], HIGH);
    delay(WAITINTERVAL);
    digitalWrite(Rels[1], HIGH);
  } else {
    digitalWrite(Rels[1], LOW);
    delay(WAITINTERVAL);
    digitalWrite(Rels[0], LOW);
  }
}

void openBothValves() {
  digitalWrite(Rels[0], HIGH);
  digitalWrite(Rels[1], LOW);
}

void closeBothValves() {
  digitalWrite(Rels[0], LOW);
  digitalWrite(Rels[1], HIGH);
}
