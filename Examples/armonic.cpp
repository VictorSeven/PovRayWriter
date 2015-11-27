/* Armonic motion used as animation example*/

#include <cstdio>
#include <fstream>
#include <cstring>
#include <iostream>
#include <cmath>
#include "POVRayWriter.cpp"

int main(void)
{
      POVRayWriter pov ("armonic.pov"); //Inits POVRayWrite
      double x[50]; //Position. 50 positions for 50 frames
      double t,deltat; //Elapsed time and delta time.
      double w, A, phi; //Motion constants
      int i, maxi; //Counter

      x[0] = 0; //Initial pos
      w = 5; //Angular frec
      A=4; //Amplitude
      phi =0; //
      t=0; //Initial t
      deltat = 0.1; //Delta t: if it's lower, it's more accurate, but needs more frames.
      maxi = 50; //Number of frames
      for (i=1; i < maxi; i++)
      {
          x[i] = A*sin(w*t+phi);
          t+=deltat;
      }

      //Create the camera and ligth
      pov.createCamera(0,5,20,0,0,0);
      pov.createLight(0,0,5);

      //Create a unidimensional vector array.
      pov.declareVectorArray(maxi, "pos");
      for (i=0; i <maxi; i++)
      {
        pov.addElementToVectorArray(x[i],0,1);
      }

      //Finish the array.
      pov.closeVectorArray();

      //Create the objects
      pov.createStandardPlane("z",0,"Blue", "Grey");
      pov.setNextObjectPosFromVector("pos", "clock");
      pov.createStandardSphere(0.6, "Red");

      //Close writer
      pov.closePOVRayWriter();

      //Create INI file
      pov.createIniFile("armonic.ini",50,0,50);


      return 0;

}
