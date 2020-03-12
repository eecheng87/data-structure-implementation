#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
struct node {
    int data;
    struct node *next;
} *head;

void insert(struct node *newt) {
    struct node *node = head, *prev = NULL;
    while (node != NULL && node->data < newt->data) {
        prev = node;
        node = node->next;
    }
    newt->next = node;
    if (prev == NULL)
        head = newt;
    else
        prev->next = newt;
}
void good_insert(struct node *newt)
{
    struct node **link = &head;
    while (*link && (*link)->data < newt->data)
        link = &((*link)->next);
    newt->next = *link;
    *link = newt;
}
void print(){
    struct  node *tmp = head;
    while(tmp){
        printf("%d->",tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}
long elapse(struct timespec start, struct timespec end)
{
    return ((long) 1.0e+9 * end.tv_sec + end.tv_nsec) -
           ((long) 1.0e+9 * start.tv_sec + start.tv_nsec);
}
int main(){
    /*
    * Experiment for naive-insert
    */
    struct timespec t1, t2;
    head = NULL;
    clock_gettime(CLOCK_REALTIME, &t1);
    for(int i = 1; i < 10000; i++){
        struct node *tmp= (struct node*)malloc(sizeof(struct node));
        tmp->data = i;
        tmp->next = NULL;
        insert(tmp);
    }
    clock_gettime(CLOCK_REALTIME, &t2);
    printf("Time insert : %ld\n", elapse(t1, t2));

    //print();
    /*
    * Experiment for pointer to pointer-insert
    */
    head = NULL;
    clock_gettime(CLOCK_REALTIME, &t1);
    for(int i = 1; i < 10000; i++){
        struct node *tmp= (struct node*)malloc(sizeof(struct node));
        tmp->data = i;
        tmp->next = NULL;
        good_insert(tmp);
    }
    clock_gettime(CLOCK_REALTIME, &t2);
    printf("Time good insert : %ld ", elapse(t1, t2));

    //print();
    return 0;
}