void printAllDeathPatients(int socket_fd) {
	DeathPatient patient;
	printf("\nDead Patients:\n");
	while (1) {
		read(socket_fd, &patient, sizeof(DeathPatient));
		if (strcmp(patient.name, "end") == 0) {
			break;
		}

		printf("Patient : %s\n EGN: %s \n", patient.name, patient.egn);
		memset(&patient, 0, sizeof(DeathPatient));
	}
	printf("\n");
}
