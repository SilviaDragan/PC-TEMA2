#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/task_helper.h"

void print(char*);

char ultimalitera(char *cuv)
{
	return cuv[strlen(cuv)-1];
}

void uppercase(char*p)
{

	int i;
	//daca primul carater e litera mica, il transform in litera mare
	if(p[0] >='a' && p[0] <='z')
		p[0]=p[0]-32;
	//orice caracter ce nu este primul pe un rand nou
	//si este litera mare, transform in mica
	for(i=1; p[i]!='\0'; i++)
	{

		if(p[i-1]!='\n')
			{
				if(p[i]>='A' && p[i]<='Z')
					p[i]=p[i]+32;
			}
		//daca e litera mica la inceput de vers, transform in litera mare
		else 
			if(p[i] >='a' && p[i] <='z')
				p[i]=p[i]-32;
	}		
	return;
}

void trimming(char *p)
{

	int i=0, j;

	while(p[i]!='\0')
	{
		//elimin caracterele nedorite
		if( strchr(",.;:!?", p[i]) != NULL )
		{
			for(j=i; j<strlen(p); j++)
			{
				p[j]=p[j+1];
			}
		}
		//elimin spatiile redundante
		else if( p[i]==' ' && p[i+1]==' ')
		{
			for(j=i+1; j<strlen(p); j++)
			{
				p[j]=p[j+1];
			}
		}
		else i++;
		
	}
	return;
}


//functie de schimbare a unui cuvant cu altul 
void switch_word(char *p, char *old, char *new, long poz)
{
	char aux[100000];
	strncpy(aux,p,poz);
	aux[poz]='\0';

	strcat(aux,new);
	strcat(aux,p+poz+strlen(old));
	strcpy(p,aux);
}

void rima_imperecheata(char *poezie, char last_word[4][50], 
	char last_word_copy[4][50], char last_letter[5])
{

	char **sinonime;
	int i=0, j=0, x=0, n=-1;
	char sinonim[4][50];
	char *poz=poezie;

	poz=poezie;

	for(i=0; i<4; i=i+2)
	{
		for(j=0; j<4; j++)
			sinonim[j][0]='\0';
		n=-1;

		/* daca ultimele litere ale ultimelor cuvinte de pe versurile 
		imperecheate nu sunt egale, caut sinonim pentru primul*/
		if(last_letter[i] != last_letter[i+1])
		{
			get_synonym(last_word[i], &n, &sinonime);
			for(j=0; j<n; j++)
			{
				if(ultimalitera(sinonime[j])==ultimalitera(last_word[i+1]))
				{
					if(sinonim[i][0]=='\0') strcpy(sinonim[i], sinonime[j]);
					else 
						/*verific daca sinonimul este cel mai bun 
						lexicografic in cazul in care sunt mai multe 
						care rimeaza */
						if(strcmp(sinonim[i], sinonime[j]) >0 )
								strcpy(sinonim[i], sinonime[j]);


				}
			}
			//inlocuiesc cuvantul care nu rimeaza cu sinonimul sau in poezie
			if(sinonim[i][0]!='\0' && n>0 && strcmp(sinonim[i], last_word_copy[i])!=0)
			{
				poz=strstr(poz+strlen(sinonim[i]),last_word_copy[i]);
				x=strlen(poezie)-strlen(poz);
				switch_word(poezie, last_word[i], sinonim[i], x);
			}
			/* daca nu gasesc sinonim care rimeaza pentru primul cuvant, 
			incerc pentru celalalt*/
			else 
			{
				for(j=0; j<4; j++)
					sinonim[j][0]='\0';
				n=-1;

				get_synonym(last_word[i+1], &n, &sinonime);

				for(j=0; j<n; j++)
				{
					if(ultimalitera(sinonime[j])==ultimalitera(last_word[i]))
					{
						if(sinonim[i+1][0]=='\0')
						 strcpy(sinonim[i+1], sinonime[j]);
						else 
							if(strcmp(sinonim[i+1], sinonime[j]) >0 )
									strcpy(sinonim[i+1], sinonime[j]);


					}
				}
				if(sinonim[i+1][0]!='\0' && n>0 && strcmp(sinonim[i+1], last_word_copy[i+1])!=0)
				{
					poz=strstr(poz+strlen(sinonim[i+1]),last_word_copy[i+1]);
					x=strlen(poezie)-strlen(poz);
					switch_word(poezie, last_word[i+1], sinonim[i+1], x);
				}
			}
		}
	}
	
}

void rima_incrucisata(char *poezie, char last_word[4][50], 
	char last_word_copy[4][50], char last_letter[5])
{

	char **sinonime;
	int i=0, j=0, x=0, n=-1;
	char sinonim[4][50];
	char *poz=poezie;
	for(i=0; i<4; i++)
		sinonim[i][0]='\0';
	poz=poezie;
	/*acelasi algoritm cu cel pentru rima imperecheata, dar pentru cuvintele
	de pe versuri incrucisate(obviously)*/
	for(i=0; i<2; i++)
	{
		for(j=0; j<4; j++)
			sinonim[j][0]='\0';
		n=-1;

		if(last_letter[i] != last_letter[i+2])
		{
			get_synonym(last_word[i], &n, &sinonime);
			for(j=0; j<n; j++)
			{
				if(ultimalitera(sinonime[j])==ultimalitera(last_word[i+2]))
				{
					if(sinonim[i][0]=='\0') strcpy(sinonim[i], sinonime[j]);
					else 
						if(strcmp(sinonim[i], sinonime[j]) >0 )
								strcpy(sinonim[i], sinonime[j]);


				}
			}
			if(sinonim[i][0]!='\0' && n>0 && strcmp(sinonim[i], last_word_copy[i])!=0)
			{
				poz=strstr(poz+strlen(sinonim[i]),last_word_copy[i]);
				x=strlen(poezie)-strlen(poz);
				switch_word(poezie, last_word[i], sinonim[i], x);
			}
			else 
			{
				for(j=0; j<4; j++)
					sinonim[j][0]='\0';
				n=-1;

				get_synonym(last_word[i+2], &n, &sinonime);

				for(j=0; j<n; j++)
				{
					if(ultimalitera(sinonime[j])==ultimalitera(last_word[i]))
					{
						if(sinonim[i+2][0]=='\0')
						 strcpy(sinonim[i+2], sinonime[j]);
						else 
							if(strcmp(sinonim[i+2], sinonime[j]) >0 )
									strcpy(sinonim[i+2], sinonime[j]);


					}
				}
				if(sinonim[i+2][0]!='\0' && n>0 && strcmp(sinonim[i+2], last_word_copy[i+2])!=0)
				{
					poz=strstr(poz+strlen(sinonim[i+2]),last_word_copy[i+2]);
					x=strlen(poezie)-strlen(poz);
					switch_word(poezie, last_word[i+2], sinonim[i+2], x);
				}
			}
		}
	}
	
}
void rima_imbratisata(char *poezie, char last_word[4][50], 
	char last_word_copy[4][50], char last_letter[5])
{

	char **sinonime;
	int i=0, j=0, x=0, n=-1;
	char sinonim[4][50];
	char *poz=poezie;
	for(i=0; i<4; i++)
		sinonim[i][0]='\0';
	poz=poezie;
	
	for(j=0; j<4; j++)
			sinonim[j][0]='\0';
	n=-1;

	/*acelasi algoritm de verificare al rimei si inlocuire,
	 dar verificat pentru cuvintele 0,3; 1,2, pentru ca nu am gasit
	 un pattern sa fac un for :( */
	if(last_letter[0] != last_letter[3])
		{
			for(j=0; j<4; j++)
			sinonim[j][0]='\0';
			n=-1;
			get_synonym(last_word[0], &n, &sinonime);
			for(j=0; j<n; j++)
			{
				if(ultimalitera(sinonime[j])==ultimalitera(last_word[3]))
				{
					if(sinonim[0][0]=='\0') strcpy(sinonim[0], sinonime[j]);
					else 
						if(strcmp(sinonim[0], sinonime[j]) >0 )
								strcpy(sinonim[0], sinonime[j]);


				}
			}
			if(sinonim[0][0]!='\0' && n>0 && strcmp(sinonim[0], last_word_copy[0])!=0)
			{
				poz=strstr(poz+strlen(sinonim[0]),last_word_copy[0]);
				x=strlen(poezie)-strlen(poz);
				switch_word(poezie, last_word[0], sinonim[0], x);
			}
			else 
			{
				for(j=0; j<4; j++)
					sinonim[j][0]='\0';
				n=-1;

				get_synonym(last_word[3], &n, &sinonime);

				for(j=0; j<n; j++)
				{
					if(ultimalitera(sinonime[j])==ultimalitera(last_word[3]))
					{
						if(sinonim[3][0]=='\0')
						 strcpy(sinonim[3], sinonime[j]);
						else 
							if(strcmp(sinonim[3], sinonime[j]) >0 )
									strcpy(sinonim[3], sinonime[j]);


					}
				}
				if(sinonim[3][0]!='\0' && n>0 && strcmp(sinonim[3], last_word_copy[3])!=0)
				{
					poz=strstr(poz+strlen(sinonim[3]),last_word_copy[3]);
					x=strlen(poezie)-strlen(poz);
					switch_word(poezie, last_word[3], sinonim[3], x);
				}
			}
		}

	if(last_letter[1] != last_letter[2])
		{
			for(j=0; j<4; j++)
			sinonim[j][0]='\0';
			n=-1;
			get_synonym(last_word[1], &n, &sinonime);
			for(j=0; j<n; j++)
			{
				if(ultimalitera(sinonime[j])==ultimalitera(last_word[2]))
				{
					if(sinonim[1][0]=='\0') strcpy(sinonim[1], sinonime[j]);
					else 
						if(strcmp(sinonim[1], sinonime[j]) >0 )
								strcpy(sinonim[1], sinonime[j]);


				}
			}
			if(sinonim[1][0]!='\0' && n>0 && strcmp(sinonim[1], last_word_copy[1])!=0)
			{

				poz=strstr(poz+strlen(sinonim[1]),last_word_copy[1]);
				x=strlen(poezie)-strlen(poz);
				switch_word(poezie, last_word[1], sinonim[1], x);
			}
			else 
			{
				for(j=0; j<4; j++)
					sinonim[j][0]='\0';
				n=-1;

				get_synonym(last_word[2], &n, &sinonime);

				for(j=0; j<n; j++)
				{
					if(ultimalitera(sinonime[j])==ultimalitera(last_word[1]))
					{
						if(sinonim[2][0]=='\0')
						 strcpy(sinonim[2], sinonime[j]);
						else 
							if(strcmp(sinonim[2], sinonime[j]) >0 )
									strcpy(sinonim[2], sinonime[j]);


					}
				}
				if(sinonim[2][0]!='\0' && n>0 && strcmp(sinonim[2], last_word_copy[2])!=0)
				{
					poz=strstr(poz+strlen(sinonim[2]),last_word_copy[2]);
					x=strlen(poezie)-strlen(poz);
					switch_word(poezie, last_word[2], sinonim[2], x);
				}
			}
		}
}
	
void rhimy(char *poezie, char *rima)
{
	char **sinonime;
	char *token=NULL, *poz=poezie, aux[100*100];
	int nr=0, i, j, k, x, n=-1;
	char copy[10000], matrice_versuri[1000][1000];
	
	copy[0]='\0';

	for(i=0; i<1000; i++)
		matrice_versuri[i][0]='\0';

	strcpy(copy, poezie);

	 //construiesc o matrice de versuri
	token=strtok(copy, "\n\0");
	while( token!=NULL)
	{
		strcpy(matrice_versuri[nr], token);
		nr++;
		token=strtok(NULL, "\n\0");
	}
	char last_word[4][50], last_word_copy[4][50];
	char last_letter[5];

	for(i=0; i<nr; i=i+4)
	{
		for(j=0; j<4; j++)
		{
			last_word[j][0]='\0';
			last_word_copy[j][0]='\0';
			last_letter[j]='\0';

			//iau ultimul cuvant din fiecare vers pentru a verifica rimele
			strcpy(last_word[j], strrchr(matrice_versuri[j+i], ' '));
			for(k=0; last_word[j][k]!='\0'; k++)
			{
				last_word[j][k]=last_word[j][k+1];
			}
			strcpy(last_word_copy[j], last_word[j]);
			trimming(last_word_copy[j]);

			uppercase(last_word[j]);
			trimming(last_word[j]);
			last_word[j][0]=last_word[j][0]+32;
			last_letter[j]=ultimalitera(last_word[j]);
		}

		if(strncmp(rima,"imperecheata", strlen("imperecheata"))==0) 
		{
		
			rima_imperecheata(poezie, last_word, last_word_copy, last_letter);
		
		}
		else if(strncmp( rima, "incrucisata", strlen("incrucisata")) ==0 )
		{
		
			rima_incrucisata(poezie, last_word, last_word_copy, last_letter);

		}		
		else if(strncmp( rima, "imbratisata", strlen("imbratisata"))==0)
		{
			rima_imbratisata(poezie, last_word, last_word_copy, last_letter);
			
		}

	}
	return;
}

void silly(char*s, float p)
{

	float sample;
	int i;
	//parcurg poezia pana la gasirea lui NULL
	for(i=0; s[i]!='\0'; i++)
	{
		//verific daca caracterul e litera
		if( (s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z') )
			{
				//generez numarul random, schimb litera daca numarul e
				// <probabilitatea
				sample=rand()%100/99.0;
				if(sample<p) 
					{
						if(s[i]>='A' && s[i]<='Z') s[i]=s[i]+32;
						else s[i]=s[i]-32;
					}
			}	
	}
	return;
}

void friendly(char *p)
{
	char copy[100*100];
	strcpy(copy, p);
	char *s, *poz=p, copyofs[100], aux[100*100];
	char *diminutiv[100];
	int x;
	//folosest strtok pentru a lua cuvintele
	s=strtok(copy, " -.\n\0");
		while(s!=NULL)
		{
			strcpy(copyofs, s);
			uppercase(copyofs);
			trimming(copyofs);
			copyofs[strlen(copyofs)]='\0';
			copyofs[0]=copyofs[0]+32;
			
			//caut diminutiv pentru fiecare cuvant
			//daca a fost gasit, inlocuiesc in poezie si caut in continuare 
			//urmatoarea aparitie a cuvantului 

			get_friendly_word(copyofs, diminutiv);
			if(*diminutiv!=NULL&&strcmp(*diminutiv,s)!=0)
			{  
				poz=strstr(poz+strlen(*diminutiv), s);
				x=strlen(p)-strlen(poz);

				switch_word(p, copyofs, *diminutiv, x);
			}
			s=strtok(NULL, " -.\n\0");
		}

	
	return;
}

void print(char*p)
{
	printf("%s\n", p);
	printf("\n");
}

int main(void)
{
	srand(42);

	char cerinta[100];
	char poem[5000];
	char *path;

	//citesc cerinta, pentru fiecare tip de cerinta apelez 
	//functia corespunzatoare
	fgets(cerinta, 100, stdin);
	while(strncmp(cerinta, "quit", strlen("quit")) !=0)
	{
		if(strncmp(cerinta, "load", strlen("load")) == 0) 
			{
				//scot path ul din cerinta load pentru a apela fct
				char *path=strrchr(cerinta,' ');
				path=path+1;				
				path[strlen(path)-1]='\0';
				load_file(path,poem);
			}
		else if(strncmp(cerinta, "uppercase", strlen("uppercase")) == 0)
			uppercase(poem);
		else if(strncmp(cerinta, "trimming", strlen("trimming")) == 0)
			trimming(poem);
		else if(strncmp(cerinta, "make_it_silly", strlen("make_it_silly")) == 0)
			{
				//scot probabiliatea data din cerinta pentru a apela fct
				char *p=strrchr(cerinta, ' ');
				p=p+1;
				p[strlen(p)-1]='\0';
				float prob=atof(p);
				silly(poem, prob);
			}
		else if(strncmp(cerinta, "make_it_friendlier", strlen("make_it_friendlier")) == 0)
			{friendly(poem);}
		else if(strncmp(cerinta, "make_it_rhyme", strlen("make_it_rhyme")) == 0)
			{
				//scot tipul de rima din cerinta pentru a apela fct
				char *tiprima=strrchr(cerinta, ' ');
				tiprima=tiprima+1;
				tiprima[strlen(tiprima)-1]='\0';
				rhimy(poem, tiprima);
			}
		else if(strncmp(cerinta, "print", strlen("print")) == 0)
			print(poem);

		fgets(cerinta, 100, stdin);

	}

	return 0;
}
