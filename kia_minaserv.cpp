#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include <pthread.h>
#include <netinet/tcp.h>
#include <unordered_map>
#include "opencv4/opencv2/opencv.hpp"
#include "json.hpp"
#include <mariadb/conncpp.hpp>
#define BUF_SIZE 1000
#define MAX_CLNT 256
#define IMG_BUF 4000

using json = nlohmann::json;
using namespace std;

void *handle_clnt(void *arg);
void error_handling(const char *msg);
void join(int clnt_sock, json jsonstr);
void login(int clnt_sock, json jsonstr);

int clnt_cnt = 0;         // 소켓 디스크립터의 인덱스 번호 역할
int clnt_socks[MAX_CLNT]; // 소켓 디스크립터 담을 256개
pthread_mutex_t mutx;     // 뮤텍스 변수

class DB
{
public:
    sql::Connection *conn;
    DB() {}
    void connect()
    {
        try
        {
            sql::Driver *driver = sql::mariadb::get_driver_instance();
            sql::SQLString url = ("jdbc:mariadb://10.10.21.111:3306/Kia_tigers");
            sql::Properties properties({{"user", "mina"}, {"password", "1234"}});
            conn = driver->connect(url, properties);
        }
        catch (sql::SQLException &e)
        {
            cerr << "Error Connecting to MariaDB Platform: " << e.what() << endl;
        }
    }

    ~DB() { delete conn; }
};

int main(int argc, char *argv[])
{
    signal(SIGPIPE, SIG_IGN);
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;
    pthread_t t_id;
    if (argc != 2)
    {
        cout << "Usage : " << argv[0] << "<port>\n";
        exit(1);
    }

    pthread_mutex_init(&mutx, NULL);
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    while (1)
    {
        clnt_adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);
        cout << "clnt_sock : " << clnt_sock << endl;

        pthread_mutex_lock(&mutx);
        clnt_socks[clnt_cnt++] = clnt_sock;
        pthread_mutex_unlock(&mutx);

        pthread_create(&t_id, NULL, handle_clnt, (void *)&clnt_sock);
        pthread_detach(t_id);
        cout << ("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr)) << endl;
    }
    close(serv_sock);
    return 0;
}

void *handle_clnt(void *arg)
{
    int clnt_sock = *((int *)arg);
    char msg[BUF_SIZE];
    json jsonstr;
    DB db;
    string jstring;
    db.connect();
    int len;
    memset(msg, 0, BUF_SIZE);
    while ((len = read(clnt_sock, msg, BUF_SIZE)) != 0)
    {
        try
        {
            msg[len] = 0;
            puts(msg);
            jstring = msg;
            jsonstr = nlohmann::json::parse(jstring);
            memset(msg, 0, BUF_SIZE);
        }
        catch (nlohmann::json::parse_error &e)
        {
            std::cerr << "JSON Parse Error: " << e.what() << std::endl;
            return NULL;
        }
        catch (const nlohmann::json::type_error &e)
        {
            cerr << "JSON Type Error: " << e.what() << endl;
        }

        cout << jsonstr << endl;

       
        if (jsonstr["protocol"] == "회원가입요청")
        {
            join(clnt_sock, jsonstr);
        }
        else if (jsonstr["protocol"] == "로그인요청")
        {
            login(clnt_sock, jsonstr);
        }
        else
        {
            cout << "다른 값을 넘겨 받음 : " << jsonstr << endl;
        }
    }
    return NULL;
}

void error_handling(const char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

void join(int clnt_sock, json jsonstr) // 회원가입 함수
{
    cout << "join 함수 두둥등장" << endl;
    string id;
    string pw;
    string name;
    json protocol_j;
    string protocol;
    json j;
    DB db;
    db.connect();

    try
    {
        j = jsonstr;

        id = j["id"];
        pw = j["pw"];
        name = j["name"];

        cout << "id : " << id << endl;
        cout << "pw : " << pw << endl;
        cout << "name : " << name << endl;

        unique_ptr<sql::PreparedStatement> stmnt(db.conn->prepareStatement("SELECT * FROM user WHERE id = ?"));
        stmnt->setString(1, id);
        sql::ResultSet *res = stmnt->executeQuery();

        if (res->next())
        {
            protocol_j["protocol"] = "중복된 아이디 입니다";
            protocol = protocol_j.dump();
        }
        else
        {
            protocol_j["protocol"] = "회원가입 완료";
            protocol = protocol_j.dump();

            unique_ptr<sql::PreparedStatement> stmnt(db.conn->prepareStatement("INSERT INTO user (user_no,id,pw,name)VALUES(DEFAULT,?,?,?)"));
            stmnt->setString(1, id);
            stmnt->setString(2, pw);
            stmnt->setString(3, name);
            stmnt->executeQuery();
        }

        cout << protocol_j["protocol"] << endl;
        write(clnt_sock, protocol.c_str(), strlen(protocol.c_str()));
    }
    catch (const nlohmann::json::type_error &e)
    {
        cerr << "JSON Type Error: " << e.what() << endl;
    }
    catch (nlohmann::json::parse_error &e)
    {
        std::cerr << "JSON Parse Error: " << e.what() << std::endl;
    }
    catch (sql::SQLException &e)
    {
        cerr << "Error Connecting to MariaDB Platform: " << e.what() << endl;
    }
}

void login(int clnt_sock, json jsonstr) // 로그인 함수
{
    cout << "login 함수 두둥등장" << endl;
    string id;
    string pw;
    json protocol_j;
    string protocol;
    json j;
    DB db;
    db.connect();

    try
    {
        j = jsonstr;

        id = j["id"];
        pw = j["pw"];

        cout << "id : " << id << endl;
        cout << "pw : " << pw << endl;

        unique_ptr<sql::PreparedStatement> stmnt(db.conn->prepareStatement("SELECT * FROM user WHERE id = ?"));
        stmnt->setString(1, id);
        sql::ResultSet *res = stmnt->executeQuery();

        if (res->next())
        {
            if (res->getString(3) == pw)
            {
                protocol_j["protocol"] = "로그인 완료";
                protocol = protocol_j.dump();
            }
            else
            {
                protocol_j["protocol"] = "회원정보가 일치하지 않습니다";
                protocol = protocol_j.dump();
            }
        }
        else
        {
            protocol_j["protocol"] = "회원정보가 일치하지 않습니다";
            protocol = protocol_j.dump();
        }

        cout << protocol_j["protocol"] << endl;
        write(clnt_sock, protocol.c_str(), strlen(protocol.c_str()));
    }
    catch (const nlohmann::json::type_error &e)
    {
        cerr << "JSON Type Error: " << e.what() << endl;
    }
    catch (nlohmann::json::parse_error &e)
    {
        std::cerr << "JSON Parse Error: " << e.what() << std::endl;
    }
    catch (sql::SQLException &e)
    {
        cerr << "Error Connecting to MariaDB Platform: " << e.what() << endl;
    }
}