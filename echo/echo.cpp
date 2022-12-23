
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

#define port 7
#define address "172.16.40.1"
#define bufSize 512 

int main (int argc, char **argv)
{
    //Aдрес программы-клиента
 sockaddr_in * cAddr = new (sockaddr_in);
 cAddr->sin_family = AF_INET; // интернет протокол IPv4
 cAddr->sin_port = 0; // любой порт на усмотрение ОС
 cAddr->sin_addr.s_addr = 0; // все адреса нашего пк

    //Адрес программы сервера
 sockaddr_in * sAddr = new (sockaddr_in);
 sAddr->sin_family = AF_INET; // интернет протокол IPv4
 sAddr->sin_port = htons(port); // порт 
 sAddr->sin_addr.s_addr = inet_addr(address); // все адреса нашего пк
	
    // Буфер для передачи и приема данных
    char *buf = new char[bufSize 512];
    int msgLen = str.length(); // вычисляем длину строки
    size_t length = str.copy(buf,msgLen); // копируем строку
	
    // создание сокет
    int Socket = socket(AF_INET, SOCK_STREAM, 0); //TCP
    if (Socket == -1) {
        cerr << "Error open socket";
    }

    int rc = bind(Socket, (const sockaddr *) cAddr, sizeof ( sockaddr_in));
    if (rc == -1) {
        close(Socket);
        cerr <<"Error bind socket with local address";
    }
    //установка соединения
	rc = connect(Socket, ( const sockaddr*) sAddr, sizeof(sockaddr_in));
    if ( rc == -1) {
        close(Socket);
        cerr <<"Error connect socket with remote server";
    }
    // передача и прием данных
 	rc = send(Socket, buf,msgLen,0);
    if ( rc == -1) {
        close(Socket);
        cerr <<"Error send message";
    }
 	cout << "We send:  " << buf << endl;

 	rc = recv(Socket, buf, 512,0);
    if ( rc == -1) {
        close(Socket);
        cerr <<"Error receive answer";
    }
 	buf[rc]='\0';
 	cout << "We receive:  " << buf << endl;
	
    // закрыть сокет
    close(Socket);

    delete cAddr;
    delete sAddr;
    delete[] buf;
    return 0;
}
