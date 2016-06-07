#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <x86intrin.h>
#include <inttypes.h>

#define BUFFER_SIZE 128

void check_zero(int status, char* msg) {
  if (status != 0) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
  }
}

void check_gezero(int status, char* msg) {
  if (status < 0) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
  }
}

void usage_error() {
  fprintf(stderr, "Valid parameters: <c/s> <address> <port> [nbytes] [trials]\n");
  exit(1);
}


struct addrinfo* ip4tcp_addr_struct(char* host, char* port) {
  struct addrinfo hints, *addr;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family   = PF_INET;     // Use IPv4
  hints.ai_socktype = SOCK_STREAM; // Use TCP streams
  if (host == NULL)
    hints.ai_flags  = AI_PASSIVE;  // Fill in local address

  int status = getaddrinfo(host, port, &hints, &addr);
  check_zero(status, "cannot create address structure");

  return addr;
}

void echo_server(char* port) {

  int status;
  // Set up server-side socket/address structures
  struct addrinfo* server_addr = ip4tcp_addr_struct(NULL, port);

  // Create a TCP socket
  int sockfd = socket( server_addr->ai_family, 
                       server_addr->ai_socktype,
                       server_addr->ai_protocol );
  check_gezero(sockfd, "cannot create server socket");

  // Bind to socket to the local port
  status = bind(sockfd, server_addr->ai_addr, server_addr->ai_addrlen);
  check_gezero(status, "cannot bind to local port");

  status = listen(sockfd, 1); // No queues, there should only be one client
  check_gezero(status, "cannot listen for new connections");

  char buffer[BUFFER_SIZE];
  int msglen;
  struct sockaddr_storage client_addr;
  socklen_t addr_size;
  int clientfd;

  while (1) {
    clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addr_size);

    msglen = read(clientfd, buffer, BUFFER_SIZE);
    msglen = write(clientfd, buffer, msglen);

    close(clientfd);
  }

  freeaddrinfo(server_addr);
}

typedef struct _tcp_timing {
  uint64_t preconnect;
  uint64_t postconnect;
  uint64_t prewrite;
  uint64_t postread;
  uint64_t postclose;
} TCPTiming;

TCPTiming timing_client(char* host, char* port, int nbytes) {

  int status;
  TCPTiming timing;

  struct addrinfo* server_addr = ip4tcp_addr_struct(host, port);
  int sockfd = socket( server_addr->ai_family,
                       server_addr->ai_socktype,
                       server_addr->ai_protocol );
  check_gezero(sockfd, "cannot create socket on client");

  char* message = malloc(nbytes);
  char buffer[BUFFER_SIZE];

  timing.preconnect = _rdtsc();
  status = connect(sockfd, server_addr->ai_addr, server_addr->ai_addrlen) ;
  timing.postconnect = _rdtsc();
  check_gezero(status, "cannot connect to host");

  timing.prewrite = _rdtsc();
  status = write(sockfd, message, nbytes);
  status = read(sockfd, buffer, BUFFER_SIZE);
  timing.postread = _rdtsc();

  close(sockfd);
  timing.postclose = _rdtsc();
  return timing;
}

void write_timing(FILE* stream, TCPTiming* timing) {
  fprintf(stream, "%lu, %lu, %lu\n", 
          timing->postconnect - timing->preconnect,
          timing->postread    - timing->prewrite,
          timing->postclose   - timing->postread);
} 

int main(int argc, char** argv) {
  if (argc < 4)
    usage_error();

  char* host = argv[2];
  char* port = argv[3];

  uint64_t ticks;

  if (argv[1][0] == 's')
    echo_server(port);
  else if (argv[1][0] == 'c') {
    if (argc < 6)
      usage_error();

    int nbytes = atoi(argv[4]);
    int trials = atoi(argv[5]);
    TCPTiming* timings = malloc(sizeof(TCPTiming)*trials);

    int tenpercent = trials/10;
    fprintf(stderr, "Starting trails: ");
    for (int i = 0; i < trials; ++i) {
      TCPTiming timing = timing_client(host, port, nbytes);
      write_timing(stdout, &timing);

      if (i % tenpercent == 0) {
        fprintf(stderr, "*");
        fflush(stderr);
      }
    }
    fprintf(stderr,"\n");
    printf("\n");
  }
  else {
    fprintf(stderr, "expected 'c' or 's', got %c\n", argv[1][0]);
    exit(1);
  }
  return 0;
}
