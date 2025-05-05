output: main.o converter1.o dollar.o
	gcc main.o converter1.o dollar.o -o output

main.o: main.c converter1.h dollar.h
	gcc -c main.c

converter1.o: converter1.c converter1.h
	gcc -c converter1.c

dollar.o: dollar.c dollar.h
	gcc -c dollar.c

clean:
	rm *.o output				
