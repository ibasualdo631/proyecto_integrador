#include <stdio.h>
#include <stdlib.h>


struct Nodo 
{
	int valor;
	struct Nodo* siguiente;
};


void agregarnodo(struct Nodo** head, int valor);
void imprimir(struct Nodo* head);

int main() 
{
	struct Nodo* lista = NULL; // listaaa vaciax
	int v;
	
	// Insertar 5 valores
	for (int i = 0; i < 5; i++) 
	{
		printf("Ingrese un numero [%d]: ", i + 1);
		scanf("%d", &v);
		agregarnodo(&lista, v); // paso direccion de memoria de lista como puntero a la estructura, y paso el valor que ingreso el usuario el siguiente nodo 
	}
	
	// Mostrar la lista
	printf("\nLa lista es:\n");
	imprimir(lista);
	
	return 0;
}


void agregarnodo(struct Nodo** head, int valor) 
{
	struct Nodo* nuevo = (struct Nodo*) malloc(sizeof(struct Nodo)); // asigno memoria para el nuevo nodo
	nuevo->valor = valor; // asigno el valor al nodo
	nuevo->siguiente = NULL; // la posicion siguiente al nuevo nodo es NULL, ya que ahi termina la lista
	
	if (*head == NULL) // me fijo si la lista estÃ¡ vacÃ­a
	{
		*head = nuevo; // si la lista estÃ¡ vacÃ­a, mi head va a ser el nuevo nodo
	} else {
		struct Nodo* actual = *head;
		while (actual->siguiente != NULL) 
		{
			actual = actual->siguiente;
		}
		actual->siguiente = nuevo; // se enlaza al final
	}
}

void imprimir(struct Nodo* head) 
{
	struct Nodo* actual = head; // creo un nodo auxiliar, que vendria a ser i = 0 en un for
	while (actual != NULL) // mientras el nodo actual no sea el fin de la lista (NULL)
	{
		printf("%d -> ", actual->valor); // imprimo el valor del nodo actual
		actual = actual->siguiente; // avanzo al siguiente nodo i ++
	}
	printf("NULL\n"); // esto es innecesario, pero sirve para indicar el fin de la lista
}
