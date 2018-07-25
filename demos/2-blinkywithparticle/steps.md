# Demos for the Getting to Blinky with Particle Session

Step-by-step instructions for the demo portions of the "Getting to Blinky with Particle" Workshop Session.

## Web IDE Walkthrough

[Shared Version](https://go.particle.io/shared_apps/5b55fef60cd885b7af000ec9)

1.  Open build.particle.io and login
2.  Show off the various parts of the Web IDE
3.  Navigate to thwe Code view and click on the "Blink and LED" example app
4.  Click "Use this example"
5.  Show the device name and firmware version in the lower-right.
6.  Select the device name and pick the device you want. Show off the "Signal" option and try it out.
7.  The #PartiBadge Blue and Yellow LEDS are on `A0` and `A1`, so change the `led1` and `led2` variables to point to these.
8.  Click flash to flash the firmware to the device.
9.  The lights should blink!

## Particle Device Cloud Primitives

[Shared Version](https://go.particle.io/shared_apps/5b5603210cd885c539001296)

1.  Head back to build.particle.io
2.  In setup, add Particle.function calls for toggling the LEDS

```
Particle.function("toggleY", toggleYellow);
Particle.function("toggleB", toggleBlue);
```

3.  Add the appropriate functions before the setup function. Talk about how every function returns an int and takes a single String parameter.

```
int toggleYellow(String command) {
    if (isYellowOn) {
        digitalWrite(yellowLED, LOW);
    } else {
        digitalWrite(yellowLED, HIGH);
    }

    isYellowOn = !isYellowOn;

    return 1;
}

int toggleBlue(String command) {
    if (isBlueOn) {
        digitalWrite(blueLED, LOW);
    } else {
        digitalWrite(blueLED, HIGH);
    }

    isBlueOn = !isBlueOn;

    return 1;
}
```

4.  Add two booleans to the top of the sketch to maintain the state of the LEDS.

```
bool isYellowOn = false;
bool isBlueOn = false;
```

5.  Add `Particle.variable()` calls to `setup` to expose those variables

```
Particle.variable("yellowOn", isYellowOn);
Particle.variable("blueOn", isBlueOn);
```

6.  Flash the new firmware to the device. Notice that the lights have stopped blinking and are now waiting for our command.

7.  Open up the CLI and trigger the function using the following command. Substitute the name, accordingly.

```
particle function call trash-panda toggleY
```

8.  Call the same function again to turn it off
9.  Repeat the same thing with the blue LED

```
particle function call trash-panda toggleB
```

10. Use the CLI to inspect the value of the Particle variables we set as well.

```
particle variable get trash-panda yellowOn
particle variable get trash-panda blueOn
```

## Managing Devices from the Console

[Shareable](https://go.particle.io/shared_apps/5b5610530cd88508dc00119a)

1.  Add a particle subscribe to the `setup` function

```
Particle.subscribe("blinkIt", handleBlink);
```

2.  Add the handler function

```
void handleBlink(const char *event, const char *data) {
    if (String(data) == "blue") {
        blinkBlue = !blinkBlue;
    } else if (String(data) == "yellow") {
        blinkYellow = !blinkYellow;
    }
}
```

3.  Add variables to handle blink state

```
bool blinkBlue = false;
bool blinkYellow = false;
```

4.  Handle blinking in the loop function

```
void loop() {
  if (blinkBlue) {
      digitalWrite(blueLED, HIGH);
      delay(500);
      digitalWrite(blueLED, LOW);
      delay(500);
  }

  if (blinkYellow) {
      digitalWrite(yellowLED, HIGH);
      delay(500);
      digitalWrite(yellowLED, LOW);
      delay(500);
  }
}
```

5.  Navigate to console.particle.io and show off the basic UI

6.  Go to your device and walk through all of the features

7.  Show the toggle functions and variables

8.  Publish a public event called `blinkIt` and pass in the value `blue` or `yellow` for data.

## Installing Firmware Libraries

1.  Click on the Libraries menu option in the Web IDE. Show off the UI.
2.  In the search bar, type Si7021.
3.  Click on the `Adafruit_Si7021` library and talk about what it shows on the screen (source and examples)
4.  Click Include in Project and put it in the project for this walkthrough.
5.  Notice that the library has been referenced at the top of the file.
6.  Initialize the sensor as in the example.

```
Adafruit_Si7021 sensor = Adafruit_Si7021();
```

7.  Add `sensor.begin()` to the setup function.
8.  Add a variable to store the temp reading.

```
Particle.variable("temp", currentTemp);
```

9.  And read from it in setup

```
currentTemp = round((sensor.readTemperature() * 1.8 + 32.00)*10)/10;
```

10. Go back to the console and show the current temp variable.

11. That's cool, but let's write to a screen! Go back to the libraries tab and search for `SSD1306`.

12. Install the Adafruit library, once again.

13. Declare the display

```
Adafruit_SSD1306 display(RESET);
```

14. Initialize the display in `setup`

```
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
```

14. Write the temp after reading

```
display.display();
display.setCursor(0, 0);
display.println();
display.setTextSize(2);
display.print(currentTemp);
display.println("%");
display.display();
```
