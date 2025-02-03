#ifndef DZ3_DZ3ASP_H
#define DZ3_DZ3ASP_H

typedef struct element{
    unsigned id, tezina;
    struct element *sled;
}Elem;

Elem* prazanGraf(unsigned *n);
Elem *dodavanjeCvor(Elem* graf, unsigned *n, unsigned id);
Elem *uklanjanjeSuseda(Elem *suseda, unsigned id);
Elem* uklanjanjeCvor(Elem *graf, unsigned *n, unsigned id);
void dodavanjeGrana(Elem *graf, unsigned *n, unsigned id1, unsigned id2);
void uklanjanjeGrana(Elem *graf, unsigned *n, unsigned id1, unsigned id2);
void ispisGrafa(Elem* graf, unsigned *n);
void brisanjeGrafa (Elem *graf, unsigned *n);

#endif DZ3_DZ3ASP_H
