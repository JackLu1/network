#include "networking.h"

void process(char *s);
void subserver(int from_client);

int main() {

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

    // while (read(client_socket, buffer, sizeof(buffer))) {

    //     printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    //     process(buffer);
    //     write(client_socket, buffer, sizeof(buffer));
    // }//end read loop
    login();
    close(client_socket);
    exit(0);
}


void login(){

    // format each line: 
    // username pw
    FILE * logins = fopen("./user.txt", "a+");
    char * line;
    size_t len = 0;
    int line_num = 0;
    ssize_t read;

    while( getline(&line, &len, logins) != -1){
        line_num++;
    }
    rewind(logins);
    char ** users = calloc(line_num, 100);
    char ** pws = calloc(line_num, 100);
    printf("%i\n", line_num);

    //int i = 0;
    //printf("Users:\n-----------------------------\n");
    //while( read = getline(&line, &len, logins) != -1 ){
    //    line[strcspn(line, "\n")] = 0;
    //    printf("|%s|\n", line);
    //    strcpy(strsep(&line, " "), users[i]);
    //    strcpy(line, pws[i]);
    //    i++;
    //    //printf("usr: |%s|\n", strsep(&line, " "));
    //    //printf("pw: |%s|\n", line);
    //}
    while( getline(&line, &len, logins) != -1){
        line[strcspn(line, "\n")] = 0;
        printf("got: |%s|", line);
        printf("len: %ld\n", strlen(line));
        printf("line = %s\n", line);
        printf("user |%s|\n", strsep(&line, " "));
        printf("pw |%s|\n", line);
    }
    rewind(logins);

    //-----------login--------------

    char * name = (char*)malloc(100*sizeof(char));
    int new = 1;

    printf("Name: ");
    fgets(name,100,stdin);
    name[strlen(name)-1] = '\0';

    while( getline(&line, &len, logins) != -1){
        if (strcmp( name, strsep(&line, " ") ) == 0){
            new = 0;
            break;
        }
    }
    rewind(logins);
    //for (i = 0; i < line_num; i++){
    //    if (strcmp(name, users[i]) == 0){
    //        // User already exists 
    //        new = 0;
    //        break;
    //    } 
    //}
    printf("New? %i\n", new);
    if (new){
        // Create new user and set pw
        char * new_pw = (char*)malloc(100*sizeof(char));
        printf("Username does not exist \n");
        printf("Creating new user: %s \n", name);
        printf("enter password: ");
        fgets(new_pw,100,stdin);
        new_pw[strlen(new_pw)-1] = '\0';
        printf("pw: %s\n", new_pw);

        fprintf(logins, "%s %s\n", name, new_pw);
    } else{
        // user exists, login
        char * pw = (char*)malloc(100*sizeof(char));
        printf("\n\nuser: %s\n", name);


        while(1){
            printf("enter pw: ");
            fgets(pw,100,stdin);
            pw[strlen(pw)-1] = '\0';
            printf("entered pw |%s|\n", pw);
            //while( getline(&line, &len, logins) != -1){
            //    if (strcmp( name, strsep(&line, " ") ) == 0){
            //        new = 0;
            //        break;
            //    }
            //}
            //rewind(logins);
            //if (strcmp(pw, pws[i]) == 0){
            //    //pws match
            //    printf("correct\n");
            //    break;
            //}
            //else {
            //    printf("Wrong pw, try again\n");
            //}
        }
    }


    printf("login end\n");
    //return name;
    //return "a";
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
