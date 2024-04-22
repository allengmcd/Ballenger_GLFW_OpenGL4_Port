Ballenger
--------

About
-----
Original Author: Jonathan Gonzalez Cortes

Porting Author: Allen Gene McDermott

This is an opengl 4.6 Linux port for Ballenger (https://www.youtube.com/watch?v=aviL3HX3UEc), still in progress.

Original Source Code: https://www.dropbox.com/s/cp244x2540zr32d/Ballenger_Demo.zip?dl=0

I rewrote almost all the opengl calls and removed the glut calls. Most of the game logic remains untouched (such as the collision and physics code).

This is a demo for a single player skill game.

Goals:
- Collect the 5 keys one by one.
- Insert each one into their respective column to open the portal.
- Cross the portal.

Keys:
- Move:			W, A, S, D
- Jump: 		Spacebar
- Rotate Camera: 	Mouse
- Fist person view: 	num. 1
- Third person view: 	num. 3
- Exit: 		ESC

Noclip keys:
- Enable noclip mode: 	F10
- Fly up: 		left mouse button
- Fly down: 		right mouse button

Building
---------------------
I will write a more detailed guide to building the project later.

I used cmake with visual studio code. You will also need to make sure you have OpenGL 4.6, glad, glm, and glfw. You may need to regenerate glad.c on your own computer if you are getting lots of errors. Other then that just configure cmake in vs code and build then debug. 

Copyright and Licence
---------------------
The source code of this work, as well as the binaries, are under 
a Creative Commons Attribution 4.0 International License.
You may share and adapt this work freely as long as you give appropriate credit to its author.

Disclaimer: The soundtrack used in this work is "Home Sweet Home" from "Beyond Good and Evil" 
of which the author of this work does not take any credit, use them at your own discretion
and risk.

How to contact us
-----------------
For any questions, remarks or thanks you can contact me at:
alleng.mcd@gmail.com


Have fun!
