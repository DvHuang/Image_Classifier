# -*- coding: utf-8 -*-

#建立表头

def android_txt():
    f = open("vector2.txt")             # 返回文件对象
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
            if line_sp[1] not in feature_map:
                zero_count+=1

                feature_map[line_sp[1]]=zero_count
        line = f.readline()



    # print ("zero_count=",zero_count)
    f.close()
    return feature_map

def normal_txt(feature_map):
    # print("len feature_map=",len(feature_map))

    f = open("vector2.txt")
    fileWriteObj = open("output.txt", 'w')

    line = f.readline()
    x = ['99' for n in range(len(feature_map))]
    first_line="first_line"
    category=0

    if first_line==first_line:
        line=f.readline()
    while line:


        # print ("new line=",line)
        tag_zero=line.find("new zero")
        tag_new_x=line.find("新的位置")
        tag_at=line.find("@/")

        if tag_zero!=-1:
            category+=1

        if tag_new_x!=-1:

            if len(x):
                # print("category=",category)

                tmp = []
                for i in range(0,len(x)):
                    tmp.append(str(x[i])+",")
                tmp.append(str(category))
                tmp.append("\n")
                fileWriteObj.writelines(tmp)
            x = ['99' for n in range(len(feature_map))]

        if tag_at!=-1:

           line_sp=line.split('@/')
           linshi=line_sp[2]

           x[feature_map[line_sp[1]]]=linshi[:2]


        line = f.readline()



    print ("len 1x==",len(x))
    fileWriteObj.close()
    f.close()
    return




def addtwodimdict(thedict, key_a, key_b, val):
    if key_a in thedict:
        thedict[key_a].update({key_b: val})
    else:
        thedict.update({key_a:{key_b: val}})
