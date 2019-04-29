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
Java_com_example_hellojni_HelloJni_setup(JNIEnv *jenv, jobject thiz) {
    readMonsterFile();
    readObjectFile();
    int seed = time(NULL);
    srand(seed);

    bossKilled = false;
    int numMonsters = 8;
    int numItems = 15;
    initMaps();
    initRememberedMap();

    fogOfWarActivated = true;

    generateRandomFloor(numMonsters, numItems);

    env = jenv;
    obj = thiz;
}


JNIEXPORT void JNICALL
Java_com_example_hellojni_HelloJni_cleanup(JNIEnv *jenv, jobject thiz) {
    free(rooms);
    free(upStairs);
    free(downStairs);

    fogOfWarActivated = false;
    printFullDungeon();

    if (playerIsInHeap(playerQueue)) {
//		mvaddstr(0, 0, EMPTY_ROW_TEXT);
		drawString(0, 0, "You Won!");
//		refresh();
//		usleep(5000000);
        return;
    } else {
//		mvaddstr(0, 0, EMPTY_ROW_TEXT);
		drawString(0, 0, "You Lose!");
//		refresh();
//		usleep(5000000);
        return;
    }
}


JNIEXPORT void JNICALL
Java_com_example_hellojni_HelloJni_playGame(JNIEnv *jenv, jobject thiz) {
    playGame();
}


JNIEXPORT jint JNICALL
Java_com_example_hellojni_HelloJni_isOver(JNIEnv *jenv, jobject thiz) {
    return playerIsInHeap(playerQueue) && !bossKilled;
}

#ifdef __cplusplus
}
#endif
