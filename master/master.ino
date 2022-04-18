#include <ArduinoJson.h>

#define CAR_1_FORWARD 11
#define CAR_1_RIGHT 9
#define CAR_1_BACKWARD 8
#define CAR_1_LEFT 10
#define CAR_2_FORWARD 2
#define CAR_2_RIGHT 2
#define CAR_2_BACKWARD 2
#define CAR_2_LEFT 2

// order is N E S W
DynamicJsonDocument doc(1024);


String directionArray[4] = {"N", "E", "S", "W"};  // has to be strings and not chars as arduino json screams at me
short carControls[2][4] = {{CAR_1_FORWARD, CAR_1_RIGHT, CAR_1_BACKWARD, CAR_1_LEFT}, {CAR_2_FORWARD, CAR_2_RIGHT, CAR_2_BACKWARD, CAR_2_LEFT}};
bool carStates[2][4] = {{false, false, false, false}, {false, false, false, false}};

enum States { IN_GAME };

States state = IN_GAME;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) continue;
  Serial.println("Starting Game Master Controller");

  for (int i = 0; i < sizeof(carControls)/sizeof(carControls[0]); i++) {
    for (int j = 0; j < sizeof(carControls[i])/sizeof(carControls[i][0]); j++) {
      pinMode(carControls[i][j], OUTPUT);  // set this control to an output
    }
  }
}

void loop() {    
  transmitControls();
  
 switch(state) {
  case IN_GAME: 
    inGameState();
    break;
  default:
    Serial.println("Invalid State");
    break;
 }
 delay(10);
}

//[{"N":false,"E":false,"S":false,"W":false},{"N":false,"E":false,"S":false,"W":false}]
void inGameState() {
  
  // read for any controller updates
  if (Serial.available()) {
    // Allocate the JSON document
    StaticJsonDocument<300> doc;
    DeserializationError err = deserializeJson(doc, Serial);

    JsonArray docArray = doc.as<JsonArray>();

    if (err == DeserializationError::Ok) {
      // Print the values
      // (we must use as<T>() to resolve the ambiguity)

      for (int i = 0; i < sizeof(carStates)/sizeof(carStates[0]); i++) {
        carStates[0][0] = docArray[0]["N"].as<boolean>();
        carStates[0][1] = docArray[0]["E"].as<boolean>();
        carStates[0][2] = docArray[0]["S"].as<boolean>();
        carStates[0][3] = docArray[0]["W"].as<boolean>();
      }
    } 
    else {
      // Print error to the "debug" serial port
      Serial.print("deserializeJson() returned ");
      Serial.println(err.c_str());
  
      // Flush all bytes in the "link" serial port buffer
      while (Serial.available() > 0)
        Serial.read();
    }
  }
}

void transmitControls() {  // remember low == false and high == true
  for (int i = 0; i < sizeof(carStates)/sizeof(carStates[0]); i++) {
    for (int j = 0; j < sizeof(carStates[i])/sizeof(carStates[i][0]); j++) {
      digitalWrite(carControls[i][j], carStates[i][j]);
    }
  }
}
