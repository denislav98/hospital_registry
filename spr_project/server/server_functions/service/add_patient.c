void addPatientToDb(Patient newPatient){
	char insertIntoPatientQuery[1000];
	snprintf(insertIntoPatientQuery, sizeof insertIntoPatientQuery, "INSERT INTO PATIENTS(name, egn, age, diagnosis, prognosis) VALUES('%s', '%s', %d, '%s', '%s')"
	         , newPatient.name, newPatient.egn, newPatient.age, newPatient.diagnosis,newPatient.prognosis);
	if((mysql_query(mysql_connection, insertIntoPatientQuery))) {
		printf("%s\n", mysql_error(mysql_connection));
	}
}

int comparePatients(Patient patient1, Patient patient2){
	if(strcmp(patient1.name,patient2.name) == 0
	   && strcmp(patient1.egn,patient2.egn) == 0) {
		return 0;
	}

	return -1;
}

void addPatientToList(Patient newPatient){
	PatientList* current = head;
	while( current != NULL) {
		if( comparePatients(current->patient, newPatient) == 0 ) {
			return;
		}

		current = current->next;
	}

	PatientList* newNode = (PatientList*)malloc(sizeof(PatientList));

	strcpy(newNode->patient.name, newPatient.name);
	newNode->patient.name[strlen(newPatient.name)] = '\0';

	strcpy(newNode->patient.egn, newPatient.egn);
	newNode->patient.egn[strlen(newPatient.egn)] = '\0';

	newNode->patient.age = newPatient.age;

	strcpy(newNode->patient.diagnosis, newPatient.diagnosis);
	newNode->patient.diagnosis[strlen(newPatient.diagnosis)] = '\0';

	strcpy(newNode->patient.prognosis, newPatient.prognosis);
	newNode->patient.prognosis[strlen(newPatient.prognosis)] = '\0';

	newNode->next = head;
	head = newNode;
}

void addNewPatient(int client_connection_fd){
	Patient newPatient;
	read(client_connection_fd, &newPatient, sizeof(Patient));
	addPatientToDb(newPatient);
	addPatientToList(newPatient);
}
