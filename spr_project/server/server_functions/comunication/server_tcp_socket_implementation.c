int connectToClient(int socket_fd){
	struct sockaddr_in clientAddress;
	int clientAddressSize = sizeof(clientAddress);
	int client_connection_fd = accept(socket_fd, (struct sockaddr*)&clientAddress, &clientAddressSize);

	if(client_connection_fd<0) {
		printf("Server accept failed\n");
		exit(3);
	}else{
		printf("Server accepted the client\n");
	}
	return client_connection_fd;
}

void makeServerListen(int socket_fd){
	if ((listen(socket_fd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else{
		printf("Server listening..\n");
	}
}

struct sockaddr_in initializeServer(){
	struct sockaddr_in serverAddress;
	bzero(&serverAddress, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(PORT);

	return serverAddress;
}

void bindServerToLocalHost(int socket_fd, struct sockaddr_in serverAddress){
	if ((bind(socket_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress))) != 0) {
		printf("Socket bind failed...\n");
		exit(1);
	}
	else{
		printf("Socket successfully binded..\n");
	}
}

int createSocket(){
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else{
		printf("Socket successfully created\n");
	}

	return socket_fd;
}

void clientComunicationService(int client_connection_fd){
	char buffer[30];
	int option;

	loadPatientsFromDatabase();

	while(1) {
		read(client_connection_fd, &option, sizeof(int));
		switch(option)
		{
		case 1: addNewPatient(client_connection_fd); break;
		case 2: sendPatientToMorgue(client_connection_fd); break;
		case 3: printPatients(client_connection_fd); break;
		//case 4: printAllDeathPatients(client_connection_fd); break;
		case 5: printf("Program closed\n"); break;
		default: printf("Option does not exist\n"); break;
		}

		if( option == 5) {
			printf("Server exit");
			break;
		}
	}
}
