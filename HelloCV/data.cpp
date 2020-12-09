#include "opencv2/opencv.hpp"
#include "iostream"
#include "data.h"

using namespace cv;
using namespace std;

void checkFile(FileStorage fs) {
	if (!fs.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}
}

FileStorage initRead() {
	FileStorage fs(FILE_NAME, FileStorage::READ);
	checkFile(fs);
	cout << "Read init finished" << endl;
	return fs;
}

FileStorage initWrite() {
	FileStorage fs(FILE_NAME, FileStorage::WRITE);
	checkFile(fs);
	cout << "Write init finished" << endl;
	return fs;
}

FileStorage initMem() {
	FileStorage fs(FILE_NAME, FileStorage::WRITE | FileStorage::WRITE);
	checkFile(fs);
	cout << "Memory init finished" << endl;
	return fs;
}

FileStorage initApp() {
	FileStorage fs(FILE_NAME, FileStorage::APPEND);
	checkFile(fs);
	cout << "Append init finished" << endl;
	return fs;
}

int64 tick(String msg, int64 previous) {
	cout << msg << " cost : " << (getTickCount() - previous) / (getTickFrequency() / 1000) << "ms" << endl;
	return getTickCount();
}