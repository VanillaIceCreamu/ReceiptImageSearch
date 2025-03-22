#include "pch.h"
#include "Image.h"

Image::Image() : Super(ResourceType::Image)
{

}

Image::~Image()
{

}

void Image::Load(const std::string& path)
{
	_img = std::make_shared<Mat>(imread(path));

	if (_img == nullptr)
		assert(true);

}