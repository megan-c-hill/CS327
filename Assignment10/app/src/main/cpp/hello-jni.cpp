#include <string.h>
#include <jni.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "characters/Character.h"
#include "shared-components.h"
#include "generate-dungeon.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_example_hellojni_HelloJni_main(JNIEnv *jenv, jobject thiz) {
	readMonsterFile();
//	readObjectFile();
	int seed = time(NULL);
	srand(seed);

	bossKilled = false;
	int numMonsters = 10;
	int numItems = 15;
	initMaps();
	initRememberedMap();

	fogOfWarActivated = false;

	generateRandomFloor(numMonsters, numItems);

	env = jenv;
	obj = thiz;

//	playGame();
    printFullDungeon();
	free(rooms);
	free(upStairs);
	free(downStairs);
}

#ifdef __cplusplus
}
#endif
