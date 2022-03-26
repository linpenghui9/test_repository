/*************************************************************************
	> File Name: server.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 26 Mar 2022 11:29:25 AM PDT
 ************************************************************************/

#include "server.h"
server::server(int port, string ip): server_port(port),server_ip(ip){}

server::~server(){
    for (auto conn:sock_arr){
        close(conn);
    close(server_sockfd);
    }
}

void server::run()
{
    //定义sockfd
    int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);

    //定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;//TCP/IP协议族
    server_sockaddr.sin_port = htons(8023);//端口号
    server_sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");//ip地址，127.0.0.1是环回地址，相当于本机ip

    //bind，成功返回0，出错返回-1
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
    {
        perror("bind");//输出错误原因
        exit(1);//结束程序
    }

    //listen，成功返回0，出错返回-1
    if(listen(server_sockfd,20) == -1)
    {
        perror("listen");//输出错误原因
        exit(1);//结束程序
    }

    //客户端套接字
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    //成功返回非负描述字，出错返回-1
    
    //不断取出新连接并创建子线程为其服务
    while(1){
        
    int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
    if(conn<0)
    {
        perror("connect");//输出错误原因
        exit(1);//结束程序
    }
    cout << "文件描述符为"<< conn <<"客户端成功连接\n";
    sock_arr.push_back(conn);
    //创建线程
    thread t(server::RecvMsg, conn);
    t.detach(); //置为分离状态，不能用join，join会导致主线程阻塞  
    }
}

void server::RecvMsg(int conn){
    

    //接收缓冲区
    char buffer[1000];

    //不断接收数据
    while(1)
    {

        memset(buffer,0,sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer),0);
        //客户端发送exit或者异常结束时，退出
        if(strcmp(buffer,"exit")==0 || len<=0)
            break;
       cout << "收到套接字描述符为"<<conn<<"收到客户端信息："<<buffer<<endl;
    }
}
