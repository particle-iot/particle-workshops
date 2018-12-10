# Chapter 2: Reading from sensors & exploring the Device Cloud

| **Project Goal**            | Start programming your Electron, read sensor data, and leverage the device cloud.                         |
| --------------------------- | --------------------------------------------------------------------------------------------------------- |
| **What you’ll learn**       | How to interact with sensors; Using Particle variables and cloud functions.                               |
| **Tools you’ll need**       | build.particle.io, console.particle.io, the Particle CLI, a Particle Electron and Continental IAQM Device |
| **Time needed to complete** | 60 minutes                                                                                                |

In this session, we're going to explore the Particle ecosystem via an, Electron-powered IAQM Device with several sensors! If you get stuck at any point during this session, [click here for the completed, working source](https://go.particle.io/shared_apps/5b92ba65df6b76d72400179f).

## Create a new project in the Web IDE

1.  Navigate to [build.particle.io](http://build.particle.io). You may need to log-in, if prompted.

![](./images/02/login.png)

2.  Once you log-in, you may be directed to the Particle home page. If so, [click here to navigate](https://build.particle.io) back to Particle Build.

![](./images/02/particle-home.png)

3.  When navigating to the Web IDE (Build), the first thing you'll see is an empty editor window for a new project and a prompt to give that project a name.

![](./images/02/newproject.png)

4.  In the Current App textbox, give your app the name "IAQMSensors" and hit enter.

![](./images/02/projectname.png)

5.  Once you've given your project a name, you're ready to code!

![](./images/02/projectnamed.png)

## The `setup()` and `loop()` functions

Before we dive into our first bit of code, a brief word about the two functions that were auto-populated into your new app. If you've done Arduino or Particle development before, you're already familiar with these and can skip ahead. If not, read on.

Every Particle application _must_ have two functions in the main file (sometimes called a "sketch"): `setup()` and `loop()`. Both of these functions are called by the Particle Device OS.

True to its name, `setup()` runs only only once when the device starts up and is used for initializing buttons, sensors and other things needed to get your project ready to execute.

`loop()`, on the other hand, runs over and over again as long as your firmware is running on the device. When the function is called by the device OS, the code inside executes sequentially until it reaches the closing brace of the function, before being called again.

While the speed at which the `loop()` function executes is determined by the specific hardware and the time needed to execute the use code you've written in the function, it's important to know that, much of the time, this function will run very fast.

The bulk of your program, from state management, handling user input, reading from sensors and more will take place inside of the `loop()` function. It can take a bit of getting used to if you're not familiar with this style of development, but once you become comfortable, you'll enjoy the power this control provides you as a firmware developer.

## Setting up the IAQM Board

1. The project box you received contains a custom PCB with a slot for a Particle Electron and several Grove-compatible breakouts for Digital and Analog pins, as well as the I2C bus on the Electron.

![](./images/02/iaqmpcb.jpg)

2. Plug your Electron into the slot on the board, making sure to line up the device to the silkscreen outline. Leave the Electron plugged into your computer via USB, and the LiPo battery connected.

![](./images/02/electroninslot.jpg)

3. Next, make sure you have the five Grove sensors we'll need for this lab. They are:

- SHT31 Temperature & Humidity Sensor
- SGP30 VOC and eCO2 Gas Sensor
- Dust Sensor
- Light sensor
- PIR Motion Sensor

![](./images/02/grovesensors.jpg)

## Working with the Temperature & Humidity Sensor

### Add the SHT31 Library

1. Find the Temperature & Humidity Sensor.

![](./images/02/temphusensor.jpg)

2. The bag includes a sensor and a four-wire cable for connecting the sensor to the board. Plug one side of the cable into the slot on the sensor PCB.

![](./images/02/tempwire.jpg)

3. Plug the other end into any of the white connectors with an "I2C" label next to it.

![](./images/02/temppluggedin.jpg)

Once connected, you're ready to start reading from this sensor!

![](./images/02/tempandelectron.jpg)

4. Since the SHT31 temperature and humidity sensor is a common device, we can use a library to work with it. Navigate to your project at [build.particle.io](https://build.particle.io) and click on the bookmark icon to open the libraries tab.

![](./images/02/libraries.png)

5. Type "SHT31" into the search box. The library we'll be using should match that name exactly.

![](./images/02/librarysearch.png)

6. Click on the library name in search results, which will bring up the description page and source code. Click the "Include in project" button.

![](./images/02/sht31.png)

7. Select your "IAQMSensors" project.

![](./images/02/whichapp.png)

8. Click "Confirm."

![](./images/02/confirm.png)

9. The library will be included in your app, which you'll see in the sidebar. Also notice that an #include statement was added for the header file for the library.

![](./images/02/libraryadded.png)

### Interact with the sensor

1. First, we'll need to add a global variable to hold the sensor class object. Add the following to the top of your program, outside of the `setup` and `loop` methods.

```cpp
SHT31 sht31 = SHT31();
```

2. Let's also create two variables to hold the temperature and humidity, just below that object.

```cpp
int currentTemperature;
int currentHumidity;
```

3. Now, we'll call the `begin` class method to initialize the sensor for reading. Add the following to your `setup` function.

```cpp
sht31.begin();
```

4. We're ready to read from the sensor. In the `loop` function, add the following two lines to set the temp and humidity variables.

```cpp
currentTemperature = round((sht31.getTemperature() * 1.8 + 32.00)*10)/10;
currentHumidity = round(sht31.getHumidity()*10)/10;
```

::: tip
The `getTemperature` method returns the temp as a Celcius value, so we multiply that value by 1.8 and add 32 to convert it to Fahrenheit. Both methods also return float values, so we'll do a bit of math to round them and cast each value to an integer.
:::

5. As stated above, the loop function runs very fast. So fast, in fact, that if your loop only contained the two statements to check the sensor value, the values would be updated faster than you can use them. One of the ways we can manage this is with the delay() function, which accepts a value that represents the number of milliseconds to pause before continuing program execution. Add the following to the end of the `loop` function.

```cpp
delay(5000);
```

6. We're getting sensor data now, but we don't have a way to read it, yet. Let's use our first Particle Device Cloud primitive and expose these as variables. The `Particle.variable` method requires two parameters, a String representing the name of the variable and the global variable to return whenever the variable is requested from the device cloud. Variables must be declared in the `setup` function, so add the following two lines to the end.

```cpp
Particle.variable("tempF", currentTemperature);
Particle.variable("humidity", currentHumidity);
```

7. You full code file should now look like this.

```cpp
#include <SHT31.h>

SHT31 sht31 = SHT31();

int currentTemperature;
int currentHumidity;

void setup() {
  sht31.begin();

  Particle.variable("tempF", currentTemperature);
  Particle.variable("humidity", currentHumidity);
}

void loop() {
  currentTemperature = round((sht31.getTemperature() * 1.8 + 32.00)*10)/10;
  currentHumidity = round(sht31.getHumidity()*10)/10;

  delay(5000);
}
```

7. To see your first code in action, we need to install the code on a device. This is often referred to as "flashing firmware". In the bottom-left corner of the Web IDE, click on the cross-hairs icon to open the devices panel.

![](./images/02/devices.png)

8. The Devices panel shows a list of all the Particle devices you own, organized by type. Online devices will include a breathing cyan dot next to the name, as well.

![](./images/02/deviceslist.png)

9. To choose a device to flash, click the start next to the name of the device you want to flash.

![](./images/02/selecttoflash.png)

10. Now, click the flash lightning bolt icon in the top-left to flash the firmware to your device.

![](./images/02/lightning.png)

### View Readings in the Particle Console

1. Open a new browser tab and navigate to [console.particle.io](https://console.particle.io). Find your Electron and click on it's ID.

![](./images/02/console.png)

2. The device dashboard is your command-center for your Electron. It shows an event log, device diagnostics and more.

![](./images/02/dash.png)

3. In the right-hand side of the screen, you'll see a section for Device Cloud functions and variables you device has set up. Your two variables should show up here.

![](./images/02/funcsandvars.png)

4. Click the "Get" button next to each variable and you should see the latest temperature and humidity readings from your Electron.

![](./images/02/variables.png)

Congrats, you've configured your first sensor, and have successfully pushed it's data to the cloud. Now let's add the next sensor and explore more of the Particle Device Cloud.

## Working with the Gas Sensor

### Add the SGP30 Library

1. Find the Gas Sensor.

![](./images/02/gassensor.jpg)

2. The bag includes a sensor and a four-wire cable for connecting the sensor to the board. Plug one side of the cable into the slot on the sensor PCB.

![](./images/02/gaspluggedin.jpg)

3. Plug the other end into any of the white connectors with an "I2C" label next to it.

![](./images/02/gasandelectron.jpg)

Once connected, you're ready to start reading from this sensor!

![](./images/02/gasandtemp.jpg)

4. Just like with the Temp and humidity sensor, we can read the gas sensor with a library. Open your project at build.particle.io and open the libraries tab.

5. Type "SGP30" into the search box. The Library we're looking for is named "SensirionSGP30."

![](./images/02/sgp30lib.png)

6. Click the library name, then "Include in Project." Select your current project and click "Confirm." You should now see two libraries included in your project.

![](./images/02/twolibraries.png)

### Interacting with the device

1. As we did with the temp sensor, we need to initialize a class object to interface with our sensor. Add the following below the object initialization code for the temp sensor.

```cpp
SensirionSGP30 sgp;
```

2. The Gas sensor reads two values, [Total Volatile Organic Compounds](https://en.wikipedia.org/wiki/Volatile_organic_compound) (TVOC) in parts per million (ppm) and [Carbon dioxide equivalent](https://climatepolicyinfohub.eu/glossary/co2eq) (CO2eq) in parts per billion (ppb), both of which can be used to determine air quality. Let's create global variables to hold both readings. Add them right after our temp and humidity variables.

```cpp
int currentTVOC;
int currentCO2eq;
```

3. Next, we'll initialize the sensor in our `setup` function.

```cpp
sgp.begin();
```

4. Then, in `loop`, we can take a reading. This library works in a slightly different fashion from the temp and humidity sensor in that both values are fetched by a single method call `IAQmeasure`, which places the readings into class variables. If the measurement is successful, the method will return `true`, so we'll check it before assigning the readings into the global variables.

```cpp
if (sgp.IAQmeasure()) {
  currentTVOC = sgp.TVOC;
  currentCO2eq = sgp.eCO2;
}
```

5. Finally, to make these values accessible to the Device Cloud, we'll add two more `Particle.Variable` calls in `setup`.

```cpp
Particle.variable("tvoc", currentTVOC);
Particle.variable("eCO2", currentCO2eq);
```

Your project code should now look like the following:

```cpp
#include <SensirionSGP30.h>
#include <SHT31.h>


SHT31 sht31 = SHT31();
SensirionSGP30 sgp;

int currentTemperature;
int currentHumidity;
int currentTVOC;
int currentCO2eq;

void setup() {
  sht31.begin();
  sgp.begin();

  Particle.variable("tempF", currentTemperature);
  Particle.variable("humidity", currentHumidity);
  Particle.variable("tvoc", currentTVOC);
  Particle.variable("eCO2", currentCO2eq);
}

void loop() {
  currentTemperature = round((sht31.getTemperature() * 1.8 + 32.00)*10)/10;
  currentHumidity = round(sht31.getHumidity()*10)/10;

  if (sgp.IAQmeasure()) {
    currentTVOC = sgp.TVOC;
    currentCO2eq = sgp.eCO2;
  }

  delay(5000);
}
```

6. Flash the new firmware to you device and go back to your device dashboard in the Console. Click the refresh icon in the variables list and you should see two new variables. Click "Get" to see the latest readings.

![](./images/02/fourvariables.png)

### Adding a Cloud Function

1. So far, we've worked exclusively with Particle variables, which allow us to read current sensor values. Let's add a function that will allow us to trigger sensor readings on-demand. Along the way, we're going to clean up the existing code a bit. Start by adding the following to the top of your file, just after the `#include`

```cpp
#define SENSOR_CHECK_INTERVAL 10000
```

::: tip
`#define` is a text substitution pre-processor directive. It tells the compiler to replace every instance of a text value (on the left) with another value (on the right). In the case above, anywhere we use `SENSOR_CHECK_INTERVAL` will be replaced with the number `10000`. It's like using a constant, except we're not using any memory in allocating a variable for the program!
:::

2. Next, let's add a new variable we can use to track the last time we checked the sensors. Add the following line right after our other variables.

```cpp
unsigned long lastSensorCheck = 0;
```

3. Now, lets add a function for checking our sensors, since we'll end up needing this in a few places. Just before the `setup` function, add a new `checkSensors` function.

```cpp
void checkSensors() {
  currentTemperature = round((sht31.getTemperature() * 1.8 + 32.00)*10)/10;
  currentHumidity = round(sht31.getHumidity()*10)/10;

  if (sgp.IAQmeasure()) {
    currentTVOC = sgp.TVOC;
    currentCO2eq = sgp.eCO2;
  }
}
```

4. Next, we need to clean up our loop a bit. We were using `delay` previously to pause execution between checks, but this isn't ideal because it blocks program execution. A better way to manage delays between actions in an embedded system is to use `millis()` and timing variables, like the ones we added earlier. `millis()` returns the number of milliseconds that have elapsed since your program started running, and it can be very useful when you need to manage time intervals.

Change your `loop` to look like the following:

```cpp
void loop() {
  if (millis() - lastSensorCheck >= SENSOR_CHECK_INTERVAL) {
    lastSensorCheck = millis();
    checkSensors();
  }
}
```

The `if` statement is checking to see how long it's been since we took a temperature reading. Basically, if 10 seconds have elapsed (our `SENSOR_CHECK_INTERVAL` value), we'll set the `lastSensorCheck` to a new value and then check the temperature sensor.

5. Since our first sensor check won't happen in the first 10 seconds, we can add an initial check to our `setup`.

```cpp{10}
void setup() {
  sht31.begin();
  sgp.begin();

  Particle.variable("tempF", currentTemperature);
  Particle.variable("humidity", currentHumidity);
  Particle.variable("tvoc", currentTVOC);
  Particle.variable("eCO2", currentCO2eq);

  checkSensors();
}
```

6. Now we can add our cloud function. `Particle.function` expects a name and a local function that will handle calls from the Device Cloud. Add the following to your `setup` function.

```cpp
Particle.function("checkSensors", checkSensorsHandler);
```

7. And, finally, we'll add the function. All functions to be used as cloud functions _MUST_ return an `int` and take a single `String` parameter, which is why the signature is different than our `checkSensors` function.

```cpp
int checkSensorsHandler(String command) {
  checkSensors();

  return 1;
}
```

::: tip
For the sake of clarity, we've wrapped the existing `checkTemp` function in our cloud function handler. How could you refactor this so we've only have one helper function for local calls and the device cloud?
:::

Your firmware should now look like this.

```cpp
#include <SensirionSGP30.h>
#include <SHT31.h>

#define SENSOR_CHECK_INTERVAL 10000

SHT31 sht31 = SHT31();
SensirionSGP30 sgp;

int currentTemperature;
int currentHumidity;
int currentTVOC;
int currentCO2eq;
unsigned long lastSensorCheck = 0;

void checkSensors() {
  currentTemperature = round((sht31.getTemperature() * 1.8 + 32.00)*10)/10;
  currentHumidity = round(sht31.getHumidity()*10)/10;

  if (sgp.IAQmeasure()) {
    currentTVOC = sgp.TVOC;
    currentCO2eq = sgp.eCO2;
  }
}

int checkSensorsHandler(String command) {
  checkSensors();

  return 1;
}

void setup() {
  sht31.begin();
  sgp.begin();

  Particle.variable("tempF", currentTemperature);
  Particle.variable("humidity", currentHumidity);
  Particle.variable("tvoc", currentTVOC);
  Particle.variable("eCO2", currentCO2eq);

  Particle.function("checkSensors", checkSensorsHandler);

  checkSensors();
}

void loop() {
  if (millis() - lastSensorCheck >= SENSOR_CHECK_INTERVAL) {
    lastSensorCheck = millis();
    checkSensors();
  }
}
```

8. Now, flash the firmware to your device and head back to the console. Refresh your device screen and you should now see your `checkSensors` function.

![](./images/02/newFunc.png)

9. Click on `Call` to execute the function. Then, click `Get` next to the `tempF` variable to see the result.

![](./images/02/callFunc.png)

Let's move onto our next sensor.

## Working with the Dust Sensor

The next sensor up is the Dust sensor. The included sensor uses a particle counting method to measure dust concentration and connects to a digital pin on the Electron. Once we connect this sensor, we'll add a `Particle.publish` to pass all sensor readings along to the Device cloud each time they are collected.

1. Find the Dust sensor.

![](./images/02/dustsensor.jpg)

2. The bag includes a sensor and a three-wire cable for connecting the sensor to the board. Plug the larger side of the cable into the slot on the sensor PCB.

![](./images/02/dustcable.jpg)

3. Plug the other end into the white connector with the `A1` label next to it.

![](./images/02/dustpluggedin.jpg)

Once connected, you're ready to start reading from this sensor!

![](./images/02/threesensors.jpg)

### Interacting with the device

The dust sensor returns a Particulate Matter (PM) level (dust concentration) using a method called Low Pulse Occupancy (LPO) time in a given time unit. LPO time is proportional to PM concentration. For more information on this sensor and how it works, [click here](http://wiki.seeedstudio.com/Grove-Dust_Sensor/).

1. Unlike our previous two sensors, the dust sensor is not I2C based. We interact with it on a single digital pin, and need to write a bit more code to take a reading. Let's start by creating a new `#define` for the digital pin.

```cpp
#define DUST_SENSOR_PIN A1
```

2. Next, create some global variables to hold various readings. Add these three to the top of the file.

```cpp
unsigned long duration;
unsigned long lowPulseOccupancy;
float ratio;
float concentration;
```

3. Before we use a digital or analog pin, we need to designate it as an input or output so that our Electron knows how to properly configure the pin. Add the following line to `setup` to designate the sensor pin as an input.

```cpp
pinMode(DUST_SENSOR_PIN, INPUT);
```

4. The dust sensor operates by reading a pulse on the sensor pin over an interval. The [`pulseIn`](https://docs.particle.io/reference/firmware/electron/#pulsein-) function used here waits for the pin to be pulled low by the sensor, waits for it to go high before it stops timing and returns the length of the pulse in microseconds. By adding the following two lines to the start of our `loop`, we'll measure the duration each time through, and add it up to represent our `lowPulseOccupancy` value. Make sure these two lines appear at the very top of `loop` outside of the interval check `if` statement.

```cpp
duration = pulseIn(DUST_SENSOR_PIN, LOW);
lowPulseOccupancy = lowPulseOccupancy + duration;
```

5. Next, we'll call a new function `checkDust` after the interval (10 sec) elapses. Your `loop` should now look like this:

```cpp{9}
void loop() {
  duration = pulseIn(DUST_SENSOR_PIN, LOW);
  lowPulseOccupancy = lowPulseOccupancy + duration;

  if (millis() - lastSensorCheck >= SENSOR_CHECK_INTERVAL) {
    lastSensorCheck = millis();
    checkSensors();

    checkDust();
  }
}
```

6. Add the `checkDust` function. The `lowPulseOccupancy` will represent the total number of microseconds that a low pulse was read over the 10 second interval, which we can use to calculate the `ratio`. `concentration` is a more complex calculation that we obtained in the [documentation for the sensor](http://wiki.seeedstudio.com/Grove-Dust_Sensor/). Once we've calculated these two values, we'll reset the `lowPulseOccupancy`.

```cpp
void checkDust() {
  ratio = lowPulseOccupancy/(SENSOR_CHECK_INTERVAL*10.0);
  concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) +520 * ratio + 0.62;

  lowPulseOccupancy = 0;
}
```

### Publish a Particle event with sensor data

Previously, we created variables to hold all of our sensor readings. We can continue to do this, but since the number of measurements we're tracking is starting to add up, we should consider putting the readings into an event that we can fire each time new readings are taken.

1. Start by creating a new function called `fireSensorEvent`

```cpp
void fireSensorEvent() {

}
```

2. In order to make it easier for us to process sensor data in the next lab, we're going to create a JSON object that holds all of our sensor values. Let's create a new `String` object and assemble that object inside of the new function. Then, we'll call `Particle.publish` to send an event along to the Particle device cloud.

```cpp
String payload = "{\"temp\":" + String(currentTemperature)
  + ", \"humidity\":" + String(currentHumidity)
  + ", \"tvoc\":" + String(currentTVOC)
  + ", \"co2eq\":" + String(currentCO2eq)
  + ", \"dust\": {\"lpo\":" + String(lowPulseOccupancy)
  + ", \"ratio\":" + String(ratio)
  + ", \"concentration\":" + String(concentration) + "}"
  + "}";

Particle.publish("device_sensors", payload, MY_DEVICES);
```

3. To call this function, add it to the end of the loop, just after `checkDust`.

```cpp
fireSensorEvent();
```

4. Flash the firmware to your device. Once loaded, navigate back to your device dashboard in the Console. Your new event should show up in the event stream after a few seconds.

![](./images/02/sensorevents.png)

That's three sensors down and two to go! Let's look at the light sensor next.

## Working with the Light Sensor

1. Find the Light sensor.

![](./images/02/lightsensor.jpg)

2. The bag includes a sensor and a four-wire cable for connecting the sensor to the board. Plug the larger side of the cable into the slot on the sensor PCB.

![](./images/02/lightplug.jpg)

3. Plug the other end into the white connector with the `A0` label next to it.

![](./images/02/lightpluggedin.jpg)

Once connected, you're ready to start reading from this sensor!

![](./images/02/foursensors.jpg)

### Interacting with the device

1. Start by adding a new `#define` mapping for our light sensor at the top of your code.

```cpp
#define LIGHT_SENSOR_PIN A0
```

2. Next, add a `pinMode` mapping in `setup`.

```cpp
pinMode(LIGHT_SENSOR_PIN, INPUT);
```

3. As we've done previously, we'll also need a global variable to hold the light level.

```cpp
double currentLightLevel;
```

4. In the `checkSensors` function, add a couple of lines to read the analog value from the sensor, and map that value (which could be between `0` and `4095`) to a value between `0` and `100` to loosely represent a percentage.

```cpp
double lightAnalogVal = analogRead(LIGHT_SENSOR_PIN);
currentLightLevel = map(lightAnalogVal, 0.0, 4095.0, 0.0, 100.0);
```

5. Finally, we'll add the light level to our event payload.

```cpp
String payload = "{\"temp\":" + String(currentTemperature)
    + ", \"humidity\":" + String(currentHumidity)
    + ", \"tvoc\":" + String(currentTVOC)
    + ", \"co2eq\":" + String(currentCO2eq)
    + ", \"dust\": {\"lpo\":" + String(lowPulseOccupancy)
    + ", \"ratio\":" + String(ratio)
    + ", \"concentration\":" + String(concentration) + "}"
    + ", \"lightLevel\":" + String(currentLightLevel)
    + "}";
```

6. Flash the firmware and navigate back to the console. Shine a light towards the sensor and watch the value change.

![](./images/02/lightLevels.png)

One more sensor to go!

## Working with the Motion Sensor

1. Find the Motion sensor.

![](./images/02/motionsensor.jpg)

2. The bag includes a sensor and a four-wire cable for connecting the sensor to the board. Plug the larger side of the cable into the slot on the sensor PCB.

![](./images/02/motioncable.jpg)

3. Plug the other end into the white connector with the `D2` label next to it.

![](./images/02/motionpluggedin.jpg)

Once connected, you're ready to start reading from this sensor!

![](./images/02/fivesensors.jpg)

### Interacting with the device & triggering an event

1. As with the previous two devices, we'll add a new `#define` for the pin mapping.

```cpp
#define MOTION_SENSOR_PIN D2
```

2. And add a `pinMode` initialization to the `setup`

```cpp
pinMode(MOTION_SENSOR_PIN, INPUT);
```

3. Next, we'll read from the sensor in the `loop` function. Add the bottom, outside of the other `if` statement, add the following.

```cpp
if (digitalRead(MOTION_SENSOR_PIN)) {
  Particle.publish("movement_detected", NULL, MY_DEVICES);
}
```

::: tip
`digitalRead` returns either a `LOW` (0) value or a `HIGH` (1). In the case of our motion sensor, `HIGH` means that movement was detected, so we'll fire an event to the Device cloud.
:::

### Adding the last motion time to our event payload

1. We can also log the last time we detected motion and pass this along to our sensor payload. Start by adding a global variable at the top of the file.

```cpp
uint32_t lastMotionTime;
```

2. Then, just after the `Particle.publish` we added above for "motion_detected", use the [`Time`](https://docs.particle.io/reference/firmware/electron/#time) class to set the `lastMotionTime` variable.

```cpp
lastMotionTime = Time.now();
```

3. Finally, add the `lastMotionTime` to our sensor payload.

```cpp
String payload = "{\"temp\":" + String(currentTemperature)
    + ", \"humidity\":" + String(currentHumidity)
    + ", \"tvoc\":" + String(currentTVOC)
    + ", \"co2eq\":" + String(currentCO2eq)
    + ", \"dust\": {\"lpo\":" + String(lowPulseOccupancy)
    + ", \"ratio\":" + String(ratio)
    + ", \"concentration\":" + String(concentration) + "}"
    + ", \"lightLevel\":" + String(currentLightLevel)
    + ", \"lastMotion\":" + String(lastMotionTime)
    + "}";
```

4. Flash the firmware to your device and re-open device dashboard in the console. Wave your hand over the sensor to trigger an event.

![](./images/02/motionsensor.gif)

When a new sensor event comes in, you'll also see the `lastMotion` property included.

![](./images/02/motionevent.png)

With that, we've wired up all of our sensors and are posting values to the cloud. You're getting to be a Particle pro now! Let's explore integrating our device with 3rd party services and getting our data into the Azure cloud.
