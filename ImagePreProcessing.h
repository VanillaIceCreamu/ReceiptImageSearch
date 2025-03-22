#pragma once
#include "PreProcessing.h"

class Image;
class ImagePreProcessing : public PreProcessing
{
	using Super = PreProcessing;
public:
	ImagePreProcessing();
	virtual ~ImagePreProcessing() override;

public:
	virtual void Execute() override;

private:
	void GrayScale(const std::shared_ptr<Image>& img);
	void Binarization(const std::shared_ptr<Image>& img);
	void Morphology(const std::shared_ptr<Image>& img, const MorphShapes& shape ,const MorphTypes& type, Size size);

private:

};

