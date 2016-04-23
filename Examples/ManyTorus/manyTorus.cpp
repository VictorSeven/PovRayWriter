//Creates a form based on various torus which are rotated

#include <cstdio>
#include <iostream>
#include "POVRayWriter.cpp"

using namespace std;

int main(void)
{
    POVRayWriter pov ("manyTorus.pov"); //Writer
    int i, n;
    double deltaPhi;

    n = 10; //Number of torus
    deltaPhi = 360 / n; //Angle variation of each torus

    pov.useTextures(); //We're going to use textures

    pov.useDegrees(); //Tell POV-Ray to use degrees.

    pov.createCamera(10,0,2,0,0,0);
    pov.createLight(20,5,20); //Define scene by camera and light

    pov.createStandardPlane(0,0,1,-5,"White","Grey"); //Creates a standard plane, z = -5

    pov.startCSG(pov.CSGUnion()); //Creates the object as a union of torus
    for (i=0; i < n; i++)
    {
        pov.addTextureToNextObject("X_Gradient"); //Set this special texture which creates lot of colors
        pov.addRotationToNextObject(deltaPhi*i,0,0); //Rotate next torus by deltaPhi * i.
        pov.createTorus(0,0,0,2,1); //Create torus of mayor radious 3 and minor radious 1
    }

    pov.addRotationToNextObject(0,0,45); //We rotate the whole united object
    pov.finishCSG(); //close the object

    pov.closePOVRayWriter(); //close writer
    return 0;
}
