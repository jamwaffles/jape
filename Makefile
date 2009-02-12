OUT=openglMain
OBJ=openglMain.o openglFont.o openglFrameTimer.o openglFps.o japeEngine.o
CC=g++
CCFLAGS=-Wall -g -pedantic
LIBS=-lglut

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) -o $(OUT) $(OBJ) $(LIBS)
	
clean:
	rm -f $(OUT) $(OBJ)

