#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

//opencv
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class DungeonMaster
{
public:
	DungeonMaster();
	~DungeonMaster();
	void update();

	void generateMap();

	inline std::vector<bool> getPlayersSatisfaction() { return m_PlayersSmiles; }
private:
	std::vector<bool> m_PlayersSmiles;

	std::string m_Story;

	int m_MapSeed;

	

	void generateNextStory();
};