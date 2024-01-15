/*
* Name:Deng Yifan
* Student ID:122090080
* The final goal: Complete a handwritten digit Recognition with MINIST
* OpenCV Version:4.8.1
* Operation System:Windows 11
* Time:2023/12/7
* purpose: declare the function of deal with the MNIST dataset and train function
*/
#ifndef MNIST_H  
#define MNIST_H
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//for little endian storage conversion
int Intreverse(int i);

//for reading the information of image data set
Mat read_mnist_image(const string filename);

//for reading the information of label data set
Mat read_mnist_label(const string filename);


#endif