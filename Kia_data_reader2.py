import numpy as np
import random
from matplotlib import pyplot as plt

class Kia_DataReader():
    def __init__(self):
        self.train_X, self.train_Y, self.test_X, self.test_Y, self.data_2024_X = self.read_data()
        print("\n\nData Read Done!")
        print("Training X Size : " + str(self.train_X.shape))
        print("Training Y Size : " + str(self.train_Y.shape))
        print("Test X Size : " + str(self.test_X.shape))
        print("Test Y Size : " + str(self.test_Y.shape))
        print("2024 Data X Size : " + str(self.data_2024_X.shape) + '\n\n')

        # print("Training X  : " + str(self.train_X))
        # print("Training Y  : " + str(self.train_Y))
    def read_data(self):
        file = open("data/kbo_all_team_stat.csv")

        file.readline()

        data = []
        data_2024 = []

        for line in file:
            splt = line.split(",")
            x, cls = self.process_data(splt)
            if x is not None and cls is not None:
                data.append((x, cls))
                if splt[0] == 'KIA' and int(splt[1]) == 2024:
                    data_2024.append(x)

        random.shuffle(data)

        X = []
        Y = []

        for el in data:
            X.append(el[0])
            Y.append(el[1])

        X = np.asarray(X)
        Y = np.asarray(Y)

        # 2024년 기아 팀 데이터 확인 및 분리
        if len(data_2024) > 0:
            X_2024 = np.asarray([el[0:] for el in data_2024])
        else:
            X_2024 = np.array([])

        print("2024 KIA Data:", data_2024)
        print("X_2024:", X_2024)

        # 2024년 데이터를 제외한 나머지 데이터로 학습 및 테스트 데이터 분할
        X = np.asarray([el[0][0:] for el in data if el[0][1] != 2024 or el[0][0] != 'KIA'])
        Y = np.asarray([el[1] for el in data if el[0][1] != 2024 or el[0][0] != 'KIA'])

        train_X = X[:int(len(X) * 0.8)]
        train_Y = Y[:int(len(Y) * 0.8)]
        test_X = X[int(len(X) * 0.8):]
        test_Y = Y[int(len(Y) * 0.8):]

        return train_X, train_Y, test_X, test_Y, X_2024

    def process_data(self, splt):
        cls = 0

        team = splt[0]  # 팀 이름
        year = int(splt[1].strip())  # 연도
        owar = float(splt[2].strip())  # 대체선수 대비 승리 기여도 (공격)
        dwar = float(splt[3].strip())  # 대체선수 대비 승리 기여도 (수비)
        war = float(splt[24].strip())  # 대체선수 대비 승리 기여도 (공격 + 수비)
        avg = float(splt[25].strip())  # 타율
        obp = float(splt[26].strip())  # 출루율
        slg = float(splt[27].strip())  # 장타율
        ops = float(splt[28].strip())  # OPS (출루율 + 장타율)
        r_epa = float(splt[29].strip())  # 우효 타석 당 득점
        wrc = float(splt[30].strip())  # 파크팩터 반영된 조정 득점 창출력
        rank = splt[31].strip()  # 순위
        # rank = splt[30].strip()  # 순위 우승만 나오는 버전임

        data = []
        data.append(owar)
        data.append(dwar)
        data.append(war)
        data.append(avg)
        data.append(obp)
        data.append(slg)
        data.append(ops)
        data.append(r_epa)
        data.append(wrc)


        if rank.endswith("W"):
            cls = 0
        elif rank.endswith("P"):
            cls = 1
        elif rank.endswith("N"):
            cls = 2

        return data, cls

def draw_graph(history):
    train_history = history.history["loss"]
    validation_history = history.history["val_loss"]
    fig = plt.figure()
    plt.title("Loss History")
    plt.xlabel("EPOCH")
    plt.ylabel("LOSS Function")
    plt.plot(train_history, "red")
    plt.plot(validation_history, 'blue')
    fig.savefig("train_history.png")

    train_history = history.history["accuracy"]
    validation_history = history.history["val_accuracy"]
    fig = plt.figure()
    plt.title("Accuracy History")
    plt.xlabel("EPOCH")
    plt.ylabel("Accuracy")
    plt.plot(train_history, "red")
    plt.plot(validation_history, 'blue')
    fig.savefig("accuracy_history.png")
