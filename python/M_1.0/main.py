# -*- coding: utf-8 -*-
#
# 该工程有两个版本1.0，和 2.0 其中1.0中，我们直接使用人为标定的类型，来进行学习模型和分类
# 在2.0中，我们先对大量的数据进行聚类，然后将聚类后的数据在进行学习
import socket


def main():

    feature_map = extra_Data_processing.android_txt()
    print(feature_map)
    extra_Data_processing.normal_txt(feature_map)
    int_feature=len(feature_map)
    X,Y= scikit_learn.extra_file("output.txt", int_feature - 1, int_feature)
    print("1x=",X)
    model= scikit_learn.logisticRegression(X, Y)

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('', 8000))
    sock.listen(5)

    while True:
        connection,address = sock.accept()
        print("connected")
        try:
            connection.settimeout(50)
            while True:
                buf = connection.recv(1024)
                print ("receive =",buf)
                if buf != '':
                  x= server.normal_recv(feature_map, buf)
                  print ("normal recv done")
                  server.recv_txt(x)
                  print ("close txt")
                  preX,preY= scikit_learn.extra_file("output_pre.txt", int_feature - 1, int_feature)

                  preY = model.predict(preX)
                  print ("preY=",preY)
                  connection.send(str(preY[-1])+'\n')
                  print ("preY=",preY)

                # connection.send('a')
        except socket.timeout:
            print 'time out'
        connection.close()







if __name__=="__main__":
    main()