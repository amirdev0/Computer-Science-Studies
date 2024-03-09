#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

struct queue {
    int *base;
    int *front;
    int *rear;
};

void enqueue(int value, struct queue *queue) {
    if (queue->rear + 1 == queue->front)
        return;
    
    *queue->rear = value;

    if (queue->rear + 1 > queue->base + SIZE) {
        if (queue->base == queue->front)
            return;
        else
            queue->rear = queue->base;
    }
    else
        queue->rear = queue->rear + 1;
}

int dequeue(struct queue *queue) {
    if (queue->front == queue->rear)
        return -1;

    int value = *queue->front;
    *queue->front = -1;

    if (queue->front + 1 > queue->base + SIZE)
        queue->front = queue->base;
    else
        queue->front = queue->front + 1;

    return value;
}

void draw(struct queue *queue) {
    int *iterator = queue->front;
    
    printf("front : ");
    while (iterator != queue->rear) {
        if (iterator + 1 > queue->base + SIZE + 1) {
            if (queue->base == queue->rear)
                break;
            iterator = queue->base;
        }

        printf("%d ", *iterator++);
    }
        
    printf(": rear\n");
}

void test(struct queue *queue) {
    printf("dequeue: %d\n", dequeue(queue));
    printf("dequeue: %d\n\n", dequeue(queue));
    
    printf("enqueue: 23\n"), enqueue(23, queue);
    printf("dequeue: %d\n\n", dequeue(queue));
    
    printf("enqueue: 20\n"), enqueue(20, queue);
    printf("dequeue: %d\n\n", dequeue(queue));
    
    printf("dequeue: %d\n", dequeue(queue));
    printf("dequeue: %d\n\n", dequeue(queue));
    
    printf("enqueue: 1\n"), enqueue(1, queue);
    printf("enqueue: 2\n"), enqueue(2, queue);
    printf("enqueue: 3\n"), enqueue(3, queue);
    printf("enqueue: 4\n"), enqueue(4, queue);
    printf("enqueue: 5\n"), enqueue(5, queue);
    printf("enqueue: 6\n"), enqueue(5, queue);
    puts("\nQueue structure: ");
    draw(queue);
    
    printf("dequeue: %d\n", dequeue(queue));
    printf("dequeue: %d\n", dequeue(queue));
    printf("dequeue: %d\n", dequeue(queue));
    printf("dequeue: %d\n", dequeue(queue));
    puts("\nQueue structure: ");
    draw(queue);
    
    printf("dequeue: %d\n", dequeue(queue));
    puts("\nQueue structure: ");
    draw(queue);
    
    printf("enqueue: 1\n"), enqueue(1, queue);
    puts("\nQueue structure: ");
    draw(queue);
    
    printf("dequeue: %d\n", dequeue(queue));
    puts("\nQueue structure: ");
    draw(queue);
}

int main()
{
    struct queue *queue = malloc(sizeof(struct queue));
    queue->base = queue->front = queue->rear = malloc((SIZE + 1) * sizeof(int));

    test(queue);

    int choice = -1;
    while (choice) {
        puts("\n1. Enqueue element to queue");
        puts("2. Dequeue element from queue");
        puts("3. Draw queue graphically");
        puts("0. Exit");
        
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        int value;
        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value, queue);
                break;
            case 2:
                printf("Dequeued value: %d\n", dequeue(queue));
                break;
            case 3:
                puts("\nQueue structure: ");
                draw(queue);
                break;
        }
    }

    free(queue->base);
    free(queue);
    return 0;
}
