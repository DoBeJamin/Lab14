
#include "oled-wing-adafruit.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

volatile bool interupt_occured = false; 

int counter = 0;

bool button_pressed = 0;
bool interupted = true;

void isr() {
  //interupt function
  interupt_occured = true;
}

void setup() {

  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  attachInterrupt(D5, isr, RISING);

  display.setup();

}

void loop() {

  display.loop();

  if (interupt_occured) { 
    //runs whenever the interup runs
    interupt_occured = false;
    counter++;

  }

  format_display();
  display.print(counter);
  display.display();

  if (!digitalRead(D6)) {
    button_pressed = true;
  }
  else if (button_pressed) {
    //turns on or off interups when the button is released 
    if (interupted) {
      noInterrupts();
    } else {
      interrupts();
    }
    interupted = !interupted;

    button_pressed = false;
  }

}

void format_display () {
  //sets up basic formatting for when using the display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE); 
  display.setCursor(0,0);
}