#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;

};

struct node* head;
struct node* tail;

struct node* reverseQueue(struct node* queue, int k); //Function to reverse the queue by K elements
void insertLast(int n);
void print();

int main() {
    //Test variables
    insertLast(10);
    insertLast(20);
    insertLast(30);
    insertLast(40);
    insertLast(50);
    insertLast(60);
    insertLast(70);
    insertLast(80);
    insertLast(90);
    insertLast(100);
    print();
    reverseQueue(head, 5);
    print();
}

void insertLast(int n){
    struct node* newNode = (struct node*)malloc(sizeof(struct node*));
    newNode->data = n;
    newNode->next = NULL;
    if (head == NULL && tail == NULL){
        head = newNode;
        tail = newNode;
        return;
    }
    else {
        struct node* current = head;
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
        tail = newNode;
    }
}

struct node* reverseQueue(struct node* queue, int k){
    //Declare a new integer to keep track of total # of elements
    int j = k;
    //First need to iterate through the queue, storing k values through a new array
    //Declaration of a new array
    int reverse[j];
    //Allowing current node to be placed at head node, allowing it to be iterated through
    struct node* current = head;
    for (int i = k; i>0; i--){
        reverse[j-i] = current->data;
        current=current->next;
    }
    //Now need to reverse the newly created queue
    for (int i = 0; k>i; i++){
        int temp = reverse[i];
        reverse[i] = reverse[k-1];
        reverse[k-1] = temp;
        k--;
    }
    k = j;
    current = head;
    //Need to now input the reverse array back into the queue
    for (int i = 0; k>i; i++){
        current->data = reverse[i];
        current = current->next;
    }
    //Simply return the queue back to the main function
    return queue;
}

void print(){
    struct node* current = head;
    while (current != NULL){
        printf("\t%d", current->data);
        current = current->next;
    }
    printf("\n");
}