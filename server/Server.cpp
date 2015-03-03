// This template is a compilation and simplified version of
// a collection of online examples. It is to be used  as  a
// building block in network programming.

#include <iostream>     // time, ctime
#include <cstdlib>      // exit
#include <cstdio>       // snprintf
#include <unistd.h>     // gethostname, write, close, sleep
#include <netdb.h>      // socket, htonl, htons
#define MAXHOSTNAME 256

void* memset(void* b, int c, size_t len);
void* memcpy(void* dst, const void* src, size_t count);

const int PERIOD = 2000000;

int main()
{
	//initialize();

    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    const int BUFF = 32;
    char ioBuff[BUFF];

    // create socket and flush memory blocks
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(ioBuff, (char)0x00, sizeof(ioBuff));

    // set socket properties
    // The client will connect using the "Static IP" of the system
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 0.0.0.0
    serv_addr.sin_port = htons(8421);               // 0.0.0.0:8421

    // Initialize and start the socket
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 10);

    while(1)
    {
        // receive incoming connection
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

        do
        {
            // read data from client
            read(connfd, ioBuff, BUFF);

            // do something
            // ioBuff = data array
            // BUFF = size of array

            // write data back to client
            write(connfd, ioBuff, BUFF);

            // continue to read and write until '-1' is received
        } while(true);

        // close connection and repeat
        close(connfd);
        sleep(10);
    }
}

void* memset(void* b, int c, size_t len) {
    char* p = (char*)b;
    for (size_t i = 0; i != len; ++i) {
        p[i] = c;
    }
    return b;
}
void* memcpy(void* dst, const void* src, size_t count) {
	void * ret = dst;
	while(count--) {
		*(char *)dst = *(char *)src;
		dst = (char *)dst + 1;
		src = (char *)src + 1;
	}
	return(ret);
}
