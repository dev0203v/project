#include <iostream>
#include "HSERVER.h"
#include "Query.cpp"

int python_sock = 0;

void handle_clnt(int clnt_sock)
{
    char msg[1024];
    std::string temp;
    std::string result;
    int str_len = 0;
    int return_value = 0;
    json new_json;
    std::string json_String;

    str_len = read(clnt_sock, msg, sizeof(msg));
    std::cout << "여기\n"
              << std::endl;
    std::cout << "msg: " << msg << std::endl;
    if (str_len <= 0)
    {
        std::cout << "오류" << std::endl;
        return;
    }

    json data_sorting = json::parse(msg, msg + str_len);
    memset(msg, 0, str_len);
    std::cout << "여기2\n";
    std::cout << data_sorting["Select"].get<int>() << std::endl;

    switch (data_sorting["Select"].get<int>())
    {
    case Image_recieve:
    {
        std::cout << "이미지 받음\n";
        std::string file_name = data_sorting["M_NAME"].get<std::string>();
        return_value = DB.Recieve_image(file_name);
        if (return_value)
            std::cout << "저장 잘됨\n";

        std::string f_size = data_sorting["Length"].get<std::string>();
        long size_ = std::stoul(f_size.c_str(), 0, 10);
        recv_image(clnt_sock, file_name, size_);
        std::string result = send_image_python(file_name, python_sock);
        DB.Result_save(result, file_name);
        std::cout << "C#에 보냄\n";
        send_msg(result.data(), result.size(), clnt_sock);
    }
    break;
    case Python_connect:
    {
        std::cout << "python connect\n";
        python_sock = clnt_sock;
        std::cout << "python_sock: " << python_sock << std::endl;
        memset(msg, 0, BUF_SIZE);
        while (1)
        {
            if (!read(clnt_sock, msg, BUF_SIZE))
                break;
        }
    }
        std::cout << "python end\n";
        break;
    case SHOW_INFO:
    {
        std::cout << "SHOW_INFO\n";
        std::string json_ = DB.Show_Info();
        send_msg(json_.data(), json_.size(), clnt_sock);
    }
    break;
    default:
        std::cout << "잘 못된 정보입니다." << std::endl;
        break;
    }
    std::cout << "bye bye~" << std::endl;
    mtx.lock();
    for (int i = 0; i < clnt_cnt; i++)
    {
        if (clnt_sock == clnt_socks[i])
        {
            while (i < clnt_cnt - 1)
            {
                clnt_socks[i] = clnt_socks[i + 1];
                i++;
            }
            break;
        }
    }
    clnt_cnt--;
    mtx.unlock();
    close(clnt_sock);
}

void send_msg(char *msg, int len, int sock)
{

    write(sock, msg, len);
    memset(msg, 0, len);
}

void error_handling(const std::string &msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}

std::string send_image_python(std::string file_path, int python_sock)
{   char recv_msg[BUF_SIZE];
    std::string temp_path = path + file_path;
    std::cout << "file_path:" << temp_path << std::endl;
    cv::Mat temp = cv::imread(temp_path, cv::IMREAD_COLOR);
    std::vector<uchar> Image_b;
    cv::imencode(".png", temp, Image_b);
    uchar *buf = new uchar[Image_b.size()];

    for (int i = 0; i < Image_b.size(); i++)
        buf[i] = Image_b[i];
    std::cout << "사이즈: " << Image_b.size() << std::endl;
    std::ostringstream oss;
    oss << Image_b.size();
    std::string abc(oss.str());
    send(python_sock, abc.c_str(), strlen(abc.c_str()), 0);

    send(python_sock, buf, Image_b.size(), 0);
    std::cout << "다보냄\n";
    int str_len;
    std::string ss;
    while (str_len = recv(python_sock, recv_msg, strlen(recv_msg), 0) > 0)
    {   int i =0;
        recv_msg[strlen(recv_msg)] = '\0';
        while(recv_msg[i] != '!')
        {   std::cout << recv_msg[i] << std::endl;
            ss += recv_msg[i];
            i++;
        }
        break;
    }
    std::cout << ss << std::endl;
    // std::cout << "recv_msg:" << recv_msg << std::endl;
    // std::cout << "python_sock: " << python_sock << std::endl;
    // std::string result(recv_msg);
    // std::cout << "result: " << result << std::endl;

    return ss;
}

void recv_image(int clnt_sock, std::string file_name, long size_) // 클라이언트로 부터 이미지파일을 전송받아 저장하는 함수
{
    std::cout << "recv_image 함수 두둥등장" << std::endl;
    uchar buf[BUF_SIZE]; // 데이터를 저장할 버퍼
    int recv_len;

    std::string filePath = path + file_name;
    std::cout << "파일 경로: " << filePath << std::endl;

    // 파일 쓰기용으로 열기
    FILE *fp = fopen(filePath.c_str(), "wb");
    if (!fp)
    {
        std::cerr << "파일을 열 수 없습니다: " << filePath << std::endl;
        return;
    }

    long file_size = size_;
    std::cout << "파일 크기: " << file_size << " 바이트" << std::endl;

    // 파일 데이터 받기
    long total_received = 0;
    while (total_received < file_size)
    {
        memset(buf, 0, BUF_SIZE);
        int readBytes = recv(clnt_sock, buf, BUF_SIZE, 0);
        if (readBytes <= 0)
        {
            std::cerr << "파일 데이터를 받는 동안 오류 발생" << std::endl;
            break;
        }
        total_received += readBytes;
        fwrite(buf, sizeof(char), readBytes, fp);
    }
    fclose(fp);
}
