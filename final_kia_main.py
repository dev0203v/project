"""
Author : Byunghyun Ban
Date : 2020.07.24.
"""
import matplotlib.pyplot as plt
from tensorflow import keras
import Kia_data_reader2 as dr
import numpy as np

# 몇 에포크 만큼 학습을 시킬 것인지 결정합니다.
EPOCHS = 50  # 예제 기본값은 20입니다.

# 데이터를 읽어옵니다.
data_reader = dr.Kia_DataReader()

# 1단계: "우승", "포스트시즌 진출", "포스트시즌 미진출" 모델 학습 및 저장
first_model = keras.Sequential([
    keras.layers.Dense(9),
    keras.layers.Dense(50, activation="relu"),
    keras.layers.Dense(10, activation="relu"),
    keras.layers.Dense(3, activation='softmax')  # 세 가지 클래스를 예측
])

first_model.compile(optimizer="adam",
                    loss="sparse_categorical_crossentropy",
                    metrics=["accuracy"])

print("************ 1단계 학습  ************")
early_stop = keras.callbacks.EarlyStopping(monitor='val_loss', patience=10)
first_history = first_model.fit(data_reader.train_X, data_reader.train_Y, epochs=EPOCHS,
                                validation_data=(data_reader.test_X, data_reader.test_Y),
                                callbacks=[early_stop])

first_model.save('model/kbo_postseason_model.keras')
dr.draw_graph(first_history)

# 2단계: 포스트시즌 진출 팀만 선택하여 "우승" 예측 모델 학습
postseason_indices = np.where(np.isin(data_reader.train_Y, [0, 1]))[0]
postseason_X = data_reader.train_X[postseason_indices]
postseason_Y = data_reader.train_Y[postseason_indices]

# 우승 여부를 예측할 두 번째 모델
champion_Y = np.where(postseason_Y == 0, 0, 1)

if len(postseason_X) > 1:  # 포스트시즌 진출 팀이 1팀 이상인 경우만 학습 진행
    champion_model = keras.Sequential([
        keras.layers.Input(shape=(postseason_X.shape[1],)),
        keras.layers.Dense(20, activation="relu"),
        keras.layers.Dense(10, activation="relu"),
        keras.layers.Dense(2, activation='softmax')  # 두 번째 모델의 출력 유닛 수는 2
    ])
    champion_model.compile(optimizer="adam",
                           loss="sparse_categorical_crossentropy",
                           metrics=["accuracy"])
    print()
    print("************ 2단계 학습  ************")
    # 두 번째 모델 학습
    early_stop = keras.callbacks.EarlyStopping(monitor='loss', patience=10)
    champion_history = champion_model.fit(postseason_X, champion_Y, epochs=EPOCHS,
                                          validation_split=0.2 if len(postseason_X) > 5 else 0.0,
                                          callbacks=[early_stop])

    champion_model.save('model/kbo_champion_model.keras')
    dr.draw_graph(champion_history)
