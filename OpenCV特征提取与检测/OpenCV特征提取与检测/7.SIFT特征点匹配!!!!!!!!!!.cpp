//#include<iostream>
//#include<opencv.hpp>
//#include<xfeatures2d.hpp>
//using namespace std;
//using namespace cv;
//using namespace cv::xfeatures2d;
//
//Mat src1, src2, dst;
//const char* title = "SIFT特征点匹配";
//int value = 500, max_value = 5000;
//int angle = 0, max_angle = 360;
//int scale = 10, max_scale = 20;
//
//void callback(int, void*);
//
//int main()
//{
//	src1 = imread("image\\热气球.JPG");
//	namedWindow(title);
//	createTrackbar("value", title, &value, max_value, callback);
//	createTrackbar("angle", title, &angle, max_angle, callback);
//	createTrackbar("scale", title, &scale, max_scale, callback);
//	callback(0, 0);
//
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	if (scale <= 1)
//	{
//		scale = 1;
//	}
//	Point center(src1.cols / 2, src1.rows / 2);
//	Mat m = getRotationMatrix2D(center, angle, scale / 10.0);
//	int size = src1.rows > src1.cols ? src1.rows : src1.cols;
//	warpAffine(src1, src2, m, Size(size,size));
//
//	Ptr<SIFT> detector = SIFT::create(value);
//	vector<KeyPoint> keypoints1, keypoints2;
//	detector->detect(src1, keypoints1);
//	detector->detect(src2, keypoints2);
//
//	Mat descriptors1, descriptors2;
//	detector->compute(src1, keypoints1, descriptors1);
//	detector->compute(src2, keypoints2, descriptors2);
//
//	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
//	vector<DMatch> matches;
//	matcher->match(descriptors1, descriptors2, matches);
//
//	drawMatches(src1, keypoints1, src2, keypoints2, matches, dst);
//	imshow(title, dst);
//}