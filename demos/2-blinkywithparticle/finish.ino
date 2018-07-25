#include <Adafruit_SSD1306.h>
#include <Adafruit_Si7021.h>

int yellowLED = A0;
int blueLED = A1;

bool isYellowOn = false;
bool isBlueOn = false;
int currentTemp;

bool blinkBlue = false;
bool blinkYellow = false;

Adafruit_Si7021 sensor = Adafruit_Si7021();
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
  sensor.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  Particle.function("toggleY", toggleYellow);
  Particle.function("toggleB", toggleBlue);

  Particle.variable("yellowOn", isYellowOn);
  Particle.variable("blueOn", isBlueOn);
  Particle.variable("temp", currentTemp);

  Particle.subscribe("blinkIt", handleBlink);

  currentTemp = round((sensor.readTemperature() * 1.8 + 32.00) * 10) / 10;

  display.display();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println();
  display.setTextSize(2);
  display.print(currentTemp);
  display.println("%");
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
