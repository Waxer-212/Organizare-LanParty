struct Player{
    char* firstName;
    char* secondName;
    int points;
};
typedef struct Player player;

struct node{
    player* jucatori;
    char* nume_echipa;
    struct node* next;
};
typedef struct node Node;

struct node_arbore{
    int height;
    player* jucatori;
    char* nume_echipa;
    struct node_arbore *left,*right;
};
typedef struct node_arbore NodeArbore;

struct coada{
    Node *front, *rear; 
};
typedef struct coada Queue;


void adauga_la_inceput(Node** head, player* n, char* nume_echipa, int jucatori);
float calculare_medie(player* jucatori, int numar_jucatori);
float cel_mai_mic_punctaj(Node* head, int numar_jucatori);
int puterea_cea_mai_apropiata_a_lui_doi(int numar);
void afiseaza_lista(Node* head, int numar_jucatori,char* nume_fisier);
void sterge_nodul( Node** head, char* nume_echipa);
void deleteList(Node** head);


Queue* createQueue();
void enQueue(Queue* q, player* jucatori,int numar_jucatori, char* nume_echipa);
int isEmpty(Node*x);
char* deQueue(Queue* q);
void deleteQueue(Queue* q);
void afiseaza_coada(Queue*q, int numar_jucatori,char* nume_fisier);
float obtine_puncte(Queue* q, int numar_jucatori);
player obtine_jucator(Queue* q, int contor);


void push(Node**top, player* jucatori, char* nume_echipa, int numar_jucatori);
char* pop(Node**top);
void deleteStack(Node** top);
void afiseazaStiva(Node*top, char* nume_fisier, int numar_jucatori);

void inorder(NodeArbore* root,char* nume_fisier, int numar_jucatori);
void insert( NodeArbore** node, int numar_jucatori, char*nume_echipa, player* jucatori);
NodeArbore* newNode(char* nume_echipa, player* jucatori,int numar_jucatori);
int height(NodeArbore* root);
int maxim( int a, int b);
NodeArbore* rightRotate(NodeArbore *y);
NodeArbore* leftRotate(NodeArbore *x);
int getBalance( NodeArbore *N);
NodeArbore* insertAVL(NodeArbore* root, int numar_jucatori, char*nume_echipa, player* echipa);
void inorderAVL(NodeArbore* root,char*nume_fisier);
void printLevel2(NodeArbore* node, int curentLevel, char* filename);
void printLevel(NodeArbore* root, char*nume_fisier);
player* assign( player* echipa, player* team, int numar_jucatori);
void deleteTree(NodeArbore* node);