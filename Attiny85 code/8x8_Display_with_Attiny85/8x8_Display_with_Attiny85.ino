/*
  > CLKA is used to generate a clock signal for the A shift register which sweeps through the LED columns (LED anodes).
  > CLKB is used to generate a clock signal for the B shift register which sweeps through the LED rows (LED cathodes). It's 8 times slower than CLKA.
  > A is used to generate a single pulse at every 8th period of CLKA, which will propagate through the A shift register's 8 outputs.
  > B (actively low) is used to generate a single pulse at every 8th period of CLKB (64th period of CLKA), which will propagate through the B shift register's 8 outputs.
  > EN is associated with the draw[64] byte array. It has a LOW state if an element from the array has a value of 0 and a HIGH state otherwise.
  > The reset pin of the microcontroller is not connected (NC).
*/



const int CLKA = 2;
const int CLKB = 3;
const int A = 1;
const int B = 0;
const int EN = 4;


unsigned int CLK_cnt = 0;
bool highCLKB = true;

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

/*
  B is set to HIGH and we generate 8 CLKB periods in order to set B shift register's outputs to HIGH before we start displaying the array.
  This ensures that when we start the main loop, during the first 8 periods of CLKB, only one LED row consisting of cathodes at a time will be LOW.
*/

  digitalWrite(B, HIGH);

  for (int i = 0; i < 8; i++) {
    // delay is purely optional, it helps to visualize the setup process during the simulation.
    digitalWrite(CLKB, HIGH);
    delay(10);
    digitalWrite(CLKB, LOW);
    delay(10);
  }
}

void loop() {

  if (draw[CLK_cnt])
    digitalWrite(EN, HIGH);
  else
    digitalWrite(EN, LOW);

  if (!(CLK_cnt % 8))
    digitalWrite(A, HIGH);

  if (!CLK_cnt)
    digitalWrite(B, LOW);

  if (!(CLK_cnt % 4)) { //generates semiperiods for CLKB

    if (highCLKB) {
      digitalWrite(CLKB, HIGH);
      highCLKB = false;
    }

    else {
      digitalWrite(CLKB, LOW);
      highCLKB = true;
    }
  }

  /*
     Each of A shift registers' 8 outputs will stay HIGH for 20ms sequencially.
     This results in a refresh rate of 1/(64*20ms) = 0.78125 Hz for the display, which depending
     on the simulation's speed, could be enough for seeing each LED light up individually.
  */

  // For a 30Hz display refresh rate, replace the delays with the commented code.
  digitalWrite(CLKA, HIGH);
  delay(10); //delayMicroseconds(260);
  digitalWrite(CLKA, LOW);
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  delay(10); //delayMicroseconds(260);

  CLK_cnt = (CLK_cnt + 1) % 64;
}