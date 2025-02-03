#include "dz3p1.h"
#include <stdio.h>
#include <stdlib.h>

Elem* prazanGraf(unsigned *n){
/**
 * @brief formira prazan graf
 *
 * Ova funckija prima pokazivac na broja elemenata u grafu i formira prazan graf (samo cvorova, bez grana)
 * koriscenjem (inverzna) lista susednosti s time sta dinamicki alocira niz pokazivaca
 * i na svaki element niza dodeli indeks (0-n), tezina (originalno 0) i pokazivac ka sledecem elementu
 *
 * @param n (unsigned*)- broj cvorova
 *
 * @return graf - niza pokazivaca na ulancanih lista
 */
    if(*n <= 0){
        printf("LOG_GRESKA");
        return NULL;
    }
    Elem *graf = NULL;
    graf = (Elem*)malloc(*n * sizeof(Elem));
    if(graf==NULL){
        printf("MEM_GRESKA");
        free(graf);
        return NULL;
    }
    for(int i=0; i<*n; i++){
        graf[i].id = i;
        graf[i].tezina = 0;
        graf[i].sled = NULL;
    }
    return graf;
}

Elem *dodavanjeCvor(Elem* graf, unsigned *n, unsigned id){
/**
 * @brief dodava cvor sa datim id-om
 *
 * Funkcija realocira dinamicki opredelena memorija od n na n+1
 * formira novi cvor sa datim id-om, tezina=0 i pokazivac na sled koji je originalno NULL
 *
 * @param graf (Elem*) - pokazivac na niz pokazivaca
 * @param n (unsigned*) - pokazivac na broja cvorova u grafu
 * @param id (unsigned) - broj indeksa cvora koga zelimo da dodamo
 *
 * @return graf sa novim cvorom
 */
    Elem *novi = NULL;
    for(int i=0; i<*n; i++){
        if(id == graf[i].id){
            printf("Cvor vec postoji\n");
            return NULL;
        }
    }
    graf = (Elem*) realloc(graf, (*n+1)*sizeof(Elem));
    if(graf == NULL){
        printf("MEM_GRESKA\n");
        return NULL;
    }
    graf[(*n)].id = id;
    graf[(*n)].tezina = 0;
    graf[(*n)].sled = NULL;
    (*n)++;

    return graf;
}

Elem *uklanjanjeSuseda(Elem *suseda, unsigned id){
/**
* @brief uklanja cvor sa datim id-om od svih liste suseda
 *
 * Standardna funkcija za uklanjanje cvor sa datom vrednoscu (u ovom slucaju id) od ulancana lista
 *
 * @param suseda (Elem*) - ulancana lista suseda od koja treba da se skloni cvor sa datim id-om
 * @param id (unsigned) - id cvora koji treba da se skloni sa grafa
 *
 * @return azurirana lista suseda sa uklonjeni cvor
*/
    Elem *pret=NULL, *tek=suseda, *stari;
    while(tek){
        if(tek->id == id){
            stari = tek;
            tek = tek->sled;
            if(!pret) suseda = tek; //uklanjamo prvi cvor
            else pret -> sled = tek;
            free(stari);
        }
        else {
            pret = tek;
            tek = tek->sled;
        }
    }
    return suseda;
}

Elem* uklanjanjeCvor(Elem *graf, unsigned *n, unsigned id){
/**
* @brief uklanja cvor sa datim id-om
 *
 * Uklanja dati cvor od liste susednosti ostalih cvorovima.
 * Onda koriscenjem standardna funkcija za uklanjanje cvor sa datom vrednoscu (id) uklanja ga od grafa.
 * Realocira memoriju od n na n-1
 *
 * @param graf (Elem*) - pokazivac na niz koji predstvalja grafa
 * @param n - (unsigned*) - pokazivac na broj cvorova u grafu
 * @param id (unsigned) - id cvora koji treba da se ukloni
 *
 * @return graf - pokazivac na azurirani graf
*/
    //Proverka da li taj svor postoji u grafu
    int prov = 0;
    for(int i=0; i<*n; i++){
        if(graf[i].id == id){
            prov = 1;
            break;
        }
    }
    if(prov == 0){
        printf("Cvor ne postoji u grafu \n");
        return NULL;
    }

    Elem *stari;
    for(int i=0; i<*n; i++){
        graf[i].sled = uklanjanjeSuseda(graf[i].sled, id);
    }

    for(int i=0; i<*n; i++){
        if(graf[i].id == id){
            while(graf[i].sled){
                stari = graf[i].sled;
                graf[i].sled = graf[i].sled -> sled;
                free(stari);
            }
            for(int j=i; j<*n-1; j++){
                graf[j] = graf[j+1];
            }
            graf = realloc(graf, ((*n)-1)*sizeof(Elem));
            (*n)--;
            if(graf == NULL){
                printf("MEM_GRESKA\n");
                return NULL;
            }
            break;
        }
    }
    return graf;
}

void dodavanjeGrana(Elem *graf, unsigned *n, unsigned id1, unsigned id2){
/**
* @brief povezuje dva cvora sa datim id-ovima
 *
 *
 *
 * @param graf (Elem*) - pokazivac na grafa
 * @param n (unsigned*) - pokazivac na broja cvorova
 * @param id1 (unsigned) - id prvog cvora
 * @param id2 (unsigned) - id drugog svora
*/
    for(int i=0; i<*n; i++){
        if(graf[i].id == id1){
            Elem *novi = malloc(sizeof(Elem));
            novi->id = id2;
            novi->tezina = 0;
            novi->sled = NULL;

            Elem *tek = graf[i].sled;
            if(tek == NULL) {
                graf[i].sled = novi;
            }
            else {
                while(tek->sled != NULL) {
                    tek = tek->sled;
                }
                tek->sled = novi;
            }
        }
    }
    for(int i=0; i<*n; i++){
        if(graf[i].id == id2){
            Elem *novi = malloc(sizeof(Elem));
            novi->id = id1;
            novi->tezina = 0;
            novi->sled = NULL;

            Elem *tek = graf[i].sled;
            if(tek == NULL) {
                graf[i].sled = novi;
            } else {
                while(tek->sled != NULL) {
                    tek = tek->sled;
                }
                tek->sled = novi;
            }
        }
    }
}

void uklanjanjeGrana(Elem *graf, unsigned *n, unsigned id1, unsigned id2){
    for(int i=0; i<*n; i++){
        if(graf[i].id == id1)
            graf[i].sled = uklanjanjeSuseda(graf[i].sled, id2);
        if(graf[i].id == id2)
            graf[i].sled = uklanjanjeSuseda(graf[i].sled, id1);
    }
}

void ispisGrafa(Elem *graf, unsigned *n){
    Elem *tek;
    for(int i=0; i<*n; i++){
        printf("%d -> ", graf[i].id);
        for(tek=graf[i].sled; tek; tek=tek->sled){
            printf(" %d", tek->id);
            if(tek->sled) putchar(',');
        }
        printf("\n");
    }
    printf("\n");
}

void brisanjeGrafa (Elem *graf, unsigned *n){
    for(int i=0; i<*n; i++){
        free(graf[i].sled);
    }
    free(graf);
    *n = 0;
}