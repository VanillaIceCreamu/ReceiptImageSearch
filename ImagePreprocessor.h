#pragma once

using namespace std;

class Image;
class ImagePreprocessor
{
public:
	static void GrayScale(std::shared_ptr<Image>& img);
	static void Binarization(std::shared_ptr<Image>& img);
	static void Morphology(std::shared_ptr<Image>& img, const MorphShapes& shape, const MorphTypes& type, Size size);
	static void FindContours(std::shared_ptr<Image>& img, vector<vector<Point>>& contours, vector<Vec4i>& hierarchy);
};

