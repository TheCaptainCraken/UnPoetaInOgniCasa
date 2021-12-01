#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

int CalcolaCompatibilita(char* verso1, char* verso2)
{
    //calcola la lunghezza di ogni stringa
    int len1 = strlen(verso1);
    int len2 = strlen(verso2);
    //calcola il valore assoluto della differenza
    int len_diff = Max(len1, len2) - Min(len1, len2);
    //calcola la percentuale della differenza sulla stringa più lunga
    float perc_len_diff = CalcolaPercentuale(len_diff, Max(len1, len2));
    //controlla se la percentuale è maggiore o minore di 20%
    if (perc_len_diff > 20) { return 0; }
    else { return 1; }
}

int CheckInRima(char* verso1, char* verso2)
{
    return 0;
}

char* CercaRima(char* verso, const char* path_to_database) {
    return NULL;
}

char* ApplicaCesura(char* verso) {
    return NULL;
}

char* CercaCesura(const char* path_to_database) {
    return NULL;
}

int CheckAssonanza(char* verso1, char* verso2) {
    return 0;
}

char* CercaAssonanza(char* verso, const char* path_to_database) {
    return NULL;
}

int CheckAlliterazione(char* verso) {
    return 0;
}

char* CercaAlliterazione(char lettera, const char* path_to_database) {
    return NULL;
}

float CalcolaPercentuale(int a, int b) {
    //min:max=x:100
    float percentage = (Min(a, b) * 100) / (float)Max(a, b);
    return percentage;
}

int Max(int a, int b) {
    if (a > b) { return a; }
    else { return b; }
}
int Min(int a, int b) {
    if (a < b) { return a; }
    else { return b; }
}