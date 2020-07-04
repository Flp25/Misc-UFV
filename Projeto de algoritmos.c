
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>


#include <string>


using namespace std;


typedef struct ALG_DATA{

	char algoritmo[35], ordem[35], tempo[35];
	char entrada[50], saida[50];
	long int *vet;
        int tam, OP_algoritmo, OP_ordem, cont;
	float tg, start, end;

}ALG_DATA;


void inicializar_struct(ALG_DATA *dt){
	
	fflush(stdin);

	dt->tam=-1;
	dt->tg=0;

	strcpy(dt->algoritmo," ");
	strcpy(dt->ordem," ");

	if(dt->vet != NULL)
		free(dt->vet);

	dt->vet = NULL;
	

	fflush(stdin);

}


int valor_rand(int i){

	int valor;
	
	srand(valor*i);
	valor=rand()%999999;

	return valor;

}


int ordem_elementos(ALG_DATA *dt){


	int i,j;

	if(dt->OP_ordem==1){

		j = 0;
		for(i=0; i<dt->tam; i++)
			dt->vet[i]=j++;


	}else if(dt->OP_ordem==2){

		j = dt->tam;
		for(i=0; i<dt->tam; i++)
			dt->vet[i]=j--;

	}else{

		for(i=0; i<dt->tam; i++)
			dt->vet[i]= valor_rand(i);

	}
	
	return 1;

}


int aloca_vetor(ALG_DATA *dt){

	switch(dt->tam){

		case 1:
			dt->tam=10;
		break;
		case 2:
			dt->tam=100;
		break;
		case 3:
			dt->tam=1000;
		break;
		case 4:
			dt->tam=10000;
		break;
		case 5:
			dt->tam=100000;
		break;
		case 6:
			dt->tam=1000000;
		break;

		default:
		break;

	}
	dt->vet=(long int*)malloc(dt->tam*sizeof(long int));

	if(dt->vet!=NULL)
		return 1;
	else {
		puts("\n\nERRO DE ALOCAO: MEM INSUFICIENTE\n");
		return 0;
	}
}


int tam_algoritmo(ALG_DATA *dt){


	printf("\n[ 1 ] - 10 valores\n");
	printf("[ 2 ] - 100 valores\n");
	printf("[ 3 ] - 1 000 valores\n");
	printf("[ 4 ] - 10 000 valores\n");
	printf("[ 5 ] - 100 000 valores\n");
	printf("[ 6 ] - 1 000 000 valores\n");
	printf("[ 0 ] - sair\n");

	while(dt->tam!=0){

		printf("\n*Defina o tamanho do vetor para a entrada de valores; ");
		scanf("%d",&dt->tam);

		if(dt->tam==1 || dt->tam==2 || dt->tam==3 || dt->tam==4 || dt->tam==5 || dt->tam==6 || dt->tam==0)
			break;
		else
			printf("    [ OPCAO INVALIDA! ]");
	}

	if(dt->tam!=0)
		return 1;
	else 
		return 0;

}


int escolha_ordem(ALG_DATA *dt){

	int i;

	printf("\n[ 1 ] crescente");
	printf("\n[ 2 ] decrescente");
	printf("\n[ 3 ] aleatorio\n");
	printf("\nEscolha a ordem em que os valores serao gerados; ");

	scanf("%d",&i);
	fflush(stdin);
	


	switch(i){

		case 1:
			dt->OP_ordem=i;
			strcpy(dt->ordem,"crescente");
		break;
		case 2:
			dt->OP_ordem=i;
			strcpy(dt->ordem,"decrescente");
		break;
		case 3:
			dt->OP_ordem=i;
			strcpy(dt->ordem,"aleatorio");
		break;
		default:
			i=0;
		break;

	}
	fflush(stdin);

	if(i!=0)
		return 1;
	else 
		return 0;
}


void insertion_sort(ALG_DATA *dt){

	int i, j, k, chave;

	system("clear");

	for(j=1; j<dt->tam; j++){

		chave=dt->vet[j];
		i= j-1;
		k = dt->tam - j;
		
                printf("\n[ %d ] - entries left...", k);
		

			while(i>-1 && dt->vet[i]>chave){

				dt->vet[i+1]=dt->vet[i];
				i--;
			
			}
		dt->vet[i+1]=chave;

	}

	return;

}


void bubble_sort(ALG_DATA *dt){

	int i, j, k, swap;


	system("clear");
	for (i = 0; i<dt->tam-1; i++){

		k = dt->tam - i;
		printf("\n[ %d ] - entries left...", k);

		for(j = 0; j< dt->tam-(i+1) ; j++){

			if(dt->vet[j] > dt->vet[j+1] ){

				
				swap = dt->vet[j];
				dt->vet[j] = dt->vet[j+1];
				dt->vet[j+1] = swap;
				
			}
		}
	}
}


void selection_sort(ALG_DATA *dt){

	int i, j, min, k, m, swap;

	j = 0;
	m = dt->tam - 1;

	system("clear");
	for(i = 0; i<m; i++){
		
		min = i;
		k = dt->tam - i;

		printf("\n[ %d ] - entries left...", k);
	
		for(j = 1+i; j<dt->tam; j++){

			
			if(dt->vet[j] < dt->vet[min])  min = j;

		}

		if(dt->vet[i] != dt->vet[min]){

			swap = dt->vet[i];
			dt->vet[i] = dt->vet[min];
			dt->vet[min] = swap;
		}
			
	} 

}

void merge(ALG_DATA *dt, int alfa, int mi, int omega){

	int aux, aux2, aux3;
	int Vet[omega-alfa+1];

	aux = alfa;
	aux2 = mi+1;
	aux3 = 0;

	while(aux <= mi && aux2 <= omega){
		
		if(dt->vet[aux] <= dt->vet[aux2]){

			Vet[aux3] = dt->vet[aux];
		        aux++;

		}else{
			Vet[aux3] = dt->vet[aux2];
			aux2++;
		}
		aux3++;
	}

	while(aux <= mi){  

		Vet[aux3] = dt->vet[aux];
		aux3++;
		aux++;
	}
 
	while(aux2 <= omega){   

		Vet[aux3] = dt->vet[aux2];
		aux3++;
		aux2++;
	}

	for(aux3 = alfa; aux3 <= omega; aux3++)   dt->vet[aux3] = Vet[aux3-alfa];

}


void merge_sort(ALG_DATA *dt, int alfa, int omega){
	
	int mi;

	if(alfa < omega){

		mi = (alfa+omega)/2;
		merge_sort(dt, alfa, mi);
		merge_sort(dt, mi+1, omega);
		merge(dt, alfa, mi, omega);

	}
}

void shell_sort(ALG_DATA *dt){

	int i, j, aux;
	int intervalo = 1;
	
	system("clear");


	intervalo = dt->tam;
		
	while(intervalo > 1){

		intervalo /= 2;

		for(i = intervalo; i< dt->tam; i++){

			aux = dt->vet[i];
			j = i - intervalo;

			while(j >= 0 && aux < dt->vet[j] ){

				dt->vet[j+intervalo] = dt->vet[j];
				j -= intervalo;

			}

			dt->vet[j + intervalo] = aux;
		}
	}
}



void pasta(ALG_DATA *dt){


	string local = dt->algoritmo;

	local.append("/Entrada/");
	local.append(dt->ordem);


	system(("mkdir -p "+local).c_str());



	sprintf(dt->entrada, "%s/Entrada/%s/%d.txt", dt->algoritmo, dt->ordem, dt->tam);

	FILE *fp;
	int i;

	fp = fopen(dt->entrada, "w");

	fprintf(fp," %d\n\n",dt->tam);

	for(i=0; i<dt->tam; i++)
		fprintf(fp," %ld\n",dt->vet[i]);
	
	fclose(fp);


}


void pasta_saida(ALG_DATA *dt){

	string local = dt->algoritmo;


	local.append("/Saida/");
	local.append(dt->ordem);


	system(("mkdir -p "+local).c_str());	
	sprintf(dt->saida, "%s/Saida/%s/%d.txt", dt->algoritmo, dt->ordem, dt->tam);


	FILE *fp;
	int i;
	

	fp = fopen(dt->saida, "w");
	fprintf(fp," %d\n\n",dt->tam);

	for(i=0; i<dt->tam; i++)
		fprintf(fp," %ld\n",dt->vet[i]);
	
	fclose(fp);

}


float tempo(float start, float end){

	float tg;
	tg = ((end - start)/(double)CLOCKS_PER_SEC);
	return tg;

}


void pasta_tempo(ALG_DATA *dt){

	string local = dt->algoritmo;


	local.append("/Tempo/");
	local.append(dt->ordem);


	system(("mkdir -p "+local).c_str());	
	sprintf(dt->tempo, "%s/Tempo/%s/%d.txt", dt->algoritmo, dt->ordem, dt->tam);

	FILE *fp;
	int i;

	fp = fopen(dt->tempo, "w");

	fprintf(fp," %d\n\n",dt->tam);
	fprintf(fp," tempo gasto: %f seg",dt->tg);
	
	fclose(fp);


}


void limpa_vet(ALG_DATA *dt){

	int i;
	for(i=0; i<dt->tam; i++)
		dt->vet[i] = 0;

	free(dt->vet);

}


void menu(){

	printf("\n-----------------------------------------\n");
	printf("[ 1 ] - Insertion Sort\n");
	printf("[ 2 ] - Bubble Sort\n");
	printf("[ 3 ] - Selection Sort\n");
	printf("[ 4 ] - Shell Sort\n");
	printf("[ 5 ] - Merge Sort\n");
	printf("[ 0 ] - Sair\n");
	printf("\nEscolha o Algoritmo: ");	

}


int main(){

	ALG_DATA dt;

	int i,alocacao,ex=1;
	float start, end;

	inicializar_struct(&dt);


	while(ex!=0){

		fflush(stdin);
		escolha_ordem(&dt);
		fflush(stdin);
		tam_algoritmo(&dt);
		fflush(stdin);
		aloca_vetor(&dt);

		menu();
		scanf("%d",&ex);

		if(ex==1){


			ordem_elementos(&dt);
			strcpy(dt.algoritmo,"Insertion_Sort");	
			pasta(&dt);

			start = clock();	
			insertion_sort(&dt);
			end = clock();

			dt.tg = tempo(start, end);

			pasta_saida(&dt);
			pasta_tempo(&dt);


		}else if(ex == 2){


			ordem_elementos(&dt);
			strcpy(dt.algoritmo, "Bubble_Sort");
			pasta(&dt);

			start = clock();
			bubble_sort(&dt);
			end = clock();

			dt.tg = tempo(start, end);

			pasta_saida(&dt);
			pasta_tempo(&dt);


		}else if(ex == 3){


			ordem_elementos(&dt);
			strcpy(dt.algoritmo, "Selection_Sort");
			pasta(&dt);

			start = clock();
			selection_sort(&dt);
			end = clock();

			dt.tg = tempo(start, end);

			pasta_saida(&dt);
			pasta_tempo(&dt);


		}else if(ex == 4){


			ordem_elementos(&dt);
			strcpy(dt.algoritmo, "Shell_Sort");
			pasta(&dt);

			start = clock();
			shell_sort(&dt);
			end = clock();

			dt.tg = tempo(start, end);

			pasta_saida(&dt);
			pasta_tempo(&dt);


		}else if(ex == 5){
			
			ordem_elementos(&dt);
			strcpy(dt.algoritmo, "Merge_Sort");
			pasta(&dt);

			start = clock();
			merge_sort(&dt, 0, dt.tam);
			end = clock();

			dt.tg = tempo(start, end);

			pasta_saida(&dt);
			pasta_tempo(&dt);
			
		}else{


			inicializar_struct(&dt);
			break;


		}

		
		inicializar_struct(&dt);


		printf("\n\n");
		system("clear");
		printf("$ END $\n\n");
		printf("[ 0 ] - sim\n");
		printf("[ 1 ] - nao\n");
		printf("\n");
		printf("Deseja sair: ");
		scanf("%d",&ex);

		if(ex == 0) break;
		
		else ex = -1;		
		
		system("clear");

	}
	
}
