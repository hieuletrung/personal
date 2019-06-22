// gcc JavaException.c -o libJavaException.so --shared -I /usr/lib/jvm/java-1.8.0-openjdk/include -I /usr/lib/jvm/java-1.8.0-openjdk/include/linux

#include "JavaException.h"

/*
 * Class:     JavaException
 * Method:    throwNativeException
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_JavaException_throwNativeException
  (JNIEnv *env, jobject obj) {
  jclass Exception = (*env)->FindClass(env, "java/lang/NullPointerException");
  (*env)->ThrowNew(env, Exception, "The passing object is NULL");
  (*env)->DeleteLocalRef(env, Exception);
}