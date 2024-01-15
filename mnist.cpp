/*
* Name:Deng Yifan
* Student ID:122090080
* The final goal: Complete a handwritten digit Recognition with MINIST
* OpenCV Version:4.8.1
* Operation System:Windows 11
* Time:2023/12/7
* Purpose: This file is used to read the data of MNIST set. 
*/
#include "mnist.h"
#include <fstream>

using namespace cv;
using namespace std;

/*
* implement:Since the big-endian mode places the high-order bytes in the low-order of the memory,c1,c2,c3, 
* and c4 in turn represent the high-order bytes of the original number. 
*/
int Intreverse(int i){
	unsigned char c1, c2, c3, c4;

	c1 = i & 255;
	c2 = (i >> 8) & 255;//Shift right 8 bits
	c3 = (i >> 16) & 255;//Shift right 16 bits
	c4 = (i >> 24) & 255;//Shift right 24 bits
	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

/*
* implement:I learned about the parameters related to image data: magic number, number of images, width and height of the image.
* Now we want to get this data through the following function
*/

Mat read_mnist_image(const string filename){
	//the variable we should get
	int magic_num = 0;
	int num_of_image = 0;
	int row = 0;
	int col = 0;

	Mat DataMat;

	//get data
	ifstream file(filename, ios::binary);
	if (file.is_open()) {
		//read all data
		//magic number
		cout << "successfully open the training image set" << endl;
		file.read((char*)&magic_num, sizeof(magic_num));
		//num_of_image
		file.read((char*)&num_of_image, sizeof(num_of_image));
		//row
		file.read((char*)&row, sizeof(row));
		//col
		file.read((char*)&col, sizeof(col));

		//convert the mode to small-endian mode
		magic_num = Intreverse(magic_num);
		num_of_image = Intreverse(num_of_image);
		row = Intreverse(row);
		col = Intreverse(col);

		//show it(use for view and debug)
		cout << "Magic Number:" << magic_num << endl;
		cout << "The Number of Image:" << num_of_image << endl;
		cout << "The Number of row:" << row << endl;
		cout << "The Number of columns:" << col << endl;

		DataMat = Mat::zeros(num_of_image, row * col, CV_32FC1);//it is a matrix with num_of_image rows,row*col columns,and CV_32F1 type
		//note:CV_32FC1 is a format of opencv,32F means each pixel value is a 32-bit floating point number,
		//c1 means  each pixel has only one channel.
		//Maybe I am not fully understand it now.:)

		//input the data to Mat
		for (int i = 0; i < num_of_image; i++) {
			for (int j = 0; j < row * col; j++) {
				//prepare the data
				unsigned char a = 0;
				file.read((char*)&a, sizeof(a));
				float pixel_value = float(a);
				DataMat.at<float>(i, j) = pixel_value;
			}
		}

		//inform the reading completed
		cout << "We complete reading the image." << endl;


	}
	file.close();
	return DataMat;
}

/*
* implement:I learned about the parameters related to image data: magic number,number_of_items.
* Now we want to get this data through the following function,and it is similar to the function fo read the image
* Notice that the type is int 
*/
Mat read_mnist_label(const string filename) {
	//the variable we should get
	int magic_num = 0;
	int num_of_item = 0;

	Mat labelMat;
	ifstream file(filename, ios::binary);
	if (file.is_open()) {
		//read the data
		//magic number
		file.read((char*)&magic_num, sizeof(magic_num));
	    //the number of item
		file.read((char*)&num_of_item, sizeof(num_of_item));

		//change mode
		magic_num = Intreverse(magic_num);
		num_of_item = Intreverse(num_of_item);

		//show it and for better debug
		cout << "Magic Number:" << magic_num << endl;
		cout << "The Number of Item:" << num_of_item << endl;

		//input the data to Mat
		labelMat = Mat::zeros(num_of_item, 1, CV_32SC1);
		for (int i = 0; i < num_of_item; i++) {
			//for (int j = 0; j < 1; j++) {
				char b = 0;
				file.read((char*)&b, sizeof(b));
				int pixel_value = (int)b;
				labelMat.at<int>(i, 0) = pixel_value;
			//}
		}

		//show that we have complete it
		cout << "We complete reading the label." << endl;


	}
	file.close();
	return labelMat;



}

