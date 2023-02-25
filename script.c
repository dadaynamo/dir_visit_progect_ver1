#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <math.h>
#define MAX_PATH_LENGTH 1024
void export_data(const char* filepath,char* nomef);

// Struttura della coda
typedef struct Queue {
	char paths[MAX_PATH_LENGTH][MAX_PATH_LENGTH];
	int head;
	int tail;
} Queue;

// Inizializza la coda
void initQueue(Queue* queue) {
	queue->head = 0;
	queue->tail = 0;
}

// Aggiunge un percorso alla coda
void enqueue(Queue* queue, const char* path) {
	strcpy(queue->paths[queue->tail], path);
	queue->tail++;
}

// Rimuove e restituisce il prossimo percorso dalla coda
char* dequeue(Queue* queue) {
	if (queue->head == queue->tail) {
		return NULL; // Coda vuota
	}
	char* path = queue->paths[queue->head];
	queue->head++;
	return path;
}

// Visita una cartella e tutti i suoi elementi
void visitDirectory(const char* path, Queue* queue) {
	DIR* dir = opendir(path); // Apri la cartella
	if (dir == NULL) {
		fprintf(stderr, "Errore: Impossibile aprire la cartella %s\n", path);
		return;
	}

	printf("dir: %s\n", path); // Stampa il nome della cartella

	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL) { // Scorro gli elementi della cartella
		char fullpath[MAX_PATH_LENGTH];
		sprintf(fullpath, "%s/%s", path, entry->d_name);

		if (entry->d_type == DT_DIR) { // Se l'elemento è una cartella
		if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) { // Ignora . e ..
		enqueue(queue, fullpath); // Aggiungi la cartella alla coda per visitarla in seguito
		}
		} else if (entry->d_type == DT_REG) { // Se l'elemento è un file
			char* extension = strrchr(entry->d_name, '.'); // Estrai l'estensione del file
			if (extension != NULL && strcmp(extension, ".dat") == 0) { // Se l'estensione è .dat
			//printf("- %s\n", entry->d_name); // Stampa il nome del file
			//printf("\n*%s*\n",fullpath);
			char nomef[256];
			strcpy(nomef,entry->d_name);
			export_data(fullpath,nomef);
			}	
		}
	}	

	closedir(dir); // Chiudi la cartella
}


// Calcola la media dei numeri all'interno del file specificato dal percorso.
// Stampa il risultato a schermo.
void export_data(const char* filepath,char* nomef) {

	FILE* file = fopen(filepath, "r");
	if (file == NULL) {
		fprintf(stderr, "Errore nell'apertura del file %s\n", filepath);
		return;
	}

	// Conta il numero di numeri all'interno del file
	int num_count = 0;
	double num_sum = 0.0;
	double num;
	double deviaziones=0.0;
	double s_dev_pot=0.0;
	double average=0.0;
	while (fscanf(file, "%lf", &num) == 1) {
		num_count++;
		num_sum += num;
		//printf("num: %lf",num);
	}
	
	if (num_count == 0) {
		average=0;
	//printf("null");
	//printf(" Il file %s è vuoto o non contiene numeri.\n", filepath);
	} else {
		average = num_sum / num_count;
		average = trunc(average*100)/100;
	//printf("   La media dei numeri nel file %s è: %.2f\n", filepath, average);
	}
	
	fclose(file);
	file=fopen(filepath,"r");
	//calcolo deviazione standard
	while(fscanf(file,"%lf", &num) == 1){
	//printf("num1: %lf",num);
		s_dev_pot=s_dev_pot+pow((num-average),2);
	}
	if(num_count == 0){
		deviaziones=0;
	}
	else{
		deviaziones=sqrt(s_dev_pot/num_count);
		deviaziones = trunc(deviaziones*100)/100;
	}
	//printf("deviazione standard= %.2f\n",deviaziones);

	
	fclose(file);
	if(num_count != 0){
		printf("%d\t\t%.2f\t\t%.2f\t\t%s\n",num_count,average,deviaziones,nomef);
	}else
	{
		printf("%d\t\t0\t\t0\t\t%s\n",num_count,nomef);
	}
}



int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Utilizzo: %s directory\n", argv[0]);
		return 1;
	}

	printf("n \t\t avg \t\t std \t\t file \n");
	printf("________________________________________________________________\n");
	Queue queue;
	initQueue(&queue);
	//printf("ciaooo %s",argv[1]);
	int length=strlen(argv[1]);	 
	if(length>0 && argv[1][length-1]== '/'){
		argv[1][length-1]='\0';
	}
	enqueue(&queue, argv[1]); // Aggiungi la directory iniziale alla coda
	
	while (1) { // Visita le cartelle in BFS
		char* path = dequeue(&queue); // Prendi la prossima cartella dalla coda
		if (path == NULL) { 
			break;
		}
	visitDirectory(path, &queue); // Inizia visita
	//free(path); // Libera la memoria allocata per il percorso corrente
	}
	printf("________________________________________________________________\n");
	return 0;
}

