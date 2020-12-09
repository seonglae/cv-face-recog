#include "opencv2/opencv.hpp"

struct matPoint {
	cv::Mat img = cv::imread("lena.jpg");
	cv::Point ptOld;
};

void drawLines(cv::Mat img);
void drawPolys(cv::Mat img);
void drawText(cv::Mat img);
void centerText(cv::Mat img, cv::String text);
void changeMat(cv::Mat img);
cv::Mat mask_copyTo(cv::Mat dst);
cv::Mat mask_setTo(cv::Mat src);
void onMouse(int event, int x, int y, int flags, void* userdata);
void showHist(cv::Mat frame);
void histgoram_stretching(cv::Mat src);
void rounded_rectangle(cv::Mat& src, cv::Point topLeft, cv::Point bottomRight, const cv::Scalar lineColor, const int thickness, const int lineType, const int cornerRadius);