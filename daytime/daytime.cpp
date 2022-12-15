#include <iostream>
#include <string>
#include <cstdlib> //exit()
#include <cstring> // strpy()
#include <unistd.h> //close()
#include <netinet/in.h> 
#include <arpa/inet.h>
using namespace std;
void Exception(const string & why, const int exitCode ) // Исключения (возможные ошибки)
{
    cout << "ErrorCode:"<<exitCode <<endl<< why << endl;
    exit(exitCode);
}
int main()
{
    // структура с адресом нашей программы (клиента)
    sockaddr_in * selfAddr = new (sockaddr_in);
    selfAddr->sin_family = AF_INET; // интернет протокол IPv4
    selfAddr->sin_port = 0;         // любой порт на усмотрение ОС
    selfAddr->sin_addr.s_addr = 0;  
    // структура с адресом "на той стороне" (сервера)
    sockaddr_in * remoteAddr = new (sockaddr_in);
    remoteAddr->sin_family = AF_INET;     // интернет протокол IPv4
    remoteAddr->sin_port = htons(7);  // port 7
    remoteAddr->sin_addr.s_addr = inet_addr("95.152.62.42"); //  адрес 
    // буфер для передачи и приема данных
    char *buffer = new char[1024];
    strcpy(buffer,"Hello, World!");   //копируем строку
    int msgLen = strlen(buffer);           //вычисляем длину строки
    // создаём сокет
    int mySocket = socket(AF_INET, SOCK_STREAM, 0); //tcp протокол
    if (mySocket == -1) {
        close(mySocket);
        Exception("Error open socket",1);
    }
    //связываем сокет с адрессом
    int rc = bind(mySocket,(const sockaddr *) selfAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        Exception("Error bind socket with local address",2);
        }
    //установливаем соединение
    rc = connect(mySocket, (const sockaddr*) remoteAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        Exception("Error connect socket with remote server.", 3);
    }

    // передаём сообщение из буффера
    rc = send(mySocket, buffer, msgLen, 0);
    if (rc == -1) {
        close(mySocket);
        Exception("Error send message", 4);
    }
    cout << "We send: " << buffer << endl; 
    // принимаем ответ в буффер
    rc = recv(mySocket, buffer, 1024, 0);
    if (rc == -1) {
        close(mySocket);
       Exception("Error receive answer.", 5);
    }
    buffer[rc] = '\0'; // конец принятой строки
    cout << "We receive: " << buffer << endl; // вывод полученного сообщения от сервера
    // закрыем сокет
    close(mySocket);
    delete selfAddr;
    delete remoteAddr;
    delete[] buffer;
    return 0;
}
