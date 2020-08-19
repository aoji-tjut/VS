//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//Mat src, dst;
//Mat map_x, map_y;
//int index = 0;
//
//void update_map();
//
//int main()
//{
//	src = imread("image\\海绵宝宝.JPG");
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	//必须用CV_32FC1
//	map_x.create(src.size(), CV_32FC1);
//	map_y.create(src.size(), CV_32FC1);
//
//	while (1)
//	{
//		index = waitKey(500);
//		if (index == 27)
//		{
//			break;
//		}
//		update_map();
//		//              x映射  y映射  固定方法      默认边缘处理    边缘白色填充
//		remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_DEFAULT, Scalar(255, 255, 255));
//		imshow("dst", dst);
//	}
//
//	waitKey(0);
//	return 0;
//}
//
//void update_map()
//{
//	for (int row = 0; row < src.rows; row++)
//	{
//		for (int col = 0; col < src.cols; col++)
//		{
//			switch (index)
//			{
//			case 48://小键盘0	长宽缩小一半
//				if ((col>src.cols*0.25) && col<(src.cols*0.75) && //长度大于四分之一小于四分之三
//					(row>src.rows*0.25) && (row < src.rows*0.75))//宽度大于四分之一小于四分之三
//				{
//					map_x.at<float>(row, col) = 2 * (col - src.cols*0.25);//x方向映射
//					map_y.at<float>(row, col) = 2 * (row - src.rows*0.25);//y方向映射
//				}
//				else//其他像素设为0
//				{
//					map_x.at<float>(row, col) = 0;
//					map_y.at<float>(row, col) = 0;
//				}
//				break;
//			case 49://小键盘1	水平翻转
//				map_x.at<float>(row, col) = src.cols - col - 1;//n列为0~n-1
//				map_y.at<float>(row, col) = row;
//				break;
//			case 50://小键盘2	垂直翻转
//				map_x.at<float>(row, col) = col;
//				map_y.at<float>(row, col) = src.rows - row - 1;//n行为0~n-1
//				break;
//			case 51://小键盘3	水平垂直翻转
//				map_x.at<float>(row, col) = src.cols - col - 1;
//				map_y.at<float>(row, col) = src.rows - row - 1;
//				break;
//			default:
//				break;
//			}
//		}
//	}
//}