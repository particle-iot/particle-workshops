# Chapter 4: Going Beyond Devices

| **Project Goal**            | Connect your badge to 3rd party services and "backhaul" sensor data to the cloud.                               |
| --------------------------- | --------------------------------------------------------------------------------------------------------------- |
| **What you’ll learn**       | How to work with the Particle CLI; Building integrations with IFTTT; Piping sensor data into the Azure IoT Hub. |
| **Tools you’ll need**       | Particle Dev (Desktop IDE), a Particle Photon and #PartiBadge                                                   |
| **Time needed to complete** | 30 minutes                                                                                                      |

## Exploring the Particle CLI and Cloud API

### The Particle CLI

1.  If you haven't already, [install the Particle CLI](https://docs.particle.io/guide/tools-and-features/cli/photon/). Open a terminal window and type the following command:

```bash
bash <( curl -sL https://particle.io/install-cli )
```

2.  Type `particle login` and enter your Particle account email and password when prompted.

![](./images/04/particlelogin.gif)

3.  Once you're logged in, type `particle list` to see your list of online devices.

![](./images/04/particlelist.gif)

4.  The device we've been using for this workshop has 3 variables and two functions. Get the value of the `temp` variable with the command `particle get temp`.

![](./images/04/temp.gif)

5.  We can also call one of the two functions to light up the yellow or blue LED button. Type the command `particle call <your-device-name> toggleB` in the terminal. Run the same command again to turn the light off.

![](./images/04/call.gif)

![](./images/04/blinkyblue.gif)

### The Particle Device Cloud API

Behind the scenes, every interface that Particle provides to work with devices, from the console to, mobile apps, SDKs and the CLI talks through a RESTful Device Cloud API, which you can also call yourself, directly.

_The next few steps assume you have cURL installed on your machine. If you don't have this command-line utility on your machine, you can download and install it [here](https://curl.haxx.se/download.html) or use a GUI-based tool like [Postman](https://www.getpostman.com/)._

1.  First, you'll need to obtain an access token from the CLI. Type `particle token list` to view the tokens associated with your account. The first one listed is your `user` token, and can be used to access the Device Cloud API. If no tokens are listed, generate a new one with `particle token new`.

2.  With your token and Device ID in hand, type the following cURL command into a terminal window, replacing the text below in `< >` with your information.

```bash
curl https://api.particle.io/v1/devices?access_token=<your token>
```

By default, the response will generate a wall of text in your terminal. If you have Python 2.6+ installed on your machine, you can pipe the output to the `json.tool` and get pretty-printed JSON.

```bash
curl https://api.particle.io/v1/devices\?access_token\=<your token>
| python -m json.tool
```

![](./images/04/curllist.gif)

3.  For this next command, you need the Device ID of the Photon attached to your badge. You can find that in the console or via the `particle list` CLI command.

4.  Let's call the `toggleB` function using the Device Cloud API. Type the following, again replacing the text below in `< >` with your information.

```bash
curl https://api.particle.io/v1/devices/3<device id>/toggleB \
     -d access_token=<your token>
```

![](./images/04/curlcall.gif)

With that, you've now explored all of the ways that you can interface with the Particle Device cloud and your connected devices! Now, let's go beyond the Particle ecosystem and explore some of the ways that you can integrate with other 3rd party services, and backhaul your data into other cloud services.

## Exploring Integrations with IFTTT

IFTTT (If This, Then That) is a web-based services that allows you to create integrations via simple conditional statements, called applets. There are hundreds of pre-build services you can leverage, and first-class support for Particle devices. In this section, we're going to create an IFTTT integration that posts a tweet when you press a button on your badge.

1.  Start by heading over to [IFTTT](https://ifttt.com) and either login, or create a new account.

![](./images/04/ifttt.png)

2.  After logging in, click "New Applet" in the top right of your dashboard.

![](./images/04/newapplet.png)

3.  Click the "+this" button.

![](./images/04/ifthis.png)

4.  In the "Search services" input, type "particle" and click on the Particle card.

![](./images/04/chooseservice.png)

![](./images/04/chooseparticle.png)

5.  Click on the "New event published" card.

![](./images/04/choosetrigger.png)

6.  In the trigger fields, set the event name as `button-pressed` the event contents to `red` and the Device name to the name of your device. Click "create trigger"

![](./images/04/completetrigger.png)

7.  You've set up the trigger on the Particle end, now its time for the **That** portion of the setup. Click the "+that" button.

![](./images/04/thenthat.png)

8.  Select the "Twitter" card.

![](./images/04/choosetwitter.png)

9.  Click the "Post a tweet" action card. You may be prompted to connect your Twitter account to IFTTT at this point. Follow the instructions provided to do so.

![](./images/04/twitteraction.png)

10. For the tweet text, copy the following, or customize as you wish. The text in double-brackets ({{}}) is replacement text based on the input event from Particle. You can click "Add ingredient" to see what other fields are available to use. Click "Create action" when you're done.

```
My #PartiBadge is tweeting! {{DeviceName}} published {{EventName}}
with data {{EventContents}}
```

![](./images/04/twitteractionfields.png)

11. Click "Finish"

![](./images/04/iftttreview.png)

12. You're all set! Toggle the switch to turn your action on if it isn't by default.

![](./images/04/iftttfinal.png)

13. Now, we need to modify our badge firmware to publish an event when the red button is pressed. Add the following to the `loop` function:

```cpp
redButtonADebouncer.update();
if (redButtonADebouncer.read() == HIGH)
{
  digitalWrite(yellowLED, HIGH);
}
else
{
  digitalWrite(yellowLED, LOW);
  Particle.publish("button-pressed", "red", MY_DEVICES);
}
```

14. Flash the firmware to your badge and press the red button a few times.

15. Head over to your Twitter account and see yout Particle-powered tweet! _Note: it may take a few minutes for IFTTT to pick up the event._

![](./images/04/badgetweet.png)

## Getting Device Data into Azure IoT
