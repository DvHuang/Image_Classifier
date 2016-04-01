#include <iostream>
#include <opencv/cv.h>
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/highgui.hpp>
#include <strstream>

using namespace std;
using namespace cv;
using namespace cv::ml;

static float calculateAccuracyPercent(const Mat &original, const Mat &predicted)
{
//    cout <<original<<endl;
//    cout<<predicted<<endl;
    return 100 * (float)countNonZero(original == predicted) / predicted.rows;
}

static float single_Precision_Recall(const Mat &original,const Mat &predicted,int class_flag)
{
    //calculate the one class's Original number
    int SGO_Number=0,SGP_Number=0,TP=0;
    for (int i=0;i<original.rows;i++){

        if (original.at<int>(i,0)==class_flag) SGO_Number+=1;
        cout<<"sgo_n"<<SGO_Number<<endl;

    }
    for (int i=0;i<predicted.rows;i++){

        if (predicted.at<int>(i,0)==class_flag) {
            if (original.at<int>(i,0)==class_flag) TP+=1;
            SGP_Number+=1;
        }
        cout<<"sgp_n"<<SGP_Number<<endl;
        cout<<"TP"<<TP<<endl;


    }

    float Precision,Recall,F1;
    Precision=TP/(TP+SGO_Number);
    Recall=TP/(TP+SGP_Number);

    cout<<"Precision"<<Precision<<endl;
    cout<<"Recall"<<Recall<<endl;
    F1=2*Precision*Recall/(Precision+Recall);

    return F1;



}

void  Logistic_Train(vector <vector <double> > m,vector <double> a )
{

    //double m[6][2]={{1,2},{2,3},{1,3},{10,12},{12,14},{15,10}};

    int m_1d_len=m.size();
    int m_2d_len=m[0].size();
    int lable_len=a.size();

    if (m_1d_len !=lable_len) cout<<"data length error"<<endl;

    cout<<"lable length=sample number="<<lable_len<<endl;

    Mat M=Mat(m_1d_len,m_2d_len,CV_32F);
    for (int i=0;i<m_1d_len;i++){

        for (int j=0;j<m_2d_len;j++){
            M.at<float>(i,j)=m[i][j];
        }
    }

    //
    //normalize the dataset,but through experimental verification ,
    //this operation has no help for the accuracy.
    //normalize(M,M,1.0,0.0,NORM_MINMAX);
    //cout<<"normalize"<<M;


    //double a[6]={1,1,1,2,2,2};
    Mat feature_class=Mat(lable_len,1,CV_32F);
    for (int i=0;i<lable_len;i++){

        feature_class.at<float>(i,0)=a[i];

    }

    cout << "training..."<<endl;
    //! [init]


    int rate_number=1;//-11 -10 -9 -8
    int iterations_number=1;  //10 100 1000 10000
    string mode_name_half="LR_Trained.xml";
    float accuracy_array[16] ;
    int accuracy_array_number=0;
    for (;rate_number<5;rate_number++){

        float learningRate=pow(10,-16+rate_number);

        for (;iterations_number<5;iterations_number++){

            int Iterations=pow(10,1+iterations_number);


            if (accuracy_array_number!=0){
            feature_class.convertTo(feature_class, CV_32F);
            }
            Ptr<LogisticRegression> lr1 = LogisticRegression::create();
            lr1->setLearningRate(learningRate);
            lr1->setIterations(Iterations);
            lr1->setRegularization(LogisticRegression::REG_L2);
            lr1->setTrainMethod(LogisticRegression::BATCH);
            lr1->setMiniBatchSize(1);
            //lr1->setTermCriteria(TermCriteria(TermCriteria::COUNT+TermCriteria::EPS,1000,0.01));
            //lr1->setTermCriteria(TermCriteria(TermCriteria::EPS,1,1000000000.0000000001));

            //! [init]
            //cout << feature_class.t() << endl;
            lr1->train(M, ROW_SAMPLE, feature_class);

            //cout << "done!" << endl;

            //cout << "predicting...";
            Mat responses;
            lr1->predict(M, responses);
            //cout << "done!" << endl;

            // show prediction report
            //cout << "original vs predicted:" << endl;
            feature_class.convertTo(feature_class, CV_32S);
            //cout << feature_class.t() << endl;
            //cout << responses.t() << endl;
            cout << "accuracy: " << calculateAccuracyPercent(feature_class, responses) << "%" << endl;

            accuracy_array[accuracy_array_number]=calculateAccuracyPercent(feature_class, responses) ;
            accuracy_array_number+=1;
            cout<<"rate_number:"<<rate_number<<endl;
            cout<<"iterations_number:"<<iterations_number<<endl;
            cout<<"accruacy_array number:"<<accuracy_array_number<<endl;





            strstream ss;
            string s;
            ss<<accuracy_array_number;
            ss>>s;
            string mode_name=s+mode_name_half;
            lr1->save(mode_name.c_str());


            //break;


            //!F1 undone~~~~
            //cout<<"F1 Score:"<<single_Precision_Recall(feature_class,responses,1)<<"%"<<endl;
            // save the classfier


//            const String saveFilename = "NewLR_Trained.xml";
//            cout << "saving the classifier to " << saveFilename << endl;
//            lr1->save(saveFilename);

            }
            iterations_number=1;

    }



//    Ptr<LogisticRegression> lr1 = LogisticRegression::create();
//    lr1->setLearningRate(learningRate);
//    lr1->setIterations(Iterations);
//    lr1->setRegularization(LogisticRegression::REG_L2);
//    lr1->setTrainMethod(LogisticRegression::BATCH);
//    //lr1->setMiniBatchSize(1);
//    //lr1->setTermCriteria(TermCriteria(TermCriteria::COUNT+TermCriteria::EPS,1000,0.01));
//    //lr1->setTermCriteria(TermCriteria(TermCriteria::EPS,1,1000000000.0000000001));
//
//    //! [init]
//    //cout << feature_class.t() << endl;
//    lr1->train(M, ROW_SAMPLE, feature_class);
//    cout << "done!" << endl;
//
//    cout << "predicting...";
//    Mat responses;
//    lr1->predict(M, responses);
//    cout << "done!" << endl;
//
//    // show prediction report
//    cout << "original vs predicted:" << endl;
//    feature_class.convertTo(feature_class, CV_32S);
//    cout << feature_class.t() << endl;
//    cout << responses.t() << endl;
//    cout << "accuracy: " << calculateAccuracyPercent(feature_class, responses) << "%" << endl;
//
//    //!F1 undone~~~~
//    //cout<<"F1 Score:"<<single_Precision_Recall(feature_class,responses,1)<<"%"<<endl;
//    // save the classfier
//    const String saveFilename = "NewLR_Trained.xml";
//    cout << "saving the classifier to " << saveFilename << endl;
//    lr1->save(saveFilename);

      //get max accuracy
        cout<<"accuracy_array"<<accuracy_array<<endl;
        int max_i=0;
        int location_number=1;
        for(max_i=0;max_i<sizeof(accuracy_array)/sizeof(accuracy_array[0]);max_i++){

            cout<<"[0]"<<accuracy_array[0]<<endl;

            cout<<"accuracy_array"<<"["<<max_i<<"]"<<accuracy_array[max_i]<<endl;

            if (accuracy_array[0]<accuracy_array[max_i]){
                accuracy_array[0]=accuracy_array[max_i];

                location_number=max_i;
                cout<<"[0]<"<<"["<<max_i<<"]"<<endl;
            }

        }
        cout<<"the location_number:"<<location_number<<endl;


        strstream ss_location;
        string s_location;
        ss_location<<location_number;
        ss_location>>s_location;

        //char* oldname=(s_location+mode_name_half).c_str();
        char* newname="NewLR_Trained.xml";
        cout<<"oldname="<<(s_location+mode_name_half).c_str()<<endl;
        cout<<"newname"<<newname<<endl;
        if (rename((s_location+mode_name_half).c_str(),newname)==0){
            cout<<"rename ok! "<<endl;
        }else{
            cout<<"rename failed!"<<endl;
        }



}

void  Logistic_Predict(vector <vector <double> > m )
{

    int m_1d_len=m.size();
    int m_2d_len=m[0].size();


    Mat M=Mat(m_1d_len,m_2d_len,CV_32F);
    for (int i=0;i<m_1d_len;i++){

        for (int j=0;j<m_2d_len;j++){
            M.at<float>(i,j)=m[i][j];
        }
    }

    //normalize
    normalize(M,M,1.0,0.0,NORM_MINMAX);
    //cout<<"normalize"<<M;

    // save the classfier
    const String saveFilename = "NewLR_Trained.xml";

    // load the classifier onto new object
    cout << "loading a new classifier from " << saveFilename << endl;
    Ptr<LogisticRegression> lr2 = StatModel::load<LogisticRegression>(saveFilename);

    // predict using loaded classifier
    cout << "predicting the dataset using the loaded classfier...";
    Mat responses2;
    lr2->predict(M, responses2);
    cout << "done!" << endl;

    cout << "predict:"<<responses2.t() << endl;


}
