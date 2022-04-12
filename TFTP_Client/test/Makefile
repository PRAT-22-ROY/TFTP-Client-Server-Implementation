CC = gcc
#used standard c99 where the __func__ is available to print function names
CFLAGS = -Wall -c -g  
OFLAGS = -o
VFLAGS = --tool=memcheck --leak-check=yes --show-reachable=yes
BIN = bin/
INCLUDE = -I../include/ -I./
HEADER = ../include/
SRC = ../src/
OBJ = obj/
CUNIT_LIB_DIR = -L/usr/lib/    #location of CUnit library
CUNIT_INC_DIR = /usr/include/CUnit/
AUT_INC =  -I$(CUNIT_INC_DIR)

#using shared library
all: $(BIN)testClient


$(BIN)testClient: $(OBJ)testMain.o $(OBJ)testClient.o $(OBJ)client.o
	$(CC) $(OFLAGS) testClient $(OBJ)client.o $(OBJ)testMain.o $(OBJ)testClient.o  $(CUNIT_LIB_DIR) -lcunit
	mv testClient $(BIN)

$(OBJ)testMain.o: testMain.c $(HEADER)client_utility.h testClient.h 
	$(CC) $(CFLAGS) testMain.c $(INCLUDE)   ${AUT_INC}
	mv testMain.o $(OBJ)

$(OBJ)testClient.o: testClient.c $(HEADER)client_utility.h 
	$(CC) $(CFLAGS) testClient.c $(INCLUDE) ${AUT_INC}
	mv testClient.o  $(OBJ)

$(OBJ)client.o: $(SRC)client.c $(HEADER)client_utility.h  
	$(CC) $(CFLAGS) $(SRC)client.c $(INCLUDE)  
	mv client.o $(OBJ)

clean: 
	rm -f $(BIN)testClient
	rm -f $(OBJ)*.o

