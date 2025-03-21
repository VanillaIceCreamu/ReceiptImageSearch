#include "pch.h"

using namespace std;

int main()
{
	Mat original;
	original = imread(".\\Receipts\\123.png");
	if (original.empty()) {
		cerr << "이미지를 읽을 수 없습니다." << endl;
		return -1;
	}

	// 그레이스케일 변환
	Mat gray;
	cvtColor(original, gray, COLOR_BGR2GRAY);

	// Morphological Gradient 계산
	Mat gradient;
	Mat morphStructure = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	morphologyEx(gray, gradient, MORPH_GRADIENT, morphStructure);

	// 이진화
	Mat binary;
	threshold(gradient, binary, 0.0, 255.0, THRESH_BINARY | THRESH_OTSU);

	// 닫힘 연산
	Mat closed;
	morphStructure = getStructuringElement(MORPH_RECT, Size(15, 1));
	morphologyEx(binary, closed, MORPH_CLOSE, morphStructure);

	// 윤곽선 찾기
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(closed, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	// Tesseract 초기화
	tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI();
	if (ocr->Init(NULL, "kor")) {  // 한국어 설정 ("kor")
		cerr << "Tesseract 초기화 실패!" << endl;
		return -1;
	}

	// 텍스트 인식
	for (size_t i = 0; i < contours.size(); ++i) {
		Rect rect = boundingRect(contours[i]);

		// 작은 영역 필터링
		if (rect.height < 10 || rect.width < 10) {
			continue;
		}

		// ROI 추출
		Mat roi = original(rect);

		// Tesseract에 이미지 설정
		ocr->SetImage(roi.data, roi.cols, roi.rows, 3, roi.step);

		// 텍스트 인식 수행
		char* outText = ocr->GetUTF8Text();
		cout << "인식된 텍스트: " << outText << endl;

		// 결과 표시
		rectangle(original, rect, Scalar(0, 255, 0), 2);
		putText(original, outText, Point(rect.x, rect.y - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);

		delete[] outText;  // 메모리 해제
	}

	// Tesseract 종료 및 메모리 해제
	ocr->End();
	delete ocr;

	Mat resized;
	resize(original, resized, Size(988, 48)); // 원하는 크기로 조정
	imshow("original", resized);
	waitKey(0);

	return 0;
}