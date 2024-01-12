CFLAGS = -Wall -std=c2x -g
LFLAGS = -lglfw -lGL -lm
LFLAGSX = -framework OpenGL -lglfw
OBJDIR = out/objects/
OBJECTS = $(OBJDIR)main.o $(OBJDIR)io.o $(OBJDIR)input.o $(OBJDIR)global.o $(OBJDIR)game.o $(OBJDIR)config.o
OBJECTS += $(OBJDIR)time.o $(OBJDIR)camera.o $(OBJDIR)renderer.o
OBJECTS += $(OBJDIR)glad.o $(OBJDIR)shader.o $(OBJDIR)vao.o $(OBJDIR)vbo.o $(OBJDIR)ebo.o
OBJECTS += $(OBJDIR)texture.o $(OBJDIR)chunk.o $(OBJDIR)block_data.o $(OBJDIR)block.o
OBJECTS += $(OBJDIR)dictionary.o $(OBJDIR)list.o

run: out/program
	./out/program

out/program: $(OBJECTS)
	# cp out/program out/program-last
	gcc $(LFLAGSX) $(OBJECTS) -o out/program

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

$(OBJDIR)renderer.o: src/game/render/*
	# gcc $(CFLAGS) -c src/game/render/render.c -o $(OBJDIR)render.o
	# gcc $(CFLAGS) -c src/game/render/render_init.c -o $(OBJDIR)render_init.o
	gcc $(CFLAGS) -c src/game/render/renderer.c -o $(OBJDIR)renderer.o
	gcc $(CFLAGS) -c src/game/render/shader.c -o $(OBJDIR)shader.o
	gcc $(CFLAGS) -c src/game/render/vao.c -o $(OBJDIR)vao.o
	gcc $(CFLAGS) -c src/game/render/vbo.c -o $(OBJDIR)vbo.o
	gcc $(CFLAGS) -c src/game/render/ebo.c -o $(OBJDIR)ebo.o
	gcc $(CFLAGS) -c src/game/render/texture.c -o $(OBJDIR)texture.o
	gcc $(CFLAGS) -c src/game/render/block_data.c -o $(OBJDIR)block_data.o
	gcc $(CFLAGS) -c src/game/render/block.c -o $(OBJDIR)block.o
	gcc $(CFLAGS) -c src/game/render/chunk.c -o $(OBJDIR)chunk.o


$(OBJDIR)game.o: src/game/game.*
	gcc $(CFLAGS) -c src/game/game.c -o $(OBJDIR)game.o

$(OBJDIR)config.o: src/game/config/*
	gcc $(CFLAGS) -c src/game/config/config.c -o $(OBJDIR)config.o

$(OBJDIR)time.o: src/game/time/*
	gcc $(CFLAGS) -c src/game/time/time.c -o $(OBJDIR)time.o

$(OBJDIR)camera.o: src/game/camera/*
	gcc $(CFLAGS) -c src/game/camera/camera.c -o $(OBJDIR)camera.o

$(OBJDIR)dictionary.o: src/game/util/dictionary.*
	gcc $(CFLAGS) -c src/game/util/dictionary.c -o $(OBJDIR)dictionary.o

$(OBJDIR)list.o: src/game/util/list.*
	gcc $(CFLAGS) -c src/game/util/list.c -o $(OBJDIR)list.o

clean:
	rm $(OBJDIR)* out/program

run-last:
	./out/program-last
