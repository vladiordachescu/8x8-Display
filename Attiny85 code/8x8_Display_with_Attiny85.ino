const int CLKA = 2;
const int CLKB = 3;
const int A = 1;
const int B = 0;
const int EN = 4;


unsigned int CLK_cnt = 0;
bool highCLKB= true;

byte draw[64] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 1, 1, 1, 1, 1, 0, 
0, 1, 1, 1, 1, 0, 1, 0, 
0, 1, 0, 1, 1, 0, 1, 0, 
0, 1, 0, 0, 1, 0, 1, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 1, 0, 0, 
0, 0, 0, 0, 0, 1, 0, 0
};

void setup() {
  pinMode(CLKA, OUTPUT);
  pinMode(CLKB, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(EN, OUTPUT);

  digitalWrite(B, HIGH);

  for(int i = 0; i < 8; i++) {
    digitalWrite(CLKB, HIGH);
    delay(10);
    digitalWrite(CLKB, LOW);
    delay(10);
  }

}

void loop() {

  if(draw[CLK_cnt])
    digitalWrite(EN, HIGH);
  else
    digitalWrite(EN, LOW);  

  if(!(CLK_cnt % 8))
    digitalWrite(A, HIGH);

  if(!CLK_cnt)
    digitalWrite(B, LOW);
    
  if(!(CLK_cnt % 4)) {

    if(highCLKB) {
      digitalWrite(CLKB, HIGH);
      highCLKB = false;
    }

    else {
      digitalWrite(CLKB, LOW);
      highCLKB = true;
    }
  }
     
  digitalWrite(CLKA, HIGH);
  delay(10);
  digitalWrite(CLKA, LOW);
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH); 
  delay(10);

  CLK_cnt = (CLK_cnt + 1) % 64;
}