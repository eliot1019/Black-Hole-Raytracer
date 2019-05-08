#include <stdio.h>
#include <stdlib.h>
#include "CGL/CGL.h"
#include <CGL/vector3D.h>
#include "Scene.h"
#include "SchwarzschildRayProcessor.h"


int main( int argc, char** argv ) {
  Vector3D cameraPos = new Vector3D(0, 3, -20);
  Vector3D lookAt = new Vector3D(0, 0, 0);
  Vector3D up = new Vector3D(-0.3f, 1, 0);
  float fov = 55f;
  float curvatureCoeff = -1.5f;
  float angularMomentum = 0;
  string fileName = "image.png";

   // TODO: override default vars through command line args ?

  //  Vector3D<IHitable *> &hitables = new Vector3D<IHitable>;

  // TODO: append these to the vector3D hitables list
  //   new TexturedDisk(2.6, 12.0, new Bitmap("disk_textured.png")), // TODO: are we using `new Mat(...)` rather than  `new Bitmap(...)` ?
  //   new Horizon(null, false),
  //   new Sky(new Bitmap("sky8k.jpg"), 30).SetTextureOffset(Math.PI / 2),

    Scene scene = new Scene(cameraPos, lookAt, up, fov, hitables, curvatureCoeff, angularMomentum);

  // new SchwarzschildRayProcessor(1920, 1080, scene, fileName).Process(); // TODO: fix this after SchwarzschildRayProcessor PR gets merged
}
