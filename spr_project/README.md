# Bikers Program

It is a program for bikers helping them to manage their routes.  
TCP Server - Client implementation.

## Installation

### Step 1

Run database_query.sql  
Change the password in **server/database/database_connection.c** to your localhost password, in order to establish the connection.

### Step 2

**Open your terminal in the same folder and run the following commands:**

```bash
gcc -o resultServer server/server.c -lmysqlclient
```
```bash
gcc -o resultClient client/client.c -lmysqlclient
```
## Run

**Run the following commands to start the program:**

```bash
./resultServer
```
```bash
./resultClient
```
