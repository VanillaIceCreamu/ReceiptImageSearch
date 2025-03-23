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
	std::shared_ptr<Image> Clone();

public:
	Size GetSize() { return _img->size(); };
	const std::shared_ptr<Mat>& Get() { return _img; };
	std::shared_ptr<Mat>& GetMutable() { return _img; }

private:
	std::shared_ptr<Mat> _img;

};

