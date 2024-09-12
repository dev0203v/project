import os
os.environ["CUDA_VISIBLE_DEVICES"] = "-1"
import socket
import threading
import sys
from tensorflow import keras
import numpy as np
import json
import kbo_all_team_statiz as stat
import pymysql

# conn = pymysql.connect (host='10.10.21.111',user ='mina',password='1234',db='Kia_tigers',charset='utf8')



BUF_SIZE = 1000
IMG_BUF = 4000
MAX_CLNT = 256

first_model = None
champion_model = None

clnt_socks = []
mutx = threading.Lock()

def handle_clnt(clnt_sock):

    while True:
        try:
            msg = clnt_sock.recv(BUF_SIZE).decode()
            if not msg:
                break
            jsonstr = json.loads(msg)
            print(jsonstr)

            if jsonstr["protocol"] == "예측하기":
                send_rank(clnt_sock, jsonstr)
            elif jsonstr["protocol"] == "그래프보기":
                send_rank(clnt_sock, jsonstr)
            else:
                print(f"다른 키를 받음: {jsonstr}")
        except json.JSONDecodeError as e:
            print(f"JSON 디코드 에러: {e}")
            break

def load_data():
    file = open(stat.file_path)

    file.readline()

    data_2024 = []

    for line in file:
        splt = line.split(",")
        x = splt
        if splt[0] == 'KIA' and int(splt[1]) == 2024:
            data_2024.append(x)
            owar = float(splt[2].strip())  # 대체선수 대비 승리 기여도 (공격)
            dwar = float(splt[3].strip())  # 대체선수 대비 승리 기여도 (수비)
            war = float(splt[24].strip())  # 대체선수 대비 승리 기여도 (공격 + 수비)
            avg = float(splt[25].strip())  # 타율
            obp = float(splt[26].strip())  # 출루율
            slg = float(splt[27].strip())  # 장타율
            ops = float(splt[28].strip())  # OPS (출루율 + 장타율)
            r_epa = float(splt[29].strip())  # 우효 타석 당 득점
            wrc = float(splt[30].strip())  # 파크팩터 반영된 조정 득점 창출력
            # rank = splt[30].strip()  # 순위 우승만 나오는 버전임

            data = [owar, dwar, war, avg, obp, slg, ops, r_epa, wrc]

            insert_data(data)
            select_data()

    # print("data_2024 : ", data_2024)
    # print("data : ", data)

    return data

def insert_data(data):
    try:
        conn = pymysql.connect(host='10.10.21.111', user='mina', password='1234', db='Kia_tigers', charset='utf8')

        cur = conn.cursor()

        # sql = """
        # INSERT INTO Kia_stat (oWAR, dWAR, WAR, AVG, OBP, SLG, OPS, R_ePA, WRC, DATE)
        # VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, 'DEFAULT');
        # """

        sql = """
                INSERT INTO Kia_stat(oWAR, dWAR, WAR, AVG, OBP, SLG, OPS, R_ePA, WRC) 
                VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s);
                """

        # 파라미터를 사용하여 쿼리 실행
        # conn.cursor.execute(sql, (owar, dwar, war, avg, obp, slg, ops, r_epa, wrc))
        print("insert data : ", data)
        cur.execute(sql, data)

        # 변경사항 커밋
        conn.commit()

    except Exception as e:
        print(f"마리아DB 연결 에러 발생: {e}")
    finally:
        conn.close()

def select_data():
    try:
        conn = pymysql.connect(host='10.10.21.111', user='mina', password='1234', db='Kia_tigers', charset='utf8')
        cur = conn.cursor()
        sql = "SELECT * FROM Kia_stat"

        cur.execute(sql)
        result = cur.fetchall()
        # print(result)

        conn.commit()
        return result
    except Exception as e:
        print(f"마리아DB 연결 에러 발생: {e}")
    finally:
        conn.close()



def load_models():
    global first_model, champion_model
    model_path_1 = 'model/kbo_postseason_model.keras'
    model_path_2 = 'model/kbo_champion_model.keras'

    try:
        first_model = keras.models.load_model(model_path_1)
        print(f"첫 번째 모델 로드 성공: {model_path_1}")
    except Exception as e:
        print(f"첫 번째 모델 로드 중 에러 발생: {e}")
        first_model = None

    try:
        champion_model = keras.models.load_model(model_path_2)
        print(f"챔피언 모델 로드 성공: {model_path_2}")
    except Exception as e:
        print(f"챔피언 모델 로드 중 에러 발생: {e}")
        champion_model = None


def predict_kia_performance(json_input):
    global first_model, champion_model
    load_models()
    if first_model is None:
        print("첫 번째 모델이 로드되지 않았습니다.")

    try:
        input_data = load_data()
        # input_data = json.loads(json_input)["data"]
        if isinstance(input_data, str):
            input_data = [float(i) for i in input_data.split(',')]
        else:
            input_data = [float(i) for i in input_data]
        input_data = np.array(input_data, dtype=np.float32).reshape(1, -1)
    except Exception as e:
        print(f"데이터 파싱 중 에러 발생: {e}")

    # 모델의 입력 형식 확인
    try:
        print(f"입력 데이터 크기: {input_data.shape}")
        print(f"모델 입력 크기: {first_model.input_shape}")
    except Exception as e:
        print(f"입력 데이터 크기 확인 중 에러 발생: {e}")

    # 2024년 데이터 예측
    if input_data.size > 0:
        # 기아 타이거즈의 2024년 데이터로 예측
        try:
            first_Y_prediction_2024 = first_model.predict(input_data)
            first_prediction_class_2024 = np.argmax(first_Y_prediction_2024, axis=1)
        except Exception as e:
            print(f"첫 번째 모델 예측 중 에러 발생: {e}")

        label_map = {0: '우승', 1: '포스트시즌 진출', 2: '포스트시즌 미진출'}
        final_predictions_2024 = []

        for i in range(len(first_prediction_class_2024)):
            if first_prediction_class_2024[i] == 1:
                if champion_model and input_data.size > 1:
                    try:
                        champion_prediction_2024 = champion_model.predict(input_data[i].reshape(1, -1))
                        if np.argmax(champion_prediction_2024, axis=1) == 0:
                            final_predictions_2024.append('우승')
                        else:
                            final_predictions_2024.append('포스트시즌 진출')
                    except Exception as e:
                        final_predictions_2024.append(f"챔피언 모델 예측 중 에러 발생: {e}")
                else:
                    final_predictions_2024.append('포스트시즌 진출')
            else:
                final_predictions_2024.append(label_map[first_prediction_class_2024[i]])

        for i in range(len(final_predictions_2024)):
            print(f"2024년 기아 타이거즈의 예측 성적 : {final_predictions_2024[i]}")
            kia_rank = final_predictions_2024[i]

        return kia_rank
    else:
        return ["데이터가 유효하지 않습니다."]


def send_rank(clnt_sock, jsonstr):
    try:
        print("send_rank 함수 두둥등장")
        json_input = json.dumps(jsonstr)
        predictions = predict_kia_performance(json_input)
        response = {"predictions": predictions,"data":select_data()}
        # print(response)
        clnt_sock.send(json.dumps(response).encode())
    except Exception as e:
        print(f"예측 수행 중 에러 발생: {e}")
        response = {"protocol": "에러", "message": str(e)}
        clnt_sock.send(json.dumps(response).encode())


def send_data(clnt_sock, jsonstr):
    try:
        print("send_data 함수 두둥등장")
        json_input = json.dumps(jsonstr)
        predictions = predict_kia_performance(json_input)
        response = {"data":select_data()}
        # print(response)
        clnt_sock.send(json.dumps(response).encode())
    except Exception as e:
        print(f"예측 수행 중 에러 발생: {e}")
        response = {"protocol": "에러", "message": str(e)}
        clnt_sock.send(json.dumps(response).encode())


def main():
    global clnt_socks, mutx
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <port>")

    port = 5791
    serv_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serv_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serv_sock.bind(("", port))
    serv_sock.listen(5)
    print(f"서버 두둥등장")

    while True:
        clnt_sock, clnt_adr = serv_sock.accept()
        print(f"연결된 클라이언트 IP: {clnt_adr[0]}")
        mutx.acquire()
        clnt_socks.append(clnt_sock)
        mutx.release()
        threading.Thread(target=handle_clnt, args=(clnt_sock,)).start()

if __name__ == "__main__":
    main()
