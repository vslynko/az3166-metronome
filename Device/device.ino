#include "RGB_LED.h"
#include "digits.h"

static RGB_LED rgbLed;

int senserPin = PB_0;
int inputValue = 0;
int counter = 0;
bool aboveThreshold = false;

bool showFullScreenCounter = true;

volatile bool button_A_pressed = false;


void setup()
{
  Screen.init();
  Screen.clean();

  Serial.begin(115200);

  attachInterrupt(USER_BUTTON_A, screenSwitch, FALLING);

  StartFullScreenCounter();
}

void screenSwitch()
{
  button_A_pressed = true;
}

void StartFullScreenCounter() {
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

  if (showFullScreenCounter)
  {
    PrintFullScreen(counter);
  }
  else
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
}
