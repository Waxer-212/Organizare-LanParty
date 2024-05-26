#include <stdlib.h>
#include <stdio.h>
#include "lanPartyLib.h"
#include <string.h>

void adauga_la_inceput(Node** head, player* n, char* nume_echipa, int numar_jucatori)
{
    Node* nod = (Node*)malloc(sizeof(Node));
    nod->nume_echipa = nume_echipa;
    nod->jucatori = (player*)malloc(sizeof(player) * numar_jucatori);
    for( int i = 0; i < numar_jucatori; i++)
    {
        nod->jucatori[i].firstName = n[i].firstName;
        nod->jucatori[i].secondName = n[i].secondName;
        nod->jucatori[i].points = n[i].points;
    }
    nod->next = (*head)->next;
    (*head)->next = nod;
  
}

void afiseaza_lista(Node* head, int numar_jucatori, char* nume_fisier)
{
    Node* t = head;
    if( t == NULL)
    {
        printf("Lista este goala");
        exit(1);
    }

    FILE *g = fopen(nume_fisier,"wt");
    if(g == NULL)
    {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }

    for(t = t->next; t != NULL; t = t->next)
    {
        fprintf(g,"%s\n",t->nume_echipa);   
    }
    fclose(g);
    
}

float calculare_medie(player* jucatori, int numar_jucatori)
{
    float media = 0;
    for(int i = 0; i < numar_jucatori; i++)
    {
        media +=jucatori[i].points;
    }
    media = media / numar_jucatori;
    return media;
}

float cel_mai_mic_punctaj(Node* head, int numar_jucatori)
{
    Node* t = head;
    float media = 0;
    float minim = 99999;
    for( t = t->next; t->next != NULL; t = t->next)
    {
        for( int i = 0; i <  numar_jucatori; i++)
        {
            media += t->jucatori[i].points;
        }
        if ( media/numar_jucatori <  minim)
        {
            minim = media/numar_jucatori;
        }

        media = 0;
    }
    
    return minim;
}

int puterea_cea_mai_apropiata_a_lui_doi(int numar)
{
    int i = 1;
    while( i*2 <= numar)
    {
        i = i*2;
    }
    return i;
}

void sterge_nodul( Node** head, char* nume_echipa)
{
    if( *head == NULL) return;
    if( (*head)->next == NULL && (*head)->nume_echipa == nume_echipa)
    {
        free(*head);
        *head = NULL;
        return;
    }

    Node* aux = (*head);
    Node* headcopy = (*head)->next;
    while( headcopy != NULL)
    {
        if( headcopy->nume_echipa != nume_echipa)
        {
            aux = headcopy;
            headcopy = headcopy->next;
        }
        else
        {
            aux->next = headcopy->next;
            free(headcopy);
            return;
        }
    }   
}

void deleteList(Node** head)
{
    Node* headcopy;
    while((*head) != NULL)
    {
        headcopy = (*head)->next;
        free(*head);
        *head = headcopy;
    }
    *head = NULL;
}

Queue* createQueue()
{
    Queue* q;
    q = (Queue*)malloc(sizeof(Queue));
    if( q == NULL) return NULL;

    q->front = q->rear = NULL;

    return q;
}

void enQueue(Queue* q, player* jucatori,int numar_jucatori, char* nume_echipa)
{
    Node* nou = (Node*)malloc(sizeof(Node));
    nou->jucatori = (player*)malloc(sizeof(player) * numar_jucatori);
    nou->nume_echipa = nume_echipa;
    for( int i = 0; i < numar_jucatori; i++)
    {
        nou->jucatori[i] = jucatori[i];
    }

    nou->next = NULL;

    if(q->rear == NULL)
        q->rear = nou;
    else
    {
        (q->rear)->next = nou;
        (q->rear) = nou;
    }
    
    if( q->front == NULL)
        q->front = q->rear;
}

int isEmpty(Node* x)
{
    return( x == NULL);
}

void deleteQueue(Queue* q)
{
    Node* aux;
    while( !isEmpty(q->front))
    {
        aux = q->front;
        q->front = q->front->next;
        free(aux);
    }
    free(q);
}

void afiseaza_coada(Queue*q, int numar_jucatori,char* nume_fisier)
{
    Node* t = q->front;
    int Caractere_Linie = 67;
    int j = 0;

    FILE *g = fopen(nume_fisier,"a");
    if(g == NULL)
    {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }
   
    while(t->next != NULL)
    {   
        int padding1 = Caractere_Linie / 2 - strlen(t->nume_echipa);
        fprintf(g,"%s",t->nume_echipa);
        for(int i = 0; i < padding1; i++)
            fprintf(g," ");
        t = t->next;
        int padding2 = Caractere_Linie / 2 - strlen(t->nume_echipa);
        fprintf(g,"-");
        for(int i = 0; i < padding2; i++)
            fprintf(g," ");
        fprintf(g,"%s\n",t->nume_echipa);
        if( t -> next == NULL)
            break;
        t = t->next;
    }
    
    fclose(g);
}

float obtine_puncte(Queue* q, int numar_jucatori)
{
    float media = 0;
    for( int i = 0; i < numar_jucatori; i++)
    {
        media += q->front->jucatori[i].points;
    }

    return media / numar_jucatori;
}

player obtine_jucator(Queue* q, int contor)
{
    return q->front->jucatori[contor];
}

char* deQueue(Queue* q)
{
    Node* aux;   
    char* sir; 
    if(isEmpty(q->front))
        return NULL;
    
    aux = q->front;

    sir = aux->nume_echipa;
    q->front = (q->front)->next;
    free(aux);
    if(q->front == NULL)
        q->rear = NULL;
    return sir;
}

void push(Node**top, player* jucatori, char* nume_echipa, int numar_jucatori)
{
    Node* nou = (Node*)malloc(sizeof(Node));
    
    nou->nume_echipa = nume_echipa;
    nou->jucatori = (player*)malloc(sizeof(player) * numar_jucatori);
    for( int i = 0; i < numar_jucatori; i++)
    {
        nou->jucatori[i].firstName = jucatori[i].firstName;
        nou->jucatori[i].secondName = jucatori[i].secondName;
        nou->jucatori[i].points = jucatori[i].points;
    }

    nou->next = (*top);
    *top = nou;
}


char* pop(Node**top)
{
    Node *t;
    char* nume_echipa;

    if(isEmpty(*top)) return NULL;
    t = (*top);
    nume_echipa = t->nume_echipa;

    *top = (*top)->next;
    free(t);
    return nume_echipa;
}

void deleteStack(Node** top)
{
    Node*temp;
    while((*top) != NULL)
    {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

void afiseazaStiva(Node*top, char* nume_fisier,int numar_jucatori)
{
    Node* temp = top;
    FILE *g = fopen(nume_fisier,"a");
    if(g == NULL)
    {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }
    while(temp != NULL)
    {   
        float punctaj = calculare_medie(temp->jucatori, numar_jucatori);
        int padding = 35 - strlen(temp->nume_echipa);
        fprintf(g ,"%s%*s-  %.2f\n",temp->nume_echipa,padding-1,"",punctaj);

        temp = temp->next;
    };

    fclose(g);
}

NodeArbore* newNode(char* nume_echipa, player* jucatori,int numar_jucatori)
{
    
    NodeArbore* temp = (NodeArbore*)malloc(sizeof(NodeArbore));
    temp->jucatori = (player*)malloc(sizeof(player) * numar_jucatori);
    (temp->nume_echipa) = nume_echipa;
    temp->height = 1;
    for(int i = 0; i < numar_jucatori; i++)
    {
        temp->jucatori[i].firstName = jucatori[i].firstName;
        temp->jucatori[i].secondName = jucatori[i].secondName;
        temp->jucatori[i].points = jucatori[i].points;  
    }
    temp->left = temp->right = NULL;
    return temp;
}

void insert( NodeArbore** node, int numar_jucatori, char*nume_echipa, player* jucatori)
{   
           
        if(*node == NULL)
        {
            *node = newNode(nume_echipa,jucatori,numar_jucatori);
            return;   
        } 
        if( calculare_medie(jucatori,numar_jucatori) < calculare_medie((*node)->jucatori,numar_jucatori))
            {
                insert(&(*node)->left,numar_jucatori,nume_echipa,jucatori);
            }
        else if (calculare_medie(jucatori,numar_jucatori) > calculare_medie((*node)->jucatori,numar_jucatori))
            {      
                insert(&(*node)->right,numar_jucatori,nume_echipa,jucatori);
            }
        else
        {
            if( strcmp(nume_echipa, (*node)->nume_echipa) > 0)
                insert(&(*node)->right,numar_jucatori,nume_echipa,jucatori);            
            else
                insert(&(*node)->left,numar_jucatori,nume_echipa,jucatori);
        }
}

void inorder(NodeArbore* root,char*nume_fisier,int numar_jucatori)
{   
    FILE *g = fopen(nume_fisier,"a");
    if(g == NULL)
    {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }
    if (root != NULL) {
        inorder(root->right,nume_fisier,numar_jucatori);
        int padding = 35 - strlen(root->nume_echipa);
        float punctaj = calculare_medie(root->jucatori, numar_jucatori);
        fprintf(g ,"%s%*s-  %.2f\n",root->nume_echipa,padding-1,"",punctaj);
        fflush(g);
        inorder(root->left,nume_fisier,numar_jucatori);
    }
    fclose(g);
}

int height(NodeArbore* root)
{
    if(root == NULL)
        return 0;
    else
        return root->height;
}

int maxim( int a, int b)
{
    return (a > b)? a : b;
}
NodeArbore* rightRotate(NodeArbore *y)
{
    NodeArbore *x = y->left;
    NodeArbore *T2 = x->right;

    //Rotatia
    x->right = y;
    y->left = T2;

    //Modificam inalitimea
    y->height = maxim(height(y->left),height(y->right)) + 1;
    x->height = maxim(height(x->left),height(x->right)) + 1;

    //Noua radacina
    return x;
}

NodeArbore* leftRotate(NodeArbore *x)
{
    NodeArbore *y =x->right;
    NodeArbore *T2 = y->left;
    //x->right = y->left;

    y->left = x;
    x->right = T2;

    x->height = maxim(height(x->left),height(x->right)) + 1;
    y->height = maxim(height(y->left),height(y->right)) + 1;

    return y;
}

int getBalance( NodeArbore *N)
{
    if( N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

NodeArbore* insertAVL(NodeArbore* root, int numar_jucatori, char*nume_echipa, player* echipa)
{
    if( root == NULL)
    {
        root = newNode(nume_echipa,echipa,numar_jucatori);
            return root;
    }

    if( calculare_medie(echipa,numar_jucatori) < calculare_medie(root->jucatori,numar_jucatori))
    {
        root->left = insertAVL(root->left,numar_jucatori,nume_echipa,echipa);
    }
    else if( calculare_medie(echipa,numar_jucatori) > calculare_medie(root->jucatori,numar_jucatori))
    {
        root->right = insertAVL(root->right,numar_jucatori,nume_echipa,echipa);
    }
    else
    {
        if( strcmp(nume_echipa, (root)->nume_echipa) < 0)
            root->right = insertAVL(root->right,numar_jucatori,nume_echipa,echipa);
        else
            root->left = insertAVL(root->left,numar_jucatori,nume_echipa,echipa);  
    }

    root->height = 1 + maxim(height(root->left),height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && calculare_medie(echipa,numar_jucatori) < calculare_medie(root->left->jucatori,numar_jucatori))
        return rightRotate(root);
    if ( balance < -1 && calculare_medie(echipa,numar_jucatori) > calculare_medie(root->right->jucatori,numar_jucatori))
        return leftRotate(root);
    if ( balance > 1 && calculare_medie(echipa,numar_jucatori) > calculare_medie(root->left->jucatori,numar_jucatori))
    {
        root->left = leftRotate(root->left);
        return(rightRotate(root));
    }
    if( balance < -1 && calculare_medie(echipa,numar_jucatori) < calculare_medie(root->right->jucatori,numar_jucatori))
    {
        root->right = rightRotate(root->right);
        return(leftRotate(root));
    }

    return root;
}

void printLevel2(NodeArbore* node, int curentLevel, char* filename)
{
    FILE *g = fopen(filename,"a");
    if(g == NULL)
    {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }

    if( node == NULL)
        return;

    printLevel2(node->right,curentLevel+1,filename);
    if(curentLevel == 2)
    {
        fprintf(g,"%s\n",node->nume_echipa);
    }
    printLevel2(node->left,curentLevel +1,filename);

    fclose(g);
}

void printLevel(NodeArbore* root, char*nume_fisier)
{
    FILE *g = fopen(nume_fisier,"a");

    fprintf(g,"%s\n",root->right->right->nume_echipa);
    fprintf(g,"%s\n",root->right->left->nume_echipa);
    fprintf(g,"%s\n",root->left->right->nume_echipa);
    fprintf(g,"%s\n",root->left->left->nume_echipa);

    fclose(g);
}

player* assign( player* echipa, player* team, int numar_jucatori) 
{
    for( int i = 0; i < numar_jucatori; i++)
    {
        echipa[i].firstName = team[i].firstName;
        echipa[i].secondName = team[i].secondName;
        echipa[i].points = team[i].points;
    }
    return echipa;
}

void deleteTree(NodeArbore* node) {
    if (node == NULL) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
}