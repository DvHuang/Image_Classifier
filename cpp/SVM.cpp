#include <iostream>
#include <opencv/cv.h>
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
#include <string>


using namespace std;
using namespace cv;
using namespace cv::ml;



float evaluate(cv::Mat& predicted, cv::Mat& actual) {
	assert(predicted.rows == actual.rows);
	int t = 0;
	int f = 0;
	for(int i = 0; i < actual.rows; i++) {
		float p = predicted.at<float>(i,0);
		float a = actual.at<float>(i,0);
		if((p >= 0.0 && a >= 0.0) || (p <= 0.0 &&  a <= 0.0)) {
			t++;
		} else {
			f++;
		}
	}
	return 100*(t * 1.0) / (t + f);
}

void svm(vector <vector <double> > m,vector <double> a)
{

    int m_1d_len=m.size();
    int m_2d_len=m[0].size();
    int lable_len=a.size();

    if (m_1d_len !=lable_len) cout<<"data length error"<<endl;

    cout<<"lable length=sample number="<<lable_len<<endl;

    Mat M=Mat(m_1d_len,m_2d_len,CV_32FC1);
    for (int i=0;i<m_1d_len;i++){

        for (int j=0;j<m_2d_len;j++){
            M.at<float>(i,j)=m[i][j];
        }
    }

    //double a[6]={1,1,1,2,2,2};
    Mat feature_class=Mat(lable_len,1,CV_32SC1);
    for (int i=0;i<lable_len;i++){
        if (a[i]>1) feature_class.at<int>(i,0)=1;
        else feature_class.at<int>(i,0)=-1;

    }
    Mat trainingDataMat=M;
    Mat labelsMat=feature_class;

    // Train the SVM
    //! [init]
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));

    //! [train]
    svm->train(M, ROW_SAMPLE, feature_class);


    Mat predicted(feature_class.rows, 1, CV_32F);

	for(int i = 0; i < M.rows; i++) {
		Mat sample = M.row(i);
		predicted.at<float>(i, 0) = svm->predict(sample);
	}
    cout << "Accuracy_{SVM} = " << evaluate(predicted, feature_class) << "%"<<endl;
}
