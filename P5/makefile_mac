.PHONY: x clean tar

EJECUTABLE= practica_objetos_B3

MODULOS:= practica_objetos_B3.o\
         objetos_B3.o\
         file_ply_stl.o\
      
#LIBS:= -lglut -lGLU -lGL -lsupc++ -lm -lc -lstdc++ -lpthread -L/usr/lib/nvidia-331
LIBS:= -framework GLUT -framework OpenGL -lm -lc -lstdc++ -lpthread 
CPPFLAGS:= -Wall -fmax-errors=2 -g

CC= g++

default: $(EJECUTABLE)

x: $(EJECUTABLE)
	./$(EJECUTABLE) beethoven

$(EJECUTABLE): $(MODULOS)	
	$(CC) -o $(EJECUTABLE) $(LDFLAGS) $(MODULOS) $(LIBS) 

# Comprimir el proyecto 
tgz:
	tar -cvzf practica_objetos_B3.tgz *.h *hpp *.cc *.ply makefile

clean:
	rm -rf *.o $(EJECUTABLE)

