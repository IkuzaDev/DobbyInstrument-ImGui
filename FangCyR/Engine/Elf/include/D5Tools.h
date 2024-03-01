//
// Created by Ikuzadev on 2023/2/10.
//

#ifndef TESTAPPLICATION_ENHANCED_DLCLOSE_H
#define TESTAPPLICATION_ENHANCED_DLCLOSE_H
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

namespace ElfTools{
    int d5close(void *handle);
    void *d5open(const char *path, int flags);
    void *d5sym(void *handle, const char *name);
}
#endif //TESTAPPLICATION_ENHANCED_DLCLOSE_H


