//database
//database_conection.c
void connectToDatabase();
//load_patients.c
void loadPatientsFromDatabase();

//load_death_patients.c
void loadDeathPatientsFromDatabase();
//service

//add_patient.c
void addPatientToDb(Patient newPatient);
int  comparePatients(Patient patient1, Patient patient2);
void addPatientToList(Patient newPatient);
void addNewPatient(int client_connection_fd);

//delete_patient.c
void deletePatientFromDb(Patient patientToRemove);
void deletePatientFromList(Patient patientToRemove);
void addPatientToMorgue(Patient deathPatient);
void addPatientToMorgueList(Patient deathPatient);
void sendPatientToMorgue(int client_connection_fd);

//comunication
//server_tcp_socket_implementation.c
int connectToClient(int socket_fd);
void makeServerListen(int socket_fd);
struct sockaddr_in initializeServer();
void bindServerToLocalHost(int socket_fd, struct sockaddr_in serverAddress);
int createSocket();
void clientComunicationService(int client_connection_fd);
