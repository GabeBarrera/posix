CC = g++
CFLAGS = -Wall -c
LFLAGS = -lpthread -lrt
TARGET = mizzo

all: $(TARGET)

$(TARGET): mizzo.o CFactoryParse.o Factory.o Producer.o Consumer.o
	$(CC) mizzo.o CFactoryParse.o Factory.o Producer.o Consumer.o -o $(TARGET) $(LFLAGS)

mizzo.o: mizzo.cpp
	$(CC) $(CFLAGS) main.cpp

CFactoryParse.o: CFactoryParse.cpp CFactoryParse.h
	$(CC) $(CFLAGS) CFactoryParse.cpp

Factory.o: Factory.cpp Factory.h
	$(CC) $(CFLAGS) Factory.cpp

Producer.o: Producer.cpp Producer.h
	$(CC) $(CFLAGS) Producer.cpp

Consumer.o: Consumer.cpp Consumer.h
	$(CC) $(CFLAGS) Consumer.cpp

clean:
	rm -f core *.o $(TARGET)
