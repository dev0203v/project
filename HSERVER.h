#ifndef HSERVER_H_
#define HSERVER_H_


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <nlohmann/json.hpp>
#include <mariadb/conncpp.hpp>
#include <iostream>
#include <queue>
#include <ctime>
#include <random>
#include <mutex>
#include <vector>
#include"opencv2/opencv.hpp"

using json = nlohmann::json;

#define AND &&
#define OR ||

#define BUF_SIZE 1024
#define MAX_CLNT 256
#define IMG_BUF 4000
#define path "/home/lms/IMAGE/"

void handle_clnt(int clnt_sock);
void send_msg(char *msg, int len, int sock);
void error_handling(const std::string &msg);
std::string send_image_python(std::string, int);
void recv_image(int, std::string, long);

int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];
std::mutex mtx;

enum {Image_recieve = 10,SHOW_INFO, Python_connect};

class DATABASE
{
private:
    std::unique_ptr<sql::Connection> conn;
public:
    DATABASE();
    void Result_save(std::string,std::string);
    std::string Show_Info();
    int Recieve_image(std::string);
};

// 쿼리 결과를 저장할 구조체

DATABASE DB;

#endif