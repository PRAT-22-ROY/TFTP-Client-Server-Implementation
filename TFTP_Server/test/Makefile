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
all: $(BIN)testServer


$(BIN)testServer: $(OBJ)testMain.o $(OBJ)testServer.o $(OBJ)server.o
	$(CC) $(OFLAGS) testServer $(OBJ)server.o $(OBJ)testMain.o $(OBJ)testServer.o  $(CUNIT_LIB_DIR) -lcunit
	mv testServer $(BIN)

$(OBJ)testMain.o: testMain.c $(HEADER)server_utility.h testServer.h 
	$(CC) $(CFLAGS) testMain.c $(INCLUDE)   ${AUT_INC}
	mv testMain.o $(OBJ)

$(OBJ)testServer.o: testServer.c $(HEADER)server_utility.h 
	$(CC) $(CFLAGS) testServer.c $(INCLUDE) ${AUT_INC}
	mv testServer.o  $(OBJ)

$(OBJ)server.o: $(SRC)server.c $(HEADER)server_utility.h  
	$(CC) $(CFLAGS) $(SRC)server.c $(INCLUDE)  
	mv server.o $(OBJ)

clean: 
	rm -f $(BIN)testServer *.txt
	rm -f $(OBJ)*.o

