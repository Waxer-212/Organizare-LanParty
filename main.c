#include <stdio.h>
#include "lanPartyLib.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char*argv[])
{   
    Node* head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    char buffer[60];
    
    char* continua = argv[1];
    char* inputFileName = argv[2];
    char* outputFileName = argv[3];

    FILE *f = fopen(inputFileName,"r");
    if(f == NULL)
    {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }
    
    FILE *g = fopen(outputFileName,"wt");
    if(g == NULL)
    {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }

    FILE *h = fopen(continua,"r");
    if(f == NULL)
    {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }

    int* check = (int*)malloc(5*sizeof(int));
    for( int  i = 0; i < 5; i++)
    {
        fscanf(h,"%d",&check[i]);
    }

    int numar_echipe, numar_jucatori, puncte;
    fscanf(f, "%d", &numar_echipe);
    for(int i = 0; i < numar_echipe; i++) /// Pentru a face toate echipele
    {   
        char c;
        fscanf(f,"%d",&numar_jucatori);
        c = fgetc(f);
        fgets(buffer,60,f);
        buffer[strcspn(buffer, "\r\n")] = 0; // eliminam caracterul '\n' de la finalul cuvintelor citite
        if(buffer[strlen(buffer) - 1] == ' ')
        {
            buffer[strlen(buffer) - 1] = '\0';  //daca avem spatiu la finalul cuvantului il inlocuim cu caracterul nul
        }

        char *sir = (char*)malloc(sizeof(char) * (strlen(buffer) + 1 ) );
        if( sir == NULL)
        {
            printf("Eroare la alocarea memoriei\n");
            exit(1);
        }
        strcpy(sir,buffer);

        player* n = (player*)malloc(sizeof(player) * numar_jucatori);
        if( n == NULL)
        {
            printf("Eroare la alocarea memoriei\n");
            exit(1);
        }

        for(int i = 0; i < numar_jucatori; i++) // Folosit pentru a face fiecare echipa in parte
        {
            fscanf(f,"%s",buffer);            
            char* nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
            strcpy(nume,buffer);
            n[i].firstName = nume;
            nume = NULL;

            fscanf(f,"%s",buffer);
            char* prenume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1 ));
            strcpy(prenume,buffer);
            n[i].secondName = prenume;
            prenume = NULL;

            fscanf(f,"%d",&puncte);
            n[i].points = puncte;
        }
        
        adauga_la_inceput(&head, n, sir, numar_jucatori);
        free(n);
    }
    afiseaza_lista(head, numar_jucatori,outputFileName);    
    
    if(check[1] == 0)  //oprim daca nu mai avem nevoie
        {   
            fclose(f);
            fclose(g);
            fclose(h);
            free(check);
            return 0;
        }

    int stop = puterea_cea_mai_apropiata_a_lui_doi(numar_echipe);
  
    Node* t = head->next;

    while( numar_echipe > stop)
    {   
        float minim = cel_mai_mic_punctaj(head,numar_jucatori);

        while( t != NULL && numar_echipe > stop)
        {   
            float medie = calculare_medie(t->jucatori,numar_jucatori);
            //printf("Media este : %f\n",medie);
            if( medie == minim)
            {
                sterge_nodul(&head, t->nume_echipa);
                numar_echipe--;
                t = head;
            }
            t = t->next;
        }
            t = head->next;
    }
    afiseaza_lista(head,numar_jucatori,outputFileName);
    //De aici incepe punctul 3
    if(check[2] == 0)
         {   
            fclose(f);
            fclose(g);
            fclose(h);
            free(check);
            return 0;
        }
    Queue *q;
    q = createQueue();
    Node* stackTop_castigatori = NULL;

    t = head->next;

    for(int i = 0; i  < numar_echipe; i++)
    {
        enQueue(q,t->jucatori,numar_jucatori,t->nume_echipa);
        t = t->next;
    }
    
    Node* stackTop_invinsi = NULL;
    int index = 0;
    player* echipa = (player*)malloc(sizeof(player) * numar_jucatori);
    char* nume_echipa;
    
    NodeArbore* rootBST = NULL;
    NodeArbore* rootAVL = NULL;
    while( numar_echipe != 1 )
    {   
        index++;
        fseek(g,0,SEEK_END);
        fprintf(g,"\n--- ROUND NO:%d\n",index);
        fflush(g);
        afiseaza_coada(q,numar_jucatori,outputFileName);

        for( int i = 0; i < numar_echipe / 2; i++)
        {   
            float puncte_echipa_1 = 0;
            float puncte_echipa_2 = 0;
            puncte_echipa_1 = obtine_puncte(q,numar_jucatori);

            echipa = assign(echipa,q->front->jucatori,numar_jucatori);
            nume_echipa = deQueue(q);

            puncte_echipa_2 = obtine_puncte(q,numar_jucatori);
            if (puncte_echipa_1 > puncte_echipa_2)
            {
                for(int i = 0; i < numar_jucatori; i++)
                        echipa[i].points = echipa[i].points + 1;

                push(&stackTop_castigatori,echipa,nume_echipa,numar_jucatori);

                echipa = assign(echipa,q->front->jucatori,numar_jucatori);
                nume_echipa = deQueue(q);
                push(&stackTop_invinsi,echipa,nume_echipa,numar_jucatori);
            }
            else if (puncte_echipa_1 <= puncte_echipa_2 )
            {
                push(&stackTop_invinsi,echipa,nume_echipa,numar_jucatori);

                echipa = assign(echipa,q->front->jucatori,numar_jucatori);
                for(int i = 0; i < numar_jucatori; i++)
                        echipa[i].points = echipa[i].points + 1;

                nume_echipa = deQueue(q);
                push(&stackTop_castigatori,echipa,nume_echipa,numar_jucatori);
            } 
        }

        //deleteStack(&stackTop_invinsi);
        fseek(g,0,SEEK_END);
        fprintf(g,"\nWINNERS OF ROUND NO:%d\n",index);
        fflush(g);        
        afiseazaStiva(stackTop_castigatori,outputFileName,numar_jucatori);

        numar_echipe  = numar_echipe / 2;
        for(int i = 0; i < numar_echipe; i++)
        {         
            echipa = assign(echipa,stackTop_castigatori->jucatori,numar_jucatori);
            nume_echipa = pop(&stackTop_castigatori);
            enQueue(q, echipa, numar_jucatori, nume_echipa);
            
            if( check[3] == 1 && numar_echipe == 8)
                insert(&rootBST,numar_jucatori,nume_echipa,echipa);
            if( check[4] == 1 && numar_echipe == 8)
                rootAVL = insertAVL(rootAVL,numar_jucatori,nume_echipa,echipa);  
        }
    }
    if( check[3] == 1)
    {
        fseek(g,0,SEEK_END);
        fprintf(g,"\nTOP 8 TEAMS:\n");
        fflush(g);
        inorder(rootBST,outputFileName,numar_jucatori);
    }
    if ( check[4] == 1)
    {   
        fseek(g,0,SEEK_END);
        fflush(g);
        fprintf(g,"\nTHE LEVEL 2 TEAMS ARE:\n");
        fflush(g);
        printLevel2(rootAVL,0,outputFileName);
        //printLevel(rootAVL,outputFileName);
    }


    //Eliberam memoria pe care am alocat-o
    deleteList(&head);
    deleteQueue(q);
    deleteStack(&stackTop_castigatori);
    fclose(f);
    fclose(g);
    fclose(h);
    continua = outputFileName = inputFileName = nume_echipa = NULL;
    free(check);
    check = NULL;
    free(t);
    t = NULL;
    free(echipa);
    echipa = NULL;
    //deleteTree(rootAVL);
    //deleteTree(rootBST);
 
    return 0;
}