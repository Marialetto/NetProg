#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
#define port 13
#define address "172.16.40.1"

int main (int argc, char **argv)
{
    //Адрес программы-клиента
    sockaddr_in *cAddr = new (sockaddr_in);
    cAddr->sin_family = AF_INET; 
   	cAddr->sin_port = 0; 
    cAddr->sin_addr.s_addr = 0;
    //Адрес программы-сервера)
    sockaddr_in * sAddr = new (sockaddr_in);
    sAddr->sin_family = AF_INET; 
    sAddr->sin_port = htons(13); 
    sAddr->sin_addr.s_addr = inet_addr("127.0.0.1"); // все адреса нашего пк
    
    //буфер для передачи и приема данных
    //string s="Сколько времени?\n";
  	char *buf = new char[512];
  	string str ("Сколько времени?\n");
  	int msgLen = str.length(); // вычисляем длину строки
  	size_t length = str.copy(buf,msgLen); // копируем строку
    
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

    delete cAddr;
    delete sAddr;
    delete[] buf;
    return 0;
}
