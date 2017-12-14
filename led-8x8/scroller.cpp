#include "LedControl.h"

#define LED_WIDTH (8)
#define LED_HEIGHT (8)

#define FIRST_CHAR (' ')
#define LAST_CHAR ('~')


class LedBuffer {
public:
  LedBuffer();
  ~LedBuffer();

  void clear();
  void setLed(int x, int y, int value);
  void show();

private:
  char* mBuffer;
  LedControl* mLedControl;
};

LedBuffer::LedBuffer() :
  mBuffer(nullptr),
  mLedControl(nullptr)
{
  mBuffer = new char[LED_HEIGHT];
  clear();

  mLedControl = new LedControl(12, 10, 11, 1);
  mLedControl->shutdown(0, false);
  mLedControl->setIntensity(0, 2);
  mLedControl->clearDisplay(0);
}

LedBuffer::~LedBuffer() {
  if (mBuffer != nullptr) {
    delete [] mBuffer;
  }
  if (mBuffer != nullptr) {
    delete mLedControl;
  }
}

void LedBuffer::clear() {
  memset(mBuffer, 0, LED_HEIGHT);
}

void LedBuffer::setLed(int x, int y, int value) {
  if (x < 0 || x >= LED_WIDTH || y < 0 || y >= LED_HEIGHT) {
    return;
  }

  value = !!value;
  mBuffer[y] ^= (-value ^ mBuffer[y]) & (0x80 >> x);
}

void LedBuffer::show() {
  for (int j = 0; j < LED_HEIGHT; j++) {
    mLedControl->setRow(0, j, *(mBuffer + j));
  }
}

// GLOBAL VARS ************************************************

unsigned long gFontBitmaps[][2] = {
  { 0, 0 },
  { 134744072, 524288 },
  { 673710080, 0 },
  { 2653224, 2082996224 },
  { 136194076, 171706368 },
  { 1620338710, 688259072 },
  { 471867417, 639172608 },
  { 134742016, 0 },
  { 135274528, 268959744 },
  { 268960772, 135266304 },
  { 706493980, 704643072 },
  { 526398, 134742016 },
  { 0, 528384 },
  { 60, 0 },
  { 0, 524288 },
  { 33818640, 541065216 },
  { 405029442, 605552640 },
  { 135792648, 136052736 },
  { 1010959384, 545128448 },
  { 1010959384, 1111228416 },
  { 135800904, 2080899072 },
  { 2118155266, 1111228416 },
  { 1010859074, 1111228416 },
  { 2114193424, 541065216 },
  { 1010973762, 1111228416 },
  { 1010975294, 37486592 },
  { 2048, 524288 },
  { 2048, 528384 },
  { 399456, 403046400 },
  { 32256, 2113929216 },
  { 6297606, 408944640 },
  { 943981592, 1048576 },
  { 3949724, 2489065500 },
  { 404235324, 1111621632 },
  { 2017753156, 1148715008 },
  { 944013440, 1144520704 },
  { 2017739844, 1148715008 },
  { 2084599872, 1081868288 },
  { 2084599872, 1077936128 },
  { 944013468, 1144520704 },
  { 1111653954, 1111621632 },
  { 1040713736, 138280960 },
  { 470025220, 1144520704 },
  { 1145589872, 1212416000 },
  { 1077952576, 1081999360 },
  { 1097028937, 1094778880 },
  { 1113739850, 1178730496 },
  { 471999010, 572260352 },
  { 2017753152, 1077936128 },
  { 471999010, 572260864 },
  { 2017753168, 1212416000 },
  { 471994380, 572260352 },
  { 2131232776, 134742016 },
  { 1111638594, 1111228416 },
  { 2168603172, 605552640 },
  { 1094797653, 1665204224 },
  { 1109661720, 608305152 },
  { 1092752392, 134742016 },
  { 2114193424, 545128448 },
  { 941629472, 540540928 },
  { 1075843080, 67239936 },
  { 940050440, 137887744 },
  { 271056896, 0 },
  { 0, 8257536 },
  { 268959744, 0 },
  { 3932734, 1178206208 },
  { 1077967938, 1650196480 },
  { 7200, 538705920 },
  { 33701442, 1178206208 },
  { 3949182, 1077673984 },
  { 1577016, 269484032 },
  { 13388, 1144259640 },
  { 538982436, 606339072 },
  { 134219784, 134742016 },
  { 134223880, 134744176 },
  { 538977320, 808189952 },
  { 269488144, 270008320 },
  { 26202, 1111621632 },
  { 11826, 572653568 },
  { 15426, 1111228416 },
  { 23650, 1115439168 },
  { 14918, 1111360002 },
  { 11314, 538968064 },
  { 1843224, 70778880 },
  { 1063952, 270008320 },
  { 8738, 639238144 },
  { 16962, 605552640 },
  { 33153, 1516634112 },
  { 16932, 409337856 },
  { 16930, 336072800 },
  { 15368, 272367616 },
  { 470822960, 270270464 },
  { 134744072, 134744064 },
  { 940051468, 137887744 },
  { 50, 1275068416 }
};


LedBuffer gLedBuffer;

// CODE ************************************************

void setup() {
}

// void drawChar(char character) {
//   if (character < FIRST_CHAR || character > LAST_CHAR) {
//     character = 'X';
//   }
//
//   unsigned long* source = gFontBitmaps[character - FIRST_CHAR];
//
//   for (int j = 0; j < 4; ++j) {
//     unsigned long shiftAmount = (3 - j) * 8ul;
//     gLedControl.setRow(0, j, source[0] >> shiftAmount);
//     gLedControl.setRow(0, j + 4, source[1] >> shiftAmount);
//   }
// }

void drawChar(char character, int x, int y) {
  if (x <= -LED_WIDTH || x >= LED_WIDTH || y <= -LED_HEIGHT || y >= LED_HEIGHT) {
    return;
  }

  if (character < FIRST_CHAR || character > LAST_CHAR) {
    character = 'X';
  }

  unsigned long* source = gFontBitmaps[character - FIRST_CHAR];

  for (unsigned long j = 0; j < 4; ++j) {
    for (unsigned long i = 0; i < LED_WIDTH; ++i) {
      unsigned long mask = (0x80ul >> i) << (j * 0x08ul);
      gLedBuffer.setLed(x + i, y + (3 - j), !!(source[0] & mask));
      gLedBuffer.setLed(x + i, y + (3 - j) + 4, !!(source[1] & mask));
    }
  }
}

int mod(int value, int mod) {
  while (value < 0) {
    value += mod;
  }
  return value % mod;
}

void loop() {
  char msg[400] = "We the People of the United States, in Order to form a more perfect Union, establish Justice, insure domestic Tranquility, provide for the common defence, promote the general Welfare, and secure the Blessings of Liberty to ourselves and our Posterity, do ordain and establish this Constitution for the United States of America. ";
  int msgLength = 328;

  for (int i = 0; i < msgLength; ++i) {
    for (int x = 7; x >= 0; --x) {
      drawChar(msg[mod(i - 1, msgLength)], x - LED_WIDTH, 0);
      drawChar(msg[i], x, 0);
      drawChar(msg[mod(i + 1, msgLength)], x + LED_WIDTH, 0);
      gLedBuffer.show();
      delay(100);
    }
  }
}
