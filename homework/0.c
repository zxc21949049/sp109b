#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(argc!=3)
    {
        printf("请输入正确的参数个数（运行文件，源网址，保存文件名）！\n");
        return -1;
    }
    // 存放源网址的字符串
    char *Char_Yuan=argv[1];
    printf("你给的源网址是：%s\n",Char_Yuan);
    // 定义hostent结构体
    /*
       struct hostent
            h_name – 地址的正式名称。
            h_aliases – 空字节-地址的预备名称的指针。
            h_addrtype –地址类型; 通常是AF_INET。
            h_length – 地址的比特长度。
            h_addr_list – 零字节-主机网络地址指针。网络字节顺序。
            h_addr - h_addr_list中的第一地址。
     */
    struct hostent *host;
    // gethostbyname()函数用于获取主机名的包含主机名字和地址信息的hostent结构的指针
    if((host=gethostbyname(Char_Yuan))== NULL){
        printf("获取ip地址失败！\n");
        return -1;
    }   
    // 定义字符串用于存放转换后的网络地址
    char buf[30];
    // inet_ntop是将网络二进制结构到ASCII类型的地址 
    /*
        第一个参数af是地址簇，
        第二个参数*src是来源地址，
        第三个参数* dst接收转换后的数据。
        第四个参数三接收数据的长度
    */
    inet_ntop(host->h_addrtype,host->h_addr_list[0],buf,sizeof(buf));
    // sockaddr结构体
    /*
       参数说明：
        sin_family指代协议族，在socket编程中只能是AF_INET
        sin_port存储端口号（使用网络字节顺序），在linux下，端口号的范围0~65535,同时0~1024范围的端口号已经被系统使用或保留。
        sin_addr存储IP地址，使用in_addr这个数据结构
        sin_zero是为了让sockaddr与sockaddr_in两个数据结构保持大小相同而保留的空字节。
    */
    struct sockaddr_in server;
    // 初始化结构体变量
    bzero(&server,sizeof(server));
    // 为结构体变量的每个成员赋值
    server.sin_family=AF_INET;
    server.sin_port=htons(80);
    server.sin_addr.s_addr=inet_addr(buf);
    // 根据目前数据，分配一个套接口的描述字及其所用的资源。
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    // connect函数进行连接套接字
    if(connect(sockfd, (struct sockaddr*)&server, sizeof(server))){
        printf("connect() error!\n");
        return -1;
    }
    // 定义套接字要进行发送的消息字符串
    char socket_send_message[1024];
    // 用sprintf函数将请求头写发送字符串
    sprintf(socket_send_message,"GET / HTTP/1.1\r\nHost:%s\r\nAccept:*/* \r\nUser-Agent:Mozilla/5.0 (Windows NT 10.0; WOW64)\r\nconnection:Keep-Alive\r\n\r\n", Char_Yuan);
    // 将缓冲区设置为两秒
    int timeout=2000;
    /*
    setsockopt函数参数：
        sockfd：标识一个套接口的描述字。
        level：选项定义的层次；支持SOL_SOCKET、IPPROTO_TCP、IPPROTO_IP和IPPROTO_IPV6。
        optname：需设置的选项。
        optval：指针，指向存放选项待设置的新值的缓冲区。
        optlen：optval缓冲区长度。 
    */
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    // 发送套接字
    if(send(sockfd, socket_send_message, strlen(socket_send_message), 0) <= 0){
        printf("send() error!\n");
        return -1;
    }
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    // 定义套接字要进行接收的消息字符串
    char socket_get_message[1024];
    // 用于进行数据的接收
    int str_len;
    // 将获取的消息写入html文件
    FILE* file = fopen(argv[2], "a+");
    if(file == NULL){
        printf("fopen() error!\n");
        return -1;
    }
    // 执行循环直到接收消息的最后
    do{
        //给定循环缓冲区一直接受，直到接受至最后
        bzero(socket_get_message, sizeof(socket_get_message));
        str_len = recv(sockfd, socket_get_message, sizeof(socket_get_message), 0);
        // 将每次接收的数据追加到文件中
        fwrite(socket_get_message, 1, 1024, file);
    }while(str_len);
    return 0;
}
————————————————
版权声明：本文为CSDN博主「流楚丶格念」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_45525272/article/details/107633178