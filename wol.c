#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void error(char *msg) {
    perror(msg);
    exit(errno);
}

void usage(void) {
    errno = EINVAL;
    error("wol <mac_addr> <ip_addr> <port>\n");
}

void get_macaddr(char *macaddr_str, uint8_t *macaddr) {
    sscanf(macaddr_str, "%x:%x:%x:%x:%x:%x",
           (uint32_t*)&macaddr[0], (uint32_t*)&macaddr[1], (uint32_t*)&macaddr[2],
           (uint32_t*)&macaddr[3], (uint32_t*)&macaddr[4], (uint32_t*)&macaddr[5]);
}

void create_magic_pkt(uint8_t *magic_pkt, int len, uint8_t *macaddr) {
    memset((void*) magic_pkt, 0, len);

    for (int i=0; i<6; i++) magic_pkt[i] = 0xff;
    for (int i=6; i<len; i+=6) memcpy(magic_pkt+i, macaddr, 6);
}

int main(int argc, char **argv) {
    int n, sockfd;
    int serverlen;
    uint8_t macaddr[6];
    struct sockaddr_in server;

    uint8_t magic_pkt[102]; //mac F4:8E:38:AB:3A:B5

    if (argc != 4) {
        usage();
    }

    get_macaddr(argv[1], macaddr);
    create_magic_pkt(magic_pkt, sizeof(magic_pkt), macaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        error("socket call failed");

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[2]);
    server.sin_port = htons(atoi(argv[3]));

    serverlen = sizeof(server);
    n = sendto(sockfd, magic_pkt, sizeof(magic_pkt), 0, 
              (struct sockaddr *)&server, serverlen);
    if (n < 0)
        error("sendto call failed");

    close(sockfd);
    return 0;
}
