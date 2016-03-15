# -*- coding: utf-8 -*-
import os

from Image_P import IP_Simple_demo
from Machine_1_0 import extra_data_processing,scikit_learn
from Data_P import DP_Simple_demo
#原始特征文件

#训练集图片文件夹
#特征向量文件

def main():

    #0.读取训练集图片文件夹，保存原始特征。
    train_file="D:/D-python/picture_res"#图像文件夹路径
    Ori_Feature_txt="Ori_Feature.txt" #原始特征文件
    #写原始特征文件
    IP_Simple_demo.Image_OriginalData_Save(train_file,Ori_Feature_txt)


    #1.读取原始特征文件，习得判断模型
    #1.0  初始化数据处理类
    original_data_path=Ori_Feature_txt          #原始特征文件路径
    trainingSet_path="trainingSet.txt"        #特征向量文件路径
    dp_flag="dp_flag:"
    data_processing = DP_Simple_demo.Data_processing(original_data_path,trainingSet_path,dp_flag) #对象data_processing 获得待判断的特征向量集合 image_p.feature_list
    data_processing.speak()
    #1.1 读取原始特征文件，获得feature_map
    data_processing.OriginalText_CreateFeatureMap()

    #1.2 依据feature_map 将特征向量集合存入文件，即 建立特征向量训练集合。
    data_processing.OriginalText_SaveFeatureList()
    int_feature=len(data_processing.out_feature_map)
    #1.3 根据训练集进行学习，实际使用时，前面的过程可忽略
    TrainingSet=data_processing.TrainingSet
    X,Y= scikit_learn.extra_file(TrainingSet, int_feature, int_feature)
    print("1x=",X)
    #1.4 获得训练模型model
    model= scikit_learn.logisticRegression(X, Y)


    #2.   循环读取文件夹内图片，进行判断。。。。上线工程时，摄像头应该有sdk供读取图片

    rootDir="D:/D-python/picture_res"  #待判断文件夹路径
    for lists in os.listdir(rootDir):
        path_3 = os.path.join(rootDir, lists)
        print "第一个文件夹", path_3
        for lists in os.listdir(path_3):
            path_4 = os.path.join(path_3, lists)
            print "第一个文件夹", path_3
            #2.0  初始化图像处理类
            image_flag="image："+path_4 #自定义类标记
            list_feature=[]          #存放单个区域属性
            image_p = IP_Simple_demo.Image_P(path_4,list_feature,data_processing.out_feature_map,image_flag) #获得对象   获得待判断的特征向量集合 image_p.feature_list
            image_p.speak()
            #特征交接有两种处理方案， 1.直接返回一个特征向量集合，该方法需要将前面生成的feature_map 给图像处理函数Image_Processing使用，得以映射特征
            #                           2.结果存入文件，由程序重新读取排列特征，好处是可以服用前面的函数，这里采用第一种方法
            image_p.Image_Processing()
            #对当前image_p.feature_list进行判断
            i=0
            print "len type image_p.feature_list",len(image_p.feature_list)
            print "type image_p.feature_list",image_p.feature_list
            for current_feature_vectore in image_p.feature_list:
                i+=1
                print ("current_feature_vectore :",current_feature_vectore)
                preY = model.predict(current_feature_vectore)
                print ("图片--%s--的第 %d 个连通区域的类别是：%d\n" %(path_4,i,preY))


if __name__=="__main__":
    main()