module.exports = {
  base: '/particle-workshops/',
  themeConfig: {
    repo: 'particle-iot/workshops',
    editLinks: true,
    editLinkText: 'Help us improve this page!',
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Team', link: 'http://particle.io' }
    ],
    sidebar: [
      '/content/',
      ['/content/ch1', 'Chapter 1: Claiming your Device'],
      ['/content/ch2', 'Chapter 2: Sense from your Badge & Control a Display'],
      ['/content/ch3', 'Chapter 3: More sensors and actuators'],
      ['/content/ch4', 'Chapter 4: Controlling your badge from the internet!'],
      ['/content/extra1', 'Extra: Taking your Photon exploration further']
    ]
  },
  title: 'Particle Workshops',
  description:
    'Workshops designed to teach the basics of IoT development with the Particle ecosystem'
};
