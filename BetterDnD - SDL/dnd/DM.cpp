#include "DM.h"
#include "../ECS/EntityComponentSystem.h"
#include "../ECS/TransformComponent.h"
#include "../ECS/SpriteComponent.h"

void detectAndDisplay(Mat frame);
CascadeClassifier smile_cascade;
CascadeClassifier face_cascade;

extern Manager manager;

DungeonMaster::DungeonMaster()
{
	face_cascade.load("database/haarcascade_frontalface_default.xml");
	smile_cascade.load("database/haarcascade_smile.xml");
	
}

DungeonMaster::~DungeonMaster()
{

}


void DungeonMaster::update()
{
	/*VideoCapture cap(0);
	for (;;)
	{
		Mat frame;
		cap >> frame;
		detectAndDisplay(frame);
		if (waitKey(30) >= 0) break;

	}*/
	//GENERATE NEXT PART OF THE STORY
	
}

void DungeonMaster::generateMap()
{
	//fill everything with water
	for (int i = 0; i <= 1154; i+=256)
	{
		for (int j = 0; j <= 760; j += 256)
		{
			auto& background(manager.addEntity());
			background.addComponent<TransformComponent>(i, j, 256, 256, 1);
			background.addComponent<SpriteComponent>("database/Map/k.jpg");
			background.addGroup(Application::groupGeneratedMap);
		}
	}

	int BigParts = rand() % 6 + 1;
	
	//auto& part1(manager.addEntity());
	//use python script to generate next part

}

void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		Mat faceROI = frame_gray(faces[i]);
		std::vector<Rect> eyes;
		//-- In each face, detect smiles
		smile_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
		for (size_t j = 0; j < eyes.size(); j++)
		{
			Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(frame, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);
		}
	}
	//-- Show what you got
	imshow("window", frame);
}