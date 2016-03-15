#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;

//in the class we default the
//      strsplit =="@\"
//      new catlog="new catlog"
//      new point ==""new object in last catloge"

//of course you can set them yourself,at the same time ,you need write yoursel file
//in fact I recommed every one should use the default value of them,
//then we could do somenthing else  worthing to do.   --davyhuang.

std::vector<std::string> d_split(std::string str,std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str+=pattern;//扩展字符串以方便操作
    int size=str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}

template <class Type>
Type stringToNum(const string& str){

    istringstream iss(str);
    Type num;
    iss>>num;
    return num;

}

class  Data_processing{

    private:

        string Original_data;   //original  filt path
        string Predict_data;
        string Vector_Set;     //vector  file path
        map <string,int> Out_feature_map;  //feature map

    public:

        vector <   vector <double>  > M_Two_vector;
        vector <   vector <double>  > P_Two_vector;
        vector <double> Lable_vector;

        Data_processing(string ori,string bete);//constructor

        void OriginalText_CreateFeatureMap();
        void OriginalText_SaveFeatureList();
        void PredictText_SaveFeatureList();

};
Data_processing::Data_processing(string ori,string bete){

    cout << "Construct Data_Processing Object!!"<<endl;
    Original_data=ori;
    Predict_data=bete;
    //useful for other program
    Vector_Set="/home/samba/c++/davy/vector_set.dat";

}


//get feature_map
void Data_processing:: OriginalText_CreateFeatureMap(){

    //file related
    string buffer_line;
    ifstream outfile;
    outfile.open(Original_data.c_str(),ios::in);

    //find related

    vector<string> feature_name;
    int feature_Number=0;
    string split_flag="@/";

    //find   feature_name
    while (getline(outfile,buffer_line)){

        //cout<<buffer_line<<endl;

        vector<string> v = d_split(buffer_line, split_flag);

        //cout<<v.size()<<"v size"<<endl;

        //debug use;

//        for(vector<string>::size_type i = 0; i != v.size(); ++i)
//            cout << v[i] << " ";
//        cout << endl;


        if (v.size()>1){

            if (!Out_feature_map.count(v[0])){

                Out_feature_map[v[0]]=feature_Number;
                feature_Number+=1;

            }//if the feature not int the feature map
        }
    }
    outfile.close();
    //test my map;

    map <string,int>::iterator iter=Out_feature_map.begin(),iter_end=Out_feature_map.end();

    if (Out_feature_map.empty()){
        cout<<"Out_feature is empty"<<endl;
    }
    while (iter!=iter_end){
        cout<<"feature_map"<<(*iter).first<<" (";
        cout<<"number"<<(*iter).second<<")"<<endl;
        ++iter;


    }
}

void Data_processing::OriginalText_SaveFeatureList(){

    //read file init
    string buffer_line;
    ifstream outfile;
    outfile.open(Original_data.c_str(),ios::in);

    //write file init
    ofstream writefile;
    writefile.open(Vector_Set.c_str(),ios::out|ios::trunc);//tuunc delete the old file
    //the feature vector
    int len_feature_map;
    len_feature_map=Out_feature_map.size()+1;
    //string feature_vector[len_feature_map];
    double feature_vector[len_feature_map];

    int number_category=0;
    int M_Two_vector_Number=0;



    //str tag
    string::size_type zero_tag;
    string::size_type new_catlog_tag;
    string::size_type at_tag;
    int first_line_flag=1;

    string new_catlog="new catloge";
    string new_object="new object in last catloge";
    string str_split="@/";
    while (getline(outfile,buffer_line)){

        //cout<<buffer_line<<endl;

        zero_tag=buffer_line.find(new_catlog);
        new_catlog_tag=buffer_line.find(new_object);
        at_tag=buffer_line.find(str_split);


        if (zero_tag!=buffer_line.npos) {
            number_category+=1;
            continue;
        }
        if (new_catlog_tag!=buffer_line.npos & first_line_flag==0){//the last category's new object

            int i;
            string string_vector;
            for (i=0;i<len_feature_map;i++)
            {
                ostringstream strs;
                strs<<feature_vector[i];
                string_vector+=strs.str()+",";
            }

            //string_vector+=string_vector
            writefile<<string_vector<<'\n';
            //writefile<<"hello"<<'\n';
            vector <double> linshi(feature_vector,feature_vector+len_feature_map);

            M_Two_vector.push_back(linshi);
            Lable_vector.push_back(number_category);
//            cout<<"M_two_vector"<<M_Two_vector<<endl;
//            cout<<"Lable_vector"<<Lable_vector<<endl;
            //has read one object ,to zero
            string_vector="";
            M_Two_vector_Number+=1;
            //feature_vector=memset
        }
        if (at_tag!=buffer_line.npos){
            first_line_flag=0;

            vector<string> v = d_split(buffer_line, str_split); //可按多个字符来分隔;
            feature_vector[Out_feature_map[v[0]]]=stringToNum<double>(v[1]);
            //feature_vector[Out_feature_map[v[0]]]=v[1];
            //cout<<v[0]<<endl;

        }
    }

}

void Data_processing::PredictText_SaveFeatureList(){

    //read file init
    string buffer_line;
    ifstream outfile;
    outfile.open(Predict_data.c_str(),ios::in);

    //write file init
    ofstream writefile;
    writefile.open(Vector_Set.c_str(),ios::out|ios::trunc);//tuunc delete the old file
    //the feature vector
    int len_feature_map;
    len_feature_map=Out_feature_map.size()+1;
    //string feature_vector[len_feature_map];
    double feature_vector[len_feature_map];

    int number_category=0;
    int M_Two_vector_Number=0;



    //str tag
    string::size_type zero_tag;
    string::size_type new_catlog_tag;
    string::size_type at_tag;
    int first_line_flag=1;

    string new_catlog="new catloge";
    string new_object="new object in last catloge";
    string str_split="@/";
    while (getline(outfile,buffer_line)){

        //cout<<buffer_line<<endl;

        zero_tag=buffer_line.find(new_catlog);
        new_catlog_tag=buffer_line.find(new_object);
        at_tag=buffer_line.find(str_split);


        if (zero_tag!=buffer_line.npos) {
            number_category+=1;
            continue;
        }
        if (new_catlog_tag!=buffer_line.npos & first_line_flag==0){//the last category's new object

            int i;
            string string_vector;
            for (i=0;i<len_feature_map;i++)
            {
                ostringstream strs;
                strs<<feature_vector[i];
                string_vector+=strs.str()+",";
            }

            //string_vector+=string_vector
            writefile<<string_vector<<'\n';
            //writefile<<"hello"<<'\n';
            vector <double> linshi(feature_vector,feature_vector+len_feature_map);

            P_Two_vector.push_back(linshi);
            //Lable_vector.push_back(number_category);
//            cout<<"M_two_vector"<<M_Two_vector<<endl;
//            cout<<"Lable_vector"<<Lable_vector<<endl;
            //has read one object ,to zero
            string_vector="";
            M_Two_vector_Number+=1;
            //feature_vector=memset
        }
        if (at_tag!=buffer_line.npos){
            first_line_flag=0;

            vector<string> v = d_split(buffer_line, str_split); //可按多个字符来分隔;
            feature_vector[Out_feature_map[v[0]]]=stringToNum<double>(v[1]);
            //feature_vector[Out_feature_map[v[0]]]=v[1];
            //cout<<v[0]<<endl;

        }
    }

}
