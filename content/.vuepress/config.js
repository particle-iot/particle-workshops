module.exports = {
  base: '/',
  themeConfig: {
    repo: 'particle-iot/particle-workshops',
    editLinks: true,
    editLinkText: 'Help us improve this page!',
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Team', link: 'http://particle.io' }
    ],
    sidebar: [
      '/docs/',
      ['/docs/ch1', 'Chapter 1: Claiming your device'],
      ['/docs/ch2', 'Chapter 2: Get your badge to blinky!'],
      ['/docs/ch3', 'Chapter 3: Input and sensor basics'],
      ['/docs/ch4', 'Chapter 4: Going beyond devices'],
      ['/docs/extra1', 'Extra: Building apps with Particle']
    ]
  },
  title: 'Particle Photon Workshop',
  description:
    'Workshops designed to teach the basics of IoT development with the Particle ecosystem & the Particle Photon'
};
