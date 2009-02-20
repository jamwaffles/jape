OUT=openglMain
OBJ=openglMain.o openglFont.o openglFrameTimer.o openglFps.o japeEngine.o openglTerminal.o
CC=g++
CCFLAGS=-Wall -g -pedantic
LIBS=-lglut -lGL -lGLU -lglpng -lgc -lGLee

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) -o $(OUT) $(OBJ) $(LIBS)
	
clean:
	rm -f $(OUT) $(OBJ)

