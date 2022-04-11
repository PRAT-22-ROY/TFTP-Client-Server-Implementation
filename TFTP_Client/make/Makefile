CC = gcc
CFLAGS = -g -Wall 
INCLUDEPATH = ./../include
SRCPATH = ./../src
OBJPATH = ./../obj
BINPATH = ./../bin
LOGPATH = ./../logs

$(BINPATH)/main: $(OBJPATH)/main.o $(OBJPATH)/client.o
	$(CC) $(CFLAGS) -o main $(OBJPATH)/main.o $(OBJPATH)/client.o
	mv main $(BINPATH)
	
$(OBJPATH)/main.o: $(SRCPATH)/main.c $(INCLUDEPATH)/CLIENT_UTILITY.h
	$(CC) $(CFLAGS) -c $(SRCPATH)/main.c -I $(INCLUDEPATH)/
	mv main.o $(OBJPATH)/

$(OBJPATH)/client.o: $(SRCPATH)/client.c $(INCLUDEPATH)/CLIENT_UTILITY.h
	$(CC) $(CFLAGS) -c $(SRCPATH)/client.c -I $(INCLUDEPATH)/
	mv client.o $(OBJPATH)/

clear:
	rm $(BINPATH)/main $(OBJPATH)/main.o $(OBJPATH)/client.o

clearlogs:
	rm -f $(LOGPATH)/*.log
