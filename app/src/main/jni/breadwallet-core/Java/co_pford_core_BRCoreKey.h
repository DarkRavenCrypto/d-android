/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class co_pford_core_BRCoreKey */

#ifndef _Included_co_pford_core_BRCoreKey
#define _Included_co_pford_core_BRCoreKey
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    getSecret
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_co_pford_core_BRCoreKey_getSecret
(JNIEnv *, jobject);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    getPubKey
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_co_pford_core_BRCoreKey_getPubKey
(JNIEnv *, jobject);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    getCompressed
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_co_pford_core_BRCoreKey_getCompressed
(JNIEnv *, jobject);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    getPrivKey
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_co_pford_core_BRCoreKey_getPrivKey
(JNIEnv *, jobject);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    getSeedFromPhrase
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_co_pford_core_BRCoreKey_getSeedFromPhrase
(JNIEnv *, jclass, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    getAuthPrivKeyForAPI
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_co_pford_core_BRCoreKey_getAuthPrivKeyForAPI
(JNIEnv *, jclass, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    getAuthPublicKeyForAPI
 * Signature: ([B)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_co_pford_core_BRCoreKey_getAuthPublicKeyForAPI
(JNIEnv *, jclass, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    decryptBip38Key
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_co_pford_core_BRCoreKey_decryptBip38Key
(JNIEnv *, jclass, jstring, jstring);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    createJniCoreKey
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_co_pford_core_BRCoreKey_createJniCoreKey
(JNIEnv *, jclass);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    createCoreKeyForBIP32
 * Signature: ([BJJ)J
 */
JNIEXPORT jlong JNICALL Java_co_pford_core_BRCoreKey_createCoreKeyForBIP32
(JNIEnv *, jclass, jbyteArray, jlong, jlong);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    setPrivKey
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_co_pford_core_BRCoreKey_setPrivKey
(JNIEnv *, jobject, jstring);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    setSecret
 * Signature: ([BZ)Z
 */
JNIEXPORT jboolean JNICALL Java_co_pford_core_BRCoreKey_setSecret
(JNIEnv *, jobject, jbyteArray, jboolean);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    compactSign
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_co_pford_core_BRCoreKey_compactSign
(JNIEnv *, jobject, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    createKeyRecoverCompactSign
 * Signature: ([B[B)J
 */
JNIEXPORT jlong JNICALL Java_co_pford_core_BRCoreKey_createKeyRecoverCompactSign
(JNIEnv *, jclass, jbyteArray, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    encryptNative
 * Signature: ([B[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_co_pford_core_BRCoreKey_encryptNative
(JNIEnv *, jobject, jbyteArray, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    decryptNative
 * Signature: ([B[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_co_pford_core_BRCoreKey_decryptNative
(JNIEnv *, jobject, jbyteArray, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    encryptUsingSharedSecret
 * Signature: ([B[B[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_co_pford_core_BRCoreKey_encryptUsingSharedSecret
(JNIEnv *, jobject, jbyteArray, jbyteArray, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    decryptUsingSharedSecret
 * Signature: ([B[B[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_co_pford_core_BRCoreKey_decryptUsingSharedSecret
(JNIEnv *, jobject, jbyteArray, jbyteArray, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    createPairingKey
 * Signature: ([B)J
 */
JNIEXPORT jlong JNICALL Java_co_pford_core_BRCoreKey_createPairingKey
(JNIEnv *, jobject, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    address
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_co_pford_core_BRCoreKey_address
(JNIEnv *, jobject);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    addressLegacy
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_co_pford_core_BRCoreKey_addressLegacy
  (JNIEnv *, jobject);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    isValidBitcoinPrivateKey
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_co_pford_core_BRCoreKey_isValidBitcoinPrivateKey
(JNIEnv *, jclass, jstring);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    isValidBitcoinBIP38Key
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_co_pford_core_BRCoreKey_isValidBitcoinBIP38Key
(JNIEnv *, jclass, jstring);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    encodeSHA256
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_co_pford_core_BRCoreKey_encodeSHA256
(JNIEnv *, jclass, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    encodeSHA256Double
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_co_pford_core_BRCoreKey_encodeSHA256Double
(JNIEnv *, jclass, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    encodeBase58
 * Signature: ([B)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_co_pford_core_BRCoreKey_encodeBase58
(JNIEnv *, jclass, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    decodeBase58
 * Signature: (Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_co_pford_core_BRCoreKey_decodeBase58
(JNIEnv *, jclass, jstring);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    sign
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_co_pford_core_BRCoreKey_sign
(JNIEnv *, jobject, jbyteArray);

/*
 * Class:     co_pford_core_BRCoreKey
 * Method:    verify
 * Signature: ([B[B)Z
             */
JNIEXPORT jboolean JNICALL Java_co_pford_core_BRCoreKey_verify
(JNIEnv *, jobject, jbyteArray, jbyteArray);

#ifdef __cplusplus
}
#endif
#endif