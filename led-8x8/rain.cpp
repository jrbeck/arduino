#include "LedControl.h"

#define NUM_DROPS (10)

struct Drop {
  bool active;
  int x;
  int y;
};


class RainSim {
public:
  RainSim();
  ~RainSim() {};

  void update();
  void draw();

private:
  LedControl mLedControl;
  Drop mDrops[NUM_DROPS];
};

RainSim::RainSim() :
  mLedControl(LedControl(12, 10, 11, 1))
{
  mLedControl.shutdown(0, false);
  mLedControl.setIntensity(0, 2);
  mLedControl.clearDisplay(0);

  for (int i = 0; i < NUM_DROPS; ++i) {
    Drop* drop = &mDrops[i];
    drop->active = false;
  }
}

void RainSim::update() {
  for (int i = 0; i < NUM_DROPS; ++i) {
    Drop* drop = &mDrops[i];
    if (drop->active) {
      drop->y++;
      if (drop->y == 8) {
        drop->active = false;
      }
    }
    else if ((rand() % 5) == 0) {
      drop->active = true;
      drop->x = rand() % 8;
      drop->y = 0;
    }
  }
}

void RainSim::draw() {
  mLedControl.clearDisplay(0);
  for (int i = 0; i < NUM_DROPS; ++i) {
    Drop* drop = &mDrops[i];
    if (drop->active) {
      mLedControl.setLed(0, drop->y, drop->x, true);
    }
  }
}

RainSim gRainSim;

// ******************************************************************

void setup() {
}

void loop() {
  gRainSim.update();
  gRainSim.draw();
  delay(200);
}
