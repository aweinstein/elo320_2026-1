#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int read;
    int write;
    int n; // cantidad de datos en cada momento
    int size; // tamanio fijo del buffer
    int *data;  // El tamanio lo definimos en tiempo de ejecucion
} buffer;

/* Protipo de las funciones*/
buffer *make_buffer(int size);
int get_buffer(buffer *b);
void put_buffer(buffer *b, int a);
int is_empty_buffer(buffer *b);
int is_full_buffer(buffer *b);
void display_buffer(buffer *b);
void destroy_buffer(buffer *b);

int main(void)
{
    printf("Buffer circular \n");
    buffer *b = NULL;
    b = make_buffer(10);
    put_buffer(b, 12);
    put_buffer(b, 34);  // debiesemos verificar que hay espacio en el buffer
    display_buffer(b);
    for(int i=0; i < 10; i++) {
        if(!is_full_buffer(b))
            put_buffer(b, i);
        else
            printf("Buffer lleno, no se pudo escribir %d\n", i);
    }
    display_buffer(b);
    printf("Leamos algunos datos\n");
    printf("%d \n", get_buffer(b));  // debiesemos verificar que hay datos
    printf("%d \n", get_buffer(b));  // debiesemos verificar que hay datos
    display_buffer(b);
    printf("Saquemos todos los datos\n");
    while(!is_empty_buffer(b))
        printf("%d ", get_buffer(b));
    printf("\nYa no hay datos :(\n");
    destroy_buffer(b);
    return 0;    
}


buffer *make_buffer(int size)
{
    buffer *b = malloc(sizeof(buffer)); // Falta manejar caso en que falla malloc
    b->read = 0;
    b->write = 0;
    b->n = 0;
    b->size = size;
    b->data = malloc(size * sizeof(int));
    return b;    
}

int get_buffer(buffer *b)
{
    int d;
    d = b->data[b->read];
    b->n--;
    b->read = (b->read + 1) % b->size;
    return d;
}

void put_buffer(buffer *b, int a)
{
    b->data[b->write] = a;
    b->n++;
    b->write = (b->write + 1) % b->size;
}


int is_empty_buffer(buffer *b)
{
    return (b->n == 0);    
}

int is_full_buffer(buffer *b)
{
    return (b->n == b->size);    
}

void display_buffer(buffer *b)
{
    int i, cursor;
    cursor = b->read;
    for(i = 0; i < b->n; i++) {
        printf("%d ", b->data[cursor]);
        cursor = (cursor + 1) % b->size;
    }
    printf("\n");
}

void destroy_buffer(buffer *b)
{
    free(b->data);
    free(b);    
}
