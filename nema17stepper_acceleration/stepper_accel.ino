
// the setup function runs once when you press reset or power the board

const int step_pin = 8;
const int dir_pin = 9;
int counter = 0;
int i_delay = 1000;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(step_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

  
  counter++;
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(step_pin, HIGH);
  delayMicroseconds(i_delay);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   
  digitalWrite(step_pin, LOW);
  delayMicroseconds(i_delay);                       // wait for a second

  if(counter%10 == 0)
  {
    if(i_delay > 1) i_delay--;
    //delay(1000);
  }
  if(counter%100 == 0)
  {
    Serial.println(i_delay);
    //delay(1000);
  }

  //120 microseconds max delay on full step

}
