module.exports = {
  base: '/',
  themeConfig: {
    repo: 'nielsclausen/workshop-mesh-thingscon2018',
    nav: [{ text: 'Particle', link: 'http://particle.io' }],
    sidebar: [
      ['/workshop/', 'Introduction'],
      ['/workshop/prerequisites', 'Preparations'],
      ['/workshop/box-to-blinky', '1 – From Box to Blinky'],
      ['/workshop/grove-kit-distance-display', '2 – Measuring a distance'],
      ['/workshop/mesh-messaging', '3 – Working in the Mesh'],
      ['/workshop/mesh-distance-display', '4 – Putting it all together']
    ]
  },
  title: 'IoT Workshop – Particle Mesh'
};
