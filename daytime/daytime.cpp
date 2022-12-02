#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#define BUFFLEN 1024
#define SERVER_PORT 8888
int main(int argc, char *argv[])
{
         INT S; / * Дескриптор файла сокета сервера * /
         Структура Sockaddr_in Сервер; / * Локальный адрес * /
         Char Buff [Bufflen]; / * Буфер данных трансиверов * /
 
         Int n = 0; / * Получать длина строк * /
         Socklen_t len ​​= 0; / * Длина адреса * /
         S = разъем (AF_INET, SOCK_DGRAM, 0); / * Установить сокет UDP * /
 
         / * Инициализация инициализации адреса * /
         MEMSET (& SERVER, 0, SIZEOF (СЕРВЕР); / * CLEAR * /
         Server.sin_family = af_inet; / * af_inet протокол * /
         Server.sin_addr.s_addr = htonl (inaddr_any); / * любой локальный адрес * /
         Server.sin_port = htons (server_port); / * порт сервера * /
 
    while(1){
                 MEMSET (BUFF, 0, BUFFLEN); / * CLEAR * /
                 Strcpy (buff, "Сколько времени?"); / * Копировать Строка отправки * /
 
                 / * Отправить данные * /
        sendto(s, buff, strlen(buff), 0, (struct sockaddr*)&server,
        sizeof(server));
                 MEMSET (BUFF, 0, BUFFLEN); / * CLEAR * /
 
                 / * Получать данные * /
        len = sizeof(server);
        n = recvfrom(s, buff, BUFFLEN, 0, (struct sockaddr*)&server, &len);
 
                 / * Печать сообщения * /
        if(n >0){
            printf("%s",buff);
        }
        sleep(1);
    }
 
    close(s);
    return 0;
}
