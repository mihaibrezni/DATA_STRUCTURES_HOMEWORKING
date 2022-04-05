# Declaratiile de variabile
CC = gcc
CFLAGS = -g -Wall -lm -std=c99
 
# Regula de compilare
build: 
	$(CC)  tema_1.c functions.c \
		-o tema1 $(CFLAGS)


# Regulile de "curatenie" (se folosesc pentru stergerea fisierelor intermediare si/sau rezultate)
.PHONY : clean
clean :
	rm -rf tema1