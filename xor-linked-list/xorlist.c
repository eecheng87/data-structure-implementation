#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct __list list;
struct __list {
    int data;
    struct __list *addr;
};

#define XOR(a, b) ((list *) ((uintptr_t) (a) ^ (uintptr_t) (b)))
#define LIST_SIZE 10000
#define EXP_TIME 20
list* insert_sort(list*,int);

static int threshold = 0;

void print(list *l){
    /*list *next = l->addr;
    while(l){
        list *tmp;
        printf("%3d  ",l->data);
        if(next){
            tmp = XOR(next->addr,l);
        }
        l = next;
        next = tmp;
    }*/
    //printf("\n");
    printf("List: ");
    list *curr = l;
    list *prev = NULL;
    list *next;
    while (curr != NULL)
    {
        //printf ("%d(%p,%p) ", curr->data,curr->addr,curr);
        printf ("%d ", curr->data);
        next = XOR (prev, curr->addr);
        prev = curr;
        curr = next;
    }
    printf("\n");
}

void insert_node(list **l, int d) {
    list *tmp = (list*)malloc(sizeof(list));
    tmp->data = d;

    if (!(*l)) {
        tmp->addr = NULL;
    } else {
        (*l)->addr = XOR(tmp, (*l)->addr);
        tmp->addr = *l;
    }
    *l = tmp;
}

void delete_list(list *l) {
    while (l) {
        list *next = l->addr;
        if (next)
            next->addr = XOR(next->addr, l);
        free(l);
        l = next;
    }
}
list *opt_sort(list *start, int begin, int end)
{
    /*
        Merge sort
    */

    //printf("%d %d %d\n",start->data,begin,end);
    /*if(start)
        printf("%d ",start->data);
    printf("%d %d \n",begin,end);*/
    if (!start || !start->addr || begin == end)
        return start;

    if(end - begin + 1 < threshold)
        return insert_sort(start, end - begin + 1);

    int mid = (end - begin + 1) / 2;
    int it = 0;
    list *right = start;
    list *left = start;

    list *pre_right = NULL;
    list *tmpr = right;
    list *tmpp;
    while(it < mid){
        tmpr = right;
        right = XOR(pre_right,right->addr);
        pre_right = tmpr;
        it++;
    }
    // cut two list
    //tmpr = right->addr;
    //tmpp = pre_right->addr;
    pre_right->addr = XOR(pre_right->addr,right);
    right->addr = XOR(right->addr,pre_right);
    //right->addr = XOR
    //pre_right = tmpr;

    //print(right);
    //print(start);
    //left->addr = NULL;
    //right->addr = XOR(right->addr, left);

    left = opt_sort(left,begin,begin + mid-1);
    right = opt_sort(right,begin + mid, end);
    //print(left);
    //print(right);

    for (list *merge = NULL; left || right;) {
        if (!right || (left && left->data < right->data)) {
            list *next = left->addr;
            if (next)
                next->addr = XOR(left, next->addr);

            if (!merge) {
                start = merge = left;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(merge->addr, left);
                left->addr = merge;
                merge = left;
            }
            left = next;
        } else {
            list *next = right->addr;
            if (next)
                next->addr = XOR(right, next->addr);

            if (!merge) {
                start = merge = right;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(merge->addr, right);
                right->addr = merge;
                merge = right;
            }
            right = next;
        }
    }

    return start;
}
list* ori_merge_sort(list *start){
    if (!start || !start->addr)
        return start;

    list *left = start, *right = start->addr;
    left->addr = NULL;
    right->addr = XOR(right->addr, left);

    left = ori_merge_sort(left);
    right = ori_merge_sort(right);

    for (list *merge = NULL; left || right;) {
        if (!right || (left && left->data < right->data)) {
            list *next = left->addr;
            if (next)
                next->addr = XOR(left, next->addr);

            if (!merge) {
                start = merge = left;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(merge->addr, left);
                left->addr = merge;
                merge = left;
            }
            left = next;
        } else {
            list *next = right->addr;
            if (next)
                next->addr = XOR(right, next->addr);

            if (!merge) {
                start = merge = right;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(merge->addr, right);
                right->addr = merge;
                merge = right;
            }
            right = next;
        }
    }
    return start;
}
list* insert_sort(list* head,int ssize) {
    // insertion sort
    if(!head)
        return NULL;
    list* dum = head;
    list *pre_tmp;
    list *tmp;
    list *res; // this is global temorary variable
    // get size first


    int size = ssize;


    //list *next = l->addr;
    /*list *next = dum->addr;
    while(dum){
        if(next){
            tmp = XOR(next->addr,dum);
        }
        dum = next;
        next = tmp;
        size++;
    }*/
    // curr is the next element of sorted list
    list *pre_curr = head;
    list *curr = head->addr;
    // prev->next == curr
    list *pre_prev = NULL;
    list *prev = head;
    // tail indicates the tail of sorted list
    list *pre_tail = NULL;
    list *tail = head;

    for(int i = 1; i < size; i++) {
        //print(head);
        //printf("%d\n",curr->data);
        pre_tmp = NULL;
        tmp = head;
        pre_prev = NULL;
        prev = head;
        //printf("%d",i);
        // find the location to be inserted
        for(int j = 0; j < i && tmp->data < curr->data; j++) {
            //tmp = tmp->next;

            res = tmp;
            tmp = XOR(tmp->addr,pre_tmp);
            pre_tmp = res;
            if(j != 0) {
                res = prev;
                prev = XOR(prev->addr,pre_prev);
                pre_prev = res;
            }
        }
        //printf("%d %d %d\n",curr->data,tail->data,pre_tail->data);
        // insert
        if(tmp == head) {
            //printf("hi");
            /*tail->next = curr->next;
            curr->next = head;
            head = curr;*/
            //tail->addr = XOR(XOR(tail->addr,curr),XOR(curr->addr,tail));
            if(!pre_tail)
                pre_tail = curr;
            //printf("%d\n",pre_tail->data);
            tail->addr = XOR(pre_tail,XOR(curr->addr,tail));
            curr->addr = tmp;
            if(tmp != tail)
                tmp->addr = XOR(curr,tmp->addr);
            head = curr;
        } else if(tmp == curr) {
            //tail = tail->next;
            res = XOR(pre_tail,tail->addr); // res is tail->next
            pre_tail = tail;
            tail = res;
        } else {
            /*prev->next = curr;
            tail->next = curr->next;
            curr->next = tmp;*/
            //tail->addr = XOR(XOR(tail->addr,curr),XOR(curr->addr,tail));
            if(tail == tmp){
                tail->addr = XOR(curr,XOR(curr->addr,tail));
                pre_tail = curr;
            }else{
                tail->addr = XOR(XOR(tail->addr,curr),XOR(curr->addr,tail));
                tmp->addr = XOR(XOR(tmp->addr,pre_tmp),curr);
            }
            curr->addr = XOR(prev, tmp);
            prev->addr = XOR(pre_prev,curr);
            //tmp->addr = XOR(XOR(tmp->addr,pre_tmp),curr);
        }
        //curr = tail->next;
        list *ttmp = curr;
        curr = XOR(pre_tail,tail->addr);
        //printf("%p %p %p\n",curr->addr,curr,tail);
        if(curr)
            curr->addr = XOR(XOR(curr->addr,ttmp),tail);
        //printf("%d %p\n",curr->data,curr->addr);
        //printf("%d---\n",curr->data);
    }

    return head;
}
double elapse(struct timespec start, struct timespec end)
{
    // return time in micro-second
    return (end.tv_sec * 1000 + (double)1.0e-6 * end.tv_nsec) -
           (start.tv_sec * 1000 + (double)1.0e-6 * start.tv_nsec);
}
int main(){
    list *head = NULL;
    time_t t;
    struct timespec t1, t2;

    /*for(int j = 0; j < EXP_TIME; j++){
        threshold = j;
        head = NULL;
        srand((unsigned) time(&t));
        for(int i = 0; i < LIST_SIZE; i++){
            insert_node(&head,rand()%1000);
        }
        //print(head);
        clock_gettime(CLOCK_REALTIME, &t1);
        head = opt_sort(head,0,LIST_SIZE-1);
        //head = ori_merge_sort(head);
        //head = insert_sort(head,LIST_SIZE);
        clock_gettime(CLOCK_REALTIME, &t2);
        //print(head);
        //printf("When S = %d, Time insert : %lf\n", j, elapse(t1, t2));
        printf("%d %lf\n",j,elapse(t1, t2));
        delete_list(head);
    }*/
    for(int j = 0; j < EXP_TIME; j++){
        double time_ori;
        double time_opt;
        double time_insert;
        threshold = 10;
        // measuring optimize merge sort (+insertion sort)
        head = NULL;
        srand((unsigned) time(&t));
        for(int i = 0; i < LIST_SIZE; i++){
            insert_node(&head,rand()%1000);
        }
        clock_gettime(CLOCK_REALTIME, &t1);
        head = opt_sort(head,0,LIST_SIZE-1);
        clock_gettime(CLOCK_REALTIME, &t2);
        time_opt = elapse(t1, t2);
        delete_list(head);

        // measuring insertion sort
        head = NULL;
        srand((unsigned) time(&t));
        for(int i = 0; i < LIST_SIZE; i++){
            insert_node(&head,rand()%1000);
        }
        clock_gettime(CLOCK_REALTIME, &t1);
        head = insert_sort(head,LIST_SIZE);
        clock_gettime(CLOCK_REALTIME, &t2);
        time_insert = elapse(t1, t2);
        delete_list(head);

        // measuring original merge sort
        head = NULL;
        srand((unsigned) time(&t));
        for(int i = 0; i < LIST_SIZE; i++){
            insert_node(&head,rand()%1000);
        }
        clock_gettime(CLOCK_REALTIME, &t1);
        head = ori_merge_sort(head);
        clock_gettime(CLOCK_REALTIME, &t2);
        time_ori = elapse(t1, t2);
        delete_list(head);

        printf("%d %lf %lf %lf\n",j,time_opt,time_ori,time_insert);
    }

    /*threshold = 6;
    head = NULL;
    srand((unsigned) time(&t));
    for(int i = 0; i < LIST_SIZE; i++){
        insert_node(&head,rand()%1000);
    }
    //print(head);
    clock_gettime(CLOCK_REALTIME, &t1);
    head = sort(head,0,LIST_SIZE-1);
    clock_gettime(CLOCK_REALTIME, &t2);
    //print(head);
    printf("Time insert : %ld\n", elapse(t1, t2));
    delete_list(head);

    head = NULL;
    srand((unsigned) time(&t));
    for(int i = 0; i < LIST_SIZE; i++){
        insert_node(&head,rand()%1000);
    }
    //print(head);
    clock_gettime(CLOCK_REALTIME, &t1);
    head = insert_sort(head, LIST_SIZE-1);
    clock_gettime(CLOCK_REALTIME, &t2);
    //print(head);
    printf("Time insert : %ld\n", elapse(t1, t2));
    delete_list(head);*/

    /*for(int i = 0; i < LIST_SIZE; i++){
        insert_node(&head,rand()%1000);
    }
    (void)sort(head,0,LIST_SIZE-1);
    delete_list(head);

    for(int i = 0; i < LIST_SIZE; i++){
        insert_node(&head,rand()%1000);
    }
    (void)sort(head,0,LIST_SIZE-1);
    delete_list(head);*/


    /*printf("Before sorting\n");
    print(head);
    printf("After sorting\n");
    print(sort(head,0,LIST_SIZE-1));*/
    //print(insert_sort(head));
    //print(head);
    //head = sort(head);
    //print(head);
    return 0;
}

