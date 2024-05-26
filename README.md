# Organizare-LanParty
Acest fișier Readme conține informații despre programul de gestionare a turneului LAN Party, scris în limbajul C. Programul automatizează procesul de organizare a evenimentului semestrial găzduit de Facultatea de Automatică și Calculatoare prin LSAC, facilitând gestionarea echipelor, jucătorilor, desfășurarea rundelor și generarea clasamentelor.

Prelucrarea datelor:

    Programul citeste dintr-un fisier c.in pana unde trebuie sa parcurga pasii ( un total de 5 pasi)
    Programul citește datele despre echipe și jucători dintr-un fișier text de intrare.
    Fiecare echipă are un nume unic și un număr asociat de jucători.
    Informațiile despre jucători includ prenumele, numele de familie și punctele individuale.
    Se creaza o lista cu toate echipele aflate in fisier. (Pasul 1);

Structuri de date:

    Echipele sunt stocate într-o listă legată, permițând inserarea rapidă de noi echipe (O(1)).
    Pentru gestionarea eficientă a rundelor, se utilizează o coadă pentru meciurile viitoare și două stive - una pentru câștigători și alta pentru învinși.
    Un arbore binar de căutare (BST) ordonează echipele din Top 8 în funcție de punctajul total (descrescător).
    Un arbore AVL stochează, de asemenea, echipele din Top 8, permițând accesul rapid la echipele de pe un anumit nivel (nivelul 2 în acest caz).

Procesul turneului:

    Eliminare inițială: Se elimină iterativ echipele cu cel mai mic punctaj total, pana cand numarul de echipe este egal cu o putere a lui 2. Daca numarul echipelor initiale este o putere a lui doi nu are loc nicio eliminare (pasul 2)
    Simularea meciurilor: Echipele se confruntă în meciuri simulate, iar câștigătorii primesc un punct suplimentar.
    Eliminarea învinșilor: După fiecare rundă, echipele din stiva învinșilor sunt eliminate din competiție.  (pasul 3) 
    Finala: Meciurile continuă până la determinarea echipei câștigătoare.
    De asemenea programul creaza un top 8 al echipelor care este stocat intr-un arbore BST (pasul 4) si arbore AVL (pasul 5)

Rezultate:

    Programul tine evidenta tuturor echipelor aflate in competitie prin scrierea acestora intr-un fisier.
    Programul realizeaza un top 8 al echipelor pe care il afiseaza dupa ce finala este simulata
    Programul afiseaza la final valorile aflate pe nivelul al doilea al unui arbore AVL
