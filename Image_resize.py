'''
이미지 크기 조정하는 py
'''

import os
import cv2
import numpy as np
import tensorflow as tf

file_path='image/Train/WithMask'
file_names=os.listdir(file_path)
file_path2= 'TrainData/WithMask'
file_path3= 'image/Train/WithoutMask'
file_path4= 'TrainData/Without'
file_path5='CNNData/Orchid'
file_path6='TrainData/Orchid'
file_path7='CNNData/Sunflower'
file_path8='TrainData/Sunflower'
file_path9='CNNData/Tulip'
file_path10='TrainData/Tulip'
for name in os.listdir(file_path) :
    src = os.path.join(file_path, name)
    img =cv2.imread(src,cv2.IMREAD_COLOR)
    reimg=cv2.resize(img,(50,50),interpolation=cv2.INTER_LINEAR)
    cv2.imwrite(os.path.join(file_path2,name),reimg)

for name in os.listdir(file_path3):
    src = os.path.join(file_path3, name)
    img =cv2.imread(src,cv2.IMREAD_COLOR)
    reimg=cv2.resize(img,(50,50),interpolation=cv2.INTER_LINEAR)
    cv2.imwrite(os.path.join(file_path4,name),reimg)
