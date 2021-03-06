#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </usr/include/mysql/mysql.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define DESTINATION_NAME_LENGTH 50

#include "../structures/patient.h"
#include "../structures/death_patient.h"
#include "../structures/patients_list.h"
#include "../structures/death_patient_list.h"

PatientList* head;
DeathPatientsList* death_head;

#include "server_prototypes.h"
MYSQL* mysql_connection;

#include "server_functions/service/print_patients.c"
#include "server_functions/service/print_death_patients.c"
#include "server_functions/service/add_patient.c"
#include "server_functions/service/remove_patient.c"

#include "server_functions/database/load_patients.c"
#include "server_functions/database/load_death_patients.c"
#include "server_functions/database/database_connection.c"

#include "server_functions/comunication/server_tcp_socket_implementation.c"

int main(){
	connectToDatabase();

	int socket_fd = createSocket();

	struct sockaddr_in serverAddress = initializeServer();
	bindServerToLocalHost(socket_fd, serverAddress);
	makeServerListen(socket_fd);

	int client_connection_fd = connectToClient(socket_fd);
	clientComunicationService(client_connection_fd);

	close(socket_fd);
	mysql_close(mysql_connection);
	return 0;
}
