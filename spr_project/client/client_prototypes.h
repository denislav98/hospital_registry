//add_route_implemetation.c
Patient createPatient();
void addNewPatient(int socket_fd);

//delete_route_implementation.c
void sendPatientToMorgue(int socket_fd);

//print_routes.case
void printAllPatients(int socket_fd);

//client_ctp_socket_implementation.c
void printMenu();
int createSocket();
void connectToServer(int socket_fd);
void serverComunicationService(int socket_fd);