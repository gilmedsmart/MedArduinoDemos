

// relay pins

#define numButton 3
#define numRels 4
#define WAITINTERVAL 250
#define WAITLONGINTERVAL 1000


const int Rels[numRels] = {4, 7, 8, 12};
const int buttonPin[numButton] = {5, 2, 3}; // {Pedal, Botton 1, Botton 2}

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
    buttonState[i] = HIGH;
    lastButtonState[i] = HIGH;
  }
  openBothValves();

}

void loop() {
  for (int i = 0; i < numButton; i++) {
    // Read the state of the button
    lastButtonState[i] = buttonState[i];
    buttonState[i] = digitalRead(buttonPin[i]);
    //Serial.print(buttonState[i]);
    //Serial.print(" ");
  }
  //Serial.println();

  // Pedal press
  if ((buttonState[0] == LOW) && (lastButtonState[0] == HIGH)) {
    Serial.println("Pedal Press");
    if (valveState == HIGH) {
      setCOValveState();
      delay(WAITLONGINTERVAL);
    }
    setOCValveState();
    valveState = LOW;
  }

  // Pedal Release
  if ((buttonState[0] == HIGH) && (lastButtonState[0] == LOW)) {
    Serial.println("Pedal Release");
    setCOValveState();
  }

  // Botton 1
  if ((buttonState[1] == LOW) && (lastButtonState[1] == HIGH)) {
    Serial.println("Botton 1");
    closeBothValves();
    valveState = HIGH;
  }

  // Botton 2
  if ((buttonState[2] == LOW) && (lastButtonState[2] == HIGH)) {
    Serial.println("Botton 2");
    openBothValves();
    valveState = LOW;
  }
  delay(10);
}


void setOCValveState() {
  digitalWrite(Rels[0], HIGH);
  delay(WAITINTERVAL);
  digitalWrite(Rels[1], HIGH);
}

void setCOValveState() {
  digitalWrite(Rels[1], LOW);
  delay(WAITINTERVAL);
  digitalWrite(Rels[0], LOW);

}

void openBothValves() {
  digitalWrite(Rels[0], LOW);
  digitalWrite(Rels[1], HIGH);
}

void closeBothValves() {
  digitalWrite(Rels[0], HIGH);
  digitalWrite(Rels[1], LOW);
}
