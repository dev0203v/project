#include <iostream>
#include <thread>
#include "BSERVER.cpp"

int main(int argc, char *argv[]) {

    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;
 
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    while (1) {
        clnt_adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        std::cout<<"clnt_sock : "<<clnt_sock<<std::endl;
        std::cout<<"clnt_socks[clnt_cnt++] : "<<clnt_socks[clnt_cnt]<<std::endl;

        mtx.lock();
        clnt_socks[clnt_cnt] = clnt_sock;
        ++clnt_cnt;
        mtx.unlock();

        std::thread t1(handle_clnt, clnt_sock);
        t1.detach();

        printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
    }
    close(serv_sock);

    return 0;
}