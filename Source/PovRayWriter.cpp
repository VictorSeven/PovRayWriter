#include <cstdio>
#include <fstream>
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

class POVRayWriter
{
    private:
        //Variables imprescindibles
    string filePath;
    ofstream writer;
    ofstream iniCreator;

        //Control default
    bool defaultFinish;
    bool defaultPigment;

        //Control de finish
    double phongToAdd;
    double ambientToAdd;
    double diffuseToAdd;
    bool finish;
        //Control de pigment
    string colorToAdd;
    string checkerColorToAdd[2];
    double transmitToAdd;
    double filterToAdd;
    bool pigment;
    bool checker;
        //Control de burbujas
    double powerToAdd;
    bool inBlob;
        //Control de vectores
    string nameToUse;
    string indexToUse;
    bool useVector;
        //Control de rotación
    bool rad;
    string rotationToAdd;
    bool rotation;
    double pi;
        //Control de texturas
    string textureToAdd;
    bool texture;


        //Funciones auxiliares
    string rgbToString(int r, int g, int b);
    void writeVectorAtIndex();
    void writeVector(double x, double y, double z);

    public:

    POVRayWriter(string path);

    void createIniFile(string path, int frames, int initClock, int endClock);
    void createIniFile(string path, int frames);

    string Clock();

    void addFinishToNextObject(double phong, double ambient, double diffuse);
    void writeFinish();

    void addPigmentToNextObject(string color, double transmit, double filter);
    void addPigmentToNextObject(double transmit, double filter);
    void addPigmentToNextObject(int r, int g, int b, double transmit, double filter);
    void setObjectColorChecker(string c1, string c2);
    void setObjectColorChecker(int r1, int g1, int b1, int r2, int g2, int b2);
    void writePigment();

    void useTextures();
    void addTextureToNextObject(string texture);
    void writeTexture();

    void setDefaultPigment();
    void setDefaultFinish();
    void unsetDefaults();

    void createCamera(double xi, double yi, double zi, double xf, double yf, double zf);
    void createCameraLocationFromVectorArray(double xf, double yf, double zf);
    void createCameraLookingAtFromVectorArray(double xi, double yi, double zi);
    void createCameraFromVectorArray(string vectorLocation, string vectorLookAt, string indexPos, string indexLookingAt);
    void createCameraFromVectorArray(string vectorToUse, string indexPos, string indexLookingAt);

    void createLight(double x, double y, double z, double r, double g, double b);
    void createLight(double x, double y, double z);


    void createSphere(double r, double x, double y, double z);
    void createSphere(double r);
    void createPlane(double n1, double n2, double n3, double d);
    void createPlane(double d);
    void createPlane(string plane, double d);
    void createBox(double xi, double yi, double zi, double xf, double yf, double zf);
    void createBoxInitFromVectorArray(double xf, double yf, double zf);
    void createBoxLastFromVectorArray(double xi, double yi, double zi);
    void createBoxFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex);
    void createCylinder(double xi, double yi, double zi, double xf, double yf, double zf, double r);
    void createCylinderInitFromVectorArray(double xf, double yf, double zf, double r);
    void createCylinderLastFromVectorArray(double xi, double yi, double zi, double r);
    void createCylinderFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex, double r);
    void createTorus(double middleR, double minorR);
    void createTorus(double x, double y, double z, double middleR, double minorR);

    void createStandardSphere(double r, double x, double y, double z, string color);
    void createStandardSphere(double r, string color);
    void createStandardPlane(double n1, double n2, double n3, double d, string c1, string c2);
    void createStandardPlane(double d, string c1, string c2);
    void createStandardPlane(string plane, double d, string c1, string c2);
    void createStandardBox(double xi, double yi, double zi, double xf, double yf, double zf, string color);
    void createStandardBoxInitFromVectorArray(double xf, double yf, double zf, string color);
    void createStandardBoxLastFromVectorArray(double xi, double yi, double zi, string color);
    void createStandardBoxFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex, string color);
    void createStandardCylinder(double xi, double yi, double zi, double xf, double yf, double zf, double r, string color);
    void createStandardCylinderInitFromVectorArray(double xf, double yf, double zf, double r, string color);
    void createStandardCylinderLastFromVectorArray(double xi, double yi, double zi,double r, string color);
    void createStandardCylinderFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex, double r, string color);
    void createStandardTorus(double middleR, double minorR, string color);
    void createStandardTorus(double x, double y, double z, double middleR, double minorR, string color);

    void startBlob(double threshold);
    void addPowerToNextObjects(double power);
    void finishBlob();
    void writeBlob();

    void startCSG(string CSG);
    void finishCSG();
    string CSGUnion();
    string CSGIntersection();
    string CSGDifference();
    string CSGMerge();


    void setNextObjectPosFromVector(string name, string index);
    void createFullVectorArray(int n, string name, double x[], double y[], double z[]);

    void declareVectorArray(int n, string name);
    void addElementToVectorArray(double x, double y, double z);
    void closeVectorArray();

    void addRotationToNextObject(double x, double y, double z);
    void addRotationToNextObject(string name, string index);
    void writeRotation();
    void useRadians();
    void useDegrees();



    void write(string str);

    void closePOVRayWriter();

};

/* SIGUIENTE:

- Cuidado con la UseVector en writeVectorAtIndex.
- Añadir comentarios.

*/


// ================ CLASS CONSTRUCTOR ================== //

//Class constructor. Initializes the file writer.
POVRayWriter::POVRayWriter(string path)
{
    writer.open(path.c_str());

    if (writer.is_open())
    {
            filePath = path;
            writer << "// This file have been generated with" << endl;
            writer << "// Victor Buendia's POVRAY WRITER" << endl << endl;

            writer << "#include \"colors.inc\" " << endl << endl;
            writer << "background { color Cyan } " << endl << endl;
    }

    finish = pigment = checker = defaultFinish = defaultPigment = inBlob = rotation = texture = false;
    pi = 3.14159265358;
    return;
}

//Returns the clock variable of POV-Ray
string POVRayWriter::Clock()
{
    return "clock";
}

//Creates a ini animation file with the specified number of frames, starting
//at initClock and ending at endClock. The file will be created in the path specified.
void POVRayWriter::createIniFile(string path,int frames, int initClock, int endClock)
{
    iniCreator.open(path.c_str());

    iniCreator << "; INI File Generated with Victor Buendia's POVRayWriter" << endl;
    iniCreator << "Input_File_Name = " << filePath << endl;
    iniCreator << "Initial_Frame = 0" << endl << "Final_Frame = " << frames << endl;
    iniCreator << "Initial_Clock = " << initClock << endl << "Final_Clock = " << endClock << endl;

    iniCreator.close();
    return;
}

//Create a ini animation file in the path given, with the specified frames.
//InitClock and endClock will be adjusted to make a relation 1:1 between
//frames and clocks; this is useful for arrays.
void POVRayWriter::createIniFile(string path, int frames)
{
    iniCreator.open(path.c_str());

    iniCreator << "; INI File Generated with Victor Buendia's POVRayWriter" << endl;
    iniCreator << "Input_File_Name = " << filePath << endl;
    iniCreator << "Initial_Frame = 0" << endl << "Final_Frame = " << frames << endl;
    iniCreator << "Initial_Clock = 0" << endl << "Final_Clock = " << frames << endl;

    iniCreator.close();
    return;
}

//Allows the user to write custom content.
void POVRayWriter::write(string str)
{
    writer << str;
    return;
}

//Close the final.
//IT'S VERY IMPORTANT TO INVOKE THIS FUNCTION AFTER FINISH.
void POVRayWriter::closePOVRayWriter()
{
    writer.close();
    return;
}


// ================= PRIMITIVE CREATION ============================ //

//Create a standard camera from its positions and the point that is looking at.
void POVRayWriter::createCamera(double xi, double yi, double zi, double xf, double yf, double zf)
{
    writer << "camera { " << endl;
    writer << "location ";
    writeVector(xi, yi, zi);
    writer << endl << "look_at ";
    writeVector(xf, yf, zf);
    writer << endl << "sky <0,0,1>" << endl << "} " << endl << endl;

    return;
}

//Create a light with custom position and RGB color.
void POVRayWriter::createLight(double x, double y, double z, double r, double g, double b)
{
    writer << "light_source {" << endl;
    writeVector(x,y,z);
    writer << endl << "color rgb <" << r <<", " << g << ", " << b << ">" << endl;
    writer << "} " << endl << endl;

    return;
}

//Create a light with a standard color at the specified position
void POVRayWriter::createLight(double x, double y, double z)
{
    writer << "light_source {" << endl;
    writeVector(x,y,z);
    writer << endl << "color rgb <1,1,1>" << endl;
    writer << "} " << endl << endl;

    return;
}

//Create a sphere with the radious and coordinates indicated
void POVRayWriter::createSphere(double r, double x, double y, double z)
{
    writer << "sphere {" << endl;

    writeVector(x,y,z);

    writer << r; //<< endl;


    writeBlob();
    writeTexture();
    writeFinish();
    writePigment();

    writeRotation();
    writer << "}" << endl << endl;

    return;
}

//Creates an sphere with radious and a vector array
//Needs to be initialized with setNextObjectPosFromVector function
void POVRayWriter::createSphere(double r)
{
    writer << "sphere {" << endl;

    writeVectorAtIndex();
    writer << r;// << endl;

    writeBlob();
    writeFinish();
    writeTexture();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;

    return;
}

//Create a plane with the normal vector and distances indicated
void POVRayWriter::createPlane(double n1, double n2, double n3, double d)
{
    writer << "plane {" << endl;
    writeVector(n1, n2, n3);
    writer << ", " <<  d << endl;

    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;
    return;
}

//Create a plane perpendicular to the selected vector, at
//a d distance.
void POVRayWriter::createPlane(double d)
{
    writer << "plane {" << endl;
    writeVectorAtIndex();
    writer << d << endl;

    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;
    return;
}

//Create a plane from its formula, like "x" or "3*z" at a d distance.
void POVRayWriter::createPlane(string plane, double d)
{
    writer << "plane {" << endl;
    writer << plane << ",  " << d << endl;

    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;
    return;
}

//Creates a bnx from the upper left corner and down right corner.
void POVRayWriter::createBox(double xi, double yi, double zi, double xf, double yf, double zf)
{
    writer << "box {" << endl;
    writeVector(xi,yi,zi);
    writeVector(xf, yf, zf);

    writer << endl;
    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;

    return;
}

//Creates a box substituting the first vector by the vector array at the index selected by
//setNextObjectPosFromVector, which is mandatory to use.
void POVRayWriter::createBoxInitFromVectorArray(double xf, double yf, double zf)
{
    writer << "box {" << endl;
    writeVectorAtIndex();
    writeVector(xf, yf, zf);

    writer << endl;
    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;

    return;
}

//Creates a box substituting the last vector by the vector array at the index selected by
//setNextObjectPosFromVector, which is mandatory to use.
void POVRayWriter::createBoxLastFromVectorArray(double xi, double yi, double zi)
{
    writer << "box {" << endl;
    writeVector(xi, yi, zi);
    writeVectorAtIndex();


    writer << endl;
    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;

    return;
}

//Creates a box using the vectors indicated.
void POVRayWriter::createBoxFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex)
{
    writer << "box {" << endl;

    setNextObjectPosFromVector(initVector,initIndex);
    writeVectorAtIndex();
    setNextObjectPosFromVector(lastVector,lastIndex);
    writeVectorAtIndex();


    writer << endl;
    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;

    return;
}

//Creates a basic cylinder from the position of its faces and a radious.
 void POVRayWriter::createCylinder(double xi, double yi, double zi, double xf, double yf, double zf, double r)
 {
     writer << "cylinder {" << endl;
     writeVector(xi, yi, zi);
     writeVector(xf, yf, zf);
     writer << r; //<< endl;

     writeBlob();
     writeTexture();
     writeFinish();
     writePigment();
     writeRotation();
     writer << "}" << endl << endl;

     return;
 }

 //Creates a cylinder substituting the first vector by the vector array at the index selected by
//setNextObjectPosFromVector, which is mandatory to use.
  void POVRayWriter::createCylinderInitFromVectorArray(double xf, double yf, double zf, double r)
 {
     writer << "cylinder {" << endl;
     writeVectorAtIndex();
     writeVector(xf, yf, zf);
     writer << r;// << endl;

     writeBlob();
     writeTexture();
     writeFinish();
     writePigment();
     writeRotation();
     writer << "}" << endl << endl;

     return;
 }

  //Creates a cylinder substituting the last vector by the vector array at the index selected by
//setNextObjectPosFromVector, which is mandatory to use.
  void POVRayWriter::createCylinderLastFromVectorArray(double xi, double yi, double zi, double r)
 {
     writer << "cylinder {" << endl;
    writeVector(xi, yi, zi);
    writeVectorAtIndex();
     writer << r; //<< endl;

     writeBlob();
     writeTexture();
     writeFinish();
     writePigment();
     writeRotation();
     writer << "}" << endl << endl;

     return;
 }

  //Creates a cylinder substituting the last vector by the vector array at the index selected by
//setNextObjectPosFromVector, which is mandatory to use.
  void POVRayWriter::createCylinderFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex, double r)
 {
     writer << "cylinder {" << endl;

    setNextObjectPosFromVector(initVector,initIndex);
    writeVectorAtIndex();
    setNextObjectPosFromVector(lastVector,lastIndex);
    writeVectorAtIndex();

    writer << r;// << endl;

     writeBlob();
     writeTexture();
     writeFinish();
     writePigment();
     writeRotation();
     writer << "}" << endl << endl;

     return;
 }

 //Creates a torus using the major radious (from center to middle line) and the
 //minor radious of the torus, in the position specified by the function
 //setNextObjectPosFromVector.
 void POVRayWriter::createTorus(double middleR, double minorR)
 {
     writer << "torus {" << endl << middleR << ", " << minorR << endl;

     writeTexture();
     writeFinish();
     writePigment();
     writeRotation();

     writer << "translate ";
     writeVectorAtIndex();

     writer << "}" << endl << endl;

     return;
 }

 //Creates a torus using the major radious (from center to middle line) and the
 //minor radious of the torus, in the indicated position
 void POVRayWriter::createTorus(double x, double y, double z, double middleR, double minorR)
 {
     writer << "torus {" << endl << middleR << ", " << minorR << endl;

     writeTexture();
     writeFinish();
     writePigment();
     writeRotation();

     writer << "translate ";
     writeVector(x,y,z);

     writer << "}" << endl << endl;

     return;
 }




// ========================== DECORATED PRIMITIVE CREATION ==================== //

/* Creates a camera using a vector; The vector can substitute the location, the look_at or both.
Note the first two (which only substitute one parameter) needs to be initialized with
setNextObjectPosFromVector function.
The other two don't need this sentence.*/


void POVRayWriter::createCameraLocationFromVectorArray(double xf, double yf, double zf)
{
    writer << "camera { " << endl;
    writer << "location ";
    writeVectorAtIndex();
    writer << endl << "look_at ";
    writeVector(xf, yf, zf);
    writer << endl << "sky <0,0,1>" << endl << "} " << endl << endl;

    return;
}

void POVRayWriter::createCameraLookingAtFromVectorArray(double xi, double yi, double zi)
{
    writer << "camera { " << endl;
    writer << "location ";
    writeVector(xi, yi, zi);
    writer << endl << "look_at ";
    writeVectorAtIndex();
    writer << endl << "sky <0,0,1>" << endl << "} " << endl << endl;

}

void POVRayWriter::createCameraFromVectorArray(string vectorLocation, string vectorLookAt, string indexPos, string indexLookingAt)
{
    setNextObjectPosFromVector(vectorLocation, indexPos);

    writer << "camera { " << endl;
    writer << "location ";
    writeVectorAtIndex();

    setNextObjectPosFromVector(vectorLookAt, indexLookingAt);

    writer << endl << "look_at ";
    writeVectorAtIndex();
    writer << endl << "sky <0,0,1>" << endl << "} " << endl << endl;


    return;
}

void POVRayWriter::createCameraFromVectorArray(string vectorToUse, string indexPos, string indexLookingAt)
{
    setNextObjectPosFromVector(vectorToUse, indexPos);

    writer << "camera { " << endl;
    writer << "location ";
    writeVectorAtIndex();

    setNextObjectPosFromVector(vectorToUse, indexLookingAt);

    writer << endl << "look_at ";
    writeVectorAtIndex();
    writer << endl << "sky <0,0,1>" << endl << "} " << endl << endl;


    return;
}

/* Creates the same primitive shapes, but with a predefined color and a standard value
of phong = 0.5. NOTE: if you want to add a custom rgb color o custum finish / pigment properties
you should use the primitives instead of this functions. */

void POVRayWriter::createStandardSphere(double r, double x, double y, double z, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createSphere(r,x,y,z);

    return;
}

void POVRayWriter::createStandardSphere(double r, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createSphere(r);

    return;
}

void POVRayWriter::createStandardPlane(double n1, double n2, double n3, double d, string c1, string c2)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject("", -1,-1);
    setObjectColorChecker(c1, c2);

    createPlane(n1, n2, n3, d);

    return;
}

void POVRayWriter::createStandardPlane(double d, string c1, string c2)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject("", -1,-1);
    setObjectColorChecker(c1, c2);

    createPlane(d);

    return;
}

void POVRayWriter::createStandardPlane(string plane, double d, string c1, string c2)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject("", -1,-1);
    setObjectColorChecker(c1, c2);

    createPlane(plane, d);

    return;
}

void POVRayWriter::createStandardBox(double xi, double yi, double zi, double xf, double yf, double zf, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createBox(xi, yi, zi, xf, yf, zf);

    return;
}

void POVRayWriter::createStandardBoxInitFromVectorArray(double xf, double yf, double zf, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createBoxInitFromVectorArray(xf, yf, zf);

    return;
}

void POVRayWriter::createStandardBoxLastFromVectorArray(double xi, double yi, double zi, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createBoxLastFromVectorArray(xi, yi, zi);

    return;
}

void POVRayWriter::createStandardBoxFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createBoxFromVectorArray(initVector,lastVector,initIndex,lastIndex);

    return;
}

void POVRayWriter::createStandardCylinder(double xi, double yi, double zi, double xf, double yf, double zf,double r, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createCylinder(xi, yi, zi, xf, yf, zf,r);

    return;
}

void POVRayWriter::createStandardCylinderInitFromVectorArray(double xf, double yf, double zf, double r, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createCylinderInitFromVectorArray(xf, yf, zf,r);

    return;
}

void POVRayWriter::createStandardCylinderLastFromVectorArray(double xi, double yi, double zi, double r, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createCylinderLastFromVectorArray(xi, yi, zi,r);

    return;
}

void POVRayWriter::createStandardCylinderFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex, double r, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createCylinderFromVectorArray(initVector,lastVector,initIndex,lastIndex,r);

    return;
}


void POVRayWriter::createStandardTorus(double middleR,double minorR,string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createTorus(middleR, minorR);

    return;
}

void POVRayWriter::createStandardTorus(double x, double y, double z, double middleR,double minorR,string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createTorus(x,y,z,middleR, minorR);

    return;
}


// ============================= DECORATORS =========================== //


//This will make FINISH true so next instantiated object will have
//a particular value of phong, ambient, etc. If any of this values is < 0
//then is NOT added to the finish.
void POVRayWriter::addFinishToNextObject(double phong, double ambient, double diffuse)
{
    finish = true;
    phongToAdd = phong;
    diffuseToAdd=diffuse;
    ambientToAdd=ambient;
    return;
}

//Write the finish part of a primite object
void POVRayWriter::writeFinish()
{
    if (finish || defaultFinish)
    {
        finish = false;
        writer << "finish { ";
        if (phongToAdd > 0)
        {
            writer << "phong " << phongToAdd << " ";
        }
        if (diffuseToAdd > 0)
        {
            writer << "diffuse " << diffuseToAdd << " ";
        }
        if (ambientToAdd > 0)
        {
            writer << "ambient " << ambientToAdd << " ";
        }

        writer << " } " << endl;

    }
    return;
}

//Makes true the PIGMENT property so next instantiated object will have
//the particular selected values. It's obligatory to choose a color.
//The other properties can be ignored, only setting them to -1.
void POVRayWriter::addPigmentToNextObject(int r, int g, int b, double transmit, double filter)
{
    pigment = true;
    colorToAdd = rgbToString(r,g,b);
    transmitToAdd = transmit;
    filterToAdd = filter;
    return;
}

//Makes true the PIGMENT property so next instantiated object will have
//the particular selected values. It's obligatory to choose a color.
//The other properties can be ignored, only setting them to -1.
void POVRayWriter::addPigmentToNextObject(string color, double transmit, double filter)
{
    pigment = true;
    colorToAdd = color;
    transmitToAdd = transmit;
    filterToAdd = filter;
    return;
}

//Add a pigment to the next object, with color white and custom transmit/filter
void POVRayWriter::addPigmentToNextObject(double transmit, double filter)
{
    pigment = true;
    colorToAdd = "White";
    transmitToAdd = transmit;
    filterToAdd = filter;
    return;
}

//This can set the color of an object to a checkr mode
void POVRayWriter::setObjectColorChecker(string c1, string c2)
{
    checker = true;
    checkerColorToAdd[0] = c1;
    checkerColorToAdd[1] = c2;
    return;
}

//This can set the color of an object to a checkr mode
void POVRayWriter::setObjectColorChecker(int r1, int g1, int b1, int r2, int g2, int b2)
{
    checker = true;
    checkerColorToAdd[0] = rgbToString(r1,g1,b1);
    checkerColorToAdd[1] = rgbToString(r2,g2,b2);
    return;
}

//Write the pigment property of an object.
void POVRayWriter::writePigment()
{
    if (pigment || defaultPigment)
    {
        pigment = false;
        if (checker)
        {
            checker = false;
            writer << "pigment { checker color " << checkerColorToAdd[0] << " color " << checkerColorToAdd[1] << " ";
        }
        else
        {
            writer << "pigment { color " << colorToAdd << " ";
        }

        if (transmitToAdd > 0)
        {
            writer << "transmit " << transmitToAdd << " ";
        }
        if (filterToAdd > 0)
        {
             writer << "filter " << filterToAdd << " ";
        }

        writer << " }" << endl;
    }
}

//inclusion for textures in POV-Ray. Mandatory to include it at
//the beginning of the file if we want to include textures.
void POVRayWriter::useTextures()
{
    writer << "#include \"textures.inc\"" << endl << endl;
    return;
}

//Include the specified texture to next object. It's necesary
//to invoke useTextures at the beginning of the file to do this.
void POVRayWriter::addTextureToNextObject(string text)
{
    textureToAdd = text;
    texture = true;
    return;
}

//Write the texture into the material
void POVRayWriter::writeTexture()
{
    if (texture)
    {
        writer << "texture { " << textureToAdd << " }" << endl;
    }
    texture = false;
    return;
}

//Set the default finish true, so all objects will have
//same finish configuration after invoke this.
//That configuration is stablished with addFinishToNextObject.
void POVRayWriter::setDefaultFinish()
{
    defaultFinish = true;
    return;
}

//Set the default pigment true, so all objects will have
//same pigment configuration after invoke this.
//That configuration is stablished with addPigmentToNextObject.
void POVRayWriter::setDefaultPigment()
{
    defaultPigment = true;
    return;
}

//Delete all defualt configurations
void POVRayWriter::unsetDefaults()
{
    defaultFinish = defaultPigment = false;
    return;
}


// ============================ BLOBS AND CSG GEOMETRIES =========================== //

//Inits a blob object. It must be followed of the creation of primitives. After that,
//it must be closed using finishBlob function.
void POVRayWriter::startBlob(double threshold)
{
    writer << "blob {" << endl << "threshold " << threshold << endl;
    inBlob = true;
    return;
}

//Set the power for the next objects inside a blob.
//It's mandatory to include at least one of this inside a blob
//Power can be negative.
void POVRayWriter::addPowerToNextObjects(double power)
{
    powerToAdd = power;
}

//Closes the blob.It is not affected by the defaults.
void POVRayWriter::finishBlob()
{
    if (!defaultFinish)
    {
        writeFinish();
    }
    if (!defaultPigment)
    {
        writePigment();
    }


    writeTexture();
    writeRotation();

    writer << endl << "}" << endl << endl;
    inBlob = false;
    return;
}

//Write blob configuration inside an object
void POVRayWriter::writeBlob()
{
    if (inBlob)
    {
        writer << "," << endl << powerToAdd << endl;
    }
    else
    {
        writer << endl;
    }
    return;
}

//Start a new CSG object
//The string CSG can be union, difference,
//etc. depeding on what we want to do.
void POVRayWriter::startCSG(string CSG)
{
    writer << CSG << " {" << endl;
    return;
}

//Finish a CSG object and apply it's configuration
void POVRayWriter::finishCSG()
{
    if (!defaultFinish)
    {
        writeFinish();
    }
    if (!defaultPigment)
    {
        writePigment();
    }

    writeTexture();
    writeRotation();

    writer << endl << "}" << endl << endl;

    return;
}

/* This functions return the value of the constant
strings that can be used in startCSG argument */
 string POVRayWriter::CSGUnion()
 {
     return "union";
 }
string POVRayWriter::CSGIntersection()
{
    return "intersection";
}
string POVRayWriter::CSGDifference()
{
    return "difference";
}
string POVRayWriter::CSGMerge()
{
    return "merge";
}



// ===================== ARRAYS AND ROTATIONS=========================== //

//Declare a vector with a specific size and name
//IT'S NECESSARY TO CLOSE THIS WITH closeVectorArray.
 void POVRayWriter::declareVectorArray(int n, string name)
 {
     writer << "#declare " << name << " = array[" << n << "] {" << endl;

     return;
 }
 //This will add a element to the current opened/declared vector
void POVRayWriter::addElementToVectorArray(double x, double y, double z)
{
    writer << "<" << x << ", " << y << ", " << z << ">,";
}
//Closes the current vector. It's necessary to close a vector
//after the data input
void POVRayWriter::closeVectorArray()
{
    writer << endl << "} " << endl << endl;
}

//Declares a vector, introduces the data stored in x[], y[] and z[] and closes the vector
//This is a faster way to create a vector. If you need a flexible way or you like to control
//the details of the data input, you can use the primitives above.
void POVRayWriter::createFullVectorArray(int n, string name, double x[], double y[], double z[])
{
    int i;
    declareVectorArray(n, name);
    for (i=0; i < n; i++)
    {
        addElementToVectorArray(x[i], y[i], z[i]);
    }
    closeVectorArray();
}

//Allows the user to set the position of an object from the value of
//a vector array. It will affect only the next object.
void POVRayWriter::setNextObjectPosFromVector(string name, string index)
{
    nameToUse=name;
    indexToUse=index;
    useVector=true;

    return;
}

//Tell the system to use radians
//It will only affect the first overload of
//addRotationToNextObject
void POVRayWriter::useRadians()
{
    rad = true;
    return;
}

//Tell the system to use degrees (default configuration)
//It will only affect the first overload of
//addRotationToNextObject
void POVRayWriter::useDegrees()
{
    rad = false;
    return;
}

//Rotates the object x degrees around X axis, y  degrees
//around Y axis and z degrees around Z axis.
//The units by default are degrees, but it can be set to radians.
void POVRayWriter::addRotationToNextObject(double x, double y, double z)
{
    if (rad)
    {
        x = (180 * x) / pi;
        y = (180 * y) / pi;
        z = (180 * z) / pi;
    }
    stringstream s1, s2, s3;
    s1 << x;
    s2 << y;
    s3 << z;
    rotationToAdd = "<" + s1.str() + ", " + s2.str() + ", " + s3.str() + ">";
    rotation = true;
    return;
}

//It uses the vector name[index] to rotate the object. This will be
//ALWAYS in degrees, so if you use radians, make sure to transform them
//when you write your vector
void POVRayWriter::addRotationToNextObject(string name, string index)
{
    rotationToAdd.append(name);
    rotationToAdd.append("[");
    rotationToAdd.append(index);
    rotationToAdd.append("]");
    rotation = true;
    return;
}

//Write the rotation into an object
void POVRayWriter::writeRotation()
{
    if (rotation)
    {
        writer << "rotate " << rotationToAdd << endl;
    }

    return;
}



// ============================== AUXILIAR FUNCTIONS ===================================== //

//Write the (r,g,b) values into a correctly formated rgb color
string POVRayWriter::rgbToString(int r, int g, int b)
{
     stringstream s1, s2, s3;
    s1 << r;
    s2 << g;
    s3 << b;
    return "rgb <" + s1.str() + ", " + s2.str() + ", " + s3.str() + ">";
}

//Write the vector value at the index selected.
void POVRayWriter::writeVectorAtIndex()
{
    writer << nameToUse << "[" << indexToUse << "] ";
    useVector = false; //AÑADIDO DESPUES. CUIDADO. PUEDE QUE HAYA QUE QUITAR
    return;
}

//Writes the vector indicated in the file
void POVRayWriter::writeVector(double x, double y, double z)
{
    writer << "<" << x << ", " << y << ", " << z << "> ";
    return;
}
