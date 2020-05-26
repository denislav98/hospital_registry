void loadDeathPatientsFromDatabase() {
	MYSQL_RES* result;
	MYSQL_ROW row;

	char* selectAllQuery = "SELECT * FROM DEATH_PATIENTS";
	head = NULL;

	if ((mysql_query(mysql_connection, selectAllQuery))) {
		printf("%s\n", mysql_error(mysql_connection));
	}
	result = mysql_use_result(mysql_connection);

	while ((row = mysql_fetch_row(result))) {
		DeathPatientsList* newNode = (DeathPatientsList*)malloc(sizeof(DeathPatientsList));

		strcpy(newNode->patient.name, row[1]);
		newNode->patient.name[strlen(row[1])] = '\0';

		strcpy(newNode->patient.egn, row[2]);
		newNode->patient.egn[strlen(row[2])] = '\0';

		newNode->next = death_head;
		death_head = newNode;
	}
	mysql_free_result(result);
}
