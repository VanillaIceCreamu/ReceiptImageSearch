#include "pch.h"
#include "ImagePreProcessing.h"
#include "Image.h"

ImagePreProcessing::ImagePreProcessing()
	: Super(PreProcessingType::Image)
{

}

ImagePreProcessing::~ImagePreProcessing()
{

}

void ImagePreProcessing::Execute()
{
	
}

void ImagePreProcessing::GrayScale(const std::shared_ptr<Image>& img)
{
	Mat mat = *img->GetImage();
	cvtColor(mat, *img->GetImage(), COLOR_BGR2GRAY);
}
void ImagePreProcessing::Binarization(const std::shared_ptr<Image>& img)
{
	Mat mat = *img->GetImage();
	threshold(mat, *img->GetImage(), 0.0, 255.0, THRESH_BINARY | THRESH_OTSU);
}

void ImagePreProcessing::Morphology(const std::shared_ptr<Image>& img, const MorphShapes& shape, const MorphTypes& type, Size size)
{
	Mat mat = *img->GetImage();
	Mat morphStructure = getStructuringElement(shape, size);
	morphologyEx(mat, *img->GetImage(), type, morphStructure);
}
