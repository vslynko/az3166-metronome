#include "wiring.h"
#include "RGB_LED.h"
#include "digits.h"

static RGB_LED rgbLed;

int senserPin = 16;
int inputValue = 0;
int counter = 0;
bool aboveThreshold = false;

volatile unsigned char buttonAswitch = LOW;

unsigned char testBmp[42*6] = {0x01,0x01,0x01,0x01,0x02,0x02,0x02,0x02,0x04,0x04,0x04,0x04,0x08,0x08,0x08,0x08,0xFF,0xFF,0xFF,0xFF,0x10,0x10,0x10,0x10,0x20,0x20,0x20,0x20,0x40,0x40,0x40,0x40,0x80,0x80,0x80,0x80,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x01,0x01,0x01,0x01,0x02,0x02,0x02,0x02,0x04,0x04,0x04,0x04,0x08,0x08,0x08,0x08,0xFF,0xFF,0xFF,0xFF,0x10,0x10,0x10,0x10,0x20,0x20,0x20,0x20,0x40,0x40,0x40,0x40,0x80,0x80,0x80,0x80,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x01,0x01,0x01,0x01,0x02,0x02,0x02,0x02,0x04,0x04,0x04,0x04,0x08,0x08,0x08,0x08,0xFF,0xFF,0xFF,0xFF,0x10,0x10,0x10,0x10,0x20,0x20,0x20,0x20,0x40,0x40,0x40,0x40,0x80,0x80,0x80,0x80,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x01,0x01,0x01,0x01,0x02,0x02,0x02,0x02,0x04,0x04,0x04,0x04,0x08,0x08,0x08,0x08,0xFF,0xFF,0xFF,0xFF,0x10,0x10,0x10,0x10,0x20,0x20,0x20,0x20,0x40,0x40,0x40,0x40,0x80,0x80,0x80,0x80,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x01,0x01,0x01,0x01,0x02,0x02,0x02,0x02,0x04,0x04,0x04,0x04,0x08,0x08,0x08,0x08,0xFF,0xFF,0xFF,0xFF,0x10,0x10,0x10,0x10,0x20,0x20,0x20,0x20,0x40,0x40,0x40,0x40,0x80,0x80,0x80,0x80,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x01,0x01,0x01,0x01,0x02,0x02,0x02,0x02,0x04,0x04,0x04,0x04,0x08,0x08,0x08,0x08,0xFF,0xFF,0xFF,0xFF,0x10,0x10,0x10,0x10,0x20,0x20,0x20,0x20,0x40,0x40,0x40,0x40,0x80,0x80,0x80,0x80,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,};

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
  if (buttonAswitch)
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
    char buf1[10];
    sprintf(buf1, "%d", counter);
    Screen.print(3, buf1, false);
  }
  else
  {
    Screen.print("Bar Count", false);
    Screen.draw(0, 2, 42, 8, zero);
    Screen.draw(43, 2, 85, 8, one);
    Screen.draw(86, 2, 128, 8, one);
  }
}
