#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
#define port 13
#define address "172.16.40.1"

int main (int argc, char **argv)
{
    //Адрес программы-клиента
    sockaddr_in *сAddr = new (sockaddr_in);
    сAddr->sin_family = AF_INET; 
   	сAddr->sin_port = 0; 
    сAddr->sin_addr.s_addr = 0;
    //Адрес программы-сервера)
    sockaddr_in * sAddr = new (sockaddr_in);
    sAddr->sin_family = AF_INET; 
    sAddr->sin_port = htons(port); 
    sAddr->sin_addr.s_addr = inet_addr(address); // все адреса нашего пк
    
    //буфер для передачи и приема данных
    string s("Сколько времени?\n");
    char *buf = new char[512];
    strcpy (buf, s.c_str());
    int msgLen = s.size(); 
    
    // создание сокета
    int Socket = socket(AF_INET, SOCK_DGRAM, 0);//UDP 
    if (Socket == -1) {
         exit(1);
    }
    int rc = bind(Socket, (const sockaddr *) cAddr, sizeof (sockaddr_in));
    if (rc == -1) {
        exit(1);
    }
    //установка соединения
    rc = connect(Socket, (const sockaddr*) sAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(Socket);
        exit(1);
    }
    //передача и приём данных 
    rc = send(Socket, buf,msgLen,0);
    if (rc == -1) {
        close(Socket);
        exit(1);
    }
    cout << "We send: " << buf << endl;
    rc = recv(Socket, buf, 512,0);
    if ( rc == -1) {
        close(Socket);
        exit(1);
    }
    buf[rc]='\0';
    cout << "We receive: " << buf << endl;
    // закрыть сокет
    close(Socket);

    delete сAddr;
    delete sAddr;
    delete[] buf;
    return 0;
}
