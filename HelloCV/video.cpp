#include "opencv2/opencv.hpp"
#include "iostream"
#include "draw.h"
#include "video.h"
#include "data.h"

using namespace cv;
using namespace std;

struct matPoint {
	Mat img = imread("lena.jpg");
	Point ptOld;
};

void videoEditShow(VideoCapture cap) {
	checkCap(cap);
	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	double fps = cap.get(CAP_PROP_FPS);
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	int delay = cvRound(1000 / fps);
	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));
	checkWrt(outputVideo);

	int input;
	Mat frame, inversed, outFrame;
	matPoint userdata;
	FileStorage fs;
	namedWindow("frame");
	setMouseCallback("frame", onMouse, (void*)&userdata);
	int index = 0;
	while (true) {
		cap >> frame;
		input = waitKey(delay);
		if (frame.empty() || input == 27 || input == 'q')
			break;
		// reverse output
		if (input == 'i' || input == 'o') {
			inversed = ~frame;
			imshow("inversed", inversed);
			outputVideo << inversed;
		}
		// save
		if (input == 's' || input == 'w') {
			fs = initWrite();
			checkFile(fs);
			fs << "frame" << frame;
		}
		// read from new window
		if (input == 'r') {
			inversed = ~frame;
			imshow("inversed", inversed);
			outputVideo << inversed;
		}
		// show text
		if (input == 't') {
			outFrame = changeFrame(frame);
		}
		// default camera
		imshow("frame", frame);
		index++;
	}
	destroyAllWindows();
}

Mat changeFrame(Mat frame) {
	Mat newFrame = frame.clone();
	changeMat(newFrame);
	drawPolys(newFrame);
	return newFrame;
}

void checkCap(VideoCapture cap) {
	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}
}

void checkWrt(VideoWriter output) {
	if (!output.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}
}


void onMouse(int event, int x, int y, int flags, void* userdata) {
	matPoint* data = (matPoint*) userdata;
	Mat img = data->img;
	Point ptOld = data->ptOld;
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
