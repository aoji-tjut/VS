#include<iostream>
#include<opencv.hpp>
#include<xfeatures2d.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

Mat src1, src2, dst;
const char* title = "SURF特征点匹配";
int angle = 0, max_angle = 360;//旋转角度
int scale = 10, max_scale = 20;//缩放大小
int value = 2500, max_value = 5000;//阈值特征点检测算子

void callback(int, void*);

int main()
{
	src1 = imread("image\\热气球.JPG");
	namedWindow(title);
	createTrackbar("value", title, &value, max_value, callback);
	createTrackbar("angle", title, &angle, max_angle, callback);
	createTrackbar("scale", title, &scale, max_scale, callback);
	callback(0, 0);

	waitKey(0);
	return 0;
}

void callback(int, void*)
{
	if (scale <= 1)//缩放比例不能为0
	{
		scale = 1;
	}
	//制作第二张图片
	Point center(src1.cols / 2, src1.rows / 2);
	//                           中心   角度  缩放
	Mat m = getRotationMatrix2D(center, angle, (scale / 10.0));//旋转方式
	int size = src1.rows > src1.cols ? src1.rows : src1.cols;
	//       原始图 输出图 旋转方式 输出大小
	warpAffine(src1, src2, m, Size(size, size));

	//检测特征点
	Ptr<SURF> detector = SURF::create(value);//检测器
	vector<KeyPoint> keypoints1, keypoints2;//特征点集合
	detector->detect(src1, keypoints1);
	detector->detect(src2, keypoints2);

	//计算特征向量
	Mat descriptors1, descriptors2;//特征向量
	detector->compute(src1, keypoints1, descriptors1);
	detector->compute(src2, keypoints2, descriptors2);

	//匹配
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");//匹配器
	vector<DMatch> matches;//向量匹配集合
	matcher->match(descriptors1, descriptors2, matches);

	//绘制
	drawMatches(src1, keypoints1, src2, keypoints2, matches, dst);
	imshow(title, dst);
}