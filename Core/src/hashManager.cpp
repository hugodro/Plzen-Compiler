/**************************************************
* File: hashManager.cc.
* Desc: Implementation of the AkHashManager class.
* Module: AkraLog : JavaKit.
* Rev: 29 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/


#include "hashBucket.h"
#include "hashManager.h"


unsigned AkHashManager::smallPrimes[256]= {
    3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
    127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
    283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
    353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
    467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
    547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
    607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
    661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
    739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
    811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
    877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
    947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013,
    1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069,
    1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151,
    1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223,
    1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291,
    1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373,
    1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451,
    1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
    1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583,
    1597, 1601, 1607, 1609, 1613, 1619, 1621
};


unsigned AkHashManager::bigPrimes[256]= {
    996841, 996847, 996857, 996859, 996871, 996881, 996883, 996887, 996899, 996953,
    996967, 996973, 996979, 997001, 997013, 997019, 997021, 997037, 997043, 997057,
    997069, 997081, 997091, 997097, 997099, 997103, 997109, 997111, 997121, 997123,
    997141, 997147, 997151, 997153, 997163, 997201, 997207, 997219, 997247, 997259,
    997267, 997273, 997279, 997307, 997309, 997319, 997327, 997333, 997343, 997357,
    997369, 997379, 997391, 997427, 997433, 997439, 997453, 997463, 997511, 997541,
    997547, 997553, 997573, 997583, 997589,997597, 997609, 997627, 997637, 997649,
    997651, 997663, 997681, 997693, 997699, 997727,997739, 997741, 997751, 997769,
    997783, 997793, 997807, 997811, 997813, 997877, 997879,997889, 997891, 997897,
    997933, 997949, 997961, 997963, 997973, 997991, 998009, 998017,998027, 998029,
    998069, 998071, 998077, 998083, 998111, 998117, 998147, 998161, 998167,998197,
    998201, 998213, 998219, 998237, 998243, 998273, 998281, 998287, 998311, 998329,
    998353, 998377, 998381, 998399, 998411, 998419, 998423, 998429, 998443, 998471,
    998497,998513, 998527, 998537, 998539, 998551, 998561, 998617, 998623, 998629,
    998633, 998651,998653, 998681, 998687, 998689, 998717, 998737, 998743, 998749,
    998759, 998779, 998813,998819, 998831, 998839, 998843, 998857, 998861, 998897,
    998909, 998917, 998927, 998941,998947, 998951, 998957, 998969, 998983, 998989,
    999007, 999023, 999029, 999043, 999049,999067, 999083, 999091, 999101, 999133,
    999149, 999169, 999181, 999199, 999217, 999221,999233, 999239, 999269, 999287,
    999307, 999329, 999331, 999359, 999371, 999377, 999389,999431, 999433, 999437,
    999451, 999491, 999499, 999521, 999529, 999541, 999553, 999563,999599, 999611,
    999613, 999623, 999631, 999653, 999667, 999671, 999683, 999721, 999727,999749,
    999763, 999769, 999773, 999809, 999853, 999863, 999883, 999907, 999917, 999931,
    999953, 999959, 999961, 999979, 999983, 1000003, 1000033, 1000037, 1000039, 1000081,
    1000099, 1000117, 1000121, 1000133, 1000151, 1000159, 1000171, 1000183, 1000187, 1000193,
    1000199, 1000211, 1000213, 1000231, 1000249, 1000253
};


unsigned int AkHashManager::stringHashOne(char *aKey)
{
    unsigned int result= ((*aKey == '\0') ? 0 : 1);

    while (*aKey != '\0') {
	result+= bigPrimes[(unsigned int)*aKey];
	aKey++;
    }
    return result;
}


unsigned int AkHashManager::stringHashTwo(char *aKey)
{
    unsigned int result= ((*aKey == '\0') ? 0 : 1);

    while (*aKey != '\0') {
	result+= bigPrimes[255 - (unsigned int)*aKey];
	aKey++;
    }
    return result;
}


AkHashManager::AkHashManager(void)
{
    hashOne= stringHashOne;
    hashTwo= stringHashTwo;
    bucketSize= 2039;		// Maximal prime smaller than 2048.
    nbrBuckets= 1;
    buckets= new AkHashBucket*[1];
    buckets[0]= new AkHashBucket(bucketSize);
}


AkHashManager::~AkHashManager(void)
{
    delete buckets[0];
    delete buckets;
}


bool AkHashManager::findKey(char *aKey)
{
// TODO.
    return false;
}


bool AkHashManager::addUniqueItem(char *aKey, void *aValue, AkHashElement **resultElement)
{
    AkHashBucket *targetBuck;
    unsigned int elementIndex;
    unsigned int bucketIndex;
    bool gotBuckIndex= false;

    // Compute the hash.
    elementIndex= hashOne(aKey) % bucketSize;

    // Check for membership.
    if (nbrBuckets > 1) {
	bucketIndex= hashTwo(aKey);
	targetBuck= buckets[bucketIndex % nbrBuckets];
	gotBuckIndex= true;
    }
    else {
	targetBuck= buckets[0];
    }

    if (!targetBuck->locateKeyAt(aKey, elementIndex)) {
	    // Add at given hash position if not there.
	if (!gotBuckIndex) {
	    bucketIndex= hashTwo(aKey);
	}
	if (targetBuck->addElementAt(aKey, aValue, elementIndex, bucketIndex, resultElement)) {
	    // Deal with restructuration of buckets where there is too much collisions.
	}
    }
    else {
	    // Key already in bucket, retuse to overwrite.
	return false;		// Warning: quick exit.
    }

    return true;
}


void *AkHashManager::getItem(char *aKey, bool &indicator)
{
    AkHashBucket *targetBuck;
    unsigned int elementIndex;
    unsigned int bucketIndex;
    bool gotBuckIndex= false;

    // Compute the hash.
    elementIndex= hashOne(aKey) % bucketSize;

    // Check for membership.
    if (nbrBuckets > 1) {
	bucketIndex= hashTwo(aKey);
	targetBuck= buckets[bucketIndex % nbrBuckets];
	gotBuckIndex= true;
    }
    else {
	targetBuck= buckets[0];
    }

    return targetBuck->getItemAt(aKey, elementIndex, indicator);
}

