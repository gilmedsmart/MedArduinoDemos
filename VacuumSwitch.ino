

// relay pins

#define numButton 2
#define numRels 4
#define WAITINTERVAL 250

const int Rels[numRels] = {4, 7, 8, 12};
const int buttonPin[numButton] = {3, 2};

bool buttonState[numButton] = {LOW, LOW};
bool lastButtonState[numButton] = {LOW, LOW};

int valveState = 0;

void setup() {
  // relay pins
  Serial.begin(9600);

  for (int j = 0; j < numRels; j++) {
    pinMode(Rels[j], OUTPUT);
    digitalWrite(Rels[j], HIGH);
    // setting all relays to open
    delay(WAITINTERVAL);
    digitalWrite(Rels[j], LOW);
  }
  delay(WAITINTERVAL);
  // tactile
  for (int i = 0; i < numButton; i++)
    pinMode(buttonPin[i], INPUT);

  // Start serial communication for debugging (optional)
  //Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < numButton; i++) {
    // Read the state of the button
    buttonState[i] = digitalRead(buttonPin[i]);

    // Check for a single press (button pressed and then released)
    if (buttonState[i] != lastButtonState[i]) {
      // If the button is pressed
      if (buttonState[i] == HIGH) {
        // Run the function when button is pressed
        switchValveState(i);
      }
      // Update last button state
      lastButtonState[i] = buttonState[i];
    }
  }

}

void switchValveState(int bot) {
  switch (bot) {
    case 0:
      if (valveState == LOW) {
        digitalWrite(Rels[0], HIGH);
        delay(WAITINTERVAL);
        digitalWrite(Rels[1], HIGH);
        valveState = HIGH;
      } else {
        digitalWrite(Rels[1], LOW);
        delay(WAITINTERVAL);
        digitalWrite(Rels[0], LOW);
        valveState = LOW;
      }
      break;
    case 1:
      if (valveState == LOW) {
        digitalWrite(Rels[0], HIGH);
        digitalWrite(Rels[1], LOW);
        valveState = HIGH;
      } else {
        digitalWrite(Rels[0], LOW);
        digitalWrite(Rels[1], HIGH);
        valveState = LOW;
      }
      break;
  }
}
