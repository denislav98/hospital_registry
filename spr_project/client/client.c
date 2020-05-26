#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT 8080

#include "../structures/patient.h"
#include "../structures/death_patient.h"
#include "client_prototypes.h"

#include "client_functions/print_death_patients.c"
#include "client_functions/print_patients.c"
#include "client_functions/add_patient.c"
#include "client_functions/remove_patient.c"
#include "client_functions/client_tcp_socket.c"

int main(){
	int socket_fd = createSocket();
	connectToServer(socket_fd);

	serverComunicationService(socket_fd);

	close(socket_fd);
	return 0;
}
