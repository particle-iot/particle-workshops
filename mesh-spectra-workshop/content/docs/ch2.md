# Chapter 2: Setting up your first Mesh network

| **Project Goal**            | Create a Mesh network and connect a second Xenon to it                                                              |
| --------------------------- | ------------------------------------------------------------------------------------------------------------------- |
| **What you’ll learn**       | How-to: add a second device to your Mesh network; communicate through a Mesh gateway to an endpoint device.         |
| **Tools you’ll need**       | A Xenon, Ethernet FeatherWing, access to an Ethernet port, Xenon connected to a PartiBadge, the Particle Mobile App |
| **Time needed to complete** | 15 minutes                                                                                                          |

In the last session, you configured your first Xenon and set-up a mesh network. In this session, you're going to add a second Xenon (the one in your PartiBadge) to that mesh network and interact with your second device via the gateway.

## Add your PartiBadge Xenon to your Mesh Network

Your PartiBadge Xenon has already been configured with firmware and added to the Spectra mesh network. In this section, you'll claim the Xenon in your to your account and add it to your personal mesh network.

1.  In the mobile app, on the "Your Devices" screen, click the "+" in the top-right to add a new device.

![](./images/01/04-mobiledevicelist.png)

2.  Select the "Mesh" option and choose "Xenon" on the next screen.

![](./images/01/mobileadd.png)

3. Hold the SETUP button on your PartiBadge Xenon for three seconds until is starts blinking blue, indicating that it has entered Listening Mode.

![](./images/02/listeningmode.gif)

4. You'll now follow the same device claiming flow you used for your first Xenon. Follow the on-screen instructions and scan the data matrix on your Xenon to pair with it.

![](./images/02/pairDevice.png)

5. Select the network you created in the last section.

![](./images/02/selecMeshNetwork.png)

6. You'll be instructed now to pair your phone wih an "assisting device." An assisting device is a device on a mesh network that will help your new device join the network. In this case, that device is your Ethernet FeatherWing gateway. Put the Gateway Xenon into listening mode by holding down the `MODE` button for 3 seconds until it begins blinking blue.

![](./images/02/pairAssistingDevice.png)

8. Scan the data matrix on the Gateway Xenon and wait for the pairing to complete.

![](./images/02/joinerPair.png)

7. When prompted, enter the network password you specified in the last section.

![](./images/02/meshProgress.png)

Congratulations! You now have a Particle Mesh network of two devices. Let's explore the power of Mesh by controlling your Badge Xenon from the cloud.

## Explore your mini Mesh network

In the last lab, you learned how to control a Particle device running the default Tinker firmware using the mobile app. In this section, you'll use the Particle Console to control your PartiBadge using Cloud Functions, which we'll learn more about in the next module.

1. Open a browser tab and navigate to [console.particle.io](https://console.particle.io). Log in with your Particle account, if prompted.

2. Your device dashboard will show all of the Particle devices you own. You should see at least two, one for your gateway/ethernet-connected Xenon and one for your badge Xenon. Click on the badge Xenon.

![](./images/02/consoleMain.png)

3. Your PartiBadge was pre-loaded with firmware. That firmware includes several Particle Cloud Functions and variables, which you can see listed on the right side of the overview screen for your device.

![](./images/02/primitives.png)

4. Set the name on your badge so it can be uniquely yours! Find the function named `updateFName` and enter your first name in the text box.

![](./images/02/updateFName.png)

5. Click `Call`. If the function call succeeded, a "1" should appear next to the function name.

![](./images/02/callUpdateName.png)

6. Now, enter your last name in the `updateLName` box and click `Call`. Optionally, you can enter your Twitter handle in the `updateTwttr` box.

![](./images/02/updateLName.png)

7. To confirm everything has been set correctly, you can click `Get` on the Particle variables for `wearerFName`, `wearerLName` and `wearerTwttr`. If the value you get back is the one you entered, you're good to go!

![](./images/02/getVars.png)

8. Now it's time to see your name in lights! Grab your PartiBadge and activate the menu by clicking the joystick or one of the LED buttons. Click the `Display` menu item, then `Name`. You should see your name (and Twitter handle, if your set it) scrolling across the screen!

![](./images/02/updateName.gif)

It's important to note that the Xenon in your PartiBadge does not have a Wi-Fi or cellular radio and thus, does not have a connection to the Internet. But Particle Mesh knows that your badge is connected via your gateway, and how to route messages through the gateway to your endpoint device. All you have to do is enter some text and click buttons!

To underscore that this is the case, try accessing your badge when your gateway Xenon is disconnected.

9. Unplug the Ethernet cable from your gateway Xenon.

10. Navigate back to the [Particle Console](https://console.particle.io) and open the dashboard for your device.

11. Try changing your first or last name and clicking "Call." You should get a timeout message toast at the bottom of the screen. If you try re-displaying your name, it should be unchanged.

![](./images/02/callFailed.png)

12. Plug an Ethernet cable back into your FeatherWing and repeat the last few steps. Everything should work.

Congratulations on setting up your first Particle Mesh network and exploring how mesh devices work together! In our last lab, you'll learn how to explicitly send messages between Mesh devices, as well as using Particle Cloud Functions, variables and Device Cloud events.
