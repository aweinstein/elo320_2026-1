/* Implementacion basica de lista enlazada simple.
   Basada en https://github.com/skorks/c-linked-list
*/
#include <stdio.h>
#include <stdlib.h>

/*
Ejemplo en que trabajamos directamente con head, en vez de con la lista

typedef struct List {
  Node *head;
} List;
*/

typedef struct Node {
  int key;
  struct Node * next;
} Node;


/* Prototipo de funciones */
void add(int key, Node **head);
void add_nw(int key, Node *head); // Por que no funciona
void display(Node *head);

int main(void)
{
    Node *a_head = NULL; // lista vacia
    printf("Ejemplo de implementacion de listas enlazada simple.\n");
    // Crear una lista vacia
    add_nw(5, a_head);
    add_nw(27, a_head);
    add_nw(39, a_head);
    display(a_head);

    printf("Por que no funciona?\n");
    printf("Probando con la otra funcion\n\n");
    a_head = NULL;
    add(5, &a_head);
    add(27, &a_head);
    add(39, &a_head);
    display(a_head);

    return 0;
}


Node *create_node(int key)
{
    Node * new_node = malloc(sizeof(Node));
    if(new_node == NULL)
        return NULL;
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}


// Agrega un nodo al final de la lista
void add(int key, Node **head)
{
    Node *current = NULL;
    if(*head == NULL) // La lista esta vacia, es el primer nodo
        *head = create_node(key);
    else { // Si no esta vacia, tenemos que encontrar el ultimo nodo
        current = *head;
        while(current->next != NULL)
            current = current->next;
      current->next = create_node(key);
    }
}


void add_nw(int key, Node *head)
{
    Node *current = NULL;
    if(head == NULL) // La lista esta vacia, es el primer nodo
        head = create_node(key);
    else { // Si no esta vacia, tenemos que encontrar el ultimo nodo
        current = head;
        while(current->next != NULL)
            current = current->next;
      current->next = create_node(key);
    }
}

void display(Node *head)
{
    Node *current = head;
    while(current != NULL) {
        printf("%d \n", current->key);
        current = current->next;
    }
    printf("NULL\n");
}

