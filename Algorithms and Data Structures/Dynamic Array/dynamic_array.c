#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct array {
    int *begin;
    int *end;
    int size;
    int capacity;
};

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int* resize(int new_capacity, struct array *arr) {
    if (arr->begin = realloc(arr->begin, new_capacity * sizeof(int)))
        arr->capacity = new_capacity;
    
    return arr->begin;
}

int expandable(struct array *arr) {
    return arr->size + 1 > arr->capacity;
}

int shrinkable(struct array *arr) {
    return arr->size <= arr->capacity / 2;
}


int size(struct array *arr) {
    return arr->size;
}

int capacity(struct array *arr) {
    return arr->capacity;
}

void push_back(int value, struct array *arr) {
    if (arr->begin == NULL) {
        arr->begin = arr->end = malloc(sizeof(int));
        arr->capacity = 1;
    }

    if (expandable(arr)) {
        arr->begin = resize(arr->capacity * 2, arr);
        arr->end = arr->begin + arr->size;
    }
    
    *arr->end++ = value;
    arr->size++;
}

int pop_back(struct array *arr) {
    if (arr->size == 0) {
        if (arr->begin != NULL)
            free(arr->begin);
        
        arr->begin = arr->end = NULL;
        arr->capacity = 0;
        
        return -1;
    }

    int value = *(arr->end -= 1);
    arr->size--;

    if (shrinkable(arr)) {
        arr->begin = resize(arr->capacity / 2, arr);
        arr->end = arr->begin + arr->size;
    }

    return value;
}

int at(int index, struct array *arr) {
    if (index > arr->size - 1 || index < 0)
        return -1;
    
    return arr->begin[index];
}

int assign_at(int index, int value, struct array *arr) {
    if (at(index, arr) == -1)
        return -1;

    arr->begin[index] = value;
    
    return 0;
}

int insert_at(int index, int value, struct array *arr) {
    if (at(index, arr) == -1)
        return -1;

    push_back(value, arr);
    
    for (int i = arr->size - 2; i >= index; i--)
        swap(&arr->begin[i + 1], &arr->begin[i]);
    
    return 0;
}

int remove_at(int index, struct array *arr) {
    if (at(index, arr) == -1)
        return -1;
    
    for (int i = index; i < arr->size - 1; i++)
        swap(&arr->begin[i], &arr->begin[i + 1]);
    
    pop_back(arr);
    
    return 0;
}

int search(int value, struct array *arr) {
    for (int i = 0; i < arr->size; i++)
        if (arr->begin[i] == value)
            return i;

    return -1;
}

int reserve(int size, struct array *arr) {
    int *result;
    if (size > arr->size) 
        result = resize(size, arr);
    arr->end = arr->begin + arr->size;
    
    return result != NULL;
}

void clear(struct array *arr) {
    for (int i = 0; i < arr->size; i++)
        arr->begin[i] = 0;
}

void fill(int value, struct array *arr) {
    while (arr->size < arr->capacity)
        push_back(value, arr);
}

void rand_fill(struct array *arr) {
    srand(time(0));
    while (arr->size < arr->capacity)
        push_back(rand() % 100, arr);
}


void test(struct array *arr) {
    puts("Test of dynamic array\n");
    printf("Popped value: %d\n", pop_back(arr));
    printf("Popped value: %d\n", pop_back(arr));
    printf("Remove at index %d: %d\n", 0, remove_at(0, arr));
    printf("Remove at index %d: %d\n", 21, remove_at(21, arr));
    printf("Push %d\n", remove_at(0, arr));
}

int main() {
    struct array *arr = calloc(1, sizeof(struct array));

    test(arr);

    int choice = -1;
    while (choice) {
        puts("\n--- Dynamic Array ---");
        puts("1. Push value to the back");
        puts("2. Pop value from the back");
        puts("3. Insert value at index");
        puts("4. Remove value at index");
        puts("5. Assign value at index");
        puts("6. Search value in array");
        puts("7. Reserve space for array");
        puts("8. Fill/Clear array");
        puts("9. Print array iformation");
        puts("0. Exit");
        
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) == 0)
            break;
        
        int index = -1, value = 0;
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push_back(value, arr);
                break;
            case 2:
                value = pop_back(arr);
                printf("Popped value: %d\n", value);
                break;
            case 3:
                printf("Enter index: ");
                scanf("%d", &index);
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert_at(index, value, arr);
                break;
            case 4:
                printf("Enter index: ");
                scanf("%d", &index);
                printf("Enter value to remove: ");
                scanf("%d", &value);
                remove_at(index, arr);
                break;
            case 5:
                printf("Enter index: ");
                scanf("%d", &index);
                printf("Enter value to assign: ");
                scanf("%d", &value);
                assign_at(index, value, arr);
                break;
            case 6:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if ((index = search(value, arr)) == -1)
                    printf("Not found\n");
                else
                    printf("Found at index %d\n", index);
                break;
            case 7:
            {
                int space;
                printf("Enter space to reserve: ");
                scanf("%d", &space);
                if (reserve(space, arr))
                    puts("Succeed to reserve space");
                else
                    puts("Failed to reserve space");
                break;
            }
            case 8:
            {
                int operation;
                puts("\n1. Fill array with designated value");
                puts("2. Fill array with random values");
                puts("3. Clear array (set values to zero)");
                
                printf("\nEnter number of operation: ");
                if (scanf("%d", &operation) == 0)
                    break;
                
                if (operation == 1) {
                    printf("Enter value to fill array: ");
                    scanf("%d", &value);
                    fill(value, arr);
                }
                if (operation == 2)
                    rand_fill(arr);
                if (operation == 3)
                    clear(arr);
                break;
            }
            case 9:
                printf("Array capacity = %d, size = %d\n", capacity(arr), size(arr));
                for (int i = 0; i < arr->size; i++)
                    printf("%d ", at(i, arr));
                printf("\n");
                break;
        }
    }

    free(arr);    
    return 0;
}
