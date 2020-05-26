void sendPatientToMorgue(int socket_fd){
	char egn[15];
        char name[50];
        char prognosis[50];
        
	printf("\n");

	Patient deletePatient;
	
	printf("Enter patient name : \n"); 
        fgets(name, sizeof(name),stdin);
	strcpy(deletePatient.name, name);
	deletePatient.name[strlen(name)] = '\0';
	(deletePatient.name)[strcspn(deletePatient.name,"\n")]='\0'; 

	printf("Enter patient egn : \n");
	fgets(egn, sizeof(egn),stdin);
	strcpy(deletePatient.egn, egn);
	deletePatient.egn[strlen(egn)] = '\0';
	(deletePatient.egn)[strcspn(deletePatient.egn,"\n")]='\0';
       
       
	printf("\n");
	write(socket_fd, &deletePatient, sizeof(Patient));
	
	
	read(socket_fd, &deletePatient, sizeof(Patient));

	if(strcmp(deletePatient.prognosis, "living") == 0) {
	   printf("Are you crazy, this patient will live, you can't send him to the morgue \n");
	}else{
	 printf("Patient : %s is sent to the morgue \n",deletePatient.name);
	}
	
	memset(&deletePatient, 0, sizeof(Patient));
}
