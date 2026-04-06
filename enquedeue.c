#include <stdio.h>

#define MAX 100

int queue[MAX];
int front = -1, rear = -1;

// Enqueue
void enqueue(int x) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = x;
}

// Dequeue
void dequeue() {
    if (front == -1 || front > rear) return;
    printf("%d ", queue[front]);
    front++;
}

int main() {
    int n, i, x;

    // Number of print jobs
    scanf("%d", &n);

    // Input jobs
    for (i = 0; i < n; i++) {
        scanf("%d", &x);
        enqueue(x);
    }

    // Process jobs (FIFO)
    for (i = 0; i < n; i++) {
        dequeue();
    }

    return 0;
}
