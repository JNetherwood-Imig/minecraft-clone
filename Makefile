CFLAGS = -Wall -std=c2x -g
LFLAGS = -lglfw -lGL -lm
LFLAGSX = -framework OpenGL -lglfw -lGLEW
OBJDIR = out/objects/
OBJECTS = $(OBJDIR)main.o $(OBJDIR)io.o $(OBJDIR)input.o $(OBJDIR)global.o $(OBJDIR)game.o $(OBJDIR)config.o
OBJECTS += $(OBJDIR)time.o $(OBJDIR)render.o $(OBJDIR)render_init.o $(OBJDIR)render_utils.o $(OBJDIR)camera.o
OBJECTS += $(OBJDIR)glad.o

run: out/program
	./out/program

out/program: $(OBJECTS)
	gcc $(LFLAGS) $(OBJECTS) -o out/program

$(OBJDIR)main.o: src/main.c
	gcc $(CFLAGS) -c src/main.c -o $(OBJDIR)main.o

$(OBJDIR)glad.o: src/glad.c
	gcc $(CFLAGS) -c src/glad.c -o $(OBJDIR)glad.o

$(OBJDIR)io.o: src/game/io/*
	gcc $(CFLAGS) -c src/game/io/io.c -o $(OBJDIR)io.o

$(OBJDIR)input.o: src/game/input/*
	gcc $(CFLAGS) -c src/game/input/input.c -o $(OBJDIR)input.o

$(OBJDIR)global.o: src/game/global.*
	gcc $(CFLAGS) -c src/game/global.c -o $(OBJDIR)global.o

$(OBJDIR)render.o: src/game/render/*
	gcc $(CFLAGS) -c src/game/render/render.c -o $(OBJDIR)render.o
	gcc $(CFLAGS) -c src/game/render/render_init.c -o $(OBJDIR)render_init.o
	gcc $(CFLAGS) -c src/game/render/render_utils.c -o $(OBJDIR)render_utils.o

$(OBJDIR)game.o: src/game/game.*
	gcc $(CFLAGS) -c src/game/game.c -o $(OBJDIR)game.o

$(OBJDIR)config.o: src/game/config/*
	gcc $(CFLAGS) -c src/game/config/config.c -o $(OBJDIR)config.o

$(OBJDIR)time.o: src/game/time/*
	gcc $(CFLAGS) -c src/game/time/time.c -o $(OBJDIR)time.o

$(OBJDIR)camera.o: src/game/camera/*
	gcc $(CFLAGS) -c src/game/camera/camera.c -o $(OBJDIR)camera.o

clean:
	rm $(OBJDIR)* out/program

run-last:
	./out/program
