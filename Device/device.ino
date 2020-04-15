#include "RGB_LED.h"
#include "digits.h"

static RGB_LED rgbLed;

int senserPin = PB_0;
int inputValue = 0;
int counter = 0;
bool aboveThreshold = false;

volatile unsigned char buttonAswitch = LOW;

void setup()
{
  Screen.init();
  Screen.clean();

  Serial.begin(115200);

  attachInterrupt(USER_BUTTON_A, screenSwitch, FALLING);
}

void screenSwitch()
{
  Screen.clean();
  buttonAswitch = !buttonAswitch;
}

void loop()
{
  inputValue = analogRead(senserPin);

  if (inputValue > 600)
  {
    rgbLed.setColor(150, 0, 0);
    if (!aboveThreshold)
    {
      counter++;
      aboveThreshold = true;
    }
  }
  else
  {
    rgbLed.setColor(0, 0, 150);
    aboveThreshold = false;
  }

  if (buttonAswitch)
  {
    Screen.print("Analog Value:", false);

    char buf[10];
    sprintf(buf, "%d", inputValue);
    Screen.print(1, buf);

    Screen.print(2, "Counter:", false);

    char buf1[10];
    sprintf(buf1, "%d", counter);
    Screen.print(3, buf1, false);
  }
  else
  {
    Screen.print("Bar Counter");

    PrintFullScreen(counter);
  }
}
