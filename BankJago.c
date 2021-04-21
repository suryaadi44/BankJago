#include <stdio.h>
#include <stdlib.h>   
#include <string.h>
#include <time.h> 

struct tm* waktu;
struct account {
    int rank;
    char uname[20];
    char pass[20];
};
struct rek {
    int id;
    long norek;
    char namaDepan[20];
    char namaBelakang[20];
    long isi;
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

//Fungsi Rekening
void buatRek();
void hapusRek();
void editRek();

//Fungsi Pendukung Rekening
void menuTransaksi();
void pauseRek();
void printRek();
int cekId();
void riwayat();

//Fungsi Transaksi antar Rekening
void cekSaldo();
void tarik();
void setor();
void transfer();

int session = -1;    //Id akun saat ini yang masuk
int sessionRank = 0; //Rank akun saat ini yang masuk   

int main() {
    int cek;
    clear();

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
        buatRek();
        main();
        break;
    case 2:
        editRek();
        main();
        break;
    case 3:
        menuTransaksi();
        break;
    case 4:
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

void pauseRek() {
    char lanjut;
    printf("\nApakah anda ingin melanjutkan? (y/t) :");
    scanf("\n");
    scanf("%c", &lanjut);
    if (lanjut == 'y') {
        menuTransaksi();
    }
}

void printRek() {
    FILE* fp;
    struct rek nasabah;
    char file[] = "./db_rek/data_rek.csv";
    int baris = Hbaris(file);

    fp = fopen(file, "r");
    printf("\n----------------------------------- \n");
    printf("  Rek ID  |  Nama  \n");
    printf("-----------------------------------\n");
    for (int i = 0; i < baris; i++) {
        fscanf(fp, "%d,%ld,%[^,],%[^,],%ld", &nasabah.id, &nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, &nasabah.isi);
        printf("    %d     |   %s %s   \n", i, nasabah.namaDepan, nasabah.namaBelakang);
    }
    printf("----------------------------------- \n");
    fclose(fp);
}

int cekId(char file[]) {
    int id = -1;
    int baris = Hbaris(file);

    scanf("%d", &id);

    while (id > baris || id < 0) {
        printf("\nID Tidak Ditemukan");
        printf("\nSilakan Masukan ID Lagi :");
        scanf("%d", &id);
    }

    return id;
}

void riwayat(long norek, int jenis, long jumlahTx, long jumlahSaldo) {
    FILE* fp, * logall;

    time_t mentah;
    struct tm* waktu;
    time(&mentah);
    waktu = localtime(&mentah);

    char convert[9];
    char* format = ".csv";
    char* dir = "./rek_record/";
    snprintf(convert, 9, "%ld", norek);

    int mem = strlen(convert) + strlen(format) + strlen(dir);
    char file[mem];
    char fileLog[] = "./db_rek/riwayat_transaksi.csv";

    strcpy(file, dir);
    strcat(file, convert);
    strcat(file, format);

    logall = fopen(fileLog, "a");
    fp = fopen(file, "a");

    int barisLog = Hbaris(fileLog);
    int baris = Hbaris(file);

    if (baris == 0) {
        fprintf(fp, "No,Waktu,Jenis Transaksi,Jumlah Transaksi,Saldo\n");
        fclose(fp);
        fp = fopen(file, "a");
        baris = Hbaris(file);
    }

    if (barisLog == 0) {
        fprintf(logall, "No,Waktu,No.Rekening,Jenis Transaksi,Jumlah Transaksi,Saldo\n");
        fclose(logall);
        logall = fopen(fileLog, "a");
        barisLog = Hbaris(fileLog);
    }

    switch (jenis) {
    case 1:
        fprintf(fp, "%d,%02d:%02d:%02d-%02d/%02d/%d,TARIK,%ld,%ld\n", baris, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, jumlahTx, jumlahSaldo);
        fprintf(logall, "%d,%02d:%02d:%02d-%02d/%02d/%d,%ld,TARIK,%ld,%ld\n", barisLog, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, norek, jumlahTx, jumlahSaldo);
        break;
    case 2:
        fprintf(fp, "%d,%02d:%02d:%02d-%02d/%02d/%d,SETOR,%ld,%ld\n", baris, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, jumlahTx, jumlahSaldo);
        fprintf(logall, "%d,%02d:%02d:%02d-%02d/%02d/%d,%ld,SETOR,%ld,%ld\n", barisLog, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, norek, jumlahTx, jumlahSaldo);
        break;
    case 3:
        fprintf(fp, "%d,%02d:%02d:%02d-%02d/%02d/%d,TRANSFER KELUAR,%ld,%ld\n", baris, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, jumlahTx, jumlahSaldo);
        fprintf(logall, "%d,%02d:%02d:%02d-%02d/%02d/%d,%ld,TRANSFER KELUAR,%ld,%ld\n", barisLog, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, norek, jumlahTx, jumlahSaldo);
        break;
    case 4:
        fprintf(fp, "%d,%02d:%02d:%02d-%02d/%02d/%d,TRANSFER MASUK,%ld,%ld\n", baris, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, jumlahTx, jumlahSaldo);
        fprintf(logall, "%d,%02d:%02d:%02d-%02d/%02d/%d,%ld,TRANSFER MASUK,%ld,%ld\n", barisLog, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, norek, jumlahTx, jumlahSaldo);
        break;
    case 5:
        fprintf(fp, "%d,%02d:%02d:%02d-%02d/%02d/%d,REKENING BARU,%ld,%ld\n", baris, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, jumlahTx, jumlahSaldo);
        fprintf(logall, "%d,%02d:%02d:%02d-%02d/%02d/%d,%ld,REKENING BARU,%ld,%ld\n", barisLog, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, norek, jumlahTx, jumlahSaldo);
        break;
    case 6:
        fprintf(fp, "%d,%02d:%02d:%02d-%02d/%02d/%d,HAPUS REKENING,%ld,%ld\n", baris, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, jumlahTx, jumlahSaldo);
        fprintf(logall, "%d,%02d:%02d:%02d-%02d/%02d/%d,%ld,HAPUS REKENING,%ld,%ld\n", barisLog, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, norek, jumlahTx, jumlahSaldo);
        break;
    deafult:
        fprintf(fp, "%d,%02d:%02d:%02d-%02d/%02d/%d,ERROR,%ld,%ld\n", baris, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, jumlahTx, jumlahSaldo);
        fprintf(logall, "%d,%02d:%02d:%02d-%02d/%02d/%d,%ld,ERROR,%ld,%ld\n", barisLog, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, norek, jumlahTx, jumlahSaldo);
        break;
    }
    fclose(fp);
    fclose(logall);
}

//Fungsi Rekening
void buatRek() {
    FILE* fp;
    struct rek nasabah;
    char file[] = "./db_rek/data_rek.csv";

    fp = fopen(file, "a+");

    clear();
    landing();

    printf("\nMasukan Data untuk Rekening Baru ");
    printf("\nNama Depan    : ");
    scanf("\n");
    scanf("%[^\n]%*c", nasabah.namaDepan);
    printf("Nama Belakang : ");
    scanf("%[^\n]%*c", nasabah.namaBelakang);
    printf("Setoran Awal  : ");
    scanf("%ld", &nasabah.isi);

    nasabah.norek = (long)(10000000 + Hbaris(file));
    nasabah.id = Hbaris(file);

    fprintf(fp, "%d,%ld,%s,%s,%ld\n", nasabah.id, nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, nasabah.isi);
    riwayat(nasabah.norek, 5, nasabah.isi, nasabah.isi);
    fclose(fp);
}

void editRek() {
    FILE* fp, * fpsementara;

    char file[] = "./db_rek/data_rek.csv";
    fp = fopen(file, "r");
    fpsementara = fopen("./db_rek/fpsementara.csv", "a+");

    int baris = Hbaris(file);

    struct rek nasabah;
    char namaDepanBaru[20];
    char namaBelakangBaru[20];

    clear();
    landing();

    printRek();
    printf("Pilih User Mana yang Ingin Diganti Dengan Mengetik User ID-nya: ");
    int pilihganti = cekId(file);

    printf("Ketik Nama Depan Baru User: ");
    scanf("\n");
    scanf("%[^\n]%*c", namaDepanBaru);
    printf("Ketik Nama Belakang Baru: ");
    scanf("\n");
    scanf("%[^\n]%*c", namaBelakangBaru);

    for (int i = 0; i < baris; i++) {
        fscanf(fp, "%d,%ld,%[^,],%[^,],%ld", &nasabah.id, &nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, &nasabah.isi);
        if (i == pilihganti) {
            fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah.id, nasabah.norek, namaDepanBaru, namaBelakangBaru, nasabah.isi);
        } else {
            fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah.id, nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, nasabah.isi);
        }
    }
    fclose(fp);
    fclose(fpsementara);

    remove(file);
    if (rename("./db_rek/fpsementara.csv", file) != 0) printf("\nGagal Mengedit");
}

void hapusRek() {
    FILE* fp, * fpsementara;

    char file[] = "./db_rek/data_rek.csv";
    struct rek nasabah;
    fp = fopen(file, "r");
    fpsementara = fopen("./db_rek/fpsementara.csv", "a+");
    int baris = Hbaris(file);

    clear();
    landing();
    printRek();

    printf("Pilih User Mana yang Ingin Dihapus Dengan Mengetik User ID-nya: ");
    scanf("\n");
    int pilihganti = cekId(file);

    for (int i = 0; i < baris; i++) {
        fscanf(fp, "%d,%ld,%[^,],%[^,],%ld", &nasabah.id, &nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, &nasabah.isi);
        printf("%d,%ld,%s,%s,%ld\n", nasabah.id, nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, nasabah.isi);
        if (i != pilihganti) {
            fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah.id, nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, nasabah.isi);
        } else {
            fprintf(fpsementara, "%d,%d,%s,%s,%d\n", -1, 0, "Akun ini", "Telah Dihapus", 0);
            riwayat(nasabah.norek, 6, nasabah.isi, 0);
        }
    }
    fclose(fp);
    fclose(fpsementara);

    remove(file);
    if (rename("./db_rek/fpsementara.csv", file) != 0) printf("\nGagal Mengedit");
}

//Fungsi Transaksi antar Rekening
void cekSaldo() {
    FILE* fp;

    struct rek nasabah;

    char file[] = "./db_rek/data_rek.csv";
    fp = fopen(file, "r");

    int baris = Hbaris(file);

    clear();
    landing();

    printRek();

    printf("Pilih ID : ");
    int rek = cekId(file);

    for (int i = 0; i < baris; i++) {
        fscanf(fp, "%d,%ld,%[^,],%[^,],%ld", &nasabah.id, &nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, &nasabah.isi);
        if (i == rek) {
            if (nasabah.id == -1) printf("Akun Telah Dihapus\n");
            else printf("Saldo    : %ld", nasabah.isi);
        }
    }
    pauseRek();
}

void tarik() {
    FILE* fp, * fpsementara;

    struct rek nasabah;
    char file[] = "./db_rek/data_rek.csv";
    fp = fopen(file, "r");
    fpsementara = fopen("./db_rek/fpsementara.csv", "a+");

    int baris = Hbaris(file);
    long tarik;

    clear();
    landing();

    printRek();

    printf("Pilih ID     : ");
    int rek = cekId(file);

    printf("Banyak Tarik : ");
    scanf("%ld", &tarik);

    for (int i = 0; i < baris; i++) {
        fscanf(fp, "%d,%ld,%[^,],%[^,],%ld", &nasabah.id, &nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, &nasabah.isi);
        if (i == rek) {
            if (nasabah.id == -1) {
                printf("Akun Telah Dihapus\n");
                fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah.id, nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, nasabah.isi);
            } else {
                if (nasabah.isi < tarik) {
                    printf("\nSaldo Tidak Mencukupi");
                    printf("\nSaldo saat ini adalah: %ld", nasabah.isi);
                    fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah.id, nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, nasabah.isi);
                } else {
                    fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah.id, nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, (nasabah.isi - tarik));
                    riwayat(nasabah.norek, 1, tarik, (nasabah.isi - tarik));
                }
            }
        } else {
            fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah.id, nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, nasabah.isi);
        }
    }
    fclose(fp);
    fclose(fpsementara);

    remove("./db_rek/data_rek.csv");
    if (rename("./db_rek/fpsementara.csv", file) != 0) printf("\nGagal Melakukan Transaksi");

    pauseRek();
}

void setor() {
    FILE* fp, * fpsementara;

    struct rek nasabah;
    char file[] = "./db_rek/data_rek.csv";
    fp = fopen(file, "r");
    fpsementara = fopen("./db_rek/fpsementara.csv", "a+");

    int baris = Hbaris(file);
    long setoran;

    clear();
    landing();

    printRek();

    printf("Pilih ID     : ");
    int rek = cekId(file);

    printf("Banyak Setor : ");
    scanf("%ld", &setoran);

    for (int i = 0; i < baris; i++) {
        fscanf(fp, "%d,%ld,%[^,],%[^,],%ld", &nasabah.id, &nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, &nasabah.isi);
        if (i == rek) {
            if (nasabah.id == -1) {
                fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah.id, nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, nasabah.isi);
                printf("Akun Telah Dihapus\n");
            } else {
                riwayat(nasabah.norek, 2, setoran, (nasabah.isi + setoran));
                fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah.id, nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, (nasabah.isi + setoran));
            }
        } else {
            fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah.id, nasabah.norek, nasabah.namaDepan, nasabah.namaBelakang, nasabah.isi);
        }
    }

    fclose(fp);
    fclose(fpsementara);

    remove(file);
    if (rename("./db_rek/fpsementara.csv", file) != 0) printf("\nGagal Melakukan Transaksi");

    pauseRek();
}

void transfer() {
    FILE* fp, * fpsementara;

    struct rek nasabah[3];
    char file[] = "./db_rek/data_rek.csv";
    fp = fopen(file, "r");
    fpsementara = fopen("./db_rek/fpsementara.csv", "a+");

    int baris = Hbaris(file);
    int statusTf = 0;
    int refund = 0;
    long transfer;

    clear();
    landing();

    printRek();

    printf("Pilih ID Asal   : ");
    int rekAsal = cekId(file);

    printf("Pilih ID Tujuan : ");
    int rekTujuan = cekId(file);

    printf("Banyak Transfer : ");
    scanf("%ld", &transfer);

    for (int i = 0; i < baris; i++) {
        fscanf(fp, "%d,%ld,%[^,],%[^,],%ld", &nasabah[0].id, &nasabah[0].norek, nasabah[0].namaDepan, nasabah[0].namaBelakang, &nasabah[0].isi);
        if (i == rekAsal) {
            if (nasabah[0].id == -1) {
                printf("Akun Telah Dihapus\n");
                fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah[0].id, nasabah[0].norek, nasabah[0].namaDepan, nasabah[0].namaBelakang, nasabah[0].isi);
                statusTf = 0;
            } else {
                if (nasabah[0].isi < transfer) {
                    printf("\nSaldo Tidak Mencukupi");
                    printf("\nSaldo saat ini adalah: %ld", nasabah[0].isi);
                    statusTf = 0;
                    fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah[0].id, nasabah[0].norek, nasabah[0].namaDepan, nasabah[0].namaBelakang, nasabah[0].isi);
                } else {
                    fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah[0].id, nasabah[0].norek, nasabah[0].namaDepan, nasabah[0].namaBelakang, (nasabah[0].isi - transfer));

                    nasabah[2].norek = nasabah[0].norek;
                    nasabah[2].isi = nasabah[0].isi - transfer;

                    statusTf = 1;
                }
            }
        } else {
            fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah[0].id, nasabah[0].norek, nasabah[0].namaDepan, nasabah[0].namaBelakang, nasabah[0].isi);
        }
    }

    fclose(fp);
    fclose(fpsementara);

    if (statusTf == 1) {
        FILE* fpsementara2;

        fpsementara = fopen("./db_rek/fpsementara.csv", "r");
        fpsementara2 = fopen("./db_rek/fpsementara2.csv", "a+");

        for (int i = 0; i < baris; i++) {
            fscanf(fpsementara, "%d,%ld,%[^,],%[^,],%ld", &nasabah[1].id, &nasabah[1].norek, nasabah[1].namaDepan, nasabah[1].namaBelakang, &nasabah[1].isi);
            if (i == rekTujuan) {
                if (nasabah[1].id == -1) {
                    printf("Akun Telah Dihapus\n");
                    fprintf(fpsementara, "%d,%ld,%s,%s,%ld\n", nasabah[1].id, nasabah[1].norek, nasabah[1].namaDepan, nasabah[1].namaBelakang, nasabah[1].isi);
                    refund = 1;
                } else {
                    fprintf(fpsementara2, "%d,%ld,%s,%s,%ld\n", nasabah[1].id, nasabah[1].norek, nasabah[1].namaDepan, nasabah[1].namaBelakang, (nasabah[1].isi + transfer));

                    riwayat(nasabah[2].norek, 3, transfer, nasabah[2].isi);
                    riwayat(nasabah[1].norek, 4, transfer, (nasabah[1].isi + transfer));
                }
            } else {
                fprintf(fpsementara2, "%d,%ld,%s,%s,%ld\n", nasabah[1].id, nasabah[1].norek, nasabah[1].namaDepan, nasabah[1].namaBelakang, nasabah[1].isi);
            }
        }
        fclose(fpsementara);
        fclose(fpsementara2);

        if (refund == 0) {
            remove("./db_rek/fpsementara.csv");

            remove(file);
            if (rename("./db_rek/fpsementara2.csv", file) != 0) printf("\nGagal Melakukan Transaksi");
        } else {
            fclose(fpsementara);
            remove("./db_rek/fpsementara.csv");
            remove("./db_rek/fpsementara1.csv");
        }
    } else {
        remove("./db_rek/fpsementara.csv");
    }
    pauseRek();
}

void clear() {
#ifdef _WIN32
    std : system("cls");
#else
std: system("clear");
#endif
}