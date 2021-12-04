#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int CalcolaCompatibilita(char* verso1, char* verso2) {
	/* calcola la lunghezza di ogni stringa*/
	int len1 = strlen(verso1);
	int len2 = strlen(verso2);

	/* calcola il valore assoluto della differenza*/
	int len_diff = Max(len1, len2) - Min(len1, len2);

	/* calcola la percentuale della differenza sulla stringa più lunga*/
	float perc_len_diff = CalcolaPercentuale(len_diff, Max(len1, len2));

	/* controlla se la percentuale è maggiore o minore di 20%*/
	return (perc_len_diff <= 20);
}

int CheckInRima(char* verso1, char* verso2)
{
	size_t s1 = strlen(verso1);
	size_t s2 = strlen(verso2);

	/* Non è vero quasi mai vero che due versi sono in rima se le ultime 3 lettere sono uguali ma vabbè */
	return (s1 >= 3 && s2 >= 3) && (strcmp(&verso1[s1 - 3], &verso2[s2 - 3]) == 0);
}

char* CercaRima(char* verso, char** database, size_t numero_righe) {
	/*NON IMPLEMENTATO*/
	return NULL;
}

char* ApplicaCesura(char* verso) {
	char* stringa = verso;
	while (*stringa != '\0' && *stringa != '.' && *stringa != ';')
		++stringa;

	if (*stringa == '\0')
		return NULL;

	*stringa = '\0';

	return verso;
}

char* CercaCesura(char** database, size_t numero_righe) {
	for (int i = 0; i < numero_righe; i++) {
		char* tentativo = ApplicaCesura(*(database + i));
		if (tentativo != NULL) {
			return tentativo;
		}
	}
	return NULL;
}

int CheckAssonanza(char* verso1, char* verso2) {
	/*NON IMPLEMENTATO*/
	return 0;
}

char* CercaAssonanza(char* verso, char** database, size_t numero_righe) {
	/*NON IMPLEMENTATO*/
	return NULL;
}

int CheckAlliterazione(char* verso) {
	/*NON IMPLEMENTATO*/
	return 0;
}

char* CercaAlliterazione(char lettera, char** database, size_t numero_righe) {
	/*NON IMPLEMENTATO*/
	return NULL;
}

float CalcolaPercentuale(int a, int b) {
	/*min:max=x:100 */
	float percentage = (Min(a, b) * 100) / (float)Max(a, b);
	return percentage;
}

int Max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

int Min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}

char** CaricaDatabase(const char* filename, size_t verse_max_len, size_t* out_size) {
	FILE* file = NULL;
	char** verses = NULL; /* matrice di puntatori a ogni verso, ritornata dalla funzione */
	char** buffer = NULL; /* usato in caso realloc fallisse per non evitare memory leaks */
	char* hold = NULL;	/* usato per leggere ogni verso dal file */
	char* str = NULL;	/* usato per salvare ogni verso in memoria */
	size_t entries;

	if (out_size != NULL && verse_max_len > 0) {
		/* open file */
		fopen_s(&file, filename, "rt");
		if (!file) {
			return NULL;
		}

		entries = 0;
		hold = (char*)malloc(sizeof(char) * verse_max_len); /* ogni verso ha al massimo verse_max_len incluso il terminatore */
		if (hold == NULL) {
			goto Errors;
		}

		/* get each verse */
		while (fgets(hold, verse_max_len, file) != NULL) {
			/* reset current verse */
			str = NULL;

			size_t len = strlen(hold);
			if (len == 0 || len >= verse_max_len) {
				goto Errors;
			}

			/* string returned by fgets may include a \n at the end before the \0 */
			if (hold[len - 1] == '\n')
				hold[len - 1] = '\0';

			buffer = verses; /* save old pointer in case realloc fails */
			verses = (char**)realloc(verses, sizeof(char*) * (entries + 1));
			if (verses == NULL) /* realloc failed */
			{
				verses = buffer;
				goto Errors;
			}

			/* allocate space for current verse and copy it from hold */
			str = (char*)malloc(sizeof(char) * len + 1);
			if (str == NULL || strcpy_s(str, len + 1, hold) != 0) {
				goto Errors;
			}

			/* set new pointer to current verse */
			verses[entries] = str;
			entries++;

			/* reset hold */
			memset(hold, 0, verse_max_len);
		} /* end while */

		if (!feof(file)) /* an error occurred while reading the file */
		{
			goto Errors;
		}

		/* close file and release hold */
		free(hold);
		fclose(file);

		*out_size = entries;
		return verses;
	} /* if */
	else {
		return NULL;
	} /* else - se nessun errore si verifica, l'esecuzione della funzione termina sempre qua */

Errors:
	/*
	* se l'esecuzione del programma arriva qua, allora sicuramente da qualche parte qualcosa è andato storto
	* per sicurezza, ogni cosa venga usata nella funzione viene controllata e rilasciata se necessario
	*/
	if (file) fclose(file);
	if (hold) free(hold);
	if (str) free(str);
	if (verses) {
		/* free all entries */
		int i;
		for (i = 0; i < entries; ++i)
			if (verses[i])
				free(verses[i]);

		/* free all pointers */
		free(verses);
	}
	return NULL;
}


void LiberaDatabase(char** verses, size_t count) {
	if (verses) {
		int i;
		/* free all entries */
		for (i = 0; i < count; ++i)
			if (verses[i])
				free(verses[i]);

		/* free all pointers */
		free(verses);
	}
}


char* ToLower(char* str) {
	size_t str_len = strlen(str);
	char* rtn_str = (char*)malloc(sizeof(char) * str_len);
	if (rtn_str == NULL) { return NULL; }
	for (int i = 0; i < str_len; i++) {
		if (*(str + i) >= 65 && *(str + i) <= 90) {
			*(rtn_str + i) = *(str + i) + 32;
		}
		else {
			*(rtn_str + i) = *(str + i);
		}
	}
	return rtn_str;
}
