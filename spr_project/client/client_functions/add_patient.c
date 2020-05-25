Patient createPatient() {
	Patient patient;
	char name[50];
	char egn[15];
	char diagnosis[100];
	char prognosis[15];
	char age[5];

	printf("\nEnter patient full name\n");
	fgets(name, sizeof(name), stdin);
	strcpy(patient.name, name);
	patient.name[strlen(name)] = '\0';
	(patient.name)[strcspn(patient.name, "\n")] = '\0';

	printf("\nEnter patient EGN\n");
	fgets(egn, sizeof(egn), stdin);
	strcpy(patient.egn, egn);
	patient.egn[strlen(egn)] = '\0';
	(patient.egn)[strcspn(patient.egn, "\n")] = '\0';

	printf("\nEnter patient age\n");
	fgets(age, sizeof(age), stdin);
	patient.age = atoi(age);
	fflush(stdin);

	printf("\nEnter patient diagnosis\n");
	fgets(diagnosis, sizeof(diagnosis), stdin);
	strcpy(patient.diagnosis, diagnosis);
	patient.diagnosis[strlen(diagnosis)] = '\0';
	(patient.diagnosis)[strcspn(patient.diagnosis, "\n")] = '\0';

	printf("\nEnter patient prognosis\n");
	fgets(prognosis, sizeof(prognosis), stdin);
	strcpy(patient.prognosis, prognosis);
	patient.prognosis[strlen(prognosis)] = '\0';
	(patient.prognosis)[strcspn(patient.prognosis, "\n")] = '\0';

	printf("\n");
	return patient;
}

void addNewPatient(int socket_fd) {
	Patient newPatient = createPatient();
	write(socket_fd, &newPatient, sizeof(Patient));
	printf("Patient : %s with EGN: %s added successfully.\n",newPatient.name,newPatient.egn);
}
