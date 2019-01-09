//Photoresistor Pin
int PhotoResL = 0;
int PhotoResM = 1;
int PhotoResR = 2;
int count = 0;

int LF = 9;
int LB= 8;
int RF = 11;
int RB = 10;

int sensorpin = 3;                 // analog pin used to connect the sharp sensor
int val = 0;                 // variable to store the values from sensor(initially zero)


float Left_Avg = 0;
float Right_Avg = 0;
float Mid_Avg = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  
  digitalWrite(LF, HIGH);
  digitalWrite(LB, LOW);
  digitalWrite(RF, HIGH);
  digitalWrite(RB, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  SKIPMOVE:
  val = analogRead(sensorpin);       // reads the value of the sharp sensor
  if(val > 400)
  {
    digitalWrite(LF, LOW);
    digitalWrite(LB, LOW);
    digitalWrite(RF, LOW);    //If it's RED, the bot STOPS
    digitalWrite(RB, LOW);
    goto SKIPMOVE;

  }
 
  int Left_LightLevel = analogRead(PhotoResL);
  int Right_LightLevel = analogRead(PhotoResR);
  int Mid_LightLevel = analogRead(PhotoResM);
    
  float Left_Voltage = Left_LightLevel * (5.0 / 1024.0);//Formula to convert Raw data into Voltage
  float Right_Voltage = Right_LightLevel * (5.0 / 1024.0);//Formula to convert Raw data into Voltage
  float Mid_Voltage = Mid_LightLevel * (5.0 / 1024.0);//Formula to convert Raw data into Voltage
  
  count = count + 1;
  Left_Avg = Left_Avg + Left_Voltage;
  Right_Avg = Right_Avg + Right_Voltage;
  Mid_Avg = Mid_Avg + Mid_Voltage;
  
  if (count == 100)
  {
     Left_Avg = Left_Avg/count;
     Right_Avg = Right_Avg/count;
     Mid_Avg = Mid_Avg/count;
     
     Serial.print("Left:  ");
     Serial.println(Left_Avg);

     Serial.print("Right: ");
     Serial.println(Right_Avg);
     
     Serial.print("Mid: ");
     Serial.println(Mid_Avg);

/*     if (Mid_Avg > 3 && Mid_Avg < 3.8)
     {
      
      digitalWrite(LF, LOW);
      digitalWrite(LB, LOW);
      digitalWrite(RF, LOW);    //If it's RED, the bot STOPS
      digitalWrite(RB, LOW);        
      count = 0;
      Left_Avg = 0;
      Right_Avg = 0;
      Mid_Avg = 0;

      goto SKIPMOVE;
     }*/
     if (Right_Avg < 1.7)
     {
      digitalWrite(LF, LOW);
      digitalWrite(LB, HIGH);
      digitalWrite(RF, LOW);
      digitalWrite(RB, HIGH);
      delay(500);
      digitalWrite(LF, HIGH);
      digitalWrite(LB, LOW);   //If Right Sensor sees black, it moves Left
      digitalWrite(RF, LOW);
      digitalWrite(RB, HIGH);
      delay(250);
      count = 0;
      Left_Avg = 0;
      Right_Avg = 0;
      Mid_Avg = 0;

      goto SKIPMOVE;      
     }
     if(Left_Avg < 1.7)
     {
      digitalWrite(LF, LOW);
      digitalWrite(LB, HIGH);
      digitalWrite(RF, LOW);
      digitalWrite(RB, HIGH);
      delay(500);
      digitalWrite(LF, LOW);
      digitalWrite(LB, HIGH);   //If Left Sensor sees black, it moves Right
      digitalWrite(RF, HIGH);
      digitalWrite(RB, LOW);
      delay(250);
      count = 0;
      Left_Avg = 0;
      Right_Avg = 0;
      Mid_Avg = 0;

      goto SKIPMOVE;      
     }

     digitalWrite(LF, HIGH);
     digitalWrite(LB, LOW);
     digitalWrite(RF, HIGH);
     digitalWrite(RB, LOW);

     count = 0;
     Left_Avg = 0;
     Right_Avg = 0;
     Mid_Avg = 0;
     
  }

  
}
