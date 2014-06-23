#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

using namespace cv;
using namespace std;

#define NUMBER_OF_TRAINING_SAMPLES 25
#define ATTRIBUTES_PER_SAMPLE 2260		// 25 x 25 image
#define NUMBER_OF_TESTING_SAMPLES 36

int main()
{
   
// ------------ Data for visual representation ------------------

    //int width = 512, height = 512;
    //Mat image = Mat::zeros(height, width, CV_8UC3);

// --------- Set up training labels ------------------

    //float labels[59] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0};
    //Mat labelsMat(59, 1, CV_32FC1, labels);

//--------------------- 1. Set up training data from CSV file ----------------------------------

    string train_filename = "/home/latifanjum/fuerte_workspace/sandbox/SVM_training_and_testing_package/trainingTestingData/3Joints_Track/trainingData_June17/trainingData_June17.csv";
    //string train_filename = "/home/latifanjum/opencv/Activity_Recognition_Project/DataSet/June17/2Joints_Track /trainingData/2JointsTraining_June19.csv";
    //~ string train_filename = "/media/Data/Paper2/ML_data_Matlab/training_data3.csv";
    //~ string train_filename = "/media/Data/Paper2/ML_data_Matlab/digits_train.csv";
    //~ string train_filename = "/media/Data/Paper_related/Training/FTA/training_data.csv";
    
    CvMLData train_data;
	
	train_data.read_csv(train_filename.c_str());	// read the csv file 
	train_data.set_response_idx(0);
	
	Mat rs1 = train_data.get_values();		// get pointer to read data
//	const CvMat* rs1 = train_data.get_values();
	
	/** define training data storage matrices (one for attribute examples, one
		for classifications) */

    Mat trainingDataMat;// = Mat(NUMBER_OF_TRAINING_SAMPLES, ATTRIBUTES_PER_SAMPLE, CV_32FC1);
    Mat labelsDataMat ;//= Mat(NUMBER_OF_TRAINING_SAMPLES, 1, CV_32FC1);
    
	Mat temp = rs1(Range::all(), Range(0,1));	// put all first column elements in rs1 in tmp matrix
    labelsDataMat = temp.clone();	
    
    temp = rs1(Range::all(), Range(1, ATTRIBUTES_PER_SAMPLE+1));	// put all first column elements in rs1 in tmp matrix
    //temp = rs1(Range::all(), Range::all());	// put all first column elements in rs1 in tmp matrix
    trainingDataMat = temp.clone();	


	cout<<"Training Data Rows:" << trainingDataMat.rows << " and Columns: " << trainingDataMat.cols << endl;
	cout<<"Rows of labelsMat matrix: " << labelsDataMat.rows << endl << endl;
	/************************************************************************************/

//-------- Set up SVM's parameters---------------------------

    CvSVMParams params;
    params.svm_type    = CvSVM::C_SVC;
    params.kernel_type = CvSVM::LINEAR;
    params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);

//--------- Train the SVM--------------------------

    CvSVM SVM;
    cout<<"Starting the training of data " << endl;
    SVM.train(trainingDataMat, labelsDataMat, Mat(), Mat(), params);
    cout<<"Ending the training of data " << endl;
    SVM.save("trained_with_3JointsTrainingData_June19"); 
/*
//    Vec3b green(0,255,0), blue (255,0,0);

//--------- Show the decision regions given by the SVM------------------------
    for (int i = 0; i < image.rows; ++i)
        for (int j = 0; j < image.cols; ++j)
        {
            Mat sampleMat = (Mat_<float>(1,2) << j,i);
            float response = SVM.predict(sampleMat);

            if (response == 1)
                image.at<Vec3b>(i,j)  = green;
            else if (response == -1)
                 image.at<Vec3b>(i,j)  = blue;
        }

    // Show the training data
    int thickness = -1;
    int lineType = 8;
    circle( image, Point(501,  10), 5, Scalar(  0,   0,   0), thickness, lineType);
    circle( image, Point(255,  10), 5, Scalar(255, 255, 255), thickness, lineType);
    circle( image, Point(501, 255), 5, Scalar(255, 255, 255), thickness, lineType);
    circle( image, Point( 10, 501), 5, Scalar(255, 255, 255), thickness, lineType);

    // Show support vectors
    thickness = 2;
    lineType  = 8;
    int c     = SVM.get_support_vector_count();

    for (int i = 0; i < c; ++i)
    {
        const float* v = SVM.get_support_vector(i);
        circle( image,  Point( (int) v[0], (int) v[1]),   6,  Scalar(128, 128, 128), thickness, lineType);
    }

    imwrite("result.png", image);        // save the image

    imshow("SVM Simple Example", image); // show it to the user
    waitKey(0);
*/
    return 0;
}
