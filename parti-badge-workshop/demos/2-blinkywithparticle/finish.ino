#include <Adafruit_Si7021.h>
#include <Adafruit_SSD1306.h>

int yellowLED = A0;
int blueLED = A1;

bool isYellowOn = false;
bool isBlueOn = false;

bool blinkBlue = false;
bool blinkYellow = false;

Adafruit_SSD1306 display(RESET);

int toggleYellow(String command)
{
  if (isYellowOn)
  {
    digitalWrite(yellowLED, LOW);
  }
  else
  {
    digitalWrite(yellowLED, HIGH);
  }

  isYellowOn = !isYellowOn;

  return 1;
}

int toggleBlue(String command)
{
  if (isBlueOn)
  {
    digitalWrite(blueLED, LOW);
  }
  else
  {
    digitalWrite(blueLED, HIGH);
  }

  isBlueOn = !isBlueOn;

  return 1;
}

void handleBlink(const char *event, const char *data)
{
  if (String(data) == "blue")
  {
    blinkBlue = !blinkBlue;
  }
  else if (String(data) == "yellow")
  {
    blinkYellow = !blinkYellow;
  }
}

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  Particle.function("toggleY", toggleYellow);
  Particle.function("toggleB", toggleBlue);

  Particle.variable("yellowOn", isYellowOn);
  Particle.variable("blueOn", isBlueOn);

  Particle.subscribe("blinkIt", handleBlink);

  display.display();
  display.setCursor(0, 0);
  display.println();
  display.setTextSize(2);
  display.setTextWrap(true);
  display.setTextColor(WHITE);
  display.print("Hello THAT Conference!");
  display.display();
}

void loop()
{
  if (blinkBlue)
  {
    digitalWrite(blueLED, HIGH);
    delay(500);
    digitalWrite(blueLED, LOW);
    delay(500);
  }

  if (blinkYellow)
  {
    digitalWrite(yellowLED, HIGH);
    delay(500);
    digitalWrite(yellowLED, LOW);
    delay(500);
  }
}
