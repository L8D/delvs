#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

int makesocket(char *address, int port) {
  int sock;
  struct hostent *host;
  struct sockaddr_in server_addr;

  host = gethostbyname(address);

  if(host == NULL) {
    fprintf(stderr, "Host not found\n");
    exit(1);
  }

  sock = socket(AF_INET, SOCK_STREAM, 0);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr = *((struct in_addr *)host->h_addr_list[0]);
  bzero(&(server_addr.sin_zero), 8);

  connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

  return sock;
}
