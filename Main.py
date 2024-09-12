"""
Author : Byunghyun Ban
Date : 2020.07.24.
"""
from tensorflow import keras
import data_reader
# 몇 에포크 만큼 학습을 시킬 것인지 결정합니다.
EPOCHS = 5  # 예제 기본값은 20입니다.

# 데이터를 읽어옵니다.
dr=data_reader.DataReader()

# 인공신경망을 제작합니다.
model = keras.Sequential([
    keras.layers.Conv2D(64, (3, 3),padding='valid'),
    keras.layers.BatchNormalization(),
    keras.layers.ReLU(),
    keras.layers.MaxPooling2D((2, 2)),
    keras.layers.Dropout(rate=0.25),
    keras.layers.Conv2D(128, (3, 3),padding='valid'),
    keras.layers.BatchNormalization(),
    keras.layers.ReLU(),
    keras.layers.MaxPooling2D((2, 2)),
    keras.layers.Dropout(rate=0.25),
    keras.layers.Conv2D(128, (3, 3),padding='valid'),
    keras.layers.BatchNormalization(),
    keras.layers.ReLU(),
    keras.layers.Dropout(rate=0.5),
    keras.layers.Flatten(),
    keras.layers.Dense(128, activation='relu'),
    keras.layers.Dropout(rate=0.5),
    keras.layers.Dense(2, activation='softmax')
])


# 인공신경망을 컴파일합니다.
model.compile(optimizer='adam', metrics=['accuracy'],
              loss='sparse_categorical_crossentropy')
#sparse_categorical_crossentropy
# 인공신경망을 학습시킵니다.
print("\n\n************ TRAINING START ************ ")
early_stop = keras.callbacks.EarlyStopping(monitor='val_loss', patience=2)
history = model.fit(dr.train_X, dr.train_Y, epochs=EPOCHS,
                    validation_data=(dr.test_X, dr.test_Y),
                    callbacks=[early_stop])
# 학습 결과를 그래프로 출력합니다.
data_reader.draw_graph(history)
model.save('Model/Testmodel')