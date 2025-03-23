#include "pch.h"
#include "ImagePreprocessor.h"
#include "Image.h"

void ImagePreprocessor::GrayScale(std::shared_ptr<Image>& img)
{
	cvtColor(*img->Get(), *img->Get(), COLOR_BGR2GRAY);
}

void ImagePreprocessor::Binarization(std::shared_ptr<Image>& img)
{
	threshold(*img->Get(), *img->Get(), 0.0, 255.0, THRESH_BINARY | THRESH_OTSU);
}

void ImagePreprocessor::Morphology(std::shared_ptr<Image>& img, const MorphShapes& shape, const MorphTypes& type, Size size)
{
	Mat morphStructure = getStructuringElement(shape, size);
	morphologyEx(*img->Get(), *img->Get(), type, morphStructure);
}

void ImagePreprocessor::FindContours(std::shared_ptr<Image>& img, vector<vector<Point>>& contours, vector<Vec4i>& hierarchy)
{
	findContours(*img->Get(), contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
}
