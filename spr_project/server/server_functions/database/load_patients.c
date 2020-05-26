void loadPatientsFromDatabase(){
	MYSQL_RES* result;
	MYSQL_ROW row;

	char* selectAllQuery = "SELECT * FROM PATIENTS";

	head = NULL;

	if((mysql_query(mysql_connection, selectAllQuery))) {
		printf("%s\n", mysql_error(mysql_connection));
	}
	result = mysql_use_result(mysql_connection);

	while ((row = mysql_fetch_row(result))) {
		PatientList* newNode = (PatientList*)malloc(sizeof(PatientList));

		strcpy(newNode->patient.name, row[1]);
		newNode->patient.name[strlen(row[1])]='\0';

		strcpy(newNode->patient.egn, row[2]);
		newNode->patient.egn[strlen(row[2])]='\0';

		newNode->patient.age = atoi(row[3]);

		strcpy(newNode->patient.diagnosis, row[4]);
		newNode->patient.diagnosis[strlen(row[4])] = '\0';

		strcpy(newNode->patient.prognosis, row[5]);
		newNode->patient.prognosis[strlen(row[5])] = '\0';
printf("Patient : %s\n EGN: %s\n Age: %d\n Diagnosis: %s \n Prognosis: %s \n", newNode->patient.name, newNode->patient.egn, newNode->patient.age, newNode->patient.diagnosis, newNode->patient.prognosis);
		newNode->next = head;
		head = newNode;
	}
	mysql_free_result(result);
}
