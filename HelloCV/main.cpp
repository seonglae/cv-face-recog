#include "opencv2/opencv.hpp"
#include "opencv2/core/ocl.hpp"
#include "video.h"

#define CAMERA_NUM 0
#define MP4_NAME "atmos.mp4"

using namespace cv;

int main() {
	// ocl::setUseOpenCL(true);
	VideoCapture cap(CAMERA_NUM);
	VideoCapture mp4(MP4_NAME);
	checkCap(cap);
	cap.set(CAP_PROP_FRAME_WIDTH, 100);
	cap.set(CAP_PROP_FRAME_WIDTH, 100);
	videoEditShow(cap);
	return 0;
}
