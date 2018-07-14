 #include<iostream>
 #include "opencv2/imgproc/imgproc.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include <opencv2/core/core.hpp>
 #include<dirent.h>
 #include<string.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <stdio.h>

using namespace std;
using namespace cv;
 using namespace std;
 using namespace cv;

 int main()
 {
     string dirName = "images/";
     DIR *dir;
     dir = opendir(dirName.c_str());
     string imgName;
     struct dirent *ent;
     if (dir != NULL) {
     while ((ent = readdir (dir)) != NULL) {
           imgName= ent->d_name;
           //I found some . and .. files here so I reject them.
           if(imgName.compare(".")!= 0 && imgName.compare("..")!= 0)
           {
             string aux;
             aux.append(dirName);
             aux.append(imgName);
             cout << aux << endl;
             Mat image= imread(aux);
             resize(image,image,Size(640, 480));
             CascadeClassifier face_cascade;
             face_cascade.load( "haarcascade_frontalface_alt.xml" );
             if(face_cascade.empty())
// if(!face_cascade.load("D:\\opencv2410\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml"))
                 {
                  cerr<<"Error Loading XML file"<<endl;
                  return 0;
                 }
                std::vector<Rect> faces;
                face_cascade.detectMultiScale( image, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

                // Draw circles on the detected faces
                for( int i = 0; i < faces.size(); i++ )
                {
                    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
                    ellipse( image, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
                }
             imshow(aux,image);
             waitKey(0);
           }
      }
      closedir (dir);
  } else {
      cout<<"not present"<<endl;
     }
 }