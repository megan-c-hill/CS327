BIN = dungeon
OBJS = dungeon.c shared-components.c generate-dungeon.c distance/distance.c distance/pathFindingHeap.c characters/monster.c characters/characterHeap.c

all: $(BIN)

$(BIN): $(OBJS)
	gcc $(OBJS) -o $(BIN)

 clean:
	rm -f dungeon *~
