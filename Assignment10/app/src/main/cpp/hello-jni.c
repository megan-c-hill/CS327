#include <string.h>
#include <jni.h>
#include <stdbool.h>
#include <stdio.h>

JNIEXPORT jstring JNICALL
Java_com_example_hellojni_HelloJni_showString(JNIEnv *env, jobject thiz, jint y, jint x) {
    char char_arr [2] = "B";
    int intChar = ((int)x + (int)y) % 10;
    sprintf(char_arr, "%d", intChar);
    return (*env)->NewStringUTF(env, char_arr);
}
