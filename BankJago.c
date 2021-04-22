#include <stdio.h>
#include <stdlib.h>   
#include <string.h>
#include <time.h> 
#include "lib/rek_func.h"

struct tm* waktu;
struct account {
    int rank;
    char uname[20];
    char pass[20];
};

//Fungsi Pendukung
void landing();     //Logo 
void menu();        //Menu Utama
void akunDefault(); //Akun Default 
int login();        //Fungsi Login
int Hbaris();       //Fungsi Menghitung Baris Files
void clear();       //Define Command Clear terminal

//Fungsi Akun
void menuAkun();
void eAkun();
void addAkun();
void delAkun();

void menuTransaksi();

int session = -1;    //Id akun saat ini yang masuk
int sessionRank = 0; //Rank akun saat ini yang masuk   

int main() {
    int cek;
    //clear();

    akunDefault();

    landing();

    if (session == -1) {
        cek = login();
    }

    if (cek == 1 || session != -1) {
        menu();
    } else {
        printf("Username atau Password Salah!\n");
    }

    return 0;
}

//Fungsi Pendukung
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

void menu() {
    int mpilih;

    clear();
    landing();

    printf("\nMenu");
    printf("\n 1.Buat Rekening");
    printf("\n 2.Edit Rekening");
    printf("\n 3.Transaksi Rekening");
    printf("\n 4.Hapus Rekening");
    printf("\n 5.Edit Akun");
    printf("\n 6.Log Out");
    printf("\n 7.Keluar");
    printf("\nPilih : ");
    scanf("%d", &mpilih);

    switch (mpilih) {
    case 1:
        clear();
        landing();

        buatRek();
        main();
        break;
    case 2:
        clear();
        landing();

        editRek();
        main();
        break;
    case 3:
        menuTransaksi();
        break;
    case 4:
        clear();
        landing();
        
        hapusRek();
        main();
        break;
    case 5:
        menuAkun();
        break;
    case 6:
        session = -1;
        sessionRank = 0;
        main();
        break;
    case 7:
        break;
    default:
        menu();
        break;
    }
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

int login() {
    FILE* fp;

    struct account acc;
    char user[20];
    char pass[20];
    char file[] = "./db_user/name_pass.csv";

    int cocok = 0;
    int baris = Hbaris(file);

    fp = fopen(file, "r");

    printf("\nMasukan Username dan password");
    printf("\nUsername : ");
    scanf("\n");
    scanf("%[^\n]%*c", user);
    printf("Password : ");
    scanf("%[^\n]%*c", pass);

    for (int i = 0; i < baris && cocok == 0; i++) {
        fscanf(fp, "%d,%[^,],%[^\n]", &acc.rank, acc.uname, acc.pass);
        int cekU = strcmp(acc.uname, user);
        int cekP = strcmp(acc.pass, pass);

        if (cekU == 0 && cekP == 0) {
            cocok = 1;
            session = i;
            sessionRank = acc.rank;
        } else {
            cocok = 0;
        }
    }
    fclose(fp);
    return cocok;
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

//Fungsi Akun
void menuAkun() {
    int mpilih;

    clear();
    landing();

    printf("\nMenu Edit Akun");
    printf("\n 1.Edit Username & Password");
    printf("\n 2.Buat Akun");
    printf("\n 3.Hapus Akun");
    printf("\n 4.Keluar");
    printf("\nPilih : ");
    scanf("%d", &mpilih);

    switch (mpilih) {
    case 1:
        eAkun();
        main();
        break;
    case 2:
        addAkun();
        main();
        break;
    case 3:
        delAkun();
        main();
        break;
    case 4:
        menu();
        break;
    default:
        menuAkun();
        break;
    }
}

void eAkun() {
    FILE* fp, * fpsementara;

    struct account acc;
    char us[20];
    char ps[20];
    char file[] = "./db_user/name_pass.csv";

    fp = fopen(file, "r");
    fpsementara = fopen("./db_user/fpsementara.txt", "a+");

    int baris = Hbaris(file);

    clear();
    landing();

    printf("\nMasukan Username dan password baru");
    printf("\nUsername : ");
    scanf("\n");
    scanf("%[^\n]%*c", us);
    printf("Password : ");
    scanf("\n");
    scanf("%[^\n]%*c", ps);

    for (int i = 0; i < baris; i++) {
        fscanf(fp, "%d,%[^,],%[^\n]", &acc.rank, acc.uname, acc.pass);
        if (i == session) {
            fprintf(fpsementara, "%d,%s,%s\n", acc.rank, us, ps);
        } else {
            fprintf(fpsementara, "%d,%s,%s\n", acc.rank, acc.uname, acc.pass);
        }
    }

    fclose(fp);
    fclose(fpsementara);

    remove(file);
    if (rename("./db_user/fpsementara.txt", file) != 0) printf("\nGagal Mengedit");
}

void addAkun() {
    FILE* fp;
    struct account acc;
    char file[] = "./db_user/name_pass.csv";

    clear();
    landing();

    fp = fopen(file, "a+");

    if (sessionRank == 1) {
        printf("\nMasukan Username, password dan rank untuk akun baru (Rank 1 = admin , Rank 0 = user)");
        printf("\nUsername : ");
        scanf("\n");
        scanf("%[^\n]%*c", acc.uname);
        printf("Password : ");
        scanf("%[^\n]%*c", acc.pass);
        printf("Rank     : ");
        scanf("%d", &acc.rank);

        while (acc.rank < 0 || acc.rank > 1) {
            printf("Rank invalid!\n");
            printf("Rank     : ");
            scanf("%d", &acc.rank);
        }

        fprintf(fp, "%d,%s,%s\n", acc.rank, acc.uname, acc.pass);
    } else {
        printf("Anda tidak memiliki ijin untuk mengakses menu ini");
    }
    fclose(fp);
}

void delAkun() {
    FILE* fp, * fpsementara;
    char file[] = "./db_user/name_pass.csv";
    fp = fopen(file, "r");

    int baris = Hbaris(file);
    struct account acc;

    clear();
    landing();

    int pilihAkun;

    if (sessionRank == 1) {
        fpsementara = fopen("./db_user/fpsementara.txt", "a+");
        printf("------------------------- \n");
        printf(" User ID  | Username  \n");
        printf("------------------------- \n");
        for (int i = 0; i < baris; i++) {
            fscanf(fp, "%d,%[^,],%[^\n]", &acc.rank, acc.uname, acc.pass);
            printf("    %d     |   %s    \n", i, acc.uname);
        }
        printf("------------------------- \n");
        printf("Pilih : ");
        pilihAkun = cekId(file);

        for (int i = 0; i < baris; i++) {
            if (i != pilihAkun) {
                fscanf(fp, "%d,%[^,],%[^\n]", &acc.rank, acc.uname, acc.pass);
                fprintf(fpsementara, "%d,%s,%s\n", acc.rank, acc.uname, acc.pass);
            }
        }
    } else {
        printf("Anda tidak memiliki ijin untuk mengakses menu ini");
    }
    fclose(fp);

    remove(file);
    if (rename("./db_user/fpsementara.txt", file) != 0) printf("\nGagal Menghapus");
}

//Fungsi Pendukung Rekening
void menuTransaksi() {
    int mpilih;

    clear();
    landing();

    printf("\nMenu Transaksi");
    printf("\n 1.Cek Saldo");
    printf("\n 2.Tarik");
    printf("\n 3.Setor");
    printf("\n 4.Transfer");
    printf("\n 5.Keluar");
    printf("\nPilih : ");
    scanf("%d", &mpilih);

    switch (mpilih) {
    case 1:
        cekSaldo();
        break;
    case 2:
        tarik();
        break;
    case 3:
        setor();
        break;
    case 4:
        transfer();
        break;
    case 5:
        menu();
        break;
    default:
        menuTransaksi();
    }
}



void clear() {
#ifdef _WIN32
    std : system("cls");
#else
std: system("clear");
#endif
}