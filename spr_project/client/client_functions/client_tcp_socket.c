void printMenu(){
	printf("\n");
	printf("1. Add new Patient\n");
	printf("2. Send patient to the underground\n");
	printf("3. Print all patients\n");
	printf("4. Print all death patients\n");
	printf("5. Exit\n");
	printf("\n");
}

int createSocket(){
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	} else{
		printf("Socket successfully created..\n");
	}
	return socket_fd;
}

void connectToServer(int socket_fd){
	struct sockaddr_in serverAddress;
	bzero(&serverAddress, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress.sin_port = htons(PORT);

	if (connect(socket_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}       else{
		printf("connected to the server..\n");
	}
}

void serverComunicationService(int socket_fd){
	int n;
	int option;
	char optionString[20];
	while(1) {
		printf("Enter one of the below options:\n");
		printMenu();
		fgets(optionString, sizeof(optionString), stdin);
		option = atoi(optionString);
		write(socket_fd, &option, sizeof(int));
		switch (option) {
		case 1: addNewPatient(socket_fd); break;
		case 2: sendPatientToMorgue(socket_fd); break;
		case 3: printAllPatients(socket_fd); break;
		case 4:  break;
		case 5: printf("Program exit"); break;
		default: printf("Option does not exist"); break;
		}
		if( option == 5) {
			printf("Client exit");
			break;
		}
	}
}
