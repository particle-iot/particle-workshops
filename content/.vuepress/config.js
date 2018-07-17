module.exports = {
  base: '/',
  themeConfig: {
    repo: 'particle-iot/workshops',
    editLinks: true,
    editLinkText: 'Help us improve this page!',
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Team', link: 'http://particle.io' }
    ],
    sidebar: [
      '/docs/',
      ['/docs/ch1', 'Chapter 1: Claiming your Device'],
      ['/docs/ch2', 'Chapter 2: Sense from your Badge & Control a Display'],
      ['/docs/ch3', 'Chapter 3: More sensors and actuators'],
      ['/docs/ch4', 'Chapter 4: Controlling your badge from the internet!'],
      ['/docs/extra1', 'Extra: Taking your Photon exploration further']
    ]
  },
  title: 'Particle Workshops',
  description:
    'Workshops designed to teach the basics of IoT development with the Particle ecosystem'
};
