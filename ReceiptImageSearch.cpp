#include "pch.h"
#include "OCR.h"
#include "Image.h"
using namespace std;

int main()
{
	OCR *ocr = new OCR();
	ocr->Init("kor");
	
	shared_ptr<Image> img = make_shared<Image>(); 
	img->Load(".\\Receipts\\123.png");
	ocr->ContourOCR(img);
	return 0;
}