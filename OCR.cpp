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
		cout << "Tesseract 초기화 실패" << endl;
		assert(true);
	}
}

void OCR::ContourOCR(const shared_ptr<Image>& original)
{
	shared_ptr<Image> result = original->Clone();
	shared_ptr<Image> img = original->Clone();

	// 그레이스케일 변환
	ImagePreprocessor::GrayScale(img);

	// Morphological Gradient 계산
	ImagePreprocessor::Morphology(img, MORPH_ELLIPSE, MORPH_GRADIENT, Size(3, 3));

	// 이진화
	ImagePreprocessor::Binarization(img);

	// 닫힘 연산
	ImagePreprocessor::Morphology(img, MORPH_RECT, MORPH_CLOSE, Size(15, 1));

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	ImagePreprocessor::FindContours(img, contours, hierarchy);

	// 텍스트 인식
	for (size_t i = 0; i < contours.size(); ++i) 
	{
		Rect rect = boundingRect(contours[i]);

		// 작은 영역 필터링
		if (rect.height < 10 || rect.width < 10) {
			continue;
		}

		// ROI 추출
		Mat roi = (*result->Get())(rect);

		// Tesseract에 이미지 설정
		_ocr->SetImage(roi.data, roi.cols, roi.rows, 3, roi.step);

		// 텍스트 인식 수행
		char* outText = _ocr->GetUTF8Text();
		cout << "인식된 텍스트: " << outText << endl;

		// 결과 표시
		rectangle(*result->Get(), rect, Scalar(0, 255, 0), 2);
		putText(*result->Get(), outText, Point(rect.x, rect.y - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);

		delete[] outText;  // 메모리 해제
	}

	Mat resized;
	resize(*result->Get(), resized, result->GetSize()); // 원하는 크기로 조정
	imshow("original", resized);
	waitKey(0);
}
