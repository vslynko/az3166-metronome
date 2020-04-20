#include "RGB_LED.h"
#include "digits.h"

static RGB_LED rgbLed;

int senserPin = PB_0;
int inputValue = 0;
int counter = 0;

int bigMax = 0;

bool aboveThreshold = false;

bool showFullScreenCounter = false;

volatile bool button_A_pressed = false;

void setup()
{
  Screen.init();
  Screen.clean();

  Serial.begin(115200);

  attachInterrupt(USER_BUTTON_A, screenSwitch, FALLING);
}

void screenSwitch()
{
  button_A_pressed = true;
}

void StartFullScreenCounter()
{
  showFullScreenCounter = true;
  Screen.clean();
  Screen.print("Bar Counter");
}

void loop()
{
  if (button_A_pressed)
  {
    button_A_pressed = false;
    showFullScreenCounter = !showFullScreenCounter;
    if (showFullScreenCounter)
    {
      StartFullScreenCounter();
    }
  }

  inputValue = analogRead(senserPin);
  if (inputValue > bigMax) bigMax = inputValue;

  if (inputValue > 100)
  {
    rgbLed.setColor(100, 10, 10);
    if (!aboveThreshold)
    {
      counter++;
      aboveThreshold = true;
    }
  }
  else
  {
    rgbLed.turnOff();
    aboveThreshold = false;
  }

  if (showFullScreenCounter)
  {
    PrintFullScreen(counter);
  }
  else
  {
    Screen.print("Input", false);

    char buf[10];
    sprintf(buf, "Cur=%d Max=%d", inputValue, bigMax);
    Screen.print(1, buf);

    char buf1[10];
    sprintf(buf1, "Bar=%d", counter);
    Screen.print(3, buf1, false);
  }
}
