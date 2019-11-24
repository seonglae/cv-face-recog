#include "opencv2/opencv.hpp"

#define FILE_NAME "data.json"

static int64 countT;

void checkFile(cv::FileStorage fs);
cv::FileStorage initRead();
cv::FileStorage initWrite();
cv::FileStorage initMem();
cv::FileStorage initApp();
cv::Mat showFrame(cv::VideoCapture cap);
int64 tick(cv::String msg, int64 previous);