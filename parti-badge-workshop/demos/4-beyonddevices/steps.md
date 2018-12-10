# Demos for the Getting to Blinky with Particle Session

Step-by-step instructions for the demo portions of the "Beyond Devices" Workshop Session.

## CLI Walkthrough

1.  Open a terminal window and type `particle help`. Look at the various options.
2.  Type `particle whoami`
3.  Type `particle list`
4.  Type `particle get temp`
5.  Type `particle call trash-panda toggleB` to toggle blue LED on and off
6.  Type `particle nyan trash-panda on` and then `particle nyan trash-panda off`
7.  Clear the window and type in a curl command to toggle the LED

```bash
curl https://api.particle.io/v1/devices/3b001e000247363339343638/toggleB \
     -d access_token=2b5810b22ce75c52e9be18bf88b8687b90f8a183
```

8.  And another to get devices

```bash
curl https://api.particle.io/v1/devices?access_token=2b5810b22ce75c52e9be18bf88b8687b90f8a183
```

## Using the Particle JS Library

**We won't do any live-coding for this section. It will just be about opening projects I've already written and showing them off**

### Particle JS, Promises and Async

1.  Open the [Ditching Promises App](https://github.com/bsatrom/ditching-promises) in VS Code.
2.  Open `particle.js` and show off the functions, including `deviceFunctions` and `deviceFunctionsAsync`
3.  Open the project in the console and run `npm run serve`
4.  Open a browser tab and show off the console results.

### NativeScript & Vue.js

1.  Open the `led-commander-app` folder in the console and type `npm run watch:ios` to run the app.
2.  Open the [Exploring Particle LEDs App](https://github.com/bsatrom/exploring-particle-leds/led-commander-app) in VS Code.
3.  Flash the [LED Tester Board](https://github.com/bsatrom/exploring-particle-leds/tree/master/led-tester-board) to a device
4.  Open `RGBController.vue` and show off the UI (XML), script that calls the API directly, and all of the functions. And the CSS.
5.  Project your phone and the device and show it in action.
6.  Make a change in the code and show the app update dynamically.

### AWS Lambda and the Particle JS API

1.  open the [Particle Cloud Alexa Skill](https://github.com/bsatrom/particle-cloud-alexa-skill) project in VSCode.
2.  Open `index.js` and talk about how this is used in a Lambda function that's called by an Alexa skill.
3.  Show `particleApiUtils.js`
4.  If there's time, navigate to the Alexa dev center and test out the skill

## Using Webhooks and Integrations

### IFTTT

1.  Navigate to [IFTTT](https://ifttt.com/my_services) and Click "New Applet".
2.  Click "this" and search for Particle. Click on Particle.
3.  Click "New event published".
4.  Set event name to `button-pressed`.
5.  Set is to `red`.
6.  Choose you current device.
7.  Click create trigger.
8.  Click "That" and click "Twitter"
9.  Click "Post a tweet"
10. In the text, set the value to "My #PartiBadge is tweeting! {{DeviceName}} published {{EventName}} with data {{EventContents}}"
11. Click "Create action"
12. Click "Finish"
13. Now, head over to your firmware and add the following to where the red button is checked:

```cpp
Particle.publish("button-pressed", "red", MY_DEVICES);
```

14. Flash to me device and press the button to trigger the event.
15. Navigate to your Twitter account to show the tweet.

### Webhooks with Zapier

1.  Navigate to [Zapier](https://zapier.com/app/dashboard) and click "Make a Zap!"
2.  Click "Webhooks" under "Built-in apps"
3.  Choose "Catch Hook" and click "Save + Continue"
4.  Click "Set up Webhook" and copy it to your clipboard.
5.  Navigate to console.particle.io in a new tab and click on Integrations
6.  Click the New Integration button and choose Webhook
7.  Set the event name to `env-sensors`
8.  Paste in the URL from Zapier
9.  Change the request format to `JSON`
10. Set the device to your device name
11. Click "Create Webhook"
12. Go to your Photon code and add the following to `setup` after reading the temp

```cpp
currentHumidity = round((sensor.readHumidity()) * 10) / 10;
Particle.publish("env-sensors", "{\"temp\":" + String(currentTemp) + ",\"hu\":" + String(currentHumidity) + "}", PRIVATE);
```

13. Flash the firmware to your device and reset it a few times.
14. Go back to Zapier and click "Pull in samples"
15. When its done, click "Continue"
16. Now you have to define an action. Choose Google Sheet.
17. Click "Create Spreadsheet row"
18. Pick the "Particle Hunt" spreadsheet.
19. Pick the "Temps" worksheet.
20. Add the values to post and map those to columns
21. Deploy the hook and test it by clicking "Send test"
22. Then test for real by turning it on and resetting your device

## Getting Data into Azure

### Setting up an Azure IoT Hub app

1.  Open up the Integrations and click "New integration"
2.  Click "Azure IoT Hub"
3.  Show the "Setup required" section
4.  Open the Azure portal
5.  Click "New resource" and add an IoT Hub
6.  use the `workshop-group` resource group
7.  Name the hub `tc-workshop-hub`
8.  Click "review and create"
9.  Click "create"
10. It will take a minute to create your hub. If it takes too long, just show of the existing one. Once created, click on "Shared access policies" and create a new policy.
11. Give the policy the name `workshop-policy` and choose all permissions.
12. Grab the primary key and go back to the integration tab of the Particle console.
13. For the Event name use, "env-sensors"
14. For the hub name use "tc-workshop-hub"
15. Policy name is "workshop-policy"
16. Copy in the Shared Policy Key and click "Enable Integration"
17. Click "Test". You might have to do this a few times.
18. Get the connection string from the policy
19. Open a console and use the command below to view events. You might need to reset the device to have it come through.

```bash
iothub-explorer monitor-events 3b001e000247363339343638 --login ""
```

20. Reset the device a few times and watch data stream through.
21. Show the device in the "IoT Devices" part of the console.

### Show off the Stream Analytics and Power BI

1.  In the Azure portal, open my Stream Analytics job. Show the input, query and output.
2.  Show off the UDF for transforming the payload data.
3.  Show off the output to Power BI.
4.  Open Power BI and show off the dashboard for temp and hu data and the backend editor.
