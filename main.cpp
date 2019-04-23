#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "unistd.h"
#include <thread>
#include <vector> 
#include "Data.h"

double compute(Data data) {
    double result = 0; 
    for(long i = 0; i < data.i; ++i) {
        result += (data.d1 * data.d2) * (i % 8);
    }
    printf("%f\n",result);
    return result;
}
        
double readMsgFromConnection(short port){
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    int counter=0;
    double res=0;
    Data buffer;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return 0; 
    } 
    
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port); 

    while(counter < 1000){
        valread = read(sock, &buffer, sizeof(buffer)); 
        res += compute(buffer);
        counter++;
    }
    return res / 1000;
}

int main(int argc,char *argv[]){
    short PORT = atoi(argv[1]);
    printf("%f\n",readMsgFromConnection(PORT));

    return 0;
}
