DROP DATABASE IF EXISTS hospital_registry;
CREATE DATABASE hospital_registry;
USE hospital_registry;

CREATE TABLE IF NOT EXISTS PATIENTS(
	id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(60) NOT NULL,
    egn VARCHAR(60) NOT NULL UNIQUE,
    age INT NOT NULL,
    diagnosis VARCHAR(60) NOT NULL,
    prognosis VARCHAR(10) NOT NULL
);

CREATE TABLE IF NOT EXISTS DEATH_PATIENTS(
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(60) NOT NULL,
    egn VARCHAR(60) NOT NULL UNIQUE,
    age INT NOT NULL,
    diagnosis VARCHAR(60) NOT NULL,
    prognosis VARCHAR(10) NOT NULL
);

INSERT INTO PATIENTS(name, egn, age, diagnosis,prognosis) VALUES
    ( 'Test', '1234567890', 69, "Alkoholic","dying" ),
    ( 'Bai Ivan', '1441412', 100 , "Programer.." ,"living" ),
    ( 'Ibrqm Mustafa', '34515151', 76, "Insomnia" ,"living" );
