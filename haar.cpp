#include<opencv2/opencv.hpp>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;
using namespace cv;

void draw_locations(Mat & img, const vector< Rect > & locations, const Scalar & color);

int main(int argc, char** argv) {
	VideoCapture cap;
	Mat img, img_gray;
	CascadeClassifier car_filter;
	vector<Rect> vFound;

	car_filter.load("cars3.xml");
	cap.open("dirve2.mp4");

	while (cap.read(img)) {

		cvtColor(img, img_gray, COLOR_BGR2GRAY);
		equalizeHist(img_gray, img_gray);
		car_filter.detectMultiScale(img_gray, vFound, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

		draw_locations(img, vFound, Scalar(0, 255, 0));
		imshow("please", img);

		waitKey(30);
	}
	return 0;
}
void draw_locations(Mat & img, const vector< Rect > & locations, const Scalar & color) {

	if (!locations.empty()) {

		vector<Rect>::const_iterator loc = locations.begin();
		vector<Rect>::const_iterator end = locations.end();
		for (; loc != end; ++loc) {
			rectangle(img, *loc, color, 2);
		}
	}
}
