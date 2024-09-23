PROG1 = piserial
PROG2 = pithreads

CC = gcc
CFLAGS = -lm -pthread


all: $(PROG1) $(PROG2)

$(PROG1): piserial.c
	@echo "\n[+] Compilando el programa SIN hilos piserial.c\n"
	$(CC) -o $(PROG1) piserial.c $(CFLAGS)
$(PROG2): pithreads.c
	@echo "\n[+] Compilando el programa CON hilos pithreads.c\n"
	$(CC) -o $(PROG2) pithreads.c $(CFLAGS)

clean:
	@echo "Limpiando archivos generados..."
	rm -f $(PROG1) $(PROG2)