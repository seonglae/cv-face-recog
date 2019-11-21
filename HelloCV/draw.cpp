#include "opencv2/opencv.hpp"
#include "draw.h"
#include <vector>

using namespace std;
using namespace cv;

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
	putText(img, "SIMPLEX", Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 1, LINE_AA);
	putText(img, "PLAIN", Point(20, 100), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255), 1, LINE_AA);
	putText(img, "DUPLEX", Point(20, 150), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 1, LINE_AA);
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