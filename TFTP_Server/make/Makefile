CC = gcc
CFLAGS = -g -Wall 
INCLUDEPATH = ./../include
SRCPATH = ./../src
OBJPATH = ./../obj
BINPATH = ./../bin
LOGPATH = ./../logs

$(BINPATH)/main: $(OBJPATH)/main.o $(OBJPATH)/server.o
	$(CC) $(CFLAGS) -o main $(OBJPATH)/main.o $(OBJPATH)/server.o
	mv main $(BINPATH)/
	
$(OBJPATH)/main.o: $(SRCPATH)/main.c $(INCLUDEPATH)/SERVER_UTILITY.h
	$(CC) $(CFLAGS) -c $(SRCPATH)/main.c -I $(INCLUDEPATH)/
	mv main.o $(OBJPATH)/

$(OBJPATH)/server.o: $(SRCPATH)/server.c $(INCLUDEPATH)/SERVER_UTILITY.h
	$(CC) $(CFLAGS) -c $(SRCPATH)/server.c -I $(INCLUDEPATH)/
	mv server.o $(OBJPATH)/

clear:
	rm $(BINPATH)/main $(OBJPATH)/main.o $(OBJPATH)/server.o

clearlogs:
	rm -f $(LOGPATH)/*.log
