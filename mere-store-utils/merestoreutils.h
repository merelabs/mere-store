#ifndef MERESTOREUTILS_H
#define MERESTOREUTILS_H

#include "merestoreutilsglobal.h"
#include "mere/store/merestoreunit.h"

class MERE_STORE_UTILS_LIBSPEC MereStoreUtils
{
public:
     MappedStoreUnit toMap(Unit unit);
//    static MereStoreUnit fromMap(const MappedStoreUnit &map);

};

#endif // MERESTOREUTILS_H
