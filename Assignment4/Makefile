BIN = dungeon
OBJS = dungeon.c shared-components.c generate-dungeon.c distance.c heap.c

all: $(BIN) etags

$(BIN): $(OBJS)
	gcc $(OBJS) -o $(BIN)

 clean:
	rm -f dungeon *~
