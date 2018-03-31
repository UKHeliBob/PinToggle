#include <PinToggle.h>

PinToggle output0(13);
PinToggle output1(12);
PinToggle output2(11);
PinToggle output3(10);

int previousToggleCount;
int currentToggleCount;

void setup()
{
  Serial.begin(115200);
  output0.begin();
  output1.begin();
  output2.begin();
  output3.begin();
  output0.startToggling(HIGH, 500, 100);
  output1.startToggling(HIGH, 500, 111);
  output2.startToggling(HIGH, 1000, 1000, 10);
  output3.setOutputState(LOW);
}

void loop()
{
  output0.update();
  output1.update();
  output2.update();
  output3.update();
  previousToggleCount = currentToggleCount;
  currentToggleCount = output2.getToggleCount();
  if (currentToggleCount != previousToggleCount)
  {
    Serial.print("Toggle count : ");
    Serial.println(output2.getToggleCount());
  }
  if (currentToggleCount == 0)
  {
    output2.restartToggling();
    output3.setOutputState(!output3.getOutputState());
    output0.updateLowPeriod(random(50, 5000));
    output0.updateHighPeriod(random(50, 5000));
    output1.updateLowPeriod(random(50, 5000));
    output1.updateHighPeriod(random(50, 5000));
  }
}