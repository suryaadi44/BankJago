#include "lib/rek_func.h"
#include "lib/acc_func.h"
#include "lib/mainLogic.h"
#include "lib/login_func.h"     

void menu(); 
void menuAkun();
void menuTransaksi();

int main() {
    int cek;
    clear();

    akunDefault();
    landing();

    if (session == -1) cek = login();

    if (cek == 1 || session != -1) menu();
    else printf("Username atau Password Salah!\n");

    return 0;
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
        if (pauseRek()) menuTransaksi();
        break;
    case 2:
        tarik();
        if (pauseRek()) menuTransaksi();
        break;
    case 3:
        setor();
        if (pauseRek()) menuTransaksi();
        break;
    case 4:
        transfer();
        if (pauseRek()) menuTransaksi();
        break;
    case 5:
        menu();
        break;
    default:
        menuTransaksi();
    }
}