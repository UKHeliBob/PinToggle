#include <PinToggle.h>

PinToggle output0(13);
PinToggle output1(12);
PinToggle output2(11);
PinToggle output3(10);

void setup()
{
  Serial.begin(115200);
  Serial.println(output0.begin());
  Serial.println(output1.begin());
  Serial.println(output2.begin());
  Serial.println(output3.begin());
  output0.waitBeforeToggling(LOW, 500, 500, 5000);	//5 second delay before toggling starts
  output1.waitBeforeToggling(HIGH, 500, 500, 5000);
  output2.startToggling(HIGH, 1000, 1000, 10);
  output3.setOutputState(HIGH);
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