#include <stdio.h>
#include <stdlib.h>

//Used to create the node field, using struct type
struct node{
    int data;
    struct node* next;
    struct node* previous;
};

void insertLast(int n); //Functionally equivalent to 'create' function; Duplicated to insert a second function
void insertLast1(int n);
void insertFirst(int n);
void deleteFirst(int n);
void insertpos(int n);
void merge();
void print(struct node* head);
void print1(struct node* head, int n);

struct node* head;
struct node* tail;
struct node* head1;
struct node* tail1;

int main() {
    insertLast(2);
    insertLast(3);
    insertFirst(3);
    print(head);
    deleteFirst(3);
    print(head);
    insertpos(3);
    print(head);
    insertLast1(1);
    insertLast1(5);
    insertLast1(6);
    print(head1);
    merge();
}

//Used to create the first
void insertLast(int n){
    struct node* newNode = (struct node*)malloc(sizeof(struct node*));
    newNode->data = n;
    newNode->next = NULL;
    if (head == NULL && tail == NULL){
        newNode->previous = NULL;
        head = newNode;
        tail = newNode;
        return;
    }
    else {
        struct node* current = head;
        while (current->next != NULL)
            current = current->next;
        newNode->previous = current;
        current->next = newNode;
        tail = newNode;
    }
}

void insertLast1(int n){
    struct node* newNode = (struct node*)malloc(sizeof(struct node*));
    newNode->data = n;
    newNode->next = NULL;
    if (head1 == NULL && tail1 == NULL){
        newNode->previous = NULL;
        head1 = newNode;
        tail1 = newNode;
        return;
    }
    else {
        struct node* current = head1;
        while (current->next != NULL)
            current = current->next;
        newNode->previous = current;
        current->next = newNode;
        tail1 = newNode;
    }
}

void insertFirst(int n){
    struct node* newNode = (struct node*)malloc(sizeof(struct node*));
    newNode->data = n;
    newNode->next = head;
    newNode->previous = NULL;
    newNode->next->previous = newNode;
    head=newNode;
}

void deleteFirst(int n){
    struct node* current = head;
    while (current-> data != n)
        current = current->next;
    struct node* temp = current;
    if (current->previous == NULL){
        head = current->next;
        current->next->previous = NULL;
        temp->next = NULL;
        temp->previous = NULL;
        return;
    }else if (current->next == NULL){
        tail = current->previous;
        current->previous->next = NULL;
        temp->next = NULL;
        temp->previous = NULL;
        return;
    }else{
        current->previous->next = current->next;
        current->next->previous = current->previous;
        temp->next = NULL;
        temp->previous = NULL;
        return;
    }
}

void insertpos(int n){
    struct node* newNode = (struct node*)malloc(sizeof(struct node*));
    struct node* temp = head;
    while(temp != NULL){
        if ((n>temp->data && n<temp->next->data)){
            newNode->next = temp->next;
            newNode->previous = temp;
            newNode->data = n;
            temp->next = newNode;
            temp->next->previous = newNode;
        }
        else if ((temp->previous == NULL && n<temp->data)){
            newNode->next = temp;
            newNode->previous = NULL;
            newNode->data = n;
            temp->previous = newNode;
            head = newNode;
        }
        else if ((temp->next == NULL && n>temp->data)){
            newNode->previous = temp;
            newNode->next = NULL;
            newNode->data = n;
            temp->next = newNode;
            tail = newNode;
        }
        temp = temp->next;
    }
}

//merge function to compare
//Note that the merge function assumes that two lists are non-empty and are already sorted
void merge(){
    struct node* current1 = head;
    struct node* current2 = head1;
    while (current2 != NULL){
        struct node* temp = (struct node*)malloc(sizeof(struct node*));
        if (current1 == NULL) {
            if (current2->next == NULL){
                print1(current2, 6);
            }
            current2 = current2->next;
        }else if (current1->data > current2->data){
            if (current2->next == NULL){
                while (current1 != NULL){
                    temp->data = current1->data;
                    temp->previous = current2;
                    current2->next = temp;
                    tail1 = temp;
                    current1 = current1->next;
                }
            }
            current2 = current2->next;
        }
        else {
            if (current2->previous == NULL){
                temp->data = current1->data;
                temp->previous = NULL;
                temp->next = current2;
                current2->previous = temp;
                head1 = temp;
                current1 = current1 -> next;
            }
            else {
                temp->data = current1->data;
                temp->previous = current2->previous;
                current2->previous = temp;
                temp->next = current2;
                current2->previous->next = temp;
                current1 = current1 -> next;
            }
        }
    }
}

void print(struct node* h){
    struct node* current = h;
    while (current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void print1(struct node* h, int n){
    int j = n;
    int array[j];
    struct node* current = h;
    while (n>0){
        array[j-n] = current->data;
        current = current->previous;
        n--;
    }
    while (j>0){
        printf("%d ", array[j-1]);
        j--;
    }
    printf("\n");
}
