#include <stdio.h>
#include <stdlib.h>
#include "libraries/functions.h"


#if __has_include(<crtdbg.h>)
# include <crtdbg.h>
#define _DBG_CRT
#endif

#define MAX_LEN_VERSO 150

/* percorso relativo al database se si esegue il programma nella directory del progetto */
#define PATH_TO_DATABASE "assets/futuribili.txt"

/* visualizza il menù delle opzioni  */
void VisualizzaMenu();

/* chiede l'opzione da utilizzzare e la ritorna come intero */
int ChiediFunzionalita();

/* fa inserire un verso all'utente e ritorna un putatore ad esso  */
char* InserisciVerso();

/* mostra un errore di allocazione */
void CreaErrore()
{
	printf("ERRORE DI ALLOCAZIONE.\nIl programma verra' terminato.");
}

/* temporaneo */
void NonAncoraImplementato()
{
	printf("QUESTA FUNZIONALITA' NON E' ANCORA STATA IMPLEMENTATA\nIl programma verra' terminato.");
}


int main(int argc, char* argv[])
{
	int funzionalita;
	size_t entries = 0;
	char** verses = NULL;

	/*
	*	CRTDBG_LEAK_CHECK_DF is used at program initialization to force a
	*		leak check just before program exit. This is important because
	*		some functions may dynamically allocate memory and expect clients to free it.
	*/_
#if defined _DBG_CRT
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
#endif

	/*
	*	TODO: user should be prompted to enter a file name rather than 
	*	having it hard coded with a default and bolchini-stupid value
	*/

	/* open file */
	verses = ReadFile(PATH_TO_DATABASE, MAX_LEN_VERSO, &entries);
	if (verses == NULL || entries == 0)
	{
		printf("Cannot read file %s", PATH_TO_DATABASE);
		return EXIT_FAILURE; /* return 1; */
	}

	/* TODO: put this in an "endless" loop */
	VisualizzaMenu();
	do
	{
		funzionalita = ChiediFunzionalita();
	} while (funzionalita < 0 || funzionalita > 9);
   
	
	switch (funzionalita)
	{
	case 0:
		printf("GoodBye!\n");
		break;
	case 1:
	{
		char* verso1 = InserisciVerso();
		char* verso2 = InserisciVerso();
		if (verso1 != NULL && verso2 != NULL)
		{
			int compatibilita = CalcolaCompatibilita(verso1, verso2);
			/* 1 se la compatibilità è verificata, 0 se non lo è */
			if (compatibilita == 1)
			{
				printf("I due versi sono compatibili!\n");
			}
			else
			{
				printf("I due versi non sono compatibili!\n");
			}
		}
		else 
		{
			CreaErrore();
		}
		break;
	}
	case 2:
	{
		char* verso1 = InserisciVerso();
		char* verso2 = InserisciVerso();
		if (verso1 != NULL && verso2 != NULL)
		{
			int check_rima = CheckInRima(verso1, verso2);
			/* 1 se sono in rima, 0 se non lo sono */
			if (check_rima == 1) 
			{
				printf("I due versi sono in rima!\n");
			}
			else
			{
				printf("I due versi non sono in rima!\n");
			}
		}
		else
		{
			CreaErrore();
		}
		break;
	}
	case 3:
	{
		/* TODO: ask user to select verse to parse */
		char* verso = InserisciVerso();
		if (verso != NULL)
		{
			char* verso_in_rima = CercaRima(verso, PATH_TO_DATABASE);
			if (verso_in_rima != NULL)
			{
				printf("Ecco il verso che fa per te!\n=> %s", verso_in_rima);
			}
			else
			{
				printf("Non abbiamo trovato un verso che fa per te.");
			}
		}
		else
		{
			CreaErrore();
		}
		break;
	}
	case 4:
	{
		char* verso = InserisciVerso();
		if (verso != NULL)
		{
			verso = ApplicaCesura(verso);
			if (verso != NULL)
			{
				printf("Dopo la cesura il tuo verso e':\n=> %s", verso);
			}
			else 
			{
				printf("Non e' stato possibile applicare la cesura.");
			}
		}
		else
		{
			CreaErrore();
		}
		break;
	}
	case 5:
	{
		/* TODO: ask user to select verse to parse */
		char* verso = InserisciVerso();
		if (verso != NULL)
		{
			verso = CercaCesura(PATH_TO_DATABASE);
			if (verso != NULL) 
			{
				printf("Il verso che è stato trovato e cesurato e':\n=> %s", verso);
			}
			else 
			{
				printf("Non e' stato possibile trovare un verso cesurabile.");
			}
		}
		else 
		{
			CreaErrore();
		}
		break;
	}
	case 6:
	{
		char* verso1 = InserisciVerso();
		char* verso2 = InserisciVerso();
		if (verso1 != NULL && verso2 != NULL)
		{
			int check_assonanza = CheckAssonanza(verso1, verso2);
			/* 1 se sono in assonanza, 0 se non lo sono  */
			if (check_assonanza == 1)
			{
				printf("I due versi sono in assonanza!\n");
			}
			else
			{
				printf("I due versi non sono in assonanza!\n");
			}
		}
		else
		{
			CreaErrore();
		}
		break;
	}
	case 7:
	{
		/* TODO: ask user to select verse to parse */
		char* verso = InserisciVerso();
		if (verso != NULL)
		{
			char* verso_in_assonanza = CercaAssonanza(verso, PATH_TO_DATABASE);
			if (verso_in_assonanza != NULL)
			{
				printf("Ecco il verso che fa per te!\n=> %s", verso_in_assonanza);
			}
			else 
			{
				printf("Non abbiamo trovato un verso che fa per te.");
			}
		}
		else
		{
			CreaErrore();
		}
		break;
	}
	case 8:
	{
		char* verso = InserisciVerso();
		if (verso != NULL) {
			int check_alliterazione = CheckAlliterazione(verso);
			/* 1 se c'è una alliterazione, 0 se non c'è */
			if (check_alliterazione == 1) 
			{
				printf("Il tuo verso presenta una alliterazione.");
			}
			else 
			{
				printf("Il tuo verso non presenta una alliterazione.");
			}
		}
		else 
		{
			CreaErrore();
		}
		break;
	}
	case 9:
	{
		/* TODO: ask user to select verse to parse */
		char lettera;
		printf("Inserisci una lettera per la ricerca della alliterazione => ");
		scanf("%c", &lettera);
		char* verso_alliterante = CercaAlliterazione(lettera, PATH_TO_DATABASE);
		if (verso_alliterante != NULL)
		{
			printf("Abbiamo trovato un verso alliterante:\n => %s", verso_alliterante);
		}
		else 
		{
			printf("Non è stato possibile trovare un verso alliterante.");
		}
		break;
	}
	default:
		printf("Ivalid menu code entered.\n");
		break;
	} /* end switch */

	ReleaseContents(verses, entries);
	return 0;
} /* main */

void VisualizzaMenu()
{
	printf("Benvenut* nell'ecosistema \"Un poeta in ogni casa\"!\n");
	printf("Ecco una piccola guida sulle funzionalita' disponibili al momento:\n");
	printf("0 => per oggi ho lavorato abbastanza!\n");
	printf("1 => dati due versi, controlla la metrica.\n");
	printf("2 => dati due versi, verificare se sono in rima.\n");
	printf("3 => dato un verso, cercarne uno tra quanti non ancora usati, che sia in rima.\n");
	printf("4 => dato un verso, visualizzarne, se esiste, la cesura.\n");
	printf("5 => cercare un verso tra quanti non ancora usati, cui sia possibile applicare una cesura.\n");
	printf("6 => dati due versi, verificare se c'e' assonanza.\n");
	printf("7 => dato un verso, cercarne uno tra quanti non ancora usati, che abbia assonanza.\n");
	printf("8 => dato un verso, sapere se c'e' allitterazione.\n");
	printf("9 => data una lettera, cercare tra i versi non ancora usati uno che presenti un'allitterazione con quella lettera.\n");
}

int ChiediFunzionalita() 
{
	int funz;
	printf("Inserisci qui il numero della funzionalita che desideri utilizzare => ");
	scanf("%d", &funz);
	return funz;
}

/* TODO: permetti di inserire versi con gli spazi(scanf non funziona). */

char* InserisciVerso()
{
	char* verso;
	verso = (char*)malloc(sizeof(char) * MAX_LEN_VERSO);
	if (verso == NULL) { return NULL; }
	printf("Inserisci un verso => ");
	scanf("%s", verso);
	return verso;
}

