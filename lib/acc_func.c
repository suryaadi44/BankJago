#include "acc_func.h" 

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
