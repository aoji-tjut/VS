//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src, dst;
//	src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog.JPG");
//
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	
//	namedWindow("dog", CV_WINDOW_AUTOSIZE);
//	imshow("dog", src);
//
//	////掩膜操作：
//	//int cols = (src.cols - 1)*src.channels();//宽度
//	//int rows = src.rows;//高度
//	//int offsetx = src.channels();
//	//dst = Mat::zeros(src.size(), src.type());
//
//	//for (int row = 1; row < rows - 1; row++)
//	//{
//	//	const uchar* previous = src.ptr<uchar>(row - 1);
//	//	const uchar* current = src.ptr<uchar>(row);
//	//	const uchar* next = src.ptr<uchar>(row + 1);
//	//	uchar* output = dst.ptr<uchar>(row);
//	//	for (int col = offsetx; col < cols; col++)
//	//	{
//	//		output[col] = saturate_cast<uchar>(5 * current[col] - (current[col - offsetx] + 
//	//			current[col + offsetx] + previous[col] + next[col]));//saturate_cast<uchar>()处理像素的API
//	//	}
//	//}
//
//	int64 t1, t2;
//	t1 = getTickCount();
//
//	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);	//掩膜矩阵		|0  -1  0 |
//	filter2D(src, dst, src.depth(), kernel);//加强对比度	   			//				|-1  5  -1|
//																		//				|0  -1  0 |
//	t2 = getTickCount();
//	cout << "执行时间：" << (t2 - t1) / getTickFrequency() << endl;
//	
//	namedWindow("dog_new", CV_WINDOW_AUTOSIZE);
//	imshow("dog_new", dst);
//
//	waitKey(0);
//	return 0;
//}