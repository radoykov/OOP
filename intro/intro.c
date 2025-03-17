#include <stdio.h>
#include <stdlib.h>

#define CHECK(arr)                            \
    if (!arr)                                 \
    {                                         \
        printf("\nError allocating memory."); \
        exit(1);                              \
    }

typedef struct Vector
{
    int size;
    int capacity;
    int *array;
} Vector;

Vector *create()
{
    Vector *v = (Vector *)malloc(sizeof(Vector));
    CHECK(v);
    v->size = 0;
    v->capacity = 2;
    v->array = (int *)calloc(v->capacity, sizeof(int));
    CHECK(v->array);

    return v;
}

void add(Vector *v, int num)
{
    if (v->size == v->capacity)
    {
        v->capacity *= 2;
        v->array = (int *)realloc(v->array, v->capacity * sizeof(int));
        CHECK(v->array);
    }

    v->array[v->size++] = num;
}

int removeBack(Vector *v)
{
    if (v->size <= v->capacity / 2)
    {
        v->capacity /= 2;
        v->array = (int *)realloc(v->array, v->capacity * sizeof(int));
        CHECK(v->array);
    }

    return v->array[--v->size];
}

void freeVector(Vector *v)
{
    free(v->array);
    free(v);
}

void print(Vector *v)
{
    printf("Size: %d\n", v->size);
    printf("Capacity: %d\n", v->capacity);

    for (int i = 0; i < v->size; i++)
    {
        printf("%d, ", v->array[i]);
    }

    printf("\n");
}

int main()
{
    Vector *vector = create();
    print(vector);

    add(vector, 10);
    add(vector, 20);
    add(vector, 30);

    print(vector);

    int a = removeBack(vector);
    printf("Removed: %d\n", a);
    print(vector);

    freeVector(vector);

    return 0;
}