#ifndef IM_DATA_ML_H_INCLUDED
#define IM_DATA_ML_H_INCLUDED

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

//
using namespace cv;
using namespace std;

extern void Logistic_Train(vector <vector <double> > m,vector <double> a );
extern void Logistic_Predict(vector <vector <double> > m);
extern void svm(vector <vector <double> > m,vector <double> a );

class  Data_processing{

    private:

        string Original_data;   //original  filt path
        string Predict_data;
        string Vector_Set;     //vector  file path
        map <string,int> Out_feature_map;  //feature map

    public:

        vector <vector <double> > M_Two_vector;
        vector <vector <double> > P_Two_vector;
        vector <double> Lable_vector;

        Data_processing(string ori,string bete);//constructor
        void OriginalText_CreateFeatureMap();
        void OriginalText_SaveFeatureList();
        void PredictText_SaveFeatureList();

};






#endif // IM_DATA_ML_H_INCLUDED
