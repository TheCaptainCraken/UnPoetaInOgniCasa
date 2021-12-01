#pragma once

#if !defined (TRUE) && !defined (FALSE)
typedef int BOOL;
#define TRUE	1
#define FALSE	0
#endif

/* TODO: using sprintf, va_list and va_start print better dbg output */
#if defined (DEBUG) || defined (_DEBUG)
#	define ERROR(x, ...)	do { printf("ERROR: %s\n", x); } while (FALSE);
#	define WARNING(x, ...)	do { printf("WARNING: %s\n", x); } while (FALSE);
#else
#	define ERROR(x, ...)	{}
#	define WARNING(x, ...)	{}
#endif




/* 
* Parameters:
*	filename		-> absolute path to file to read
*	verse_max_len	-> max length of a verse, including the \0
*	out_size		-> number of verses found in file
* 
* Behaviour:
*	Open a file, read all contents, store each verse and a pointer to it, close file, 
*	return pointer to first verse or NULL on errors. All verses are zero terminated.
*
* Remarks
*	Verses can then be accessed by its index using the [] operator. Indeces are in range [0, entries).
*	Before exiting, either call ReleaseContents or manually free memory allocated for verses
*/
char** ReadFile(const char* /* filename */, int /* verse_max_len */, size_t* /* out_size */);

/* Free all memory allocated by ReadFile */
void ReleaseContents(char** verses, size_t count);

/*  controlla la compatibilità di due versi */
BOOL CalcolaCompatibilita(const char*, const char*);


/* controlla se due versi sono in rima o meno */
BOOL CheckInRima(const char*, const char*);


/*
*	controlla se, dato un verso, ne esiste uno nel database
*	di cui viene forntio il percorso relativo
*/
char* CercaRima(const char*, const char*);


/* applica la cesura su un verso, se possibile */
char* ApplicaCesura(const char*);


/*
*	cerca in un data base di cui viene fornito il
*	percorso relativo se esiste un verso cesurabile(?)
*/
char* CercaCesura(const char*);


/* controlla se due verrsi sono assonanti */
BOOL CheckAssonanza(const char*, const char*);


/*
*	controlla se, dato un verso, ne esiste uno assonante 
*	nel database di cui viene forntio il percorso relativo
*/
char* CercaAssonanza(const char*, const char*);


/* controlla se in un verso è presente una alliterazione */
BOOL CheckAlliterazione(const char*);


/* 
*	controlla se, data una lettera e il percorso ad un database,
*	se esiste un verso che ha una alliterazione con quella lettera
*/
char* CercaAlliterazione(char, const char*);