#include <stdio.h>
#include <stdlib.h>

typedef  struct Node {
  int key;
  struct Node *next;
} Node;

int main(void)
{
 printf("Lista enlazada simple\n");
 // Solo como primer ejemplo con fines padagogicos.
 // Ver ex_lista_simple_2.c para una mejor implementacion.
 
 Node *a = malloc(sizeof(Node));
 Node *b = malloc(sizeof(Node));
 Node *c = malloc(sizeof(Node));
 
 a->key = 12;
 b->key = 34;
 c->key = 56;
 
 a->next = b;
 b->next = c;
 c->next = NULL;
 
 // Imprimir la lista en orde
 Node *current = a; // Magicamente se que la lista parte en a
 while(current != NULL)
 {
  printf("%d -> ", current->key);
  current = current->next;   
 }
 printf("NULL\n");
 
 free(a);
 free(b);
 free(c);
 
 return 0;   
}
