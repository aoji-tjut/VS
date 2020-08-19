#include<opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("image\\board.JPG");
	if (src.empty())
	{
		cout << "���ܼ���ͼ��" << endl;
		return -1;
	}
	namedWindow("src", CV_WINDOW_AUTOSIZE);
	imshow("src", src);

	Mat blur,gray;
	GaussianBlur(src, blur, Size(9, 9), 0);
	cvtColor(blur, gray, CV_BGR2GRAY);
	
	Mat dst;
	src.copyTo(dst);

	vector<Vec3f> circles;//��ż�����Բʸ������
	//��ͼ Բ �̶����� 1ԭͼ ���Բ�ľ� canny����ֵ ��ֵ(ԲҪ��) ��С�뾶 ���뾶
	HoughCircles(gray, circles, HOUGH_GRADIENT, 1, 10, 200, 20, 10, 30);//���Բ

	//��ͼ
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));//Բ��
		int radius = cvRound(circles[i][2]);//�뾶
		//�Ѽ�����Բ��dst����ʾ����
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);//Բ
		circle(dst, center, 1, Scalar(0, 255, 0), 2, LINE_AA);//Բ��
	}
	imshow("dst", dst);



	waitKey(0);
	return 0;
}