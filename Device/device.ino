#include "RGB_LED.h"

static RGB_LED rgbLed;

int senserPin = 16;
int inputValue = 0;
int counter = 0;
bool aboveThreshold = false;

void setup() {
  Screen.init();
  Screen.clean();

  Serial.begin(115200);
}

void loop()
{
  Screen.print("Analog Value:", false);

  inputValue = analogRead(senserPin);
  char buf[10];
  sprintf(buf, "%d", inputValue);
  Screen.print(1, buf);

  Screen.print(2, "Counter:", false);

  if (inputValue > 600)
  {
    rgbLed.setColor(150, 0, 0);
    if (!aboveThreshold) { 
      counter++;
      aboveThreshold = true; }
  }
  else{
    rgbLed.setColor(0, 0, 150);
    aboveThreshold = false;
  }
  char buf1[10];
  sprintf(buf1, "%d", counter);
  Screen.print(3, buf1, false);
}
