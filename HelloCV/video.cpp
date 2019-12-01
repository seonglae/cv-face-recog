#include "opencv2/opencv.hpp"
#include "iostream"
#include "draw.h"
#include "video.h"
#include "data.h"
#include "key.h"
#include "Windows.h"
#include <future>
#include <thread>

using namespace cv;
using namespace std;

static Mat frame, previous, motion, temp;
static int valueB, valueC;
static CascadeClassifier faceCascade;

void videoEditShow(VideoCapture cap) {
	// init writer
	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	cout << "width : " << w << " , heith : " << h << endl;
	double fps = cap.get(CAP_PROP_FPS);
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	int delay = cvRound(1000 / fps) / 2;
	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));
	checkWrt(outputVideo);

	// set fs writer
	int index = 0;
	FileStorage fsWrite = initWrite();
	bool clean = true;
	bool saved = false;
	
	// face

	String faceXML = "C:\\opencv\\sources\\data\\haarcascades_cuda\\haarcascade_frontalface_alt.xml";
	faceCascade.load(faceXML);

	// set temp variables
	Mat outFrame;
	while (true) {
		countT = tick("frame", countT);
		frame = showFrame(cap);

		if (frame.empty() || GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(0x51))
			break;
		waitKey(1);

		// write
		if (GetAsyncKeyState(0x57)) { // w
			fsWrite << "frame" + to_string(index) << frame;
			index++;
		}
		else if (GetAsyncKeyState(0x56)) {// v
			if (saved)
				continue;
			// todo - refactoring devide save and inverse
			showSaveInverse(cap, outputVideo, frame, delay);
			clean = false;
		}
		else if (GetAsyncKeyState(0x4C)) { // l
			// todo - start time laps until next press l
			timeLaps(cap, outputVideo, frame, delay, 10);
			clean = false;
		}
		// read from new window
		else if (GetAsyncKeyState(0x52)) {// r
			if (index == 0)
				continue;
			fsWrite.release();
			showStopMotion(cap, delay, index);
			fsWrite = initApp();
		}
		// video file
		else if (GetAsyncKeyState(0x55)) {// u - reset
			if (index == 0)
				continue;
			fsWrite.release();
			fsWrite = initWrite();
			index = 0;
		}
		else if (GetAsyncKeyState(0x58)) {// x - save(reset) and show
			destroyWindow("saving");
			saved = true;
			if (clean)
				continue;
			Mat resultFrame;
			if(outputVideo.isOpened())
				outputVideo.release();
			VideoCapture result("output.avi");
			while (true) {
				result >> resultFrame;
				if (resultFrame.empty())
					break;
				imshow("result", resultFrame);
				waitKey(1);
				if (frame.empty() || GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(0x51))
					break;
				frame = showFrame(cap);
			}
			result.release();
			destroyWindow("result");
		}
		else if (GetAsyncKeyState(0x59)) {// y
			saved = false;
			destroyWindow("saving");
			if (outputVideo.isOpened())
				outputVideo.~VideoWriter();
			outputVideo.open("output.avi", fourcc, fps, Size(w, h));
			checkWrt(outputVideo);
			clean = true;
		}
		previous = frame.clone();
	}
	// release and destroy windows
	outputVideo.release();
	fsWrite.release();
	destroyAllWindows();
}

Mat changeFrame(Mat frame) {
	//  return changed
	frame = mask_setTo(frame);
	frame = mask_copyTo(frame);
	return frame;
}


// open checker
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

Mat showFrame(VideoCapture cap) {
	Mat frame;
	cap >> frame;
	checkCascade(frame, faceCascade);
	return Options(frame);;
}

Mat Options(Mat frame) {
	// bright and contrast
	if (GetKeyState(0x42)) // b
		bright(frame);
	if (GetKeyState(0x43)) // c 
		contrast(frame);
	if (GetKeyState(0x46)) { // f
		medianBlur(frame, temp, 3);
		bilateralFilter(temp, frame, -1, 10, 5);
	}
	// change
	if (GetKeyState(0x5A)) // z
		frame = changeFrame(frame);
	if (GetKeyState(0x49)) // i
		frame = ~frame;
	if (GetKeyState(0x54)) // t
		drawText(frame);
	if (GetKeyState(0x4E)) // n
		normalize(frame, frame, 0, 255, NORM_MINMAX, CV_8UC3);
	if (GetKeyState(0x45)) { // e
		Mat ycrcb, ycrcbDst;
		vector<Mat> bgr_planes;
		cvtColor(frame, ycrcb, COLOR_BGR2YCrCb);
		split(ycrcb, bgr_planes);
		equalizeHist(bgr_planes[0], bgr_planes[0]);
		merge(bgr_planes, ycrcbDst);
		cvtColor(ycrcbDst, frame, COLOR_YCrCb2BGR);
	}
	if (GetKeyState(0x53)) { // s
		histgoram_stretching(frame);
	}
	if (GetKeyState(0x47)) { // G
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		cvtColor(frame, frame, COLOR_GRAY2BGR);
	}

	//data
	if (GetKeyState(0x48)) {// histogram
		showHist(frame);
	}
	else
		if (GetAsyncKeyState(0x48))
			destroyWindow("histogram");
	// show
	if (GetKeyState(0x44)) // difference
		imshow("camera", previous - frame);
	else 
		imshow("camera", frame);
	return frame;
}

void bright(Mat frame) {
	if (GetAsyncKeyState(0x42)) { // b
		createTrackbar("Brightness", "camera", &valueB, 200);
		setTrackbarPos("Brightness", "camera", 100);
	}
	frame = frame + Scalar((double)valueB - 100, (double)valueB - 100, (double)valueB - 100);
}

void contrast(Mat frame) {
	if (GetAsyncKeyState(0x43)) { // c
		createTrackbar("Contrast", "camera", &valueC, 100);
		setTrackbarPos("Contrast", "camera", 10);
	}
	frame = frame * ((float)valueC / 10);
}

void checkCascade(Mat frame, CascadeClassifier Cascade) {
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	Cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++) {
		Point bottomRight(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
		Point topLeft(faces[i].x, faces[i].y);
		rounded_rectangle(frame, topLeft, bottomRight, Scalar(222, 220, 220), 1, LINE_AA, 10);
	}
}