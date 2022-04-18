#define CAR_1_FORWARD 8

// order is N E S W
char directionArray[4] = {'N', 'E', 'S', 'W'};
bool carOneState[4] = {false, false, false, false};  // god having to do things like this makes me hate arduino c++ i just want a hashmap
short carOneControls[4] = {CAR_1_FORWARD, 2, 2, 2};
//bool carTwoState[4] = {false, false, false false};

enum States { IN_GAME };

States state = IN_GAME;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting Game Master Controller");

  for (int i = 0; i < sizeof(carOneControls)/sizeof(carOneControls[0]); i++) {
    pinMode(carOneControls[i], OUTPUT);  // set this control to an output
  }
}

void loop() {
  // put your main code here, to run repeatedly:
 switch(state) {
  case IN_GAME: 
    Serial.println("In Game State");
    break;
  default:
    Serial.println("Invalid State");
    break;
 }
}
