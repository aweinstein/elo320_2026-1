/* Implementacion basica de lista enlazada simple.
   Basada en https://github.com/skorks/c-linked-list
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int key;
  struct Node * next;
} Node;

typedef struct List {
  Node *head;
} List;


/* Prototipo de funciones */
List * makelist();
Node * create_node(int key);
void add(int key, List *list);
void delete(int key, List *list);
void display(List *list);
void reverse(List *list);
void reverse_using_two_pointers(List *list);
void destroy(List *list);

int main(void)
{
    List *a;

    printf("Ejemplo de implementacion de listas enlazada simple.\n");
    // Crear una lista vacia
    a = makelist();
    printf("Imprimir la lista vacia:\n");
    display(a);
    add(5, a);
    add(27, a);
    add(39, a);
    printf("\nImprimir despues de agregar algunos nodos\n");
    display(a);
    printf("\nRemovemos un node en el medio.\n");
    delete(27, a);
    display(a);
    printf("\nAgregamos otros nodos.\n");
    add(134, a);
    add(98, a);
    add(14, a);
    add(31, a);
    display(a);
    printf("\nRemovemos el primer nodo.\n");
    delete(5, a);
    display(a);
    printf("\nRemovemos un nodo que no existe.\n");
    delete(12345, a);
    display(a);
    printf("\nRemovemos el ultimo nodo.\n");
    delete(31, a);
    display(a);
    printf("\nInvertimos el orden de la lista\n");
    reverse(a);
    display(a);
    printf("\nBye bye list.\n");
    destroy(a);
    return 0;
}

List * makelist(void)
{
    List *list = malloc(sizeof(List));
    if(list == NULL)
        return NULL;
    list->head = NULL;
    return list;
}


Node * create_node(int key)
{
    Node * new_node = malloc(sizeof(Node));
    if(new_node == NULL)
        return NULL;
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}


// Agrega un nodo al final de la lista
void add(int key, List *list)
{
    Node *current = NULL;
    if(list->head == NULL) // La lista esta vacia, es el primer nodo
        list->head = create_node(key);
    else { // Si no esta vacia, tenemos que encontrar el ultimo nodo
        current = list->head;
        while(current->next != NULL)
            current = current->next;
      current->next = create_node(key);
    }
}


void display(List *list)
{
    Node *current = list->head;
    while(current != NULL) {
        printf("%d \n", current->key);
        current = current->next;
    }
    printf("NULL\n");
}

// Remueve de la lista el nodo en donde aparece key por primera vez
void delete(int key, List *list)
{
    Node *current, *previous;
    current = list->head;
     while(current != NULL) {
        if(current->key == key) {
            if(current == list->head) // Actualizar head si eliminamos el primer nodo
                list->head = current->next;
            else
                previous->next = current->next;
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}


void destroy(List *list)
{
    Node *current, *next;
    current = list->head;
    next = current;
    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void reverse(List *list)
{
    Node *reversed, *current, *tmp;
    reversed= NULL; 
    current = list->head;
    while(current != NULL) {
        tmp = current;
        current = current->next;
        tmp->next = reversed;
        reversed = tmp;
    }
    list->head = reversed;
}



