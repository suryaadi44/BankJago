#ifndef REK_FUNC_H_
#define REK_FUNC_H_

#include "mainLogic.h"

//Fungsi Rekening
void buatRek();
void hapusRek();
void editRek();

//Fungsi Transaksi
void cekSaldo();
void tarik();
void setor();
void transfer();

//Fungsi Pendukung Rekening
int pauseRek();
void printRek();
void riwayat();

#endif //REK_FUNC_H_