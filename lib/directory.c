#include "directory.h"

void directoryCheck() {
    struct stat st = { 0 };

    if (stat("db_rek", &st) == -1) {
        mkdir("db_rek");
    }

    if (stat("db_user", &st) == -1) {
        mkdir("db_user");
    }

    if (stat("rek_record", &st) == -1) {
        mkdir("rek_record");
    }
}
