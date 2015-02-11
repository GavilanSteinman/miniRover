
// Define Variables:
const int chA=6;  //Constant variables relating to pin locations
const int chB=7;

int ch1;  //Varibles to store and display the values of each channel
int ch2;

int STBY = 13; //standby

//Motor A
int PWMA = 9; //Speed control 
int AIN1 = 5; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 11; //Speed control
int BIN1 = 10; //Direction
int BIN2 = 12; //Direction

int a=0;
int b=0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  // Set input pins
  pinMode(chA, INPUT);
  pinMode(chB,INPUT);
  
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}

//Main Program
void loop() {

  // read the input channels
  ch1 = pulseIn (chA,HIGH);  //Read and store channel 1
  //Serial.print ("Ch1:");  //Display text string on Serial Monitor to distinguish variables
  //Serial.print (ch1);     //Print in the value of channel 1
  //Serial.print ("|");
 
  ch2 = pulseIn (chB,HIGH);
  //Serial.print ("Ch2:");
  //Serial.print (ch2);
  //Serial.println();

  if(ch1<1490){
    a=((1490-ch1)/2+(1400-ch2)/8)/1;
    b=((1490-ch1)/2-(1400-ch2)/8)/1;
  }
  else{
    a=((1490-ch1)/2-(1400-ch2)/8)/1;
    b=((1490-ch1)/2+(1400-ch2)/8)/1;
  }
  if(abs(a)+abs(b) < 40){
    a=0;
    b=0;
  }
  if(a>0){
    move(1, abs(a), 1);
    //Serial.print("g");
    //Serial.print(abs(a));
  }
  else{
    move(1, abs(a), 2);
    //Serial.print("l");
    //Serial.print(abs(a));
  }
  Serial.print ("|");
  if(b>0){
    move(2, abs(b), 1);
    //Serial.print("g");
    //Serial.print(abs(b));
  }
  else{
    move(2, abs(b), 2);
    //Serial.print("l");
    //Serial.print(abs(b));
  }  
  Serial.println();
  
}



void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = false;
  boolean inPin2 = true;

  if(direction == 1){
    inPin1 = true;
    inPin2 = false;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
    //analogWrite(AIN1, inPin1);
    //analogWrite(AIN2, inPin2);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
    //analogWrite(BIN1, inPin1);
    //analogWrite(BIN2, inPin2);
  }
  Serial.print("|");
  Serial.print(inPin1);
  Serial.print("|");
  Serial.print(inPin2);
  Serial.print("|");
  //Serial.println();
} 
