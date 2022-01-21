//
// Created by W0L1D on 1/21/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

void readModules(FILE *f) {

    int modIndex = 0, modsize = 0;
    int i,j;
    char str[100], c;

    while((c=(char)fgetc(f))!=EOF) {
        if (c == DELIM) {
            str[modsize] = '\0';
            i = modIndex/16;
            j = modIndex%16;
            if ((i > 2) || (j > 15)) {
                printf("\n\nerreur les modules stockes depasse le nombre predefini\n");
                printf("\ni = %d, j =%d\n", i, j);
                exit(0);
            }
            modules[i][j] =(unsigned char*) strdup(str);
            modIndex++;
            modsize = 0;
            continue;
        }
        str[modsize] = c;
        modsize++;
    }
}

int main() {
    FILE *f;
    f=fopen("test.txt","rt");

    readModules(f);

    fclose(f);
    return 0;
}

