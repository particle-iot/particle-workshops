module.exports = {
  base: '/',
  themeConfig: {
    repo: 'particle-iot/workshop-continental-tire',
    editLinks: true,
    editLinkText: 'Help us improve this page!',
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Team', link: 'http://particle.io' }
    ],
    sidebar: [
      '/docs/',
      ['/docs/ch1', 'Chapter 1: Getting your Electron device online'],
      [
        '/docs/ch2',
        'Chapter 2: Reading from Sensors & exploring the Device Cloud'
      ],
      ['/docs/ch3', 'Chapter 3: Using IFTTT & Azure IoT Hub']
    ]
  },
  title: 'Particle Electron Workshop',
  description:
    'Workshops designed to teach the basics of IoT development with the Particle ecosystem & the Particle Electron'
};
