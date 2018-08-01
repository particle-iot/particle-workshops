#include <Adafruit_SSD1306.h>
#include <Adafruit_Si7021.h>
#include <Debounce.h>
#include "i2cscanner.h"
#include "music/mario.h"

#define RED_BUTTON_A WKP
#define BUZZER_PIN TX
#define DEBOUNCE_DELAY 20

int yellowLED = A0;
int blueLED = A1;

bool isYellowOn = false;
bool isBlueOn = false;
int currentTemp;

bool blinkBlue = false;
bool blinkYellow = false;

Adafruit_Si7021 sensor = Adafruit_Si7021();
Adafruit_SSD1306 display(RESET);

Debounce redButtonADebouncer = Debounce();

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

    Serial.printlnf("Yellow is %s", isYellowOn ? "on" : "off");

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

    Serial.printlnf("Blue is %s", isBlueOn ? "on" : "off");

    return 1;
}

void playTones(int tonePin, const int tones[])
{
    for (int i = 1; i < (tones[0] * 2 + 1); i = i + 2)
    {
        tone(tonePin, tones[i], (1000 / tones[i + 1]));
        delay((1000 / tones[i + 1]) * 1.30);
        noTone(tonePin);
    }
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
    Serial.begin(115200);

    Wire.begin();

    sensor.begin();
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();

    redButtonADebouncer.attach(RED_BUTTON_A, INPUT_PULLUP);
    redButtonADebouncer.interval(DEBOUNCE_DELAY);

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
    display.setCursor(0, 0);
    display.println();
    display.setTextSize(2);
    display.print(currentTemp);
    display.println("%");
    display.display();

    playTones(BUZZER_PIN, notes_MarioGameOver);
    scanforI2CDevices();
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

    redButtonADebouncer.update();
    if (redButtonADebouncer.read() == HIGH)
    {
        digitalWrite(yellowLED, HIGH);
    }
    else
    {
        digitalWrite(yellowLED, LOW);
    }
}
