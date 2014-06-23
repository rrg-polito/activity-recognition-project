#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <stdio.h>
#include <fstream>

using namespace std;
#define PI 3.14159265

int main(int argc, char** argv){
	
	ros::init(argc, argv, "my_tf_listener");
	ros::NodeHandle node;
	tf::TransformListener listener;

	ros::Rate rate(10.0);

	vector<double> right_hand_x;
	vector<double> right_hand_y;
	vector<double> right_hand_z;

	vector<double> left_hand_x;
	vector<double> left_hand_y;
	vector<double> left_hand_z;

	vector<double> head_x;
	vector<double> head_y;
	vector<double> head_z;
  
    double right_x = 0;  
    double right_y = 0;
    double right_z = 0;

    double left_x = 0;  
    double left_y = 0;
    double left_z = 0;

    double head1_x = 0;  
    double head1_y = 0;
    double head1_z = 0;

	while (node.ok()){
		tf::StampedTransform transform1;
		tf::StampedTransform transform2;

		try{
			
// ---------- FOR THE RIGHT HAND ---------------------------------------------------------------
			
			listener.lookupTransform("/right_foot_1", "/right_hand_1", ros::Time(0), transform1);

			double right_x_tmp = transform1.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			double right_y_tmp = transform1.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			double right_z_tmp = transform1.getOrigin().z();
			
			// the difference between current and previous position 
			double right_x_diff = right_x_tmp - right_x;
			double right_y_diff = right_y_tmp - right_y;
			double right_z_diff = right_z_tmp - right_z;

			right_x = right_x_tmp;  
			right_y = right_y_tmp;
			right_z = right_z_tmp;

			//putting the values in vector to save

			right_hand_x.push_back(right_x_diff);
			right_hand_y.push_back(right_y_diff);
			right_hand_z.push_back(right_z_diff);
			
			cout <<"RIGHT HAND VALUE PUSHED INTO VECTOR" <<endl;

// --------------------- FOR THE LEFT HAND ------------------------------------------------------			
			
			listener.lookupTransform("/right_foot_1", "/head_1", ros::Time(0), transform2);
			
			double left_x_tmp = transform2.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			double left_y_tmp = transform2.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			double left_z_tmp = transform2.getOrigin().z();

			// the difference between current and previous position 
			double left_x_diff = left_x_tmp - left_x;
			double left_y_diff = left_y_tmp - left_y;
			double left_z_diff = left_z_tmp - left_z;

			left_x = left_x_tmp;  
			left_y = left_y_tmp;
			left_z = left_z_tmp;

//putting the values in vector to save

			left_hand_x.push_back(left_x_diff);
			left_hand_y.push_back(left_y_diff);
			left_hand_z.push_back(left_z_diff);

// --------------------- FOR THE HEAD ------------------------------------------------------			
			
			listener.lookupTransform("/right_foot_1", "/right_shoulder_1", ros::Time(0), transform2);
			
			double head_x_tmp = transform2.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			double head_y_tmp = transform2.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			double head_z_tmp = transform2.getOrigin().z();

			// the difference between current and previous position 
			double head_x_diff = head_x_tmp - head1_x;
			double head_y_diff = head_y_tmp - head1_y;
			double head_z_diff = head_z_tmp - head1_z;

			head1_x = head_x_tmp;  
			head1_y = head_y_tmp;
			head1_z = head_z_tmp;

//putting the values in vector to save

			head_x.push_back(head_x_diff);
			head_y.push_back(head_y_diff);
			head_z.push_back(head_z_diff);


			cout <<"LEFT HAND VALUE PUSHED INTO VECTOR" <<endl;
		}
		catch (tf::TransformException ex){
			ROS_ERROR("%s",ex.what());
		}
		rate.sleep();
	}
	
    cout <<"ITERATOR STARS NOW, PLEASE PAY ATTENTION"<<endl;
    ofstream x_file;
    vector<double>::iterator j = right_hand_y.begin();
    vector<double>::iterator k = right_hand_z.begin();
    vector<double>::iterator l = left_hand_x.begin();
    vector<double>::iterator m = left_hand_y.begin();
    vector<double>::iterator n = left_hand_z.begin();
    vector<double>::iterator o = head_x.begin();
    vector<double>::iterator p = head_y.begin();
    vector<double>::iterator q = head_z.begin();


    x_file.open ("ground_June16.csv", ios::app); //the flag ios::app makes sure that the control starts at the end of already existing file.
		x_file << 5;
		x_file << ",";


    for (vector<double>::iterator i = right_hand_x.begin(); i != right_hand_x.end();++i){
		//cout << *i << endl;
		x_file << *i;
		x_file << ",";
		
		x_file << *j;
		x_file << ",";
		j++;
		
		x_file << *k;
		x_file << ",";
		k++;
		
		x_file << *l;
		x_file << ",";
		l++;		
		
		x_file << *m;
		x_file << ",";
		m++;		
		
		x_file << *n;
		x_file << ",";
		n++;
				
		x_file << *o;
		x_file << ",";
		o++;				
		
		x_file << *p;
		x_file << ",";
		p++;				
		
		x_file << *q;
		x_file << ",";
		q++;				
				
    }
    x_file << 0;
    x_file << "\n";
/*    
    cout <<"Y VALUES TARTS NOW. KEEP IN MIND"<<endl;
    for (vector<double>::iterator i = right_hand_y.begin(); i != right_hand_y.end();++i){
		cout << *i << endl;
		x_file << *i;
		x_file << ",";
	}
    x_file << "\n";
    
    cout <<"Z VALUES TARTS NOW. KEEP IN MIND"<<endl;
    
    for (vector<double>::iterator i = right_hand_z.begin(); i != right_hand_z.end();++i){
		cout << *i << endl;
		x_file << *i;
		x_file << ",";
    }
    x_file << "\n";
     
*/
    x_file.close();

	return 0;
};
