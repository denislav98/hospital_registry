void connectToDatabase(){
	char* SERVER = "localhost";
	char* USER = "root";
	char* PASSWORD = "Chaikabrat2#";
	char* DATABASE = "hospital_registry";
	mysql_connection=mysql_init(NULL);
	if (!(mysql_real_connect(mysql_connection, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0))) {
		printf("%s\n", mysql_error(mysql_connection));
	}
}
