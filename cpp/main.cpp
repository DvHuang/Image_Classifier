#include <string>
#include "Im_Data_ML.h"


int main(int argc, char *argv[])
{
    //Train
    //!extra original data from this file
    string orifile="/home/samba/c++/davy/Ori_Feature.txt";
    //!Be tested file
    string Betestedfile="/home/samba/c++/davy/Ori_Feature.txt";


    //! get regulation data Dpro.M_Two_vector,Dpro.Lable_vector
    Data_processing Dpro(orifile,Betestedfile);
    Dpro.OriginalText_CreateFeatureMap();
    Dpro.OriginalText_SaveFeatureList();

    //!use the regulation data to train
    Logistic_Train(Dpro.M_Two_vector,Dpro.Lable_vector);
    svm(Dpro.M_Two_vector,Dpro.Lable_vector);


    //! under code use to debuger
    //    double m[6][2]={{1,2},{2,3},{1,3},{10,12},{12,14},{15,10}};

    // for (vector<double>::iterator it=Dpro.Lable_vector.begin(); it!=Dpro.Lable_vector.end(); ++it)
    //        cout <<*it<<' ';
    // for (vector<double>::iterator it=Dpro.M_Two_vector.begin(); it!=Dpro.M_Two_vector.end(); ++it)
    //        cout <<*it<<' ';
    // cout<<endl;


    //    double a[6]={1,1,1,2,2,2};
    //
    //    vector <vector<double> > M(6,vector<double>(2,1));
    //    vector <double> Lable(a,a+5);

    //!   Logistic_Predict
    //!   extra data from the file
    //    string orifile="/home/samba/c++/davy/Ori_Feature.txt";
    //    Data_processing Dpro(orifile);
    //    Dpro.OriginalText_CreateFeatureMap();
    //    Dpro.OriginalText_SaveFeatureList();
    Dpro.PredictText_SaveFeatureList();

    Logistic_Predict(Dpro.P_Two_vector);


}



