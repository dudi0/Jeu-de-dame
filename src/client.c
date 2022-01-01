#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  
#include <netdb.h>
#include <arpa/inet.h>
  
#define PORT 2345 
#define BUF_SIZE 1024 

void cli_input(int sockfd, char * msg)
{
    //Envoie du message vers le serveur.
    if(send(sockfd, msg, strlen(msg), 0) < 0) 
    {
        perror("Echec de l'envoi des données\n");
        exit(EXIT_FAILURE);
    }
}

void init_client() 
{
    int sockfd;
    struct sockaddr_in serv_addr;
    socklen_t addr_len;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Echec de création de la socket\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket créée\n");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
 	serv_addr.sin_addr.s_addr = inet_addr(INADDR_ANY); 
 	serv_addr.sin_port = htons(PORT);
    addr_len = sizeof(serv_addr);

    if(connect(sockfd, (struct sockaddr *) &serv_addr, addr_len) < 0)
    {
        printf("Echec de la connexion au serveur\n");
        exit(EXIT_FAILURE);
    }
    printf("Connexion au serveur réussie\n");
}