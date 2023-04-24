int buttonPin = 3;
int relayPin = 6;
int ledPin = 5;
unsigned long startTime;
int endTime;
unsigned long interval = 10000;

boolean buttonReading = false;
boolean lastButtonReading = false;
boolean ledState = false;
boolean isOn = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  //store the button reading from last frame
  lastButtonReading = buttonReading;
  //get button reading from the current frame
  buttonReading = debounce(buttonPin, lastButtonReading);


  //TOGGLE:
  //if button is pushed now, but not pushed one frame ago
  if (buttonReading == true && lastButtonReading == false) {

    //flip ledState
    // ledState = !ledState;
    isOn = !isOn;
    if (isOn == true) {
      startTime = millis();
    }
  }
  // make automatically turn off after 2 minutes
  Serial.println(millis()-startTime);
  if( millis() - startTime >= interval){
    isOn = false; 
    // ledState = false;
    Serial.println("triggered");
  }
  Serial.println(buttonReading);
  digitalWrite(ledPin, isOn);
  digitalWrite(relayPin, isOn);
}


//FUNCTIONS
boolean debounce(int aButtonPin, boolean aLastButtonReading) {
  //get current reading of the button
  boolean currentReading = digitalRead(aButtonPin);

  //compare the current reading to the previous reading
  if (currentReading == true && aLastButtonReading == false) {
    delay(20);
  }

  //return the reading
  return currentReading;
}
