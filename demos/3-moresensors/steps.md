# Demos for the Getting to Blinky with Particle Session

Step-by-step instructions for the demo portions of the "Sensor and Input Basics" Workshop Session.

## Desktop IDE Walkthrough

[Shared Version](https://go.particle.io/shared_apps/5b5b6c45b103f2e00b001023)

1.  Open Particle Dev to an empty window
2.  Click on the "Start a new project icon"
3.  Name the project and pick a location
4.  Show the default readme and project.properties
5.  Go back to build.particle.io and download the project from our last lesson (click "Download app sources")
6.  Open the zip and show the ino and project.properties
7.  Bring the into file into our new project
8.  Add a `Serial.begin()` to the setup.
9.  Add a `Serial.printlnf()` to the places where blue and yellow are toggled

```
Serial.printlnf("Yellow is %s", isYellowOn ? "on" : "off");
Serial.printlnf("Blue is %s", isBlueOn ? "on" : "off");
```

8.  Show selecting our device and flash it
9.  Open the console and toggle blue and yellow.

## Working with Buttons

[Shared Version](https://go.particle.io/shared_apps/5b5b6ebbb103f2e00b00103f)

1.  Add a `#define` for our red button

```
#define RED_BUTTON_A WKP
```

2.  In setup, add a pin mode declaration

```
pinMode(RED_BUTTON_A, INPUT_PULLUP);
```

3.  In the loop, add the following

```cpp
if (digitalRead(RED_BUTTON_A) == HIGH)
{
    digitalWrite(yellowLED, HIGH);
}
else
{
    digitalWrite(yellowLED, LOW);
}
```

4.  Flash and the yellow button will light up. When you press red, it will turn off, but notice that it's a bit wonky. Let's see if we can fix that with a debounce.

5.  Open the libraries tab and search for Debounce and add it.

6.  Add the include for the library

```cpp
#include <Debounce.h>
```

7.  Add a new debounce object before setup

```cpp
Debounce redButtonADebouncer = Debounce();
```

8.  Add a Debounce delay define

```
#define DEBOUNCE_DELAY 20
```

9.  Replace the pinMode reference to the button in setup

```cpp
redButtonADebouncer.attach(RED_BUTTON_A, INPUT_PULLUP);
redButtonADebouncer.interval(DEBOUNCE_DELAY);
```

10. Change the digitalRead check to use our debouncer instead

```cpp
  redButtonADebouncer.update();
  if (redButtonADebouncer.read() == HIGH)
  {
    digitalWrite(yellowLED, HIGH);
  }
  else
  {
    digitalWrite(yellowLED, LOW);
  }
```

Notice how the wonkyness goes away

## Handling Environmental inputs

[Shared Version](https://go.particle.io/shared_apps/5b5b7670cd8210fba800002c)

1.  Before we read from our temp sensor, let's talk about I2C. Each I2C device has a uniue address that the master device, our photon, uses to commucate with it. We have, in our project, a file called "i2cscanner.h". Let's reference that at the top:

```cpp
#include "i2cscanner.h"
```

2.  Add the following to the end of setup

```cpp
scanforI2CDevices();
```

3.  Open up the i2cscanner and step through it to show off how it works

4.  Flash the firmware and open the serial monitor. We should see two devices on our badge, and the address is each.

5.  Let's work with our temperature and humidity sensor. Open the library window and search for Si7021. Add it to this project.

6.  Intialize the sensor right before the display init. If you have time, open the library via view source and look at the various commands.

```
Adafruit_Si7021 sensor = Adafruit_Si7021();
```

7.  Add `sensor.begin()` to the setup function.
8.  Add a variable to store the temp reading.

```
int currentTemp;
Particle.variable("temp", currentTemp);
```

9.  And read from it in setup

```
currentTemp = round((sensor.readTemperature() * 1.8 + 32.00)*10)/10;
```

10. Go back to the console and show the current temp variable.

**_ MAYBE Do an IR Blaster demo here if we have time _**

## Working with Sight and Sound

[Shared Version](https://go.particle.io/shared_apps/5b5b78a5cd821003b8000047)

1.  Open the mario.h and notes.h files and show them off.

2.  Add includes for mario.h at the top of the file

```cpp
#include "music/mario.h"
```

3.  Define the buzzer pin

```cpp
#define BUZZER_PIN TX
```

4.  Create a function to play tones

```cpp
void playTones(int tonePin, const int tones[])
{
  for (int i = 1; t < (tones[0] * 2 + 1); i = I + 2)
  {
    tone(tonePin, tones[i], (1000 / tones[i + 1]));
    delay((1000 / tones[i + 1]) * 1.30);
    noTone(tonePin);
  }
}
```

5.  Now, play something at the end of the setup

```cpp
playTones(BUZZER_PIN, notes_MarioGameOver);
```

6.  Flash the firmware and listen!

7.  Now, lets write the temp reading we got earlier to the screen. Go back to the libraries tab and search for `SSD1306`.

8.  Install the Adafruit library, once again.

9.  Declare the display

```
Adafruit_SSD1306 display(RESET);
```

10. Initialize the display in `setup`

```
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
```

11. Write the temp after reading

```
display.display();
display.setCursor(0, 0);
display.println();
display.setTextSize(2);
display.print(currentTemp);
display.println("%");
display.display();
```
