#include "opencv2/opencv.hpp"

void videoEditShow(cv::VideoCapture cap);
void checkCap(cv::VideoCapture cap);
void checkWrt(cv::VideoWriter output);
cv::Mat changeFrame(cv::Mat frame);
void onMouse(int event, int x, int y, int flags, void* userdata);