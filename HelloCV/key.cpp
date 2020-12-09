#include "opencv2/opencv.hpp"
#include "iostream"
#include "key.h"
#include "data.h"
#include "video.h"
#include "Windows.h"

using namespace cv;
using namespace std;

void timeLaps(VideoCapture cap, VideoWriter outputVideo, Mat frame, int delay, int per) {
	int count = 0;
	while (GetKeyState(0x4C)) {
		if (frame.empty() || GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(0x51))
			break;
		if (per == count) {
			imshow("saving", frame);
			outputVideo << frame;
			count = 0;
		}
		else
			count++;
		waitKey(1);
		frame = showFrame(cap);
	}
}

void showSaveInverse(VideoCapture cap, VideoWriter outputVideo, Mat frame, int delay) {
	while (GetKeyState(0x56)) {
		if (frame.empty() || GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(0x51))
			break;
		imshow("saving", frame);
		outputVideo << frame;
		waitKey(1);
		frame = showFrame(cap);
	}
}

void showStopMotion(VideoCapture cap, int delay, int index) {
	Mat read, frame;
	int redex = 0;
	cerr << index << endl;
	FileStorage fs = initRead();
	while (redex < index) {
		if (frame.empty() || GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(0x51))
			break;
		countT = tick(to_string(redex), countT);
		fs["frame" + to_string(redex)] >> read;
		imshow("read", read);
		frame = showFrame(cap);
		waitKey(1);
		redex++;
	}
	fs.release();
	destroyWindow("read");
}
