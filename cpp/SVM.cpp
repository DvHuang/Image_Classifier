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
//    CvSVMParams param = CvSVMParams();
//
//	param.svm_type = CvSVM::C_SVC;
//	param.kernel_type = CvSVM::RBF; //CvSVM::RBF, CvSVM::LINEAR ...
//	param.degree = 0; // for poly
//	param.gamma = 20; // for poly/rbf/sigmoid
//	param.coef0 = 0; // for poly/sigmoid
//
//	param.C = 7; // for CV_SVM_C_SVC, CV_SVM_EPS_SVR and CV_SVM_NU_SVR
//	param.nu = 0.0; // for CV_SVM_NU_SVC, CV_SVM_ONE_CLASS, and CV_SVM_NU_SVR
//	param.p = 0.0; // for CV_SVM_EPS_SVR
//
//	param.class_weights = NULL; // for CV_SVM_C_SVC
//	param.term_crit.type = CV_TERMCRIT_ITER +CV_TERMCRIT_EPS;
//	param.term_crit.max_iter = 1000;
//	param.term_crit.epsilon = 1e-6;

    //string name[5]={"LINEAR","POLY","RBF","SIGMOID","CHI2","INTER"}
    //we should use every kernel but there is too much time waste.



    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
//    svm->setGamma(0.01);
//    svm->setC(1);
//    svm->setP(5e-3);
//    svm->setDegree(2);
//    svm->setCoef0(2);
//    svm->setNu(2);

    //svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100000000000000, 1e-6));
    svm->setTermCriteria(TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 100000, 1e-6));
    //! [train]
    //svm->train(M, ROW_SAMPLE, feature_class);
    cv::Ptr<cv::ml::TrainData>     m_TrainData;
    m_TrainData =TrainData::create(M,ROW_SAMPLE,feature_class);
    //traindata->creat(M,feature_class);


    svm->trainAuto(m_TrainData,10,SVM::getDefaultGrid(SVM::C),
                        SVM::getDefaultGrid(SVM::GAMMA),
                        SVM::getDefaultGrid(SVM::P),
                        SVM::getDefaultGrid(SVM::NU),
                        SVM::getDefaultGrid(SVM::COEF),
                        SVM::getDefaultGrid(SVM::DEGREE),false);


//    SVM::Params param;
//    params.svmType=SVM::C_SVC;
//    params.kernelType=SVM::LINEAR;
//    //params.degree for poly
//    params.gamma=0.01;   //poly/rbf/sigmoid/chi2
//    //params.coef0 poly sigmoid
//    params.Cvalue=1;        //c_svc eps_svr nu_svr
//    //params.nu           //nu_svc  one_class  nu_svr
//    params.p=5e-3            //eps_svr
//    params.classWeights=
//    params.termCit=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 100000, 1e-6)
//
//
//
//    ParamGrid::CvParamGrid nuGrid=CvParamGrid(1,1,0);
//    ParamGrid::CvParamGrid coeffGrid=CvParamGrid(1,1,0);
//    ParamGrid::CvParamGrid degreeGrid=CvParamGrid(1,1,0);
//
//    Ptr<SVM> svm ;
//    svm.trainAuto(M, feature_class,NULL,NULL,params,10,
//    svm->getDefaultGrid(CvSVM::C),svm->getDefaultGrid(CvSVM::GAMA),
//    svm->getDefaultGrid(CvSVM::P),nuGrid,coeffGrid,degreeGrid);


    Mat predicted(feature_class.rows, 1, CV_32F);

	for(int i = 0; i < M.rows; i++) {
		Mat sample = M.row(i);
		predicted.at<float>(i, 0) = svm->predict(sample);
	}
    cout << "Accuracy_{SVM} = " << evaluate(predicted, feature_class) << "%"<<endl;
}
