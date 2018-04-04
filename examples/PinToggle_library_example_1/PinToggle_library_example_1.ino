#include <PinToggle.h>

PinToggle output0(13);
PinToggle output1(12);
PinToggle output2(11);
PinToggle output3(10);

void setup()
{
  Serial.begin(115200);
  output0.begin();
  output1.begin();
  output2.begin();
  output3.begin();
  output0.waitBeforeToggling(LOW, 500, 100, 10000);	//10 second delay before toggling starts
  output1.startToggling(HIGH, 500, 500);
  output2.startToggling(HIGH, 1000, 1000, 10);
  output3.setOutputState(LOW);
}

void loop()
{
  output0.update();
  output1.update();
  output2.update(printCount);	//use callback
  output3.update();
}

void printCount(int count)	//callback function
{
  Serial.println(count);
  if (count == 0)
  {
    output2.restartToggling();
    output3.setOutputState(!output3.getOutputState());
    output0.updateLowPeriod(random(50, 1000));
    output0.updateHighPeriod(random(50, 1000));
    output1.updateLowPeriod(random(50, 1000));
    output1.updateHighPeriod(random(50, 1000));
  }
}
