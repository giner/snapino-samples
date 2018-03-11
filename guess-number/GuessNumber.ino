/*
  Guess Number - simple game
*/

const int red = 11;
const int yellow = 10;
const int green = 9;
const int button = A0;
const int button_led = LED_BUILTIN;
const int noise = 1;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(button, INPUT);
  pinMode(button_led, OUTPUT);
  randomSeed(analogRead(noise));
}

void loop() {
  int random_number = random(1, 10);
  
  for(;;) {
    int number = readInput();
    
    if (random_number < number)
      light(yellow, 1000);
    else if (random_number > number)
      light(red, 1000);
    else {
      light(green, 0);
      break;
    }
  }
}

int readInput() {
  int counter = 0;
  
  do {
    while (waitClick(1000))
      counter++;
  } while (counter == 0);
  
  return counter;
}

bool waitClick(long wait) {
  int input;

  long start_time = millis();

  do {
    delay(1);
    input = digitalRead(button);
    if (millis() - start_time >= wait)
      return false;
  } while (input != LOW);

  digitalWrite(button_led, HIGH);

  do {
    delay(1);
    input = digitalRead(button);
  } while (input != HIGH);

  digitalWrite(button_led, LOW);

  return true;
}

void light(int led, long wait) {
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  
  digitalWrite(led, HIGH);
  
  if (wait > 0) {
    delay(wait);
    digitalWrite(led, LOW);
  }
}
