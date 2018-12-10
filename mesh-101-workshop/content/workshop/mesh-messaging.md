---
title: Messaging in the mesh
---

# How to Mesh

<SessionHeader
:goal="'Publish and receive messages to/from the mesh.'"
:time="20"
:tools="[
  'Argon',
  'Xenon',
  '2 Grove starter kits for Particle mesh'
  ]"
/>

In this session, we'll leverage a local mesh network to quickly send messages between devices. We'll get a LED to turn on/off when the button on a different device is pushed.

### Work in groups
From now on and the rest of the workshop, it is necessary to cooperate in groups of 2-3 participants. Each group will get a Xenon, and from this point on in the workshop, the group will now work with one Argon and one Xenon.

::: tip Do yo come prepared?
It is assumed that you come to this session with an Argon that you are able to program.
:::

## Setting up the mesh network
In order to set up a mesh network, you need one device with internet connection, acting as a gateway. This device will create a mesh network, other devices (currently only Xenons) can join. These devices will be the *nodes* of the mesh network. This part will guide you trhough setting up an Argon as a gateway, and a Xenon as a node.

This video walks you through it. You may follow along the 12 steps hereunder along with it, as the video has no sound.


<div align="center">
<iframe width="250" height="400" src="https://www.youtube.com/embed/MJ3aon2953I" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe> 
</div>

1. From the Particle app, add the Argon as a new device, even if it has already been added. This will not override your code on the device. Follow the steps from the previous lab, but select the option to use the Argon in a mesh network.

2. Follow the guide to add WiFi to your Argon.

3. After the Argon has connected to the Device Cloud, name your Argon.

4. Give your new mesh network a name (max 16 characters) and a password.

5. After the mesh network is successfully created, you may exit the setup guide, and set up the Xenon.

6. Add the Xenon in much the same fashion you added the Argon: Start from the "Your devices" and click on the "+" sign.

7. Hold the `Mode` button for 3 seconds to put the Xenon into listening mode.

8. Scan the sticker. The Xenon will now pair with your phone.

9. After successful pairing, the Xenon will scan for local mesh-networks. Chose the network you set up with the Argon before.

10. To connect a new device to the mesh network, you physical access to a device already on the mesh network. This device will act as a commisioner, allowing your new device to join. Put the Argon (already on the mesh network) in listening mode (blinking blue) by holding the `MODE` button down for 3 seconds. Then scan its sticker.

11. Once you have successfully paired with the Argon, enter the mesh network password you created earlier.

12. After your Xenon have successfully joined the mesh network, you may give it a name, and exit the setup guide.

You now have a functioning 

## Sending & Receiving messages

Let us take a look at two of the newest functions provided by Particle: `Mesh.publish()` and `Mesh.subscribe()`. These primitives allow you to send and receive messages within a Particle Mesh network. These messages will not reach the cloud. Each device can publish messages to ther rest of the mesh, and each device can subscribe to messages from other devices – this is called a [pub/sub architecture](https://en.wikipedia.org/wiki/Publish%E2%80%93subscribe_pattern).


The same code will be used for all devices in the network, so start by creating a new app in the [Particle Web IDE](https://build.particle.io/build/new), name it *MeshPubSubTest.ino* or come up with a more creative name.

### Sending messages
First, let's send out a message when the `MODE` button on the Argon is pushed.

1. In the `setup` function, tell the device to call the `button_handler` function, whenever the `button_status` changes (pressed or released).

```cpp
System.on(button_status, button_handler);
```

2. Now write the `button_handler` function before the `setup` function.
``` cpp
void button_handler(system_event_t event, int duration, void* ) {
  // Empty
}
```

3. Since this function gets called on both press *and* release of the `MODE` button, we can use the `duration` to check which it is. Replace the line the the *Empty* comment with the following.

```cpp
if (!duration) {
  // Just pressed.
}
```

4. Now, since we now that the button has been pressed, we should tell the whole mesh network to toggle their LEDs. We use the `Mesh.publish()` for that, which takes one or two striings as arguments. The first argument is a topic and the second is data. We will only use the topic, and we should choose a topic that will make sense for the purpose. Later other devices will be able to subscribe to this topic and will get notified whenever we publish to this topic. Replace the *Just pressed* comment line with this line, to finish the code.

```cpp
Mesh.publish("toggle-led");
```

5. You have now completed the sending part of the code. To see that everything works, first add the following line to the `setup`.
```cpp
Serial.begin(9600);
```

6. Then add a print statement like this inside the if-loop, just under the `mesh.publish` line.

```cpp
Serial.println("Button push published!");
 ```

7. Flash your device with the code, and see that it behaves as expected.

### Receiving messages
We now want to subsribe to any messages on the `toggle-led` topic (or whatever you have decided to call it).

1. First off, we need to define two variables that we will use to control the onboard LED. In the very top of the code, insert the following lines of code.
```cpp
// Define the pin connected to the onboard LED (not the big RGB one, but the smaller one just right of the USB).
int ledPin = D7;

// Set the initial state to ON (true).
bool ledStatus = true;
```

2. Then initialize the LED by making its pin writable and write its inital status. This code is inserted in the `setup` function.
```cpp
pinMode(ledPin, OUTPUT);
digitalWrite(ledPin, ledStatus);  // Update the physical LED
```

3. In the `setup` function, subscribe to the `toggle-led` topic (first argument), and tell the device which function to call (second argument) when another device broadcasts a message to the topic.
```cpp
Mesh.subscribe("toggle-led", toggleLed);
```

4. Write the function that handles incoming messages to the `toggle-led`topic. Insert the function before the `setup` function.

``` cpp
void toggleLed(const char *event, const char *data) {
  // Empty line
}
```

5. Put logic in the function that switches the status of the LED, and then update the physical LED to the new status. The following code replaces the *Empty line* comment line in the `toggleLed`function.

``` cpp
// Toggle the status of the LED.
ledStatus = !ledStatus;

// Update the state of the physical LED by writing the value to the pin
digitalWrite(ledPin, ledStatus);
```

6. To see that everything works add the two print statements like these at the bottom of the `toggleLed` function.

```cpp
Serial.print("LED status toggled. Status: ");
Serial.print(ledStatus);
```

7. Flash the code containg both receiving and sending code to your device. You have now completed the receiving part of the code. Since all devices  Try and push the `MODE` button on one of the devices in the mesh network, then see if the LEDs on the other devices are toggled.

:tada: Congratulations, you are now able to send/receive messages to/from the mesh network. Easy, right?


::: tip Got stuck in the code?
The final code for this lab is [available here](https://go.particle.io/shared_apps/5bf709ee4a72e15412000614).
:::

