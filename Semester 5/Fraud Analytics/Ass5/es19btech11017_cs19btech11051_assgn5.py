# -*- coding: utf-8 -*-
"""ES19BTECH11017_CS19BTECH11051_Assgn5.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/130SdNRUNGYI-iH6KUIvJcsWZAiJqit5h
"""

import numpy as np
import pandas as pd 
import warnings
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.metrics import precision_score
from sklearn.metrics import recall_score
from sklearn.metrics import mean_squared_error

def sigmoid(x):
    return 1.0/(1 + np.exp(-1*x))

def lossFunction(y, y_predicted):
    C_tp = 0.5
    C_tn = 0.5
    C_fn = 10
    C_fp = 10
    loss = np.mean(y*((np.log(y_predicted)*C_tp) + ((1 - np.log(y_predicted))*C_fn)) + (1 - y)*((np.log(1 - y_predicted)*C_tn) +(np.log(y_predicted)*C_fp)))

    loss = -1*loss
    return loss


def predict(X, w, b):
    return sigmoid(np.dot(X, w) + b)  


def gradients(X, y, y_predicted):
    Y = np.zeros((y.shape[0], 1))
    
    for i in range(y.shape[0]):
      Y[i][0] = y_predicted[i] - y[i]

    dw = np.dot(X.T, Y)
    db = np.sum((y_predicted - y)) 
    return dw, db


def weightInitialization(n_features):
    w = np.full((n_features, 1), 0.5)
    b = 0
    return w,b


def train(X, y, w, b, epochs = 1000, gamma = 0.1, minLoss = 0.001):
    
    y_predicted = predict(X, w, b)
    loss = lossFunction(y, y_predicted)

    for i in range(epochs):
      dw, db = gradients(X, y, y_predicted)
      w = w - gamma*dw
      b = b - gamma*db
      y_predicted = predict(X, w, b)
      prevLoss = loss
      loss = lossFunction(y, y_predicted)

      if(prevLoss - loss < minLoss):
        break

    return w, b


def classify(X, w, b):
    y_predicted = predict(X, w, b)
    prediction = []
    prediction = [1 if i > 0.5 else 0 for i in y_predicted]
    return np.array(prediction)

df = pd.read_csv("data.csv")

#x: features of the data
#y: labels of the data

y = df.iloc[:, 0]
y = y.to_numpy()

x = df.drop(['Status'], axis = 1)
x = x.to_numpy()

#Splitting the given dataset to check how the model performs

X_train, X_test, y_train, y_test = train_test_split(x[:1000], y[:1000], test_size=0.33, random_state=1)
w, b = weightInitialization(X_train.shape[1])
warnings.filterwarnings("ignore")
w_final, b_final = train(X_train, y_train, w, b, epochs = 1000, gamma = 0.1, minLoss = 0.0001)


#Predicting the status for the test cases
predictions = classify(X_test, w_final, b_final)


#Evaluating the performance of the Cost Sensitive Logistic Regression Model
accuracy = accuracy_score(y_test, predictions)
precision = precision_score(y_test, predictions, average=None)[1]
recall = recall_score(y_test, predictions, average=None)[1]

print("Test Set Accuracy: ", accuracy)
print("Test Set Precision: ", precision)
print("Test Set Recall: ", recall)