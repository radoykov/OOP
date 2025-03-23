#include <iostream>

using namespace std;

int ERROR2 = 0;

struct vector_t
{
    int *data;
    size_t size;
    size_t capacity;
} typedef Vector;

struct vector_t *initVector();

void pushBack(Vector *v, int number);
int insert(Vector *v, int index, int number);
int remove(Vector *v, int index);
void resize(Vector *v);

//////////////////////////////
// Vector's size:
// Vector's capacity:
// Vector's data:
//////////////////////////////
void print(Vector *v);

/**
 * @brief Returns the element at the provided index
 *
 * @param v
 * @param index
 * @return int
 */
int at(Vector *v, int index)
{
    // if(v->size == 0){
    //     return ERROR2;
    // }
    if (index < 0 || index + 1 > v->size)
    {
        return ERROR2;
    }
    return v->data[index];
}

/**
 * @brief Pops the last element of the vector
 *
 * @param v
 * @return int if successful, ERROR2 - if not
 */
int pop(Vector *v)
{
    return v->size == 0 ? ERROR2 : v->data[--v->size];
}

/**
 * @brief Frees the memory allocated by the vector
 *
 * @param v
 */
void destroy(Vector *v)
{
    delete[] v->data;
    delete v;
}

/**
 * @brief Adds an element in the beginning of the vector
 *
 * @param v
 * @param number
 */
void pushFront(Vector *v, int number)
{
    insert(v, 0, number);
}

/**
 * @brief Pops the first element of the vector
 *
 * @param v
 * @return int if successful, ERROR2 - if not
 */
int popFront(Vector *v)
{
    return remove(v, 0);
}

/**
 * @brief Inserts an element at a given index
 *
 * @param v
 * @param index
 * @param number
 * @return int 0 if successful, ERROR2 - if not
 */
int insert(Vector *v, int index, int number)
{
    if (index < 0)
    {
        return ERROR2;
    }

    if (v->size == v->capacity)
    {
        resize(v);
    }
    v->size++;

    for (int i = v->size - 1; i > index; i--)
    {
        v->data[i] = v->data[i - 1];
    }
    v->data[index] = number;

    return 0;
}

/**
 * @brief Removes an element at a given index
 *
 * @param v
 * @param index
 * @param number
 * @return int the number if usccesful, ERROR2 - if not
 */
int remove(Vector *v, int index)
{
    if (index < 0 || index + 1 > v->size)
    {
        return ERROR2;
    }

    int num = v->data[index];
    for (int i = index; i < v->size - 1; i++)
    {
        v->data[i] = v->data[i + 1];
    }
    v->size--;

    return num;
}

struct vector_t *initVector()
{
    Vector *v = new Vector();
    v->size = 0;
    v->capacity = 2; // 5
    v->data = new int[v->capacity];

    return v;
}

void pushBack(Vector *v, int number)
{
    if (v->size == v->capacity)
    {
        resize(v);
    }
    v->data[v->size++] = number; //++i i++
}

void resize(Vector *v)
{
    v->capacity *= 2;
    int *tmp = new int[v->capacity];
    for (size_t i = 0; i < v->size; i++)
    {
        tmp[i] = v->data[i];
    }
    delete[] v->data;
    v->data = tmp;
}

void print(Vector *v)
{
    cout << "Vector's size: " << v->size << endl;
    cout << "Vector's capacity: " << v->capacity << endl;
    cout << "Vector's data: [";

    if (v->size > 0)
        cout << v->data[0];
    for (size_t i = 1; i < v->size; i++)
    {
        cout << " " << v->data[i];
    }
    cout << "]" << endl;
}
// int main()
// {
//     Vector *v = initVector();
//     // pushBack(v, 2);
//     // pushBack(v, 3);
//     // print(v);
//     cout << at(v, 0);
//     return 0;
// }
