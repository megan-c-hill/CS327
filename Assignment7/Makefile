BIN = dungeon
OBJS = dungeon.cpp shared-components.cpp generate-dungeon.cpp distance/distance.cpp distance/pathFindingHeap.cpp characters/Character.cpp characters/characterHeap.cpp descriptions/dice.cpp descriptions/monsterDescription.cpp

all: $(BIN)

$(BIN): $(OBJS)
	g++ $(OBJS) -o $(BIN) -lcurses

 clean:
	rm -f dungeon *~
