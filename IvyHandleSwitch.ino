

// relay pins
#define numRels 4
#define WAIT_INTERVAL_S 30000UL
#define WAIT_INTERVAL_B 360000UL

const int Rels[numRels] = {4, 7, 8, 12};

void setup() {
  Serial.begin(9600);

  for (int j = 0; j < numRels; j++) {
    pinMode(Rels[j], OUTPUT);
    digitalWrite(Rels[j], HIGH);
    // setting all relays to open
    delay(100);
    digitalWrite(Rels[j], LOW);
  }
}

void loop() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(Rels[0], HIGH);    
    Serial.print("HIGH ");
    Serial.println(i);
    delay(WAIT_INTERVAL_S);

    digitalWrite(Rels[0], LOW);
    Serial.println("LOW");
    delay(WAIT_INTERVAL_S);
  }
  Serial.println("Sleeping...");
  delay(WAIT_INTERVAL_B);

}
