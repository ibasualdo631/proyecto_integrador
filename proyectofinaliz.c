#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { // LA ESTRUCTURA DE NUESTRA BDD "REGISTRO"
	int anio;
	int codigo_id;
	char delito[500];
	int cantidad_hechos;
	int cantidad_victimas;
	int cantidad_victimas_masc;
	int cantidad_victimas_fem;
	int cantidad_victimas_sd;
	float tasa_hechos;
	float tasa_victimas;
	float tasa_victimas_masc;
	float tasa_victimas_fem;
} Registro;

Registro registros[20000];
int n = 0; // cantidad de registros cargados

// ------------ Funciones auxiliares ------------

// Lectura del archivo CSV

void leerCSV(const char *nombreArchivo) 
{
	FILE *f = fopen(nombreArchivo, "r");
	if (!f) 
	{
		printf("Error al abrir el archivo.\n");
		return;
	}
	char linea[1024];
	fgets(linea, 1024, f); // saltar encabezado
	
	while (fgets(linea, 1024, f) && n < 20000) 
	{
		char *token = strtok(linea, ",");
		registros[n].anio = atoi(token);
		
		token = strtok(NULL, ",");
		registros[n].codigo_id = atoi(token);
		
		token = strtok(NULL, ",");
		strncpy(registros[n].delito, token, 500);
		
		registros[n].cantidad_hechos = atoi(strtok(NULL, ","));
		registros[n].cantidad_victimas = atoi(strtok(NULL, ","));
		registros[n].cantidad_victimas_masc = atoi(strtok(NULL, ","));
		registros[n].cantidad_victimas_fem = atoi(strtok(NULL, ","));
		registros[n].cantidad_victimas_sd = atoi(strtok(NULL, ","));
		registros[n].tasa_hechos = atof(strtok(NULL, ","));
		registros[n].tasa_victimas = atof(strtok(NULL, ","));
		registros[n].tasa_victimas_masc = atof(strtok(NULL, ","));
		registros[n].tasa_victimas_fem = atof(strtok(NULL, ","));
		
		n++;
	}
	
	fclose(f);
	printf("Archivo cargado con %d registros.\n", n);
}

// Total de hechos por año

void contarHechosPorAnio(int anio) {
	int total = 0;
	for (int i = 0; i < n; i++)
		if (registros[i].anio == anio)
			total += registros[i].cantidad_hechos;
	
	printf("Total de hechos en %d: %d\n", anio, total);
}

// Delito con más víctimas
void delitoMasVictimas() 
{
	int max = -1, pos = -1;
	for (int i = 0; i < n; i++) {
		if (registros[i].cantidad_victimas > max) 
		{
			max = registros[i].cantidad_victimas;
			pos = i;
		}
	}
	if (pos != -1) 
	{
		printf("Delito con más víctimas: %s (%d víctimas)\n",registros[pos].delito, registros[pos].cantidad_victimas);
	}
}

// Buscar delito por nombre

void buscarDelitoPorNombre(const char *nombre) 
{
	int encontrados = 0;
	for (int i = 0; i < n; i++) 
	{
		if (strstr(registros[i].delito, nombre)) 
		{
			printf("Año %d | %s | Hechos: %d | Víctimas: %d\n",
				   registros[i].anio, registros[i].delito,
				   registros[i].cantidad_hechos,
				   registros[i].cantidad_victimas);
			encontrados++;
		}
	}
	if (!encontrados)
		printf("No se encontraron delitos con '%s'.\n", nombre);
}

// Comparar dos años

void compararAnios(int anio1, int anio2) 
{
	int total1 = 0, total2 = 0;
	for (int i = 0; i < n; i++) {
		if (registros[i].anio == anio1)
			total1 += registros[i].cantidad_hechos;
		if (registros[i].anio == anio2)
			total2 += registros[i].cantidad_hechos;
	}
	printf("Hechos %d: %d | Hechos %d: %d\n", anio1, total1, anio2, total2);
}

// Porcentaje hombres/mujeres

void porcentajeVictimas() {
	int masc = 0, fem = 0;
	for (int i = 0; i < n; i++) {
		masc += registros[i].cantidad_victimas_masc;
		fem += registros[i].cantidad_victimas_fem;
	}
	int total = masc + fem;
	if (total == 0) {
		printf("No hay datos.\n");
		return;
	}
	printf("Masculino: %.2f%% | Femenino: %.2f%%\n",
		   (masc * 100.0) / total, (fem * 100.0) / total);
}

// MENU PPAL MENU PPAL MENU PPAL MENU PPALMENU PPAL MENU PPALMENU PPALMENU PPAL

int main() {
	int opcion;
	char nombreArchivo[500] = "delincuencia.csv";
	
	do {
		printf("\n--- MENU ---\n");
		printf("1. Total de hechos por año\n");
		printf("2. Delito con más víctimas\n");
		printf("3. Buscar delito por nombre\n");
		printf("4. Comparar dos años\n");
		printf("5. Porcentaje víctimas hombres vs mujeres\n");
		printf("0. Salir\n");
		printf("Opcion: ");
		scanf("%d", &opcion);
		
		if (opcion == 1) {
			int anio;
			printf("Ingrese año: ");
			scanf("%d", &anio);
			contarHechosPorAnio(anio);
		} else if (opcion == 2) {
			delitoMasVictimas();
			
		// ESTA OPCION DEBERIAMOS CAMBIARLA EN REALIDAD, YA QUE NUNCA LO APRENDIMOS, PROPONGO HACER ALGO MÁS SIMPLE PARA LA BÚSQUEDA.
			
		} else if (opcion == 3) 
		{
			char nombre[500];
			printf("Ingrese parte del nombre del delito: ");
			scanf(" %[^\n]", nombre);
			buscarDelitoPorNombre(nombre);
			
		// 

		} else if (opcion == 4) 
		{
			int a1, a2;
			printf("Ingrese primer año: ");
			scanf("%d", &a1);
			printf("Ingrese segundo año: ");
			scanf("%d", &a2);
			compararAnios(a1, a2);
		} else if (opcion == 5) {
			porcentajeVictimas();
		}
	} while (opcion != 0);
	
	printf("Saliendo...\n");
	return 0;
}

// hola que tal estoy probando el git jejej
