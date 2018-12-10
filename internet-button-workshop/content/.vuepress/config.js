module.exports = {
  base: '/',
  themeConfig: {
    repo: 'particle-iot/internet-button-workshop',
    editLinks: true,
    editLinkText: 'Help us improve this page!',
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Team', link: 'http://particle.io' }
    ],
    sidebar: [
      '/docs/',
      ['/docs/ch1', 'Chapter 1: Claiming your device'],
      ['/docs/ch2', 'Chapter 2: Blinking lights and buttons!'],
      [
        '/docs/ch3',
        'Chapter 3: The product dashboard and Particle rules engine'
      ]
    ]
  },
  title: 'Particle Blinky Onboarding',
  description:
    'Internet-Button (Photon) onboarding session designed to teach the basics of building for the Particle ecosystem.'
};
