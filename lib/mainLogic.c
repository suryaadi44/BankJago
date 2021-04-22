#include "mainLogic.h" 

int session = -1;
int sessionRank = 0;

void landing() {
    time_t mentah;
    struct tm* waktu;
    time(&mentah);
    waktu = localtime(&mentah);

    printf("==========================================================================================\n");
    printf("|  /$$$$$$$                      /$$                /$$$$$                               |\n");
    printf("| | $$__  $$                    | $$               |__  $$                               |\n");
    printf("| | $$    $$  /$$$$$$  /$$$$$$$ | $$   /$$            | $$  /$$$$$$   /$$$$$$   /$$$$$$  |\n");
    printf("| | $$$$$$$  |____  $$| $$__  $$| $$  /$$/            | $$ |____  $$ /$$__  $$ /$$__  $$ |\n");
    printf("| | $$__  $$  /$$$$$$$| $$    $$| $$$$$$/        /$$  | $$  /$$$$$$$| $$    $$| $$    $$ |\n");
    printf("| | $$    $$ /$$__  $$| $$  | $$| $$_  $$       | $$  | $$ /$$__  $$| $$  | $$| $$  | $$ |\n");
    printf("| | $$$$$$$/|  $$$$$$$| $$  | $$| $$    $$      |  $$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$/ |\n");
    printf("| |_______/   _______/|__/  |__/|__/   __/        ______/   _______/  ____  $$  ______/  |\n");
    printf("|                                                                    /$$    $$           |\n");
    printf("|                                                                   |  $$$$$$/           |\n");
    printf("|                                                                     ______/            |\n");
    printf("|                                   %02d/%02d/%d %02d:%02d:%02d                                  |\n", waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, waktu->tm_hour, waktu->tm_min, waktu->tm_sec);
    printf("==========================================================================================\n");
}

void akunDefault() {
    FILE* f, * rek;

    f = fopen("./db_user/name_pass.csv", "a+");
    rek = fopen("./db_rek/data_rek.csv", "a+");

    int baris = Hbaris("./db_user/name_pass.csv");

    if (baris == 0) {
        fprintf(f, "%d,%s,%s\n", 1, "admin", "admin");
    }
    fclose(rek);
    fclose(f);
}

int Hbaris(char bacaBaris[]) {
    FILE* cek;
    int i = 0;
    int cs;

    cek = fopen(bacaBaris, "r");
    while (!feof(cek)) {              //Loop hingga EOF  1
        cs = fgetc(cek);               //simpan stream char ke c
        if (cs == '\n') i++;         //Jika dideteksi \n , tambah i
    }
    fclose(cek);
    return i;
}

void clear() {
#ifdef _WIN32
    std : system("cls");
#else
std: system("clear");
#endif
}