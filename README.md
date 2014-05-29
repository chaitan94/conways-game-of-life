Conway's Game Of Life
=====
Conway's Game Of Life implemented in the languages

 * python [pygame]
 * C++ [OpenGL/glut]
 * java [swing's JPanel]


### Why?
I was just interested in CGOL, so I implemented it in python using pygame, soon  I noticed the simulation slowed down will 256x256 grid size, I soon wanted to compare how fast java and C++ would be at this. So I reimplemented it in C++ using OpenGL and glut libraries, and in java using JPanel. As expected, C++ with glut was way faster than java and python.
