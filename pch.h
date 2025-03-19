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
using namespace std;

// openCV + Tesseract + laptonia
#include <opencv2/highgui.hpp>
#include <opencv2/text.hpp>
#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>

using namespace cv;

#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else
#pragma comment(lib, "opencv_world470.lib")
#endif
