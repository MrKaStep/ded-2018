//
// Created by step on 20.09.18.
//

#include "file.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdexcept>

namespace Util {

size_t GetFileSize(const char* filename) {
    struct stat fileStat;
    if (stat(filename, &fileStat) == -1) {
        throw std::runtime_error("Unable to read file stat");
    }

    return fileStat.st_size;
}

}