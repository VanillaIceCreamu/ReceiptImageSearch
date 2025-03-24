#include "pch.h"
#include "OCR.h"
#include "Image.h"
#include "ImagePreprocessor.h"

OCR::OCR()
{

}

OCR::~OCR()
{

}

void OCR::Init(const std::string& lang)
{
	_ocr = new tesseract::TessBaseAPI();
	if (_ocr->Init(NULL, lang.c_str()))
	{
		cout << "Tesseract �ʱ�ȭ ����" << endl;
		assert(true);
	}
}

void OCR::ContourOCR(const shared_ptr<Image>& original)
{
	shared_ptr<Image> result = original->Clone();
	shared_ptr<Image> img = original->Clone();

	// �׷��̽����� ��ȯ
	ImagePreprocessor::GrayScale(img);

	// Morphological Gradient ���
	ImagePreprocessor::Morphology(img, MORPH_ELLIPSE, MORPH_GRADIENT, Size(3, 3));

	// ����ȭ
	ImagePreprocessor::Binarization(img);

	// ���� ����
	ImagePreprocessor::Morphology(img, MORPH_RECT, MORPH_CLOSE, Size(15, 1));

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	ImagePreprocessor::FindContours(img, contours, hierarchy);

	Mat resized;
	resize(*img->Get(), resized, img->GetSize() / 8); // ���ϴ� ũ��� ����
	imshow("original", resized);
	waitKey(0);

	// �ؽ�Ʈ �ν�
	for (size_t i = 0; i < contours.size(); ++i) 
	{
		Rect rect = boundingRect(contours[i]);

		// ���� ���� ���͸�
		if (rect.height < 10 || rect.width < 10) {
			continue;
		}

		// ROI ����
		Mat roi = (*result->Get())(rect);

		// Tesseract�� �̹��� ����
		_ocr->SetImage(roi.data, roi.cols, roi.rows, 3, roi.step);

		// �ؽ�Ʈ �ν� ����
		char* outText = UTF8ToANSI(_ocr->GetUTF8Text());
		
		cout << "�νĵ� �ؽ�Ʈ: " << outText << endl;

		// ��� ǥ��
		rectangle(*result->Get(), rect, Scalar(0, 255, 0), 8);
		putText(*result->Get(), outText, Point(rect.x, rect.y - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);

		delete[] outText;  // �޸� ����
	}

	// Mat resized;
	resize(*result->Get(), resized, result->GetSize() / 8); // ���ϴ� ũ��� ����
	imshow("original", resized);
	waitKey(0);
}

char* OCR::UTF8ToANSI(const char* pszCode)
{
	BSTR    bstrWide;
	char* pszAnsi;
	int     nLength;

	// Get nLength of the Wide Char buffer
	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1,
		NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);

	// Change UTF-8 to Unicode (UTF-16)
	MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, bstrWide, nLength);

	// Get nLength of the multi byte buffer
	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];

	// Change from unicode to mult byte
	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
	SysFreeString(bstrWide);

	return pszAnsi;
}