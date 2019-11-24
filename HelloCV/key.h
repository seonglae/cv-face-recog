#include "opencv2/opencv.hpp"
#include "iostream"

void timeLaps(cv::VideoCapture cap, cv::VideoWriter outputVideo, cv::Mat frame, int delay, int per);
void showSaveInverse(cv::VideoCapture cap, cv::VideoWriter outputVideo, cv::Mat frame, int delay);
void showStopMotion(cv::VideoCapture cap, int delay, int index);