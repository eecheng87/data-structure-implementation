#include <iostream>
#include <stdlib.h>
using namespace std;

typedef enum
{
    head,
    entry
} tagfield;
typedef struct matrixNode Node;
typedef struct entryNode
{
    int row;
    int col;
    int val;
};
typedef struct matrixNode
{
    Node *down;
    Node *right;
    tagfield tag;
    union {
        Node *next;
        entryNode entry;
    } u;
};

Node *mread();
void mwrite(Node *);
Node *mtranspose(Node *);
Node *mmult(Node *, Node *);
int compare(int, int);
Node *hdA[10];
Node *hdB;
int main()
{
    Node *matrixA;
    Node *matrixB;
    Node *matrixTransB;

    matrixA = mread();
    matrixB = mread();
    matrixTransB = mtranspose(matrixB);
    cout << "b transpose:" << endl;
    mwrite(matrixTransB);
    cout << "a*b transpose: " << endl;
    mwrite(mmult(matrixA, matrixTransB));

    return 0;
}

Node *mread()
{
    int numRows, numCols, numTerms, numHeads, i;
    int row, col, value, currentRow;
    Node *temp;
    Node *node;
    Node *last;

    cout << "Enter the number of rows, columns and number of nonzero terms:";
    cin >> numRows >> numCols >> numTerms;
    numHeads = (numCols > numRows) ? numCols : numRows;

    node = (Node *)malloc(sizeof(Node));
    node->tag = entry;
    node->u.entry.row = numRows;
    node->u.entry.col = numCols;

    if (!numHeads)
        node->right = node;
    else
    {
        for (i = 0; i < numHeads; i++)
        {
            temp = (Node *)malloc(sizeof(Node));
            hdA[i] = temp;
            hdA[i]->tag = head;
            hdA[i]->right = temp;
            hdA[i]->u.next = temp;
        }

        currentRow = 0;
        last = hdA[0];
        for (i = 0; i < numTerms; i++)
        {
            cout << "Enter row, column and value:";
            cin >> row >> col >> value;
            if (row > currentRow)
            {
                last->right = hdA[currentRow];
                currentRow = row;
                last = hdA[row];
            }
            temp = (Node *)malloc(sizeof(Node));
            temp->tag = entry;
            temp->u.entry.row = row;
            temp->u.entry.col = col;
            temp->u.entry.val = value;
            last->right = temp;
            last = temp;

            hdA[col]->u.next->down = temp;
            hdA[col]->u.next = temp;
        }

        last->right = hdA[currentRow];

        for (i = 0; i < numCols; i++)
        {
            hdA[i]->u.next->down = hdA[i];
        }
        for (i = 0; i < numHeads - 1; i++)
        {
            hdA[i]->u.next = hdA[i + 1];
        }
        hdA[numHeads - 1]->u.next = node;
        node->right = hdA[0];
    }
    return node;
}
void mwrite(Node *node)
{
    // cout << node->right->right->u.entry.col << endl;
    int i;
    Node *temp;
    Node *head = node->right;
    cout << "numRows = " << node->u.entry.row;
    cout << "numCols = " << node->u.entry.col << endl;

    cout << "The matrix by row, column and value: " << endl;
    for (i = 0; i < node->u.entry.row; i++)
    {
        for (temp = head->right; temp != head; temp = temp->right)
        {
            if (temp == head)
                continue;
            cout << temp->u.entry.row << " " << temp->u.entry.col << " " << temp->u.entry.val << endl;
        }
        head = head->u.next;
    }
}
Node *mtranspose(Node *node)
{
    // cout << node->right->down->u.entry.col << endl;
    int i;
    int numRow = node->u.entry.col;
    int numCol = node->u.entry.row;
    int numHeads = (numRow > numCol) ? numRow : numCol;

    Node *ans = (Node *)malloc(sizeof(Node));
    ans->tag = entry;
    ans->u.entry.row = numRow;
    ans->u.entry.col = numCol;

    //initial head
    Node *transHead[numHeads];
    Node *rowLast[numHeads];
    Node *colLast;
    Node *temp; //for "for" loop
    Node *tmp;  //for new temp node
    Node *headNode = node->right;

    for (i = 0; i < numHeads; i++)
    {
        tmp = (Node *)malloc(sizeof(Node));
        transHead[i] = tmp;
        transHead[i]->tag = head;
        transHead[i]->right = tmp;
        transHead[i]->u.next = tmp;
    }

    for (i = 0; i < numHeads; i++)
    {
        rowLast[i] = transHead[i];
    }

    for (i = 0; i < node->u.entry.col; i++)
    {
        for (temp = headNode->down; temp != headNode; temp = temp->down)
        {
            if (temp != headNode)
            {
                tmp = (Node *)malloc(sizeof(Node));
                tmp->tag = entry;
                tmp->u.entry.col = temp->u.entry.row;
                tmp->u.entry.row = temp->u.entry.col;
                tmp->u.entry.val = temp->u.entry.val;
                rowLast[temp->u.entry.col]->right = tmp; //connect row
                rowLast[temp->u.entry.col] = tmp;
                transHead[tmp->u.entry.col]->u.next->down = tmp; //connect col
                transHead[tmp->u.entry.col]->u.next = tmp;
            }
        }
        //rowLast->right = headNode; //connect last node in this row to head
        if (i == node->u.entry.col - 1)
        {
            break; // if it comes last column, dont change head
        }
        //headNode = transHead[i + 1];//some bug
        headNode = headNode->u.next;
    }

    for (i = 0; i < numHeads; i++)
    {
        rowLast[i]->right = transHead[i];
    }

    for (i = 0; i < numCol; i++)
    {
        transHead[i]->u.next->down = transHead[i]; //connect each column's last element to head
    }

    for (i = 0; i < numHeads - 1; i++)
    {
        transHead[i]->u.next = transHead[i + 1]; //connect each head
    }
    transHead[numHeads - 1]->u.next = ans;
    ans->right = transHead[0];

    return ans;
}
Node *mmult(Node *a, Node *b)
{
    Node *ans;

    int i, j;
    int numRow = a->u.entry.row;
    int numCol = b->u.entry.col;
    int numHeads = (numRow > numCol) ? numRow : numCol;

    ans = (Node *)malloc(sizeof(Node));
    ans->tag = entry;
    ans->u.entry.row = numRow;
    ans->u.entry.col = numCol;

    Node *ansHead[numHeads];
    Node *rowLast;
    Node *colLast;
    Node *startA;
    Node *startB;
    Node *tmp;
    Node *last[numHeads];

    for (i = 0; i < numHeads; i++)
    {
        tmp = (Node *)malloc(sizeof(Node));
        last[i] = ansHead[i] = tmp;
        ansHead[i]->tag = head;
        ansHead[i]->right = tmp;
        ansHead[i]->u.next = tmp;
    }

    //start calculate product
    int currentRow;
    int sum = 0;
    Node *headA;
    Node *headB;
    headA = a->right; // a's head[0]
    headB = b->right; // b's head[0];
    startA = headA->right;
    startB = headB->down;

    for (i = 0; i < numRow; i++)
    {
        for (j = 0; j < numCol; j++)
        {
            while (startA != headA && startB != headB)
            {
                switch (compare(startA->u.entry.col, startB->u.entry.row))
                {
                case 0: //equal
                    sum += startA->u.entry.val * startB->u.entry.val;
                    startA = startA->right;
                    startB = startB->down;
                    break;
                case 1: // a's col > b's row
                    startB = startB->down;
                    break;
                case -1: // a's col < b's row
                    startA = startA->right;
                    break;
                default:
                    break;
                }
            }

            startA = headA->right;
            headB = headB->u.next;
            startB = headB->down;

            if (sum != 0)
            {
                tmp = (Node *)malloc(sizeof(Node));
                tmp->tag = entry;
                tmp->u.entry.row = i;
                tmp->u.entry.col = j;
                tmp->u.entry.val = sum;
            }

            if (sum != 0)
            {
                last[i]->right = tmp;
                last[i] = tmp;
                ansHead[j]->u.next->down = tmp;
                ansHead[j]->u.next = tmp;
            }

            sum = 0;
        }

        headA = headA->u.next;
        startA = headA->right;
        headB = b->right;
        startB = headB->down; //is same as startB = headB ??
    }

    for (i = 0; i < numHeads; i++) // link last node to head(row)
    {
        last[i]->right = ansHead[i];
    }

    for (i = 0; i < numCol; i++)
    {
        ansHead[i]->u.next->down = ansHead[i];
    }

    for (i = 0; i < numHeads - 1; i++)
    {
        ansHead[i]->u.next = ansHead[i + 1];
    }

    ansHead[numHeads - 1]->u.next = ans;
    ans->right = ansHead[0];

    return ans;
}

int compare(int a, int b)
{
    if (a > b)
        return 1;
    else if (a == b)
        return 0;
    else
        return -1;
}
