BIN = dungeon
OBJS = dungeon.cpp shared-components.cpp generate-dungeon.cpp distance/distance.cpp distance/pathFindingHeap.cpp characters/Character.cpp characters/characterHeap.cpp descriptions/dice.cpp descriptions/monsterDescription.cpp descriptions/itemDescription.cpp

all: $(BIN)

$(BIN): $(OBJS)
	g++ -std=c++11 $(OBJS) -o $(BIN) -lcurses

 clean:
	rm -f dungeon *~
