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

JNIEXPORT jstring JNICALL Java_com_example_hellojni_HelloJni_showString(JNIEnv *env, jobject thiz, jint y, jint x) {
    char char_arr [2] = "B";
    int intChar = ((int)x + (int)y) % 10;
    sprintf(char_arr, "%d", intChar);
    return env->NewStringUTF(char_arr);
}


JNIEXPORT void JNICALL
Java_com_example_hellojni_HelloJni_main(JNIEnv *env, jobject thiz) {
//	readMonsterFile();
//	readObjectFile();
	int seed = time(NULL);
	srand(seed);

	bossKilled = false;
	int numMonsters = 10;
	int numItems = 15;
	initMaps();
	initRememberedMap();

	fogOfWarActivated = true;

	generateRandomFloor(numMonsters, numItems);

	free(rooms);
	free(upStairs);
	free(downStairs);

//	playGame();
}

#ifdef __cplusplus
}
#endif
