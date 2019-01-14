#include "networking.h"

void process(char *s);
void subserver(int from_client);

void sighandler(int s){
    printf("disconnecting all users...\n");
    fclose( fopen("./online.txt", "w") );
    exit(0);
}

int main() {

    signal(SIGINT, sighandler);

    int listen_socket;
    int f;
    listen_socket = server_setup();

    while (1) {

        int client_socket = server_connect(listen_socket);
        f = fork();
        if (f == 0)
            subserver(client_socket);
        else
            close(client_socket);
    }
}

void subserver(int client_socket) {
    char buffer[BUFFER_SIZE];
    char * opponent = calloc(1, 100);

    //get opponent
    read(client_socket, opponent, sizeof(opponent));
    printf("SERVER OPPONENT: |%s|\n", opponent);
    while (read(client_socket, buffer, sizeof(buffer))) {

        printf("[subserver %d] received: [%s]\n", getpid(), buffer);
        process(buffer);
        write(client_socket, buffer, sizeof(buffer));
    }//end read loop
    
    //char * user = login();
    //select_match(user);
    
    //fclose( fopen("./online.txt", "w") );
    //printf("opened");
    close(client_socket);
    exit(0);
}



void process(char * s) {
    while (*s) {
        if (*s >= 'a' && *s <= 'z')
            *s = ((*s - 'a') + 13) % 26 + 'a';
        else  if (*s >= 'A' && *s <= 'Z')
            *s = ((*s - 'a') + 13) % 26 + 'a';
        s++;
    }
}

