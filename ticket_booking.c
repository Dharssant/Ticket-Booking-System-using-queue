#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10

struct User {
    char name[50];
    char phone[15];
};

struct Queue {
    struct User users[MAX];
    int front, rear;
};

void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isFull(struct Queue* q) {
    return q->rear == MAX - 1;
}

int isEmpty(struct Queue* q) {
    return q->front == -1;
}

void enqueue(struct Queue* q, struct User user) {
    if (isFull(q)) {
        printf("Today's ticket is full. Meet you next day.\n");
    } else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->users[q->rear] = user;
        printf("Ticket for %s (%s) booked successfully.\n", user.name, user.phone);
    }
}

void cancelTicket(struct Queue* q, char* name, char* phone) {
    if (isEmpty(q)) {
        printf("No tickets booked.\n");
        return;
    }

    int found = 0;
    for (int i = q->front; i <= q->rear; i++) {
        if (strcmp(q->users[i].name, name) == 0 && strcmp(q->users[i].phone, phone) == 0) {
            found = 1;
            // Shift elements to remove the ticket
            for (int j = i; j < q->rear; j++) {
                q->users[j] = q->users[j + 1];
            }
            q->rear--;
            printf("Ticket for %s (%s) cancelled successfully.\n", name, phone);
            if (q->rear < q->front) {
                q->front = q->rear = -1;
            }
            break;
        }
    }
    if(!found){
        printf("Ticket not found.\n");
    }
}

void displayQueue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("No tickets booked yet.\n");
    } else {
        printf("Tickets booked:\n");
        for (int i = q->front; i <= q->rear; i++) {
            printf("%d. Name: %s, Phone: %s\n", i + 1, q->users[i].name, q->users[i].phone);
        }
    }
}

int main() {
    struct Queue q;
    initQueue(&q);

    struct User user;
    char name[50],phone[15];
    int choice;

    do {
        printf("\n1. Book Ticket\n2. Display Tickets\n3. Cancel Ticket\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter Name: ");
                scanf("%s", user.name);
                printf("Enter Phone Number: ");
                scanf("%s", user.phone);
                enqueue(&q, user);
                break;
            case 2:
                displayQueue(&q);
                break;
            case 3:
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Phone Number: ");
                scanf("%s", phone);
                cancelTicket(&q, name, phone);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
