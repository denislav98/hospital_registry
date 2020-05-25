void printAllPatients(int socket_fd){
	Patient patient;
	printf("\nPatients:\n");
	while(1) {
		read(socket_fd, &patient, sizeof(Patient));
		if(strcmp(patient.name, "end") == 0) {
			break;
		}

		printf("Patient : %s\n EGN: %s\n Age: %d\n Diagnosis: %s \n Prognosis: %s \n", patient.name, patient.egn, patient.age, patient.diagnosis,patient.prognosis);
		memset(&patient, 0, sizeof(Patient));
	}
	printf("\n");
}
