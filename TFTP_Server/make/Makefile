CC = gcc
CFLAGS = -g -Wall 
INCLUDEPATH = ./../include
SRCPATH = ./../src
OBJPATH = ./../obj
BINPATH = ./../bin


$(BINPATH)/main: $(OBJPATH)/main.o $(OBJPATH)/source.o
	$(CC) $(CFLAGS) -o main $(OBJPATH)/main.o $(OBJPATH)/source.o
	mv main $(BINPATH)
	
$(OBJPATH)/main.o: $(SRCPATH)/main.c $(INCLUDEPATH)/header.h
	$(CC) $(CFLAGS) -c $(SRCPATH)/main.c -I $(INCLUDEPATH)/
	mv main.o $(OBJPATH)/

$(OBJPATH)/source.o: $(SRCPATH)/source.c $(INCLUDEPATH)/header.h
	$(CC) $(CFLAGS) -c $(SRCPATH)/source.c -I $(INCLUDEPATH)/
	mv source.o $(OBJPATH)/

clear:
	rm $(BINPATH)/main $(OBJPATH)/main.o $(OBJPATH)/source.o
