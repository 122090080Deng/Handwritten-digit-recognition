/*
* Name:Deng Yifan
* Student ID:122090080
* The final goal: Complete a handwritten digit Recognition with MINIST
* OpenCV Version:4.8.1
* Operation System:Windows 11
* Date:2023/12/10
* Purpose:start train function and use the train model to recognition the model
*
*/
//#include <iostream>
#include "mnist.h"
#include <opencv2/ml.hpp>
#include "train.h"

using namespace cv;
using namespace cv::ml;
using namespace std;
int main()
{
    //start train function
    train();

    //read a image
    //filename
    string filename = "";
    cout << "Please enter the filename of the image to be recognition:" << endl;//it is "xxx"not"xxx.jpg",you can choose one to enter
    cin >> filename;

    string filepath = "D:\\proj_122090080\\TestImage\\" + filename + ".png";
    Mat image = imread(filepath, 0);
    Mat img_show = image.clone();
    image.convertTo(image, CV_32F);
    image = image / 255.0;
    image = image.reshape(1, 1);


    //upload svm model
    Ptr<SVM> svm = StatModel::load<SVM>("svm.xml");
    //predict
    float pre = svm->predict(image);
    cout << pre << endl;

    cv::imshow("img", img_show);//show what the image is
    cv::waitKey(0);
    return 0;
   
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
