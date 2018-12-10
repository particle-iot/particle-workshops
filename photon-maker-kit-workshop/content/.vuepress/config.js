module.exports = {
  base: '/',
  themeConfig: {
    repo: 'particle-iot/maker-kit-workshop',
    editLinks: true,
    editLinkText: 'Help us improve this page!',
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Team', link: 'http://particle.io' }
    ],
    sidebar: [
      '/docs/',
      ['/docs/ch1', 'Chapter 1: Claiming your device'],
      [
        '/docs/ch2',
        'Chapter 2: Reading from sensors and posting data to the cloud'
      ],
      ['/docs/ch3', 'Chapter 3: Connecting the Particle Device Cloud to Azure'],
      ['/docs/ch4', 'Chapter 4: Visualizing sensor data in the cloud'],
      ['/docs/ch5', 'Chapter 5: Controlling your devices from the cloud']
    ]
  },
  title: 'Particle Maker Kit Workshop',
  description:
    'Workshops designed to teach the basics of IoT development with the Particle ecosystem & the Particle Photon'
};
