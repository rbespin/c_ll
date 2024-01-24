CC = gcc

CFLAGS = #-lpthread

default: mt_ll

mt_ll: ll_ex.o mt_ll.o
	${CC} -o mt_ll ll_ex.o mt_ll.o ${CFLAGS}


clean:
	-rm -f *.o
	-rm -f mt_ll
