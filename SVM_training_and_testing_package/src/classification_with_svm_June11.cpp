#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <fstream>

using namespace cv;
using namespace std;

#define NUMBER_OF_TRAINING_SAMPLES 59
#define ATTRIBUTES_PER_SAMPLE 2260		// 25 x 25 image
#define NUMBER_OF_TESTING_SAMPLES 36

int main()
{

//--------------------- 1. Set up test data from CSV file ----------------------------------

    string test_filename = "/home/latifanjum/fuerte_workspace/sandbox/SVM_training_and_testing_package/trainingTestingData/3Joints_Track/testData_June17/testData_June17.csv";
    //string test_filename = "/home/latifanjum/fuerte_workspace/sandbox/SVM_training_and_testing_package/trainingTestingData/3Joints_Track/testData_June17/testingData_June17.csv";
    //~ string train_filename = "/media/Data/Paper2/ML_data_Matlab/digits_train.csv";
    //~ string train_filename = "/media/Data/Paper_related/Training/FTA/training_data.csv";
    
    CvMLData test_data;
	
	test_data.read_csv(test_filename.c_str());	// read the csv file 
	test_data.set_response_idx(0);
	
	Mat rs1 = test_data.get_values();		// get pointer to read data
//	const CvMat* rs1 = train_data.get_values();
	
	/** define training data storage matrices (one for attribute examples, one
		for classifications) */

    Mat testingDataMat;// = Mat(NUMBER_OF_TESTING_SAMPLES, ATTRIBUTES_PER_SAMPLE, CV_32FC1);
    
	Mat temp = rs1(Range::all(), Range(1, ATTRIBUTES_PER_SAMPLE+1));
	//Mat temp = rs1(Range::all(), Range::all());	// Copy the data from pointer rs1 to matrix temp

    testingDataMat = temp.clone();	

	cout<<"Testing Data Rows:" << testingDataMat.rows << " and Columns: " << testingDataMat.cols << endl;
	/************************************************************************************/
	
// --------------Load pre-trained file (result file of training)--------------------	
	CvSVM svm;
	svm.load("trained_with_3JointsTrainingData_June19");
//-------------------------------------------------------------------
     

//--------- Using the Classifier------------------------

    ofstream x_file;
    x_file.open ("3Jclassification_June19.csv", ios::app);
    for (int i = 0; i < testingDataMat.rows; ++i)
    {
		Mat testing_data_row = testingDataMat.row(i);
		//Mat test_label = testing_labels.row(tsample);
		float response = svm.predict(testing_data_row);
		x_file << response;
		x_file << "\n";
		cout<<"Label for row " << i << " is: " << response << endl;
	}
	x_file.close();
	
    return 0;
}
