CC = gcc
CFLAGS = -ansi

driver: driver.o maze.o queue.o cell.o mouse.o stack.o
	$(CC) -o driver driver.o maze.o queue.o cell.o mouse.o stack.o

tester: tester.o stack.o
	$(CC) -o tester tester.o stack.o

driver.o: maze.h queue.h cell.h

tester.o: stack.h

maze.o: maze.h cell.h stack.h

queue.o: queue.h cell.h

cell.o: cell.h

mouse.o: mouse.h maze.h cell.h queue.h

stack.o: stack.h

clean:
	rm -f *.o

real_clean: clean
	rm -f driver tester
