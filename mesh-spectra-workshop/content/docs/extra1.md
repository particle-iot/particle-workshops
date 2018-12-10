# Extras: Hacking on Mesh

## Clearing the badge firmware from a Xenon

The custom firmware on your PartiBadge requires certain hardware to be present in order to fully initialize. If you want to use the Xenon in your badge for your own projects, you'll need to flash new firmware to the device before you remove it from the badge hardware, or put the device into safe mode once it's been removed. Safe mode means that the Xenon is running Devices OS firmware and is connected to the cloud, but is not running any user firmware (the badge firmware, in this case).

To put your Xenon into Safe Mode:

1. Hold down the `MODE` and `RESET` buttons.
2. Let go of the `RESET` button until the onboard RGB LED starts flashing magenta.
3. Let go of the `MODE` button.

After a few seconds, your device should start slowly "breathing" magenta, indicating that it has entered safe mode. At this point, you can flash your own firmware to the Xenon, or use an example program like [Blink an LED](https://build.particle.io/examples/56214d636666d9ece3000001) to clear out the badge firmware.

Happy hacking!

## Ideas for taking your exploration further!

Now that you've gotten an overview of Mesh and the Particle Ecosystem, why not try building a web, mobile, or cloud app to interact with your Particle device? Here are a couple of ideas to get your started, and links to some resources you might find helpful.

1.  Create a Particle-powered mobile app using our [iOS](https://docs.particle.io/reference/ios/), [Android](https://docs.particle.io/reference/android/), and [Windows](https://docs.particle.io/reference/windows/) SDKs.

2.  Create a Particle-powered web app using the [Particle JS library](https://docs.particle.io/reference/javascript/) and your framework of choice, like [Vue.js](https://vuejs.org/), [React](https://reactjs.org/) and [Angular](https://angular.io/).

3.  Create a Particle-powered cross-platform mobile app using [NativeScript and Vue.js](https://www.nativescript.org/vue) and the [Particle NativeScript plugin](https://market.nativescript.org/plugins/nativescript-particle).

4.  Create an Azure IoT Hub Integration and [build dashboards with Electric IO](https://blog.particle.io/2018/09/28/create-the-dashboard-of-your-dreams-with-particle-electric-io/)

5.  [Apply to get a sneak peek at the new Particle Workbench](https://www.particle.io/workbench/apply/)

6.  [Request Access to the Particle Rules Engine Beta](https://www.particle.io/iot-rules-engine)

## Particle Resources

- [PartiBadge GitHub Repo](https://github.com/particle-iot/parti-badge)
- [Docs and Guides](https://docs.particle.io/guide/getting-started/intro/photon/)
- [Particle Community](https://community.particle.io/)
- [Particle on Hackster.io](https://www.hackster.io/particle)

And If you build something with Particle, we'd love to see it, and share it with the world! Just mention us on Twitter ([@particle](https://twitter.com/particle)) or Instagram ([@particle_io](https://www.instagram.com/particle_io/?hl=en)). We can't wait to see what you build!
