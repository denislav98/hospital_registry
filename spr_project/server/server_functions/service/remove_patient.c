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
	while (current != NULL) {
		if (comparePatients(current->patient, deathPatient) == 0) {
			return;
		}

		current = current->next;
	}

	DeathPatientsList* newNode = (DeathPatientsList*)malloc(sizeof(DeathPatientsList));

	strcpy(newNode->patient.name, deathPatient.name);
	newNode->patient.name[strlen(deathPatient.name)] = '\0';

	strcpy(newNode->patient.egn, deathPatient.egn);
	newNode->patient.egn[strlen(deathPatient.egn)] = '\0';

	strcpy(newNode->patient.diagnosis, deathPatient.diagnosis);
	newNode->patient.diagnosis[strlen(deathPatient.diagnosis)] = '\0';

	newNode->next = death_head;
	death_head = newNode;

	printf("Patient : %s successfully added to list with deads \n ", deathPatient.name);
}

void sendPatientToMorgue(int client_connection_fd) {
	Patient patient;
	read(client_connection_fd, &patient, sizeof(Patient));
	if (strcmp(patient.prognosis, "living") == 0) {
	printf("Are you crazy, this patient will live, you can't send him to the morgue \n");
		return;
	}
        deletePatientFromDb(patient);
	deletePatientFromList(patient);
	addPatientToMorgue(patient);	
}
