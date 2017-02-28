# Modèle de fichier Makefile  pour le fichier template.c
LIBDIR = /home/sasl/encad/brajard/projet/CGS_lib

# options de compilation
CC =gcc
CCFLAGS = -Wall 
LIBS = 
LDFLAGS = -lm 

# fichiers du projet
SRC = main.c seqlib.c
OBJ = $(SRC:.c=.o)
EXEC = adn


# règle initiale
all: $(EXEC) clean

# dépendance des .h
main.o: seqlib.h
seqlib.o: seqlib.h

# règles de compilation
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
	
# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)

# règles supplémentaires
clean:
	@rm -rf *.o
rmproper:
	rm -rf $(EXEC) *.o
