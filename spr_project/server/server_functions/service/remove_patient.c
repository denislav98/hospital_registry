void deletePatientFromDb(Patient patientToRemove) {
	char deletePatientQuery[500];
	snprintf(deletePatientQuery, sizeof deletePatientQuery, "DELETE FROM PATIENTS WHERE name='%s' AND egn='%s'", patientToRemove.name, patientToRemove.egn);
	if ((mysql_query(mysql_connection, deletePatientQuery))) {
		printf("%s\n", mysql_error(mysql_connection));
	}
	printf("Patient : %s successfully deleted from database \n", patientToRemove.name);
}

void deletePatientFromList(Patient patientToRemove) {
	PatientList* current = head;
	PatientList* previous = current;
	PatientList* nodeToDelete = NULL;
	while (current != NULL) {
		if (strcmp(current->patient.name, patientToRemove.name) == 0
			&& strcmp(current->patient.egn, patientToRemove.egn) == 0) {
			nodeToDelete = current;
			break;
		}

		previous = current;
		current = current->next;
	}

	if (nodeToDelete == head) {
		head = nodeToDelete->next;
	}
	else {
		previous->next = nodeToDelete->next;
	}

	if (nodeToDelete != NULL) {
		free(nodeToDelete);
	}

	printf("Patient : %s successfully deleted from list \n", patientToRemove.name);
}

void addPatientToMorgue(Patient deathPatient) {
	char insertIntoMorgueQuery[500];
	snprintf(insertIntoMorgueQuery, sizeof insertIntoMorgueQuery, "INSERT INTO DEATH_PATIENTS(name, egn) VALUES('%s', '%s')"
		, deathPatient.name, deathPatient.egn);
	if ((mysql_query(mysql_connection, insertIntoMorgueQuery))) {
		printf("%s\n", mysql_error(mysql_connection));
	}
	printf("Patient : %s successfully added to Morgue \n", deathPatient.name);
	addPatientToMorgueList(deathPatient);
}

void addPatientToMorgueList(Patient deathPatient) {
	DeathPatientsList* current = death_head;
	//while (current != NULL) {
	//	if (comparePatients(current->patient, deathPatient) == 0) {
	//		return;
	//	}

	//	current = current->next;
	//}

	DeathPatientsList* newNode = (DeathPatientsList*)malloc(sizeof(DeathPatientsList));

	strcpy(newNode->patient.name, deathPatient.name);
	newNode->patient.name[strlen(deathPatient.name)] = '\0';

	strcpy(newNode->patient.egn, deathPatient.egn);
	newNode->patient.egn[strlen(deathPatient.egn)] = '\0';

	newNode->next = death_head;
	death_head = newNode;

	printf("Patient : %s successfully added to list with dead \n ", deathPatient.name);
}

int getPatientPrognosis(Patient deletePatient) {
	MYSQL_RES* result;
	MYSQL_ROW row;
       
	char selectQuery[500];

        snprintf(selectQuery, sizeof selectQuery, "SELECT * FROM PATIENTS WHERE name='%s' AND egn='%s'", deletePatient.name, deletePatient.egn);

	if ((mysql_query(mysql_connection, selectQuery))) {
		printf("%s\n", mysql_error(mysql_connection));
	}
	result = mysql_use_result(mysql_connection);
	row = mysql_fetch_row(result);
	
	strcpy(deletePatient.prognosis, row[5]);
	deletePatient.prognosis[strlen(row[5])] = '\0';
	
	mysql_free_result(result);
	
	if (strcmp(deletePatient.prognosis, "living") == 0) {
	  return -1;
	}
	return 0;
}

void sendPatientToMorgue(int client_connection_fd) {
	Patient patient;
	read(client_connection_fd, &patient, sizeof(Patient));
	if(-1 == getPatientPrognosis(patient)){
	  printf("Are you crazy, this patient will live, you can't send him to the morgue \n");
	  strcpy(patient.prognosis, "living");
	  patient.prognosis[strlen(patient.prognosis)] = '\0';
	  write(client_connection_fd, &patient, sizeof(Patient));
	  return;
	}
	
	deletePatientFromDb(patient);
	deletePatientFromList(patient);
	addPatientToMorgue(patient);
	write(client_connection_fd, &patient, sizeof(Patient));
}
