#pragma once
#include "Image.h"

using namespace std;
class OCR
{
public:
	OCR();
	~OCR();

public:
	void Init(const std::string& lang);

public:
	void ContourOCR(const shared_ptr<Image>& original);

private:
	tesseract::TessBaseAPI* _ocr;
};

