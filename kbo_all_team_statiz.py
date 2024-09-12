import requests
from bs4 import BeautifulSoup
import pandas as pd
import  numpy as np

# Statiz에서 데이터 크롤링
url = 'https://statiz.sporki.com/stats/?m=team&m2=batting&m3=default&so=s_year&ob=DESC&year=2024&sy=2024&ey=2024&te=&po=&lt=10100&reg=&pe=&ds=&de=&we=&hr=&ha=&ct=&st=&vp=&bo=&pt=&pp=&ii=&vc=&um=&oo=&rr=&sc=&bc=&ba=&li=&as=&ae=&pl=&gc=&lr=&pr=50&ph=&hs=&us=&na=&ls=&sf1=&sk1=&sv1=&sf2=&sk2=&sv2='
response = requests.get(url)
soup = BeautifulSoup(response.content, 'html.parser')

# 모든 테이블 찾기
tables = soup.find_all('table')

# 두 번째 테이블 선택
second_table = tables[1]

# print("table : ",second_table)

# 테이블 헤더 추출
headers = [header.text for header in second_table.find_all('th')]
headers.remove("정렬▼")
headers.remove("비율")
headers.remove("Year")
# headers.remove("Team")
headers.remove("Rank")
headers[headers.index("Year▼")] = "Year"

print("headers : ",headers)

rows = []
first_row = second_table.find_all('tr')[2]  # 첫 번째 데이터 행
cells = first_row.find_all('td')
if len(cells) > 0:
    row_data = [cell.text.strip() for cell in cells]
    row_data = [cell for i, cell in enumerate(row_data) if i not in (0, 2)]  # 첫 번째와 세 번째 열 삭제
    rows.append(row_data)



# # 테이블 데이터 추출
# rows = []
# for row in second_table.find_all('tr')[1:]:  # 첫 번째 행은 헤더이므로 제외
#     cells = row.find_all('td')
#     if len(cells) > 0 :
#         rows.append([cell.text.strip() for cell in cells])

# rows = np.delete(rows, 2 , axis = 1)
# rows = np.delete(rows, 0 , axis = 1)
print("rows : ",rows)

# 데이터프레임 생성
df = pd.DataFrame(rows, columns=headers)

# CSV 파일로 저장
file_path = 'data/kia_now_stat.csv'
df.to_csv('data/kia_now_stat.csv', index=False)
print("CSV 파일 저장 완료: statiz_all_team_stat.csv")

# file = open(file_path)
#
# file.readline()
#
# data_2024 = []
#
# for line in file:
#     splt = line.split(",")
#     x = splt
#     if splt[0] == 'KIA' and int(splt[1]) == 2024:
#        data_2024.append(x)
#        owar = float(splt[2].strip())  # 대체선수 대비 승리 기여도 (공격)
#        dwar = float(splt[3].strip())  # 대체선수 대비 승리 기여도 (수비)
#        war = float(splt[24].strip())  # 대체선수 대비 승리 기여도 (공격 + 수비)
#        avg = float(splt[25].strip())  # 타율
#        obp = float(splt[26].strip())  # 출루율
#        slg = float(splt[27].strip())  # 장타율
#        ops = float(splt[28].strip())  # OPS (출루율 + 장타율)
#        r_epa = float(splt[29].strip())  # 우효 타석 당 득점
#        wrc = float(splt[30].strip())  # 파크팩터 반영된 조정 득점 창출력
#        # rank = splt[30].strip()  # 순위 우승만 나오는 버전임
#
#        data = []
#        data.append(owar)
#        data.append(dwar)
#        data.append(war)
#        data.append(avg)
#        data.append(obp)
#        data.append(slg)
#        data.append(ops)
#        data.append(r_epa)
#        data.append(wrc)
#
# print("data_2024 : ",data_2024)
# print("data : ",data)