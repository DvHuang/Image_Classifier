#coding:utf-8
import os

import cv
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from skimage import data,filter,segmentation,measure,morphology,color,io


#图像处理类，读取图片，分割，获得联通域属性
class Image_P:
    #基本属性
    directory = ''
    feature_list = []  #区域集合，每个元素区域的属性集合map
    out_feature_map=map
    #私有属性,私有属性在类外部无法直接进行访问
    __feature_vector = []    #单个区域的属性集合
    __flag = 0
    #定义构造方法
    def __init__(self,dir,fea_l,o_feature_map,fl):
        self.directory = dir
        self.feature_list = fea_l
        self.out_feature_map=o_feature_map
        self.__flag = fl

    def speak(self):
        print("class: %s\n directory: %s \n" %(self.__flag,self.directory))

    #图像处理方法
    def Image_Processing (self):

        image=io.imread(self.directory,as_grey=True)
        #image=io.imread('robot.jpg',as_grey=True)


        thresh =filter.threshold_otsu(image) #阈值分割
        print self.__flag+">阈值：" ,thresh

        bw =morphology.closing(image < thresh, morphology.square(3)) #闭运算

        cleared = bw.copy()  #复制
        segmentation.clear_border(cleared)  #清除与边界相连的目标物

        label_image =measure.label(cleared)  #连通区域标记
        borders = np.logical_xor(bw, cleared) #异或
        label_image[borders] = -1
        image_label_overlay =color.label2rgb(label_image, image=image) #不同标记用不同颜色显示

        fig,(ax0,ax1)= plt.subplots(1,2, figsize=(8, 6))
        ax0.imshow(cleared,plt.cm.gray)
        ax1.imshow(image_label_overlay)

        print  self.__flag+">区域个数：",len(measure.regionprops(label_image))
        for region in measure.regionprops(label_image): #循环得到每一个连通区域属性集

            #忽略小区域
            if region.area < 10:
                print "self.__feature_vector",self.__feature_vector
                continue
            else:
                del self.__feature_vector[:]
                print "外接边界:",region.bbox
                print "像 素 点:",region.area
                print "区域周长:",region.perimeter
                print "质心坐标:",region.centroid
                print "凸包内像素点总数:",region.convex_area
                #print "离心率:",region.Eccentricity
                print "区域面积和边界外接框面积的比率:",region.extent     #外接边界
                print "区域和外接框之间填充的像素点总数:",region.filled_area
                print "\n\n"

                if "像 素 点"  in self.out_feature_map:
                    self.__feature_vector.insert(self.out_feature_map["像 素 点"],region.area)
                if "区域周长"  in self.out_feature_map:
                    self.__feature_vector.insert(self.out_feature_map["区域周长"],region.perimeter)
                if "凸包内像素点总数"  in self.out_feature_map:
                    self.__feature_vector.insert(self.out_feature_map["凸包内像素点总数"],region.convex_area)
                if "区域面积和边界外接框面积的比率"  in self.out_feature_map:
                    self.__feature_vector.insert(self.out_feature_map["区域面积和边界外接框面积的比率"],region.extent)
                if "区域和外接框之间填充的像素点总数"  in self.out_feature_map:
                    self.__feature_vector.insert(self.out_feature_map["区域和外接框之间填充的像素点总数"],region.filled_area)
                print "self.__feature_vector",self.__feature_vector

                #特征向量的集合
                self.feature_list.append(self.__feature_vector)



            #绘制外包矩形
            minr, minc, maxr, maxc = region.bbox
            rect = mpatches.Rectangle((minc, minr), maxc - minc, maxr - minr,
                                      fill=False, edgecolor='red', linewidth=2)
            ax1.add_patch(rect)
        fig.tight_layout()
        plt.show()

#保存原始数据的方法
#paparameter：train_dic 原始图片路径，以文件夹名字作为类名字
def Image_OriginalData_Save (train_dic,Ori_Feature_txt):
    fileWriteObj = open(Ori_Feature_txt, 'w')
    #读取训练集图片

    # tag_zero=line.find("new catloge")
    # tag_new_x=line.find("new object in last catloge")
    # tag_at=line.find("@/")

    at="@/"
    for lists in os.listdir(train_dic):#获取文件夹列表名称，即类别名称列表lists
        path_0 = os.path.join(train_dic, lists)
        print "类别文件夹路径:",path_0
        fileWriteObj.write("new catloge\n")#每一个类别文件夹即新增一个类别
        for lists in os.listdir(path_0):
            path_1 = os.path.join(path_0, lists)
            print "图片文件路径：" ,path_1

            #读取图片
            image=io.imread(path_1,as_grey=True)
            #image=io.imread('robot.jpg',as_grey=True)

            #处理图片
            thresh =filter.threshold_otsu(image) #阈值分割
            print ">阈值：" ,thresh

            bw =morphology.closing(image < thresh, morphology.square(3)) #闭运算

            cleared = bw.copy()  #复制
            segmentation.clear_border(cleared)  #清除与边界相连的目标物

            label_image =measure.label(cleared)  #连通区域标记
            borders = np.logical_xor(bw, cleared) #异或
            label_image[borders] = -1
            image_label_overlay =color.label2rgb(label_image, image=image) #不同标记用不同颜色显示

            fig,(ax0,ax1)= plt.subplots(1,2, figsize=(8, 6))
            ax0.imshow(cleared,plt.cm.gray)
            ax1.imshow(image_label_overlay)

            #循环得到每一个连通区域属性集
            print  ">区域个数：",len(measure.regionprops(label_image))

            for region in measure.regionprops(label_image):
                #忽略小区域
                feature_list=list
                if region.area < 10:
                    continue
                else:
                    original_data=""
                    fileWriteObj.write("new object in last catloge\n")#每一个区域即为一个对象
                    #合成属性
                    # print "外接边界:",region.bbox
                    # print "像 素 点:",region.area
                    # print "区域周长:",region.perimeter
                    # print "质心坐标:",region.centroid
                    # print "凸包内像素点总数:",region.convex_area
                    # print "区域面积和边界外接框面积的比率:",region.extent     #外接边界
                    # print "区域和外接框之间填充的像素点总数:",region.filled_area
                    # print "\n\n"

                    # feature_list.append( "外接边界"+at+region.extent )
                    # feature_list.append( "像 素 点"+at+region.extent )
                    # feature_list.append( "区域周长"+at+region.extent )
                    # feature_list.append( "质心坐标"+at+region.extent )
                    # feature_list.append( "凸包内像素点总数"+at+region.extent )
                    # feature_list.append( "区域面积和边界外接框面积的比率"+at+region.extent )
                    # feature_list.append( "区域和外接框之间填充的像素点总数"+at+region.extent )
                    linshi=str(region.filled_area)
                    print type(linshi),"linshi:",linshi
                    original_data="像 素 点"+at+str(region.area)+"\n"\
                                  +"区域周长"+at+str(region.perimeter)+"\n"\
                                  +"凸包内像素点总数"+at+str(region.convex_area)+"\n"\
                                  +"区域面积和边界外接框面积的比率"+at+str(region.extent)+"\n"\
                                  +"区域和外接框之间填充的像素点总数"+at+str(region.filled_area)+"\n"
                    # original_data="外接边界"+at+linshi+"\n"\
                    #               +"像 素 点"+at+linshi+"\n"\
                    #               +"区域周长"+at+linshi+"\n"\
                    #               +"质心坐标"+at+linshi+"\n"\
                    #               +"区域和外接框之间填充的像素点总数"+at+str(region.extent)+"\n"
                    fileWriteObj.write(original_data)#每一个区域即为一个对象

            fig.tight_layout()
            #plt.show()
    fileWriteObj.close()







