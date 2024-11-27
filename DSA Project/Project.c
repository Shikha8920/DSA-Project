#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 5
#define MAX_ITEM_NAME 50

// Structure to represent an order
typedef struct {
    int orderId;
    char itemName[MAX_ITEM_NAME];
} Order;

// Structure to represent the circular queue
typedef struct {
    Order orders[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} CircularQueue;

// Function to initialize the queue
void initializeQueue(CircularQueue* queue) {
    queue->front = -1;
    queue->rear = -1;
    queue->size = 0;
}

// Function to check if the queue is full
int isFull(CircularQueue* queue) {
    return queue->size == MAX_QUEUE_SIZE;
}

// Function to check if the queue is empty
int isEmpty(CircularQueue* queue) {
    return queue->size == 0;
}

// Function to add an order to the queue (enqueue)
void enqueue(CircularQueue* queue, Order order) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot add more orders.\n");
        return;
    }

    if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    queue->orders[queue->rear] = order;
    queue->size++;

    printf("Order %d added: %s\n", order.orderId, order.itemName);
}

// Function to remove and return an order from the queue (dequeue)
Order dequeue(CircularQueue* queue) {
    Order emptyOrder = {-1, ""};

    if (isEmpty(queue)) {
        printf("Queue is empty. No orders to serve.\n");
        return emptyOrder;
    }

    Order order = queue->orders[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    queue->size--;

    if (isEmpty(queue)) {
        queue->front = -1;
        queue->rear = -1;
    }

    printf("Order %d served: %s\n", order.orderId, order.itemName);
    return order;
}

// Function to display all orders in the queue
void displayOrders(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("No orders in the queue.\n");
        return;
    }

    printf("Current orders in the queue:\n");
    int i, index;
    for (i = 0; i < queue->size; i++) {
        index = (queue->front + i) % MAX_QUEUE_SIZE;
        printf("%d. Order %d: %s\n", i + 1, queue->orders[index].orderId, queue->orders[index].itemName);
    }
}

int main() {
    CircularQueue orderQueue;
    initializeQueue(&orderQueue);

    // Adding orders
    enqueue(&orderQueue, (Order){1, "Burger"});
    enqueue(&orderQueue, (Order){2, "Pizza"});
    enqueue(&orderQueue, (Order){3, "Pasta"});
    enqueue(&orderQueue, (Order){4, "Salad"});
    enqueue(&orderQueue, (Order){5, "Steak"});

    printf("\n");
    displayOrders(&orderQueue);

    printf("\n");
    // Serving orders
    dequeue(&orderQueue);
    dequeue(&orderQueue);

    printf("\n");
    displayOrders(&orderQueue);

    printf("\n");
    // Adding more orders
    enqueue(&orderQueue, (Order){6, "Sushi"});
    enqueue(&orderQueue, (Order){7, "Tacos"});

    printf("\n");
    displayOrders(&orderQueue);

    return 0;
}