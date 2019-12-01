#include "opencv2/opencv.hpp"
#include "opencv2/core/ocl.hpp"
#include "video.h"
#include "draw.h"
#include "data.h"

#define CAMERA_NUM 0
#define MP4_NAME "atmos.mp4"
#define FACE_MP4 "faces.mp4"

using namespace cv;

int main() {
	// drawboard
	countT = tick("start", getTickCount());
	matPoint userdata;
	imshow("img", imread("lena.jpg"));
	setMouseCallback("img", onMouse, (void*)&userdata);
	countT = tick("drawboard", countT);

	VideoCapture cap(CAMERA_NUM);
	cap.set(CAP_PROP_FRAME_WIDTH, 600);
	cap.set(CAP_PROP_FRAME_HEIGHT, 400);
	VideoCapture mp4(FACE_MP4);
	checkCap(cap);
	countT = tick("init", countT);
	videoEditShow(mp4);
	return 0;
}