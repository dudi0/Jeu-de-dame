#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>  
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 2345 
#define BUF_SIZE 1024 
#define MAX_CLI 10 

void init_server()
{
    int i;
    int sockfd, newsock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in cl_addr;
	socklen_t addr_len;

    char buffer[BUF_SIZE];

    //Multiplexing
    //Set de descripteurs de fichiers (pour le select)
    fd_set readfds;
    int max_fd;
    //Initialisation du timeout (pour le select)
/*    struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
*/  
    //Initialisation du tableau de clients
    int clients[MAX_CLI];
    memset(clients, 0, sizeof(clients));

 	//Création de la socket
 	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
 	{
 		printf("Erreur de création de la socket.\n");
  		exit(EXIT_FAILURE);
 	}
 	printf("Socket créée.\n");

    //Permet à une socket d'accepter plusieurs connexions.
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, "1", sizeof(1)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

 	//Création de l'adresse du serveur
 	memset(&serv_addr, 0, sizeof(serv_addr));
 	serv_addr.sin_family = AF_INET;
 	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 	serv_addr.sin_port = htons(PORT); 

    //Connexion/Liaison avec la socket ?
 	if (bind(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
 	{
 		printf("Error binding!\n");
  		exit(1);
 	}
 	printf("Binding done.\n");

	//Mise en place de l'écoute du serveur
 	listen(sockfd, 5); //5 connexions simultanées max
 	printf("Waiting for a connection...\n");

    while(1)
    {
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        max_fd = sockfd;

        //Ajoute des socket client à l'ensemble de socket.
        for(i = 0; i < MAX_CLI; i++) 
        {
            sockfd = clients[i];
            
            //Vérifie si aucune erreur sur le descripteur de fichier.
            if(sockfd > 0)
            {
                FD_SET(sockfd, &readfds);
            }

            //Trouve l'index du plus grand descripteur de fichier.
            if(sockfd > max_fd)
            {
                max_fd = sockfd;
            }
        }

        //Surveille les descripteurs de fichiers prêts à pour lecture/écriture
        if ((select(max_fd + 1, &readfds, NULL, NULL, NULL) < 0) && errno != EINTR)
        {
            printf("Erreur du select");
        }

        //Cas d'une nouvelle connexion
        if (FD_ISSET(sockfd, &readfds))
        {
            if ((newsock = accept(sockfd, (struct sockaddr *)&serv_addr, &addr_len)) < 0)
            {
                printf("Erreur de connexion");
                exit(EXIT_FAILURE);
            }
            printf("Connexion : %s:%d\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));


            //Ajoute de la nouvelle socket au tableau de clients.
            for(int i = 0; i < MAX_CLI; i++) 
            {
                if(clients[i] == 0)
                {
                    clients[i] = newsock;                  
                    break;
                }
            }
        }

        //
        for(i = 0; i < MAX_CLI; i++) 
        {
            sockfd = clients[i];

            if(FD_ISSET(sockfd, &readfds)) 
            {
                char c;
                //Verifie si le client souhaite se deconnecter du serveur.
                if((c = read(sockfd, buffer, BUF_SIZE)) == 0)
                {
                    getpeername(sockfd, (struct sockaddr *) &serv_addr, (socklen_t *) &addr_len);
                    printf("Deconnexion : %s:%d \n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));
                    close(sockfd);
                    clients[i] = 0;
                }
                 
                //Réponse du serveur au client.
                else
                {
                    buffer[c] = '\0';
                    //char * response = server_response(buffer);
                    send(sockfd, "test ok", strlen("test ok"), 0);
                }
            }
        }


    }

}