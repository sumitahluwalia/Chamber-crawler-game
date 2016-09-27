CXX = g++ 
CXXFLAGS = -Wall -MMD -g3 -DGAMETYPE=2
EXEC = cc3k
OBJECTS = main.o dungeongrid.o chamber.o gameobject.o verticalwall.o horizontalwall.o floortile.o doorway.o passage.o player.o drow.o vampire.o troll.o goblin.o stairs.o potion.o restorehealth.o boostatk.o boostdef.o poisonhealth.o woundatk.o wounddef.o gold.o smallhoard.o normalhoard.o merchanthoard.o dragonhoard.o enemy.o human.o dwarf.o elf.o orc.o merchant.o halfling.o dragon.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lncurses

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
