# PovRayWriter
PovRayWriter is a C++ class designed to create 3D representation of scientific data using the PovRay raytracer.

This class can be instantiated in any C++ project. It doesn't need aditional dependences. The functions built in this class are well-organized to create even 3D representations of data. The representation can be animated to show the movement of particles in 3D space.

Features:

- Simple 3D shapes, such as spheres, cubes, planes, torus... 
- Basic coloring and texturization for objects.
- Basic CSG geometry.
- Manage cameras, lights and manipulate shapes by traslation/rotation.
- Control of animation parameters.
- Fast built-in creation of PovRay arrays or custom one. 

The class generates a POV file readable by the PovRay raytracer (http://www.povray.org/). The class is designed to work with PovRay 3.6, but it should also work fine for later versions. 

You can download it simply from the Source folder. Some commented examples and the outputs generated are in the Examples folder... There's also a full pdf manual (in Spanish, which I would like to translate) which you can also download. 

The examples avaiable in the project looks like this:

![Basic CSG](https://github.com/VictorSeven/PovRayWriter/blob/master/Examples/BasicCSG/basicCSG.png "Basic CSG")
![Many Torus](https://github.com/VictorSeven/PovRayWriter/blob/master/Examples/ManyTorus/manyTorus.png "Many Torus")
![Spheres](https://github.com/VictorSeven/PovRayWriter/blob/master/Examples/Spheres/spheres.png "Spheres")




