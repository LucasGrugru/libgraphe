#########
#
# libGraph
#
#########

# Variables
CC = gcc -g
CFLAGS = -W
CPPFLAGS = -I.
LDLIBS = -lm


LD_FLAGS =

# gestion des repertoires
SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin
LIBDIR = ./lib

# Variables locales
MAIN = $(BINDIR)/main
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all : $(BINDIR) $(MAIN)

# Regle principale avec l'edition de lien
$(MAIN) : $(OBJ) 
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDLIBS)

#  construction des .o
$(OBJDIR)/%.o : $(SRCDIR)/%.c $(SRCDIR)/%.h $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(OBJDIR)/$*.o 

#  construction des .o
$(OBJDIR)/%.o : $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(OBJDIR)/$*.o 

$(OBJDIR) : 
	mkdir $(OBJDIR)

$(BINDIR) :
	mkdir $(BINDIR)

# Nettoyage des fichiers
clean : 
	rm $(OBJ); *~

# suppression de tous les fichiers
veryclean : clean
	rm $(BINDIR)/$(MAIN)

