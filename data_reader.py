import os
import cv2
import numpy as np
import random
from matplotlib import pyplot as plt
filepath=r'TrainData'
filepath2=r'CNNDataSet\bird'
trainairplanepath=r'CNNDataSet\trainairplane'
trainbirdpath=r'CNNDataSet\trainbrid'
# for name in os.listdir(filepath2):
class DataReader():
    def __init__(self):
        self.train_X ,self.train_Y,self.test_X,self.test_Y =self.dataImread()

    def dataImread(self):
        data=[]
        for i,f in enumerate(os.listdir(filepath)):
            z=os.path.join(filepath,f)
            for c in os.listdir(z):
                img = cv2.imread(os.path.join(z,c),cv2.IMREAD_COLOR)
                img=cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
                data.append((np.asarray(img),i))

        random.shuffle(data)
        train_X=[]
        train_Y=[]
        test_X=[]
        test_Y=[]
        for i in range(len(data)):
            if i < 0.8 * len(data):
                train_X.append(data[i][0])
                train_Y.append(data[i][1])
            else:
                test_X.append(data[i][0])
                test_Y.append(data[i][1])

        train_X = np.asarray(train_X) / 255.0
        train_Y = np.asarray(train_Y)
        test_X = np.asarray(test_X) / 255.0
        test_Y = np.asarray(test_Y)
        return train_X,train_Y,test_X,test_Y
def draw_graph(history):
    train_history = history.history["loss"]
    validation_history = history.history["val_loss"]
    fig = plt.figure(figsize=(8, 8))
    plt.title("Loss History")
    plt.xlabel("EPOCH")
    plt.ylabel("LOSS Function")
    plt.plot(train_history, "red")
    plt.plot(validation_history, 'blue')
    fig.savefig("train_history.png")

    train_history = history.history["accuracy"]
    validation_history = history.history["val_accuracy"]
    fig = plt.figure(figsize=(8, 8))
    plt.title("Accuracy History")
    plt.xlabel("EPOCH")
    plt.ylabel("Accuracy")
    plt.plot(train_history, "red")
    plt.plot(validation_history, 'blue')
    fig.savefig("accuracy_history.png")
    plt.show()