
int boardLED = 13;


int rightSwitch = 17;
int leftSwitch = 2;

int rightIndicator = 15;
int leftIndicator = 4;

int rightSignal = 11;
int leftSignal = 7;

int signalLow = 9;
int rightSwitchLow = 16;
int leftSwitchLow = 3;



void setup() {  
  pinMode(rightIndicator, OUTPUT);
  pinMode(leftIndicator, OUTPUT);
  
  pinMode(rightSignal, OUTPUT);
  pinMode(leftSignal, OUTPUT);
  
  setupGroundPin(signalLow);
  setupGroundPin(leftSwitchLow);
  setupGroundPin(rightSwitchLow);
  
  setupSwitch(leftSwitch);
  setupSwitch(rightSwitch);

  pinMode(boardLED, OUTPUT);
  digitalWrite(boardLED, HIGH);
}

void setupGroundPin(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void setupSwitch(int pin) {
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
}

void loop() {
  checkAndSignal(rightSignal, rightIndicator, rightSwitch);
  checkAndSignal(leftSignal, leftIndicator, leftSwitch);
  indicateOn();
}

void checkAndSignal(int signalPin, int indicatorPin, int switchPin) {
  if (onButtonUp(switchPin)) {
    runSignal(signalPin, indicatorPin, switchPin, 15);
    digitalWrite(signalPin, LOW);
    digitalWrite(indicatorPin, LOW);
  }
}

void indicateOn() {
  digitalWrite(leftIndicator, HIGH);
  delay (1);
  digitalWrite(leftIndicator, LOW);
  
  digitalWrite(rightIndicator, HIGH);
  delay(1);
  digitalWrite(rightIndicator, LOW);
  
  digitalWrite(boardLED, HIGH);
  delay (8);
  digitalWrite(boardLED, LOW);
}

bool onButtonUp(int pin) {
  if (digitalRead(pin) == LOW) {

    digitalWrite(boardLED, LOW);
    while (digitalRead(pin) == LOW) {
      // wait for button to be released
    }

    return true;
  }
  
  return false;
}

void runSignal(int signalPin, int indicatorPin, int switchPin, int times) {
  for (int i = 0; i < times; ++i) {
    if (setAndListen(signalPin, indicatorPin, HIGH, switchPin, 3)) return;
    if (setAndListen(signalPin, indicatorPin, LOW, switchPin, 2)) return;
    if (setAndListen(signalPin, indicatorPin, HIGH, switchPin, 7)) return;
    if (setAndListen(signalPin, indicatorPin, LOW, switchPin, 8)) return;
  }
}

// true = button was pressed, false = not pressed
bool setAndListen(int signalPin, int indicatorPin, int value, int switchPin, int times) {
  int i;
  
  digitalWrite(signalPin, value);
  digitalWrite(indicatorPin, !value);
  for (i = 0; i < times; ++i) {
    delay(50);
    if (onButtonUp(switchPin)) return true;
  }
  
  return false;
}
