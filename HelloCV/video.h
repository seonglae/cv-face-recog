#include "opencv2/opencv.hpp"

void videoEditShow(cv::VideoCapture cap);
void checkCap(cv::VideoCapture cap);
void checkWrt(cv::VideoWriter output);
cv::Mat changeFrame(cv::Mat frame);
void onMouse(int event, int x, int y, int flags, void* userdata);
cv::Mat Options(cv::Mat frame);
void bright(cv::Mat frame);
void contrast(cv::Mat frame);
void checkCascade(cv::Mat frame, cv::CascadeClassifier faceCascade);