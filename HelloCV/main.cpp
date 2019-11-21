#include "opencv2/opencv.hpp"
#include "opencv2/core/ocl.hpp"
#include "video.h"

using namespace cv;

int main() {
	ocl::setUseOpenCL(true);
	VideoCapture cap(0);
	cap.set(CAP_PROP_FRAME_WIDTH, 1440);
	cap.set(CAP_PROP_FRAME_WIDTH, 1080);
	videoEditShow(cap);
	return 0;
}

