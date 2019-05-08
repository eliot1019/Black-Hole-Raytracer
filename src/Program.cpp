#include <stdio.h>
#include <stdlib.h>
#include "CGL/CGL.h"
#include <CGL/vector3D.h>
#include "CGL/Color.h"


int main( int argc, char** argv ) {
  Vector3D cameraPos = new Vector3D(0, 3, -20);
  Vector3D lookAt = new Vector3(0, 0, 0);
  Vector3D up = new Vector3(-0.3f, 1, 0);
  float fov = 55f;
  float curvatureCoeff = -1.5f;
  float angularMomentum = 0;
  string fileName = "image.png";

   // TODO: override default vars through command line

  //  Vector3D hitables = new Vector3D<Disk>;
  //   new TexturedDisk(2.6, 12.0, new Bitmap("disk_textured.png")),
  //   new Horizon(null, false),
  //   new Sky(new Bitmap("sky8k.jpg"), 30).SetTextureOffset(Math.PI / 2),
    //

    int numRandomSpheres = 0;

    // var starTexture = new Bitmap("sun2k.jpg"); // TODO:
    // var starBitmap = Utils::getNativeTextureBitmap(starTexture);

    var random = rand();

    double tempR = 0;
    double tempTheta = 0;
    double tempPhi = 0;

    double tempX = 0;
    double tempY = 0;
    double tempZ = 0;

    for (int i = 0; i < numRandomSpheres; i++) {
        tempR = 6.5 + random.NextDouble() * 6.0;
        tempTheta = random.NextDouble() * Math.PI * 2;

        Utils::toCartesian(tempR, tempTheta, 0, ref tempX, ref tempY, ref tempZ);

        hitables.Add(new TexturedSphere(tempX, tempY, tempZ, 0.05f + (float)random.NextDouble() * 0.2f, starBitmap, starTexture.Width, starTexture.Height)
            .SetTextureOffset(random.NextDouble() * Math.PI * 2));
    }

    var scene = new Scene(cameraPos, lookAt, up, fov, hitables, curvatureCoeff, angularMomentum);

  new SchwarzschildRayProcessor(1920, 1080, scene, fileName).Process();
}
