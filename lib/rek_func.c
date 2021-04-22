#include "rek_func.h" 

int pauseRek() {
    char lanjut;
    printf("\nApakah anda ingin melanjutkan? (y/t) :");
    scanf("\n");
    scanf("%c", &lanjut);
    if (lanjut == 'y') return 1;
    return 0;
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

void buatRek() {
    FILE* fp;
    struct rek nasabah;
    char file[] = "./db_rek/data_rek.csv";
    
    clear();
    landing();

    fp = fopen(file, "a+");

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
}
