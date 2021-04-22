#include "login_func.h" 

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
