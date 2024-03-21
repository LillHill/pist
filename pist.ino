//diagnostika řídící jednotky
byte OUTs[4] = {A0, A1, A2, A3};
byte BUSY = A4;
byte ALARM = A5;

//ovládání jednotky
byte INs[4] = {7,8,9,10};
byte RESET = 11;
byte STOP = 12;

void Fpos(){
  digitalWrite(INs[0], HIGH);
  digitalWrite(INs[1], HIGH);
  digitalWrite(INs[2], HIGH);
  digitalWrite(INs[3], HIGH);

  delay(10);
  while(digitalRead(BUSY));

  Serial.println("Zero pos setted.");

  digitalWrite(INs[0], LOW);
  digitalWrite(INs[1], LOW);
  digitalWrite(INs[2], LOW);
  digitalWrite(INs[3], LOW);
}

void Goto(byte position){
  Serial.print("Go to "); Serial.println(position);
  if (position < 1 || position > 15)
  {
    Serial.println("ERROR position out of range in Goto function");
    return;
  }
  const byte mask = 0b00000001;
  digitalWrite(INs[0], position & mask);
  digitalWrite(INs[1], (position >> 1) & mask);
  digitalWrite(INs[2], (position >> 2) & mask);
  digitalWrite(INs[3], (position >> 3) & mask);

  delay(100);
  while(!digitalRead(BUSY));

  Serial.println("Done");
}

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  // put your setup code here, to run once:
  for(byte i = 0; i < 6; i++){
    pinMode(OUTs[i], INPUT);
    pinMode(INs[i], OUTPUT);
  }
  pinMode(ALARM, INPUT);
  pinMode(BUSY, INPUT);

  pinMode(RESET, OUTPUT);
  pinMode(STOP, OUTPUT);

  digitalWrite(RESET, LOW);
  digitalWrite(STOP, LOW);
  
  digitalWrite(INs[0], LOW);
  digitalWrite(INs[1], LOW);
  digitalWrite(INs[2], LOW);
  digitalWrite(INs[3], LOW);

  while(digitalRead(ALARM));

  Fpos();

}
byte pos = 1;
void loop() {
  // put your main code here, to run repeatedly:

  if(pos==15)pos = 1;
  Goto(pos);
  pos++;

  if(digitalRead(ALARM)){
    Serial.println("ERROR please repair it and restart arduino.");
    while(free);
  }
}