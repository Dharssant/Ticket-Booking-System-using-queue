#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of tickets
#define MAX 10

// User structure to store each user's information (name and phone)
struct User {
    char name[50];
    char phone[15];
};

// Queue structure to hold booked tickets (users)
struct Queue {
    struct User users[MAX];
    int front, rear;  // front and rear indexes to manage the queue
};

// Initialize the queue
void initQueue(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is full
int isFull(struct Queue *q) {
    return q->rear == MAX - 1;
}

// Check if the queue is empty
int isEmpty(struct Queue *q) {
    return q->front == -1 || q->front > q->rear;
}

// Enqueue function (book ticket)
void enqueue(struct Queue *q, char name[], char phone[]) {
    if (isFull(q)) {
        printf("Today's ticket is full. Meet you next day.<br>");
    } else {
        if (q->front == -1) q->front = 0;  // Initialize front if empty
        q->rear++;
        strcpy(q->users[q->rear].name, name);  // Copy name to queue
        strcpy(q->users[q->rear].phone, phone);  // Copy phone number to queue
        printf("Ticket for %s (%s) booked successfully.<br>", name, phone);
    }
}

// Display the booked tickets
void display(struct Queue *q) {
    if (isEmpty(q)) {
        printf("No tickets booked yet.<br>");
    } else {
        printf("Booked Tickets:<br>");
        for (int i = q->front; i <= q->rear; i++) {
            printf("Name: %s, Phone: %s<br>", q->users[i].name, q->users[i].phone);
        }
    }
}

// Cancel ticket (Dequeue operation)
void cancelTicket(struct Queue *q, char name[], char phone[]) {
    if (isEmpty(q)) {
        printf("No tickets to cancel.<br>");
        return;
    }

    int found = 0;  // Flag to check if the ticket was found
    for (int i = q->front; i <= q->rear; i++) {
        if (strcmp(q->users[i].name, name) == 0 && strcmp(q->users[i].phone, phone) == 0) {
            found = 1;
            printf("Ticket for %s (%s) cancelled.<br>", name, phone);
            // Shift all remaining users forward
            for (int j = i; j < q->rear; j++) {
                strcpy(q->users[j].name, q->users[j + 1].name);
                strcpy(q->users[j].phone, q->users[j + 1].phone);
            }
            q->rear--;
            if (q->rear < q->front) {
                q->front = -1;
                q->rear = -1;
            }
            break;
        }
    }
    if (!found) {
        printf("Ticket not found for %s (%s).<br>", name, phone);
    }
}

// Main program (CGI script)
int main() {
    struct Queue q;
    initQueue(&q);
    
    char *data;
    char action[10], name[50], phone[15];
    
    // Output CGI headers (necessary for HTTP response)
    printf("Content-type: text/html\n\n");
    
    // Get input from the query string (from the HTML form)
    data = getenv("QUERY_STRING");
    if (data == NULL) {
        printf("Error: No data received.<br>");
        return 1;
    }
    
    // Parse the input (assuming format action=book&name=John&phone=12345)
    sscanf(data, "action=%s&name=%s&phone=%s", action, name, phone);

    // Based on the action, perform different operations
    if (strcmp(action, "book") == 0) {
        enqueue(&q, name, phone);  // Book a ticket
    } else if (strcmp(action, "display") == 0) {
        display(&q);  // Display booked tickets
    } else if (strcmp(action, "cancel") == 0) {
        cancelTicket(&q, name, phone);  // Cancel a ticket
    } else {
        printf("Invalid action.<br>");
    }

    return 0;
}
