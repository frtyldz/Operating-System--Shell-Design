all: bilshell producer consumer
cost: bilshell.c producer.c consumer.c
	gcc -Wall -g  -o bilshell bilshell.c
	gcc -Wall -g  -o producer producer.c
	gcc -Wall -g  -o consumer consumer.c
clean:
	rm -fr bilshell bilshell.o *~
	rm -fr producer producer.o *~
	rm -fr consumer consumer.o *~
