#coding:utf-8
import cv
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from skimage import data,filter,segmentation,measure,morphology,color,io


#数据处理类，读取原始数据，建立feature_map,保存特征向量集合
class Data_processing:
    #基本属性
    original_data=''     #原始数据 文件路径
    TrainingSet=''      #训练集合==特征向量集合 文件路径
    out_feature_map=map
    #私有属性,私有属性在类外部无法直接进行访问
    __flag = 0
    #定义构造方法
    def __init__(self,ori,train,f):
        self.original_data=ori
        self.TrainingSet = train
        self.__flag = f

    def speak(self):
        print("class: %s\n directory: %s \n" %(self.__flag,self.original_data))

    #此函数用于前期训练数据使用，旨在得到feature_map
    def OriginalText_CreateFeatureMap (self):
        f = open(self.original_data)             # 返回文件对象
        line = f.readline()
        feature_map=dict()


        zero_count=-1
        tag=1
        while line:
            # print line,
            tag=line.find("@/")
            # print ("tag=",tag)
            if tag!=-1:
                # print "step into esle"
                line_sp=line.split('@/')
                # print ("list=",line_sp)
                if line_sp[0] not in feature_map: #当该属性不存在于feature_map 中时，加入该属性，及其在特征向量中的位置zero_count
                    zero_count+=1
                    feature_map[line_sp[0]]=zero_count
            line = f.readline()
        self.out_feature_map=feature_map


    def OriginalText_SaveFeatureList(self):
        # print("len feature_map=",len(feature_map))

        f = open(self.original_data, 'r+')
        fileWriteObj = open(self.TrainingSet, 'w+')

        line = f.readline()
        x = ['99' for n in range(len(self.out_feature_map))]
        first_line="first_line"
        category=0

        if first_line==first_line:
            line=f.readline()
            line=f.readline()
        while line:


            # print ("new line=",line)
            tag_zero=line.find("new catloge")
            tag_new_x=line.find("new object in last catloge")
            tag_at=line.find("@/")

            if tag_zero!=-1:   #判断是否是一个新类型
                category+=1

            if tag_new_x!=-1:  #判断是否是一个新对象
                if len(x):
                    # print("category=",category)
                    tmp = []
                    for i in range(0,len(x)):
                        tmp.append(str(x[i])+",")
                    tmp.append(str(category))
                    tmp.append("\n")
                    fileWriteObj.writelines(tmp)   #将上一个特征向量写入文件
                x = ['99' for n in range(len(self.out_feature_map))]

            if tag_at!=-1:
               line_sp=line.split('@/')

               x[self.out_feature_map[line_sp[0]]]=line_sp[1].rstrip()
               print "linshi[:1]:",line_sp[1].rstrip(),self.out_feature_map[line_sp[0]]


            line = f.readline()



        print ("len 1x==",len(x))
        fileWriteObj.close()
        f.close()
        return







