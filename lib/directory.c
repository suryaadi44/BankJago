#include "directory.h"

void directoryCheck() {
    struct stat st = { 0 };

    if (stat("../db_rek", &st) == -1) {
        mkdir("../db_rek");
    }
}
