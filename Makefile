CC=gcc
CFLAGS=-lpthread -lrt
FILES=mizzo.c producer.c consumer.c
OBJS=mizzo.o producer.o consumer.o
EXEC=mizzo

${EXEC}: ${OBJS}
	${CC} ${OBJS} -o ${EXEC} ${CFLAGS}

clean:
	@rm -rvf *.o ${EXEC}