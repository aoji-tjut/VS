//#include<iostream>
//#include<opencv.hpp>
//#include<xfeatures2d.hpp>
//using namespace std;
//using namespace cv;
//using namespace cv::xfeatures2d;
//
//int main()
//{
//	Mat src = imread("image\\热气球.JPG");
//	resize(src, src, Size(64*5, 128*5));
//	Mat gray;
//	cvtColor(src, gray, CV_BGR2GRAY);
//	HOGDescriptor detector(Size(src.cols, src.rows), Size(16, 16), Size(8, 8), Size(8, 8), 9);
//	vector<float> descriptors;
//	vector<Point> locations;
//	detector.compute(gray, descriptors, Size(0, 0), Size(0, 0), locations);
//	cout << "向量descriptors=" << descriptors.size() << endl;
//	imshow("HOG特征点提取", gray);
//
//
//
//
//
//
//	waitKey(0);
//	return 0;
//}