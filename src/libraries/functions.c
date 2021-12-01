#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

static float CalcolaPercentuale(int a, int b)
{
	/* min:max=x:100 */
	return (Min(a, b) * 100.0 / Max(a, b));
}


static int Max(int a, int b)
{
	return (a > b ? a : b);
}

static int Min(int a, int b)
{
	return (a > b ? b : a);
}


BOOL CalcolaCompatibilita(const char* verso1, const char* verso2)
{
	if (verso1 == NULL || verso2 == NULL)
	{
		ERROR("Invalid parameter");
		return FALSE;
	}

	/* calcola la lunghezza di ogni stringa */
	int len1 = strlen(verso1);
	int len2 = strlen(verso2);

	 /* calcola il valore assoluto della differenza */
	int len_diff = Max(len1, len2) - Min(len1, len2);

	 /* calcola la percentuale della differenza sulla stringa più lunga */
	/* TODO: cannot divide by 0 */
	float perc_len_diff = CalcolaPercentuale(len_diff, Max(len1, len2));

	 /* controlla se la percentuale è maggiore o minore di 20% */
	return !(perc_len_diff > 20)
}


BOOL CheckInRima(const char* verso1, const char* verso2)
{
	if (verso1 == NULL || verso2 == NULL)
	{
		ERROR("Invalid parameter.");
		return FALSE;
	}

	WARNING("Not implemented.");
	return FALSE;
}

char* CercaRima(const char* verso1, const char* verso2)
{
	if (verso1 == NULL || verso2 == NULL)
	{
		ERROR("Invalid parameter.");
		return NULL;
	}

	WARNING("Not implemented.");
	return NULL;
}

char* ApplicaCesura(const char* verso)
{
	if (verso == NULL)
	{
		ERROR("Invalid parameter.");
		return NULL;
	}

	WARNING("Not implemented.");
	return NULL;
}

char* CercaCesura(const char* verso)
{
	if (verso == NULL)
	{
		ERROR("Invalid parameter.");
		return NULL;
	}

	WARNING("Not implemented.");
	return NULL;
}

BOOL CheckAssonanza(const char* verso1, const char* verso2)
{
	if (verso1 == NULL || verso2 == NULL)
	{
		ERROR("Invalid parameter.");
		return FALSE;
	}

	WARNING("Not implemented.");
	return FALSE;
}

char* CercaAssonanza(const char* verso1, const char* verso2)
{
	if (verso1 == NULL || verso2 == NULL)
	{
		ERROR("Invalid parameter.");
		return NULL;
	}

	WARNING("Not implemented.");
	return NULL;
}

BOOL CheckAlliterazione(const char* verso)
{
	if (verso1 == NULL || verso2 == NULL)
	{
		ERROR("Invalid parameter.");
		return FALSE;
	}

	WARNING("Not implemented.");
	return FALSE;
}

char* CercaAlliterazione(char lettera, const char* verso)
{
	if (verso1 == NULL || verso2 == NULL)
	{
		ERROR("Invalid parameter.");
		return NULL;
	}

	WARNING("Not implemented.");
	return NULL;
}



char** ReadFile(const char* filename, int verse_max_len, size_t* out_size)
{
	FILE* file = NULL;
	char** verses = NULL;
	char** buffer = NULL; /* used in order to fail successfully */
	char* hold	= NULL;	/* used to retrieve each verse from file */
	char* str	= NULL;	/* used to store each verse without wasting memory */
	size_t entries;

	if (out_size != NULL && verse_max_len > 0)
	{
		/* open file */
		fopen_s(&file, filename, "rt");
		if (!file)
		{
			ERROR("Cannot open file %s.", filename);
			return NULL;
		}

		entries = 0;
		hold = (char*)malloc(sizeof(char) * verse_max_len); /* allocate enough space to store each verse */
		if (hold == NULL)
		{
			ERROR("Out-of-memory: malloc.");
			goto Errors;
		}

		/* get each verse */
		while (fgets(hold, verse_max_len, file) != NULL)
		{
			/* reset current verse */
			str = NULL;

			size_t len = strlen(hold);
			if (len == 0 || len >= verse_max_len)
			{
				ERROR("Invalid string in file: <%s>.", hold);
				goto Errors;
			}

			/* string returned by fgets may include a \n at the end before the \0 */
			if (hold[len - 1] == '\n')
				hold[len - 1] = '\0';

			buffer = verses; /* save old pointer in case realloc fails */
			verses = (char**)realloc(verses, sizeof(char*) * (entries + 1));
			if (verses == NULL) /* realloc failed */
			{
				ERROR("Out-of-memory: realloc.");
				verses = buffer;
				goto Errors;
			}

			/* allocate space for current verse and copy it from hold */
			str = (char*)malloc(sizeof(char) * len + 1);
			if (str == NULL || strcpy_s(str, len + 1, hold) != 0)
			{
				ERROR("Out-of-memory: malloc.");
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
			ERROR("Error reading file %s.", filename);
			goto Errors;
		}

		/* close file and release hold */
		free(hold);
		fclose(file);

		*out_size = entries;
		return verses;
	} /* if */
	else
	{
		WARNING("Invalid parameter.");
		return NULL;
	} /* else - if the execution is successful, the program never gets to the Errors instructions */

Errors:
	/*
	* if execution reaches this point, something bad happened
	* this can be useful to avoid memory leaks
	*/
	if (file) fclose(file);
	if (hold) free(hold);
	if (str) free(str);
	if (verses)
	{
		/* free all entries */
		int i;
		for (i = 0; i < entries; ++i)
			if (verses[i])
				free(verses[i]);

		/* free all pointers */
		free(verses);
	}
	return NULL;
} /* Function ReadFile */


void ReleaseContents(char** verses, size_t count)
{
	if (verses)
	{
		int i;
		/* free all entries */
		for (i = 0; i < count; ++i)
			if (verses[i])
				free(verses[i]);

		/* free all pointers */
		free(verses);
	}
}