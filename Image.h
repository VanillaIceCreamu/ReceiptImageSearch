#pragma once
#include "ResourceBase.h"

class Image : public ResourceBase
{
	using Super = ResourceBase;
public:
	Image();
	virtual ~Image() override;

public:
	virtual void Load(const std::string& path) override;

public:
	Size GetSize() { return _img->size(); };
	const std::shared_ptr<Mat>& GetImage() { return _img; };

private:
	std::shared_ptr<Mat> _img;

};

