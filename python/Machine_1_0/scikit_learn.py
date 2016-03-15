# -*- coding: utf-8 -*-
import numpy as np
import urllib
from sklearn import preprocessing
from sklearn import metrics
from sklearn.ensemble import ExtraTreesClassifier
from sklearn import metrics
from sklearn.linear_model import LogisticRegression




def extra_file(path,int_feature,int_category):


    # load the CSV file as a numpy matrix
    dataset = np.loadtxt(path, delimiter=",")
    # separate the data from the target attributes
    print ("dataset:",dataset)

    X = dataset[:,0:int_feature]
    Y = dataset[:,int_category]


    return X,Y

def normalize (X_feature,Y_category):
    # normalize the data attributes
    normalized_X = preprocessing.normalize(X_feature)
    # standardize the data attributes
    standardized_X = preprocessing.scale(X_feature)

    return  normalized_X,standardized_X

def feature_selection(X_feature,Y_category):

    model = ExtraTreesClassifier()
    model.fit(X_feature, Y_category)
    # display the relative importance of each attribute
    print(model.feature_importances_)


def logisticRegression(X_feature,Y_category):
    model = LogisticRegression()
    model.fit(X_feature,Y_category)
    print(model)
    # make predictions
    expected = Y_category
    predicted = model.predict(X_feature)
    # summarize the fit of the model
    print("predict=",predicted)
    print(metrics.classification_report(expected, predicted))
    print(metrics.confusion_matrix(expected, predicted))

    return model