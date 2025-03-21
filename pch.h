#pragma once

#ifndef PCH_H
#define PCH_H
#endif //PCH_H

#include <iostream>

#include <memory>

#include <algorithm>
#include <list>
#include <Array>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <variant>
#include <windows.h>

#include <sys/timeb.h>

// openCV + Tesseract + laptonia
#include <opencv2/highgui.hpp>
#include <opencv2/text.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include "opencv2/core/utility.hpp"
using namespace cv;
using namespace cv::text;

#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>

#ifdef _DEBUG
#pragma comment(lib, "OpenCV/Debug/opencv_world4d.lib")
#pragma comment(lib, "leptonica/Debug/leptonica-1.85.0d.lib")
#pragma comment(lib, "tesseract/Debug/tesseract55d.lib")
#else
#pragma comment(lib, "OpenCV/Release/opencv_world4.lib")
#pragma comment(lib, "leptonica/Release/leptonica-1.85.0.lib")
#pragma comment(lib, "tesseract/Release/tesseract55.lib")
#endif
