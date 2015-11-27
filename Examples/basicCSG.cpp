#include <cstdio>
#include <fstream>
#include <cstring>
#include <iostream>
#include "POVRayWriter.cpp" //Set the class in the same folder that this file

using namespace std;

int main(void)
{
    POVRayWriter pov ("output.pov"); //Writer

    pov.createCamera(5,0,7,0,0,0);
    pov.createStandardPlane("z",-5,"Red", "Green");
    pov.createLight(2,0,10); //Create camera, Light, and plane z = -5;

    pov.startCSG(pov.CSGDifference()); //Create a compound object using difference

    pov.createSphere(3,0,0,0);
    pov.createBox(-2,-2,-3,2,2,3); //Difference between the Sphere and the box.
                                    //the box will be sustracted from the sphere

    pov.addPigmentToNextObject("Blue", -1,-1); //Select the color properties for the compound object

    pov.finishCSG(); //Close the compound object




    pov.closePOVRayWriter(); //Close the writer.


    return 0;
}
