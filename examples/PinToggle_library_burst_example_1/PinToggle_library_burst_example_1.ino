#include <PinToggle.h>

PinToggle output0(13);
PinToggle output1(12);

void setup()
{
  Serial.begin(115200);
  output0.begin();
  output1.begin();
  output0.startBurstMode(100, 100, 1000, 1000, HIGH);
  output1.startToggling(HIGH, 1000, 1000, 10);
}

void loop()
{
  output0.update();
  output1.update(stopBurst);
}

void stopBurst(int count)
{
  Serial.println(count);
  if (count == 5)
  {
    output0.stopBurstMode(HIGH);
    output0.startBurstMode(50, 50, 500, 500, HIGH);
  }
  if (count == 0)
  {
    output0.stopBurstMode(HIGH);
  }
} 