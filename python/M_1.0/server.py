import socket

def server ():
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

                  connection.send('welcome to server!\n')

                # connection.send('a')
        except socket.timeout:
            print 'time out'
        connection.close()


def normal_recv(feature_map,str):
    # print("len feature_map=",len(feature_map))
    x = ['99' for n in range(len(feature_map))]
    split_str=str.split('#')
    # print ("next line =",split_str)

    for i in range(0, len(split_str)):


        line_sp=split_str[i].split('@/')
        if len(line_sp)>1:
            # print ("list str",line_sp[0],line_sp[1])
             if line_sp[0] in feature_map:
             # print ("feature_map[line_sp[0]]=",feature_map[line_sp[0]])
              x[feature_map[line_sp[0]]]=line_sp[1]
    print ("len 2x==",len(x))
    return x


def recv_txt(x):
    # print("len feature_map=",len(feature_map))

    fileWriteObj = open("output_pre.txt", 'w+')
    category=0
    print ("x====",x)
    tmp = []
    for i in range(0,len(x)):
        tmp.append(str(x[i])+",")
    tmp.append(str(category))
    tmp.append("\n")
    fileWriteObj.writelines(tmp+tmp)


    print ("len 1x==",len(x))
    fileWriteObj.close()
    return



