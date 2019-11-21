#include "opencv2/opencv.hpp"

#define FILE_NAME "data.json"

void checkFile(cv::FileStorage fs);
cv::FileStorage initRead();
cv::FileStorage initWrite();
cv::FileStorage initMem();