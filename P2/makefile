.PHONY: x clean tar

EJECUTABLE= practica_objetos_B2

MODULOS:= practica_objetos_B2.o\
         objetos_B2.o\
         file_ply_stl.o\
      
#LIBS:= -lglut -lGLU -lGL -lsupc++ -lm -lc -lstdc++ -lpthread -L/usr/lib/nvidia-331
LIBS:= -framework GLUT -framework OpenGL -lm -lc -lstdc++ -lpthread 
CPPFLAGS:= -Wall -fmax-errors=2 -g

CC= g++

x: $(EJECUTABLE)
	./$(EJECUTABLE) beethoven

$(EJECUTABLE): $(MODULOS)	
	$(CC) -o $(EJECUTABLE) $(LDFLAGS) $(MODULOS) $(LIBS) 

# Comprimir el proyecto 
tgz:
	tar -cvzf practica_objetos_B2.tgz *.h *hpp *.cc *.ply makefile

clean:
	rm -rf *.o $(EJECUTABLE)

