#include "opencv2/opencv.hpp"
#include "draw.h"
#include <vector>

using namespace std;
using namespace cv;

void onMouse(int event, int x, int y, int flags, void* userdata) {
	// mouse callback
	matPoint* data = (matPoint*)userdata;
	Mat img = data->img;
	Point ptOld = data->ptOld;
	// todo - draw line function refactoring
	switch (event) {
	case EVENT_LBUTTONDOWN:
		data->ptOld = Point(x, y);
		break;
	case EVENT_MOUSEMOVE:
		if (flags == EVENT_FLAG_LBUTTON) {
			line(img, ptOld, Point(x, y), Scalar(255, 255, 255), 2);
			imshow("img", img);
			data->ptOld = Point(x, y);
		}
		break;
	default:
		break;
	}
}

void drawLines(Mat img) {
	line(img, Point(250, 50), Point(350, 100), Scalar(0, 0, 255), 6, LINE_AA);
	arrowedLine(img, Point(50, 300), Point(350, 300), Scalar(255, 0, 0), 1, LINE_AA, 0, 0.05);
	drawMarker(img, Point(50, 350), Scalar(0, 0, 255), MARKER_CROSS, 20, 4, LINE_AA);
}

void drawPolys(Mat img) {
	rectangle(img, Rect(50, 50, 100, 50), Scalar(0, 0, 255), 2, LINE_AA, 0);
	circle(img, Point(300, 120), 30, Scalar(255, 0, 0), 10, LINE_AA);
	circle(img, Point(300, 120), 30, Scalar(255, 255, 0), -1, LINE_AA);

	ellipse(img, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(255, 255, 0), FILLED, LINE_AA);
	ellipse(img, Point(120, 300), Size(100, 50), 20, 0, 360, Scalar(0, 255, 0), 2, LINE_AA);

	vector<Point> pts;
	pts.push_back(Point(250, 250)); pts.push_back(Point(300, 250));
	pts.push_back(Point(300, 300)); pts.push_back(Point(350, 300));
	pts.push_back(Point(350, 350)); pts.push_back(Point(250, 350));
	polylines(img, pts, true, Scalar(255, 0, 255), 2);
}

void drawText(Mat img) {
	putText(img, "SIMPLEX BROWN HAIR", Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 1, LINE_AA);
	putText(img, "PLAIN ARE YOU DING WHAT IS HERE", Point(20, 100), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255), 1, LINE_AA);
	putText(img, "DUPLEX IS NEW FLEX STYLE", Point(20, 150), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 1, LINE_AA);
}

void centerText(Mat img, String text) {
	int fontFace = FONT_HERSHEY_DUPLEX;
	double fontScale = 2.0;
	int thickness = 1;
	Size sizeText = getTextSize(text, fontFace, fontScale, thickness, 0);
	Size sizeImg = img.size();
	Point org((sizeImg.width - sizeText.width) / 2, (sizeImg.height + sizeText.height) / 2);
	rectangle(img, org, org + Point(sizeText.width, -sizeText.height), Scalar(0, 10, 0), -1);
	putText(img, text, org, fontFace, fontScale, Scalar(255, 255, 255), thickness);
}


void changeMat(Mat img) {
	for (MatIterator_<Vec3b> it = img.begin<Vec3b>(); it != img.end<Vec3b>(); ++it) {
		(*it)[0] = (*it)[0] / 2 + 128; // B
		(*it)[1] = (*it)[1] / 2 + 100; // G
		(*it)[2] = (*it)[2] / 2 + 100; // R
	}
}

Mat mask_copyTo(Mat dst) {
	Size temp = dst.size();
	Mat src = imread("airplane.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);

	if (src.empty() || mask.empty() || dst.empty()) {
		cerr << "Image load failed!" << endl;
		return dst;
	}
	resize(src, src, temp, 0, 0, INTER_AREA);
	resize(mask, mask, temp, 0, 0, INTER_AREA);

	src.copyTo(dst, mask);
	return dst;
}

Mat mask_setTo(Mat src) {
	Size temp = src.size();
	Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);
	flip(mask, mask, 0);
	resize(mask, mask, temp, 0, 0, cv::INTER_AREA);

	if (src.empty() || mask.empty()) {
		cerr << "Image load failed!" << endl;
		return src;
	}
	src.setTo(Scalar(255, 255, 255), mask);
	return src;
}


void showHist(Mat frame) {
	int hbins = 255;
	int channels[] = { 0 }; //index of channel
	int histSize[] = { hbins };
	float hranges[] = { 0, 256 };
	const float* ranges[] = { hranges };

	MatND HistB, HistG, HistR;
	vector<Mat> bgr_planes;
	split(frame, bgr_planes);
	calcHist(&bgr_planes[0], 1, 0, Mat(), HistB, 1, histSize, ranges, true, false);
	calcHist(&bgr_planes[1], 1, 0, Mat(), HistG, 1, histSize, ranges, true, false);
	calcHist(&bgr_planes[2], 1, 0, Mat(), HistR, 1, histSize, ranges, true, false);

	normalize(HistB, HistB, 0, 255, NORM_MINMAX);
	normalize(HistG, HistG, 0, 255, NORM_MINMAX);
	normalize(HistR, HistR, 0, 255, NORM_MINMAX);

	// Draw the histograms for B, G and R
	int hist_w = 1020; int hist_h = 255;
	int ratio = cvRound((double)hist_w / hbins);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	int x1, y1;
	int x2, y2;
	for (int i = 1; i < hbins; i++)
	{
		x1 = ratio * (i - 1);
		y1 = hist_h - cvRound(HistB.at<float>(i - 1));
		x2 = ratio * (i);
		y2 = hist_h - cvRound(HistB.at<float>(i));

		//Blue
		line(histImage, Point(x1, y1), Point(x2, y2),
			CV_RGB(0, 0, 255), 2, LINE_AA, 0);

		//Green
		y1 = hist_h - cvRound(HistG.at<float>(i - 1));
		y2 = hist_h - cvRound(HistG.at<float>(i));
		line(histImage, Point(x1, y1), Point(x2, y2),
			CV_RGB(0, 255, 0), 2, LINE_AA, 0);

		//Red
		y1 = hist_h - cvRound(HistR.at<float>(i - 1));
		y2 = hist_h - cvRound(HistR.at<float>(i));
		line(histImage, Point(x1, y1), Point(x2, y2),
			CV_RGB(255, 0, 0), 2, LINE_AA, 0);
	}
	imshow("histogram", histImage);
}

void histgoram_stretching(Mat src) {
	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);
	src = (src - gmin) * 255 / (gmax - gmin);
}

void rounded_rectangle(Mat& src, Point topLeft, Point bottomRight, const Scalar lineColor, const int thickness, const int lineType, const int cornerRadius) {
	Point p1 = topLeft;
	Point p2 = Point(bottomRight.x, topLeft.y);
	Point p3 = bottomRight;
	Point p4 = Point(topLeft.x, bottomRight.y);
	line(src, Point(p1.x + cornerRadius, p1.y), Point(p2.x - cornerRadius, p2.y), lineColor, thickness, lineType);
	line(src, Point(p2.x, p2.y + cornerRadius), Point(p3.x, p3.y - cornerRadius), lineColor, thickness, lineType);
	line(src, Point(p4.x + cornerRadius, p4.y), Point(p3.x - cornerRadius, p3.y), lineColor, thickness, lineType);
	line(src, Point(p1.x, p1.y + cornerRadius), Point(p4.x, p4.y - cornerRadius), lineColor, thickness, lineType);
	ellipse(src, p1 + Point(cornerRadius, cornerRadius), Size(cornerRadius, cornerRadius), 180.0, 0, 90, lineColor, thickness, lineType);
	ellipse(src, p2 + Point(-cornerRadius, cornerRadius), Size(cornerRadius, cornerRadius), 270.0, 0, 90, lineColor, thickness, lineType);
	ellipse(src, p3 + Point(-cornerRadius, -cornerRadius), Size(cornerRadius, cornerRadius), 0.0, 0, 90, lineColor, thickness, lineType);
	ellipse(src, p4 + Point(cornerRadius, -cornerRadius), Size(cornerRadius, cornerRadius), 90.0, 0, 90, lineColor, thickness, lineType);
}