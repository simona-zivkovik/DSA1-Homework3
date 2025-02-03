#include <stdio.h>
#include "dz3p1.h"

int main() {
    unsigned n, izbor, a, b;
    printf("Koliko cvorova hocete da ima prazni graf?\n");
    scanf("%d", &n);
    Elem *graf = prazanGraf(&n);
    while(1) {
        printf("Koja operacija hocete da uradite?\n\t1) Dodavanje novi cvor\n\t2) Uklanjanje cvor\n\t"
               "3) Dodavanje grana\n\t4) Uklanjanje grana\n\t5) Ispis grafa\n\t6) Brisanje grafa\n\t7) Izlazak od programe\n");
        scanf("%d", &izbor);
        switch (izbor) {
            case 1:
                printf("Indeks cvora koji hocete da dodate: ");
                scanf("%d", &a);
                graf = dodavanjeCvor(graf, &n, a);
                ispisGrafa(graf, &n);
                break;
            case 2:
                printf("Indeks cvora koji hocete da uklonite: ");
                scanf("%d", &a);
                graf = uklanjanjeCvor(graf, &n, a);
                ispisGrafa(graf, &n);
                break;
            case 3:
                printf("Izmedju koja dva cvora hocete da ubacite grana?\n");
                scanf("%d %d", &a, &b);
                dodavanjeGrana(graf, &n, a, b);
                ispisGrafa(graf, &n);
                break;
            case 4:
                printf("Izmedju koja dva cvora se nalazi grana koja hocete da izbacite?\n");
                scanf("%d %d", &a, &b);
                uklanjanjeGrana(graf, &n, a, b);
                ispisGrafa(graf, &n);
                break;
            case 5:
                ispisGrafa(graf, &n);
                break;
            case 6:
                brisanjeGrafa(graf, &n);
                break;
            case 7:
                brisanjeGrafa(graf, &n);
                return 0;
        }
    }

}
