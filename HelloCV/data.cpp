#include "opencv2/opencv.hpp"
#include "iostream"
#include "data.h"

#define FILE_NAME "data.json"

using namespace cv;
using namespace std;

void checkFile(FileStorage fs) {
	if (!fs.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}
}
Mat readData(int index) {
	Mat mat;
	FileStorage fs(FILE_NAME, FileStorage::READ);
	checkFile(fs);

	fs["name"] >> mat;
	return mat;
}

FileStorage initRead() {
	FileStorage fs(FILE_NAME, FileStorage::READ);
	checkFile(fs);
	return fs;
}

FileStorage initWrite() {
	FileStorage fs(FILE_NAME, FileStorage::WRITE);
	checkFile(fs);
	return fs;
}