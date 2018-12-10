#include "Adafruit_SSD1306.h"
#include "Adafruit_Si7021.h"
#include "Debounce.h"
#include "mario.h"

/* Buttons */
#define RED_BUTTON_A WKP
#define BLUE_BUTTON_B A5
#define GREEN_BUTTON_C DAC
#define YELLOW_BUTTON_D A4
#define BUZZER_PIN TX

/* Joystick Buttons */
#define JOYSTICK_UP D6
#define JOYSTICK_DOWN D5
#define JOYSTICK_LEFT D4
#define JOYSTICK_RIGHT D3
#define JOYSTICK_CENTER D2

#define DEBOUNCE_INTERVAL 20

int yellowLED = A0;
int blueLED = A1;
int greenLED = A2;
int redLED = A3;

bool isBlueOn = false;
bool isGreenOn = false;

int currentTemp;
int currentHumidity;

int displayX;
int displayY;

Adafruit_SSD1306 display(RESET);
Adafruit_Si7021 sensor = Adafruit_Si7021();

Debounce blueButtonBDebouncer = Debounce();

// Debouncers for 5-way tactile switch
Debounce joystickUpDebouncer = Debounce();
Debounce joystickDownDebouncer = Debounce();
Debounce joystickLeftDebouncer = Debounce();
Debounce joystickRightDebouncer = Debounce();

void playTones(int tonePin, const int tones[])
{
  for (int i = 1; i < (tones[0] * 2 + 1); i = i + 2)
  {
    tone(tonePin, tones[i], (1000 / tones[i + 1]));
    delay((1000 / tones[i + 1]) * 1.30);
    noTone(tonePin);
  }
}

void toggle(bool isOn, int led) {
    if (isOn)
    {
        digitalWrite(led, LOW);
    }
    else
    {
        digitalWrite(led, HIGH);
    }
}

void toggleGreen(const char *event, const char *data)
{
  toggle(isGreenOn, greenLED);

  isGreenOn = !isGreenOn;
}

int toggleBlue(String command)
{
  toggle(isBlueOn, blueLED);

  isBlueOn = !isBlueOn;

  return 1;
}

int displayName(String command)
{
    display.clearDisplay();
    display.setTextWrap(true);
    display.setTextColor(WHITE);
    display.setTextSize(3);
    display.setCursor(0, 0);
    display.println(command);
    display.display();

    return 1;
}

int displEnvSensors(String command) {
  currentTemp = round((sensor.readTemperature() * 1.8 + 32.00) * 10) / 10;
  currentHumidity = round(sensor.readHumidity()*10)/10;

  display.clearDisplay();
  display.setTextWrap(true);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.printlnf("Temp: %if", currentTemp);
  display.printlnf("Hu: %i%%", currentHumidity);
  display.display();

  return 1;
}

void drawCircle() {
  display.clearDisplay();
  display.drawCircle(displayX, displayY, 5, WHITE);
  display.display();
}

void setup() {
    sensor.begin();

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();

    pinMode(yellowLED, OUTPUT); // Yellow
    pinMode(blueLED, OUTPUT); // Blue
    pinMode(greenLED, OUTPUT); // Green
    pinMode(redLED, OUTPUT); // Red

    pinMode(RED_BUTTON_A, INPUT_PULLUP);

    blueButtonBDebouncer.attach(BLUE_BUTTON_B, INPUT_PULLUP);
    blueButtonBDebouncer.interval(DEBOUNCE_INTERVAL);

    joystickUpDebouncer.attach(JOYSTICK_UP, INPUT_PULLUP);
    joystickUpDebouncer.interval(DEBOUNCE_INTERVAL);
    joystickDownDebouncer.attach(JOYSTICK_DOWN, INPUT_PULLUP);
    joystickDownDebouncer.interval(DEBOUNCE_INTERVAL);
    joystickLeftDebouncer.attach(JOYSTICK_LEFT, INPUT_PULLUP);
    joystickLeftDebouncer.interval(DEBOUNCE_INTERVAL);
    joystickRightDebouncer.attach(JOYSTICK_RIGHT, INPUT_PULLUP);
    joystickRightDebouncer.interval(DEBOUNCE_INTERVAL);

    Particle.function("toggleBlue", toggleBlue);
    Particle.variable("greenOn", isGreenOn);
    Particle.subscribe("toggleGreen", toggleGreen, MY_DEVICES);
    Particle.function("displayName", displayName);
    Particle.function("dispTempHu", displEnvSensors);

    Particle.variable("temp", currentTemp);
    Particle.variable("humidity", currentHumidity);

    displayX = display.width()/2;
    displayY = display.height()/2;
    drawCircle();

    playTones(BUZZER_PIN, notes_MarioStartup);
}

void loop() {
    if (digitalRead(RED_BUTTON_A) == HIGH)
    {
        digitalWrite(yellowLED, HIGH);
    }
    else
    {
        digitalWrite(yellowLED, LOW);
    }

    blueButtonBDebouncer.update();
    if (blueButtonBDebouncer.read() == HIGH)
    {
        digitalWrite(greenLED, HIGH);
    }
    else
    {
        digitalWrite(greenLED, LOW);
    }

    joystickUpDebouncer.update();
    if (joystickUpDebouncer.read() == LOW)
    {
        displayY--;
        drawCircle();
    }

    joystickDownDebouncer.update();
    if (joystickDownDebouncer.read() == LOW)
    {
        displayY++;
        drawCircle();
    }

    joystickLeftDebouncer.update();
    if (joystickLeftDebouncer.read() == LOW)
    {
        displayX--;
        drawCircle();
    }

    joystickRightDebouncer.update();
    if (joystickRightDebouncer.read() == LOW)
    {
        displayX++;
        drawCircle();
    }
}
