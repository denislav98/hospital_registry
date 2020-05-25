void printPatients(int client_connection_fd){
	PatientList* current = head;
	while(current != NULL) {
		write(client_connection_fd, &(current->patient), sizeof(Patient));
		current = current->next;
	}

	char endString[10];
	strcpy(endString, "end");
	write(client_connection_fd, &endString, sizeof(endString));
}
