#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Tree {
    int value;
    char color;
    float money;
    char name[50];
    char id[11];
    struct ListNode* ListPointer;
    struct HeapNode* HeapPointer;
    struct Tree* left;
    struct Tree* right;
    struct Tree * parent;
}TreeNode;

typedef struct ListNode{
    TreeNode* z;
    struct  ListNode* next;
    struct  ListNode* prev;
}ListNode;

typedef  struct HeapNode{
    float balance;
    int index;
    TreeNode* TreePointer;
}HeapNode;


ListNode* ListRoot=NULL;
int heapSize=0;
HeapNode* Heap[2000];

/*    List prototypes !*/
ListNode* addToList(TreeNode* z);
void delFromList(ListNode* z);

/*END*/
/* Heap prototypes */
void MaxHeapifiy(HeapNode** heap, int i);
void HeapInsert(HeapNode **heap, float key,TreeNode* p);
void HeapIncreaseKey(HeapNode** heap,int i, float key);
void DelFromHeap(HeapNode** heap,HeapNode* rm);

/* END*/

/*    Tree prototypes !*/

TreeNode* NIL=NULL;
TreeNode* root=NULL;
TreeNode* createTreeNode();


void  RbInsert(TreeNode *z);
void  RbInsertFixup(TreeNode* z);
void  LeftRotate(TreeNode* x);
void  RightRotate(TreeNode* x);
void  RbDeleteFixUp(TreeNode* x);
void  preorderPrint(TreeNode* walk);
void  NodeCopy(TreeNode* src,TreeNode* des);


TreeNode* RbDelete(TreeNode* z);
TreeNode* RbSearch(TreeNode* src,int key);
TreeNode* TreeMin(TreeNode* x);
TreeNode* TreeSuccessor(TreeNode* x);
void FreeTree(TreeNode* z);
/*END*/

/*    costume prototypes !*/
void removeUser(int key);
void addUser(int key,float amount,char *name ,char *id);
void Deposite(int key,float amount);
void userInfo(int key);
void printMin();
void freeAndExit();

void main(){
    TreeNode* z=NULL;
    char name[50]={0};
    char sep[2]=" ";
    char *token[10];
    char command[100]={0};
    int exit=0,i=0;
    NIL=(TreeNode*)malloc(sizeof(TreeNode));
    NIL->color='B';
    NIL->left=NULL;
    NIL->parent=NULL;
    NIL->right=NULL;
    root=NIL;
    for (i=0;i<2000;i++) Heap[i]=NULL;
    printf("*************** Welcome to Maman - 18 your and only bank database system ***************\n");
    printf("Created by : Jenney Rad & Itamar Shimon\n");
    printf("\nPlease write you what you are wish to do, Example\n"
                   "\n'+ Yosi Levi 036527869 72634 300', yosi levy has joined the bank with account #72634 & deposite 300 NIS\n"
                   "\n'Yosi Levi 72634 400' meaning Yosi levi has deposite 400 shekel to his account number 72634\n"
                   "\nThe Exit please type 'EXIT' , Thank you\n"
                   "\nPlease refer to the full documentation in the Mamanas book page 18 Thank you\n");
    while(1){
        printf("\n\n***************************\n\n");
        printf("\nPlease type your new wish\n");

        gets(command); // Not the save way to do but save time! :)
        if (!strcmp(command,"EXIT")) {
            freeAndExit();
            printf("Bye Bye\n");
            break;
        }
        i=0;
        token[i]= strtok(command,sep);

        while (token[i]){

            i++;
            token[i]=strtok(NULL,sep);
        }
        printf("\n\n***************************\n\n");

        if (!strcmp(token[0],"+")){
            sprintf(name,"%s %s",token[1],token[2]);
            addUser((int)strtof(token[4],NULL),strtof(token[5],NULL),name,token[3]);
            continue;
        }
        if (!strcmp(token[0],"-")){
            removeUser((int)strtof(token[1],NULL));
            continue;
        }
        if (!strcmp(token[0],"?")){
            if (!strcmp(token[1],"MAX")){
                if (Heap[1]) {
                    printf("    Max balance is: \n\n");
                    printf("\n    **** MAX *** -> %s, account number %d , has the max balance of :%.2f", Heap[1]->TreePointer->name,
                           Heap[1]->TreePointer->value, Heap[1]->balance);
                }
                else{
                    printf("Database is empty\n");
                }
                    continue;
            }
            if (!strcmp(token[1],"MINUS")){
                printMin();
            continue;
            }
            userInfo((int)strtof(token[1],NULL));
            continue;

        }

        Deposite((int)strtof(token[2],NULL),strtof(token[3],NULL));

    }


}

void RbInsert(TreeNode *z) {
    TreeNode *x = root;
    TreeNode *y = NIL;
    while (x != NIL) {
        y = x;
        if (z->value < x->value)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NIL)
        root = z;
    else {
        if (z->value < y->value)
            y->left = z;
        else
            y->right = z;
    }
    z->left = NIL;
    z->right = NIL;
    z->color = 'R';
    RbInsertFixup(z);
}
void RbInsertFixup(TreeNode* z) {
    TreeNode *y = NULL;
    while (z->parent->color == 'R') {
        if (z->parent == (z->parent->parent->left)) {
            y = z->parent->parent->right;
            if (y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z=z->parent->parent;
            }
            else {

                if (z == z->parent->right) {
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                RightRotate(z->parent->parent);

            }
        } else {
            y = z->parent->parent->left;
            if (y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z=z->parent->parent;
            } else {

                if (z == z->parent->left) {
                    z = z->parent;
                    RightRotate(z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                LeftRotate(z->parent->parent);

            }

        }
    }
    root->color = 'B';
}

void  LeftRotate(TreeNode* x){
    TreeNode* y=x->right;
    x->right=y->left;
    if (y->left!= NIL) {
        y->left->parent = x;
    }
    y->parent=x->parent;
    if (x->parent == NIL)
        root=y;
    else {
        if (x==x->parent->left){
            x->parent->left=y;

        }
        else{
            x->parent->right=y;

        }
    }
    y->left=x;
    x->parent=y;

}

void  RightRotate(TreeNode* x){
    TreeNode* y=x->left;
    x->left=y->right;
    if (y->right!= NIL) {
        y->right->parent = x;
    }
    y->parent=x->parent;
    if (x->parent == NIL)
        root=y;
    else {
        if (x==x->parent->right){
            x->parent->right=y;

        }
        else{
            x->parent->left=y;

        }
    }
    y->right=x;
    x->parent=y;
}

TreeNode* createTreeNode(){
    TreeNode* z=NULL;

    z=(TreeNode*)malloc(sizeof(TreeNode));
    if (!z) {
        printf("Error Bad alloction\n");
        exit(1);
    }
    z->parent=NULL;
    z->color='B';
    z->left=NULL;
    z->right=NULL;
    z->ListPointer=NULL;
    z->HeapPointer=NULL;
    return z;

}

void  preorderPrint(TreeNode* walk){
    if (walk!=NIL){
        printf("Key :%d , Color:%c\n\n",walk->value,walk->color);
        preorderPrint(walk->left);

        preorderPrint(walk->right);


    }
}
TreeNode* RbDelete(TreeNode* z){
    TreeNode* y;
    TreeNode* x;
    if (z->left ==NIL || z->right ==NIL){
        y=z;
    }
    else {
        y = TreeSuccessor(z);
    }
    if (y->left !=NIL){
        x=y->left;
    }
    else{
        x=y->right;
    }
    x->parent=y->parent;
    if (y->parent==NIL){
        root=x;
    }
    else {
        if (y==y->parent->left){
            y->parent->left=x;
        }
        else
        {

            y->parent->right=x;
        }
    }
    if (y!=z){
        NodeCopy(y,z);
    }
    if (y->color=='B'){
        RbDeleteFixUp(x);
    }

    return y;


}
TreeNode* TreeMin(TreeNode* x){
    while (x->left!=NIL)
        x=x->left;
    return x;

}

TreeNode* TreeSuccessor(TreeNode* x){
    TreeNode* y;
    if (x->right!=NIL)
        return TreeMin(x->right);
    y=x->parent;
    while (y!=NIL && x==y->right)
    {
        x=y;
        y=y->parent;

    }
    return y;

}
void NodeCopy(TreeNode* src,TreeNode* des){
    int tempVal;
    float TempMoney;
    char name[50]={0};
    char id[11]={0};
    ListNode* List;
    HeapNode* Heap;

    tempVal=des->value;
    TempMoney=des->money;
    strcpy(name,des->name);
    strcpy(id,des->id);
    List=des->ListPointer;
    Heap=des->HeapPointer;

    des->value=src->value;
    des->money=src->money;
    strcpy(des->name,src->name);
    strcpy(des->id,src->id);
    des->ListPointer=src->ListPointer;
    des->HeapPointer=src->HeapPointer;

    src->value=tempVal;
    src->money=TempMoney;
    strcpy(src->name,name);
    strcpy(src->id,id);
    src->ListPointer=List;
    src->HeapPointer=Heap;
}

void RbDeleteFixUp(TreeNode* x) {
    TreeNode* w;
    while (x!=root && x->color=='B'){
        if (x==x->parent->left){
            w=x->parent->right;
            if (w->color=='R'){
                w->color='B';
                LeftRotate(x->parent);
                w=x->parent->right;
            }
            if (w->left->color=='B' && w->right->color=='B'){
                w->color='R';
                x=x->parent;
            }
            else {
               if (w->right->color =='B'){
                   w->left->color='B';
                   w->color='R';
                   RightRotate(w);
                   w=x->parent->right;
                }
                w->color=x->parent->color;
                x->parent->color= 'B';
                w->right->color='B';
                LeftRotate(x->parent);
                x=root;
            }
        }
        else{
            w=x->parent->left;
            if (w->color=='R'){
                w->color='B';
                RightRotate(x->parent);
                w=x->parent->left;

            }
            if (w->right->color=='B' && w->left->color=='B'){
                w->color='R';
                x=x->parent;
            }
            else {
                if (w->left->color =='B'){
                    w->right->color='B';
                    w->color='R';
                    LeftRotate(w);
                    w=x->parent->left;
                }
                w->color=x->parent->color;
                x->parent->color= 'B';
                w->left->color='B';
                RightRotate(x->parent);
                x=root;
            }




        }

    }
    x->color='B';
}

TreeNode* RbSearch(TreeNode* src,int key){
    if (src==NIL || src->value==key) return src;
    if (key<src->value)
        return RbSearch(src->left,key);
    return RbSearch(src->right,key);


}

void Deposite(int key,float amount){
    TreeNode* client=RbSearch(root,key);
    if (client==NIL) {
        printf("    Error: Couldn't find customer with account number :%d\n",key);
        return;
    }

    client->money+=amount;
    HeapIncreaseKey(Heap,client->HeapPointer->index,client->money); // Update Heap stack

    if (client->money>0 && client->ListPointer){
        delFromList(client->ListPointer);         // User was in negative balance List ... remove him!
        client->ListPointer=NULL;
    }
    if (client->money<0 && !client->ListPointer){
        client->ListPointer=addToList(client);    // Add user to negative balance list
    }
    if (amount>0){
        printf("    %s has deposite %.2f shekels\n",client->name,amount);
    }
    else {
        printf("    %s has withdraw %.2f shekels\n",client->name,amount);
    }
   printf("\n    %s has balance of %.2f shekels\n",client->name,client->money);
}

void addUser(int key,float amount,char *name ,char *id){
    TreeNode* client=RbSearch(root,key);
    if (client!=NIL){
        printf("    Error user with account number %d is already in database",key);
        return;
    }
    client=createTreeNode();
    client->money=amount;
    HeapInsert(Heap,client->money,client);
    if (amount<0){
        client->ListPointer=addToList(client);
    }
    else
        client->ListPointer=NULL;
    client->value=key;
    strcpy(client->id,id);
    strcpy(client->name,name);
    RbInsert(client);
    printf("    %s has been successfuly join the bank with starting balance of :%.2f, and client number: %d",client->name,client->money,client->value);
}

void removeUser(int key){
    TreeNode* client=RbSearch(root,key);
    if (client==NIL){
        printf("    Error user with account number %d is not in database",key);
        return;
    }
    delFromList(client->ListPointer);
    client=RbDelete(client);
    DelFromHeap(Heap,client->HeapPointer);
    if (client->money>0){
        printf("    %s has left the bank, withdraw %.2f shekels",client->name,client->money);
    }
    else{
        printf("    %s has left the bank, deposite %.2f shekels",client->name,client->money);

    }
    free(client);
}

void userInfo(int key){
    TreeNode* client=RbSearch(root,key);
    if (client==NIL) {
        printf("    Sorry could not find user with account number %d",key);
        return;
    }
    printf("    %s has balance of %.2f shekels\n",client->name,client->money);
}

ListNode* addToList(TreeNode* z){
    ListNode* node=(ListNode*)malloc(sizeof(ListNode));
    node->z=z;
    node->next=NULL;
    node->prev=NULL;
    if (!ListRoot){
        ListRoot=node;
        return node;
    }
    node->next=ListRoot;
    ListRoot->prev=node;
    ListRoot=node;
    return node;
}
void delFromList(ListNode* z){

    if (!z) return;
    if (!z->prev){
        ListRoot=z->next;
        if (z->next)
            z->next->prev=NULL;
        free(z);
        return;
    }
    if (!z->next){
        z->prev->next=NULL;
        free(z);
        return;
    }
    z->prev->next=z->next;
    z->next->prev=z->prev;
    free(z);
}

void printMin(){
    ListNode* walk;
    walk=ListRoot;
    printf("\n\nPrinting MINUS List: \n");
    while (walk){
        printf("                  %s , account number :%d , has balance of :%.2f\n",walk->z->name,walk->z->value,walk->z->money);
        walk=walk->next;

    }

}

void freeAndExit(){
    /*Free all allocation and terminate the program */
    int i=1;
    ListNode* tmp;
    for (;i<=heapSize;i++){
        if (!Heap[i]) break;
        free(Heap[i]);
    }
    while (ListRoot){
        tmp=ListRoot;
        ListRoot=ListRoot->next;
        free(tmp);
    }
    FreeTree(root);
    free(NIL);
}

void FreeTree(TreeNode* z){
    if (z==NIL) return;
    FreeTree(z->left);
    FreeTree(z->right);
    free(z);

}

void MaxHeapifiy(HeapNode** heap,int i){
    HeapNode* temp;
    int left=2*i;
    int right=2*i+1;
    int max;
    if (left<heapSize && heap[left]->balance>heap[i]->balance)
        max=left;
    else
        max=i;
    if (right<heapSize && heap[right]->balance>heap[i]->balance)
        max=right;
    if (max!=i){
        temp=heap[i];
        heap[i]=heap[max];
        heap[max]=temp;
        heap[max]->index=max;
        heap[i]->index=i;
        MaxHeapifiy(heap,max);
    }
}

void HeapIncreaseKey(HeapNode** heap,int i, float key){
    HeapNode* temp;
    if (key <heap[i]->balance){
        heap[i]->balance=key;
        MaxHeapifiy(heap,i);
        return;
    }
    heap[i]->balance=key;
    while (i>1 &&  heap[i/2]->balance < heap[i]->balance){
        temp=heap[i];
        heap[i]=heap[i/2];
        heap[i/2]=temp;
        heap[i/2]->index=i/2;
        heap[i]->index=i;

        i=i/2;

    }
}
void HeapInsert(HeapNode **heap,float key,TreeNode* p){
    heapSize++;
    heap[heapSize]=(HeapNode*)malloc(sizeof(HeapNode));
    p->HeapPointer=heap[heapSize];
    heap[heapSize]->TreePointer=p;
    heap[heapSize]->balance=1<<31;
    heap[heapSize]->index=heapSize;
    HeapIncreaseKey(heap,heapSize,key);
}
void DelFromHeap(HeapNode** heap,HeapNode* rm){
    int index=rm->index;
    heap[index]=heap[heapSize];
    heap[index]->index=index;
    heap[heapSize]=NULL;
    heapSize--;
    free(rm);
    MaxHeapifiy(heap,index);
}