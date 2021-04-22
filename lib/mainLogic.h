#ifndef MAINLOGIC_H_
#define MAINLOGIC_H_

#include <stdlib.h>   
#include <stdio.h>
#include <string.h>
#include <time.h> 

struct tm* waktu;

struct rek {
    int id;
    long norek;
    char namaDepan[20];
    char namaBelakang[20];
    long isi;
};

struct account {
    int rank;
    char uname[20];
    char pass[20];
};

void landing();     //Logo 
void akunDefault(); //Akun Default 
int Hbaris();       //Fungsi Menghitung Baris Files
void clear();       //Define Command Clear terminal
int cekId();

extern int session;
extern int sessionRank;

#endif //MAINLOGIC_H_