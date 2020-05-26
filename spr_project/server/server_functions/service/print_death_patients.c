void printAllDeathPatients(int client_connection_fd) {
	DeathPatientsList* current = death_head;

	while (current != NULL) {
		write(client_connection_fd, &(current->patient), sizeof(DeathPatient));
		current = current->next;
	}

	char endString[10];
	strcpy(endString, "end");
	write(client_connection_fd, &endString, sizeof(endString));
}
