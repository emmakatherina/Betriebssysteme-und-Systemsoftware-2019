#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Datentyp definiert
typedef struct stud_type {
    int matnum;
    char vorname[20];
    char nachname[20];
    struct stud_type *next;
} stud_type;

int const SMALLER = -1;
int const BIGGER = 1;

/* Ist die Datenbank leer?      */
//es wird geprueft, ob der Pointer eine Adresse enthaelt oder nicht.
bool is_empty(stud_type const* liste) {
    return !liste;
}


/* Einfuegen eines Elementes
 *
 * Bekommt einen Zeiger auf einen Zeiger der auf das 1. Element der Liste zeigt
 * Bekommt MatNr, Vorname und Nachname des Studenten der eingefügt werden soll
 *
 * Gibt true für Erfolg zurück
 * Gibt false für einen Fehler zurück
 */
bool enqueue(stud_type** studenten_liste, int matnum, char const vorname[20], char const nachname[20]) {
        /* Hole dynamischen Speicher für den neuen Listen Eintrag */
    stud_type * new_node = malloc(sizeof(stud_type));
   /* Befülle den Speicher (vorsicht vor buffer overflows!) */

   new_node->matnum = matnum;
   // node->vorname[20] = vorname[20];
   // node->nachname[20] = nachname[20];
   for (int i = 0; i<20; i++) {
      new_node->vorname[i] = vorname[i];
      new_node->nachname[i] = nachname[i];
   }
   new_node->next = NULL;
   // the new node is inserted before the existing node
   // node->next = *studenten_liste;

    /* Füge den neuen Eintrag in die Liste ein */
        /* Ist die Liste leer ? */
   if (is_empty(*studenten_liste) == true) {
      // the new node becomes the first node in the list
      *studenten_liste = new_node;
   }
   /* Sortier den Studenten aufsteigend nach Matrikelnummer ein (matrikelnummern sind einzigartig) */
   else {
      stud_type* curr_node = *studenten_liste;

      if (curr_node->matnum == new_node->matnum) {
         //jede Matrikelnummer sollte eindeutig sein
         return false;
      }
      if (curr_node->matnum > new_node->matnum) {
         //der neu eingefuegte Knoten wird als erstes Element
         new_node->next = curr_node;
         *studenten_liste = new_node;
      }
      else {
         while (curr_node->next) {
            if (curr_node->next->matnum == new_node->matnum) {
               //jede Matrikelnummer sollte eindeutig sein
               return false;
            }
            if (curr_node->next->matnum > new_node->matnum) {
               stud_type* temp = curr_node->next;
               curr_node->next = new_node;
               new_node->next = temp;
               return true;
            }
            curr_node = curr_node->next;
         }
         curr_node->next = new_node;
      }
      return true;
   }
   return true;
}



/* Löschen eines Elementes.
 *
 * Bekommt einen Zeiger auf einen Zeiger der auf das 1. Element der Liste zeigt
 * Bekommt die MatNr des Studenten der zu löschen ist
 *
 * Gibt true für Erfolg zurück
 * Gibt false für einen Fehler zurück
 */
bool dequeue(stud_type** studenten_liste, int matnum) {
    /* Prüfe Randbedingungen */

    // 1.Fall : die Liste ist leer
    if(*studenten_liste == NULL){
        return false;
    }
    // 2.Fall : das zu loeschende Element ist das erste Element von dem Array
    stud_type* currStud = *studenten_liste;
    if(currStud->matnum == matnum){
        *studenten_liste = currStud->next;
        return true;
    }
    // 3.Fall : das zuloeschende Element ist im Mittel des Arrays
    /* Lösche den Studenten und gibt den Speicher frei */
    stud_type* target = NULL;
    stud_type* previous;
    while(currStud){
        if(currStud->matnum == matnum){
            target = currStud;
            previous->next = currStud->next;
            free(target);
            return true;
        }
        previous = currStud;
        currStud = currStud->next;
    }
    /* Was muss passieren wenn das 1. Element gelöscht wird?
     * -> es wurde im 2. Fall behandelt.
     */

    /* Was ist wenn es nicht in der Liste ist? */
    if(target == NULL){
        return false;
    }
    /* ... */
    return true;
}

int compareFirstname(stud_type const* a, stud_type const* b){
    int i;
    int aF;
    int bF;
    for( i = 0; i<20; i++){
        aF = a->vorname[i];
        bF = b->vorname[i];

        if(aF == 0){
            return -1;
        }
        else if(bF == 0){
            return 1;
        }
        //gibt -1 zurueck, wenn der Nachname von dem ersten Parameter vorne als der vom zweiten Parameter
        else if(aF < bF){
            return -1;
        }
        //andersum
        else if (aF > bF)
        {
            return 1;
        }
    }
    //gibt 0 zurueck, wenn die Namen identisch sind
    return 0;
}

int compareLastname(stud_type const* a, stud_type const* b){
    int i;
    int aF;
    int bF;
    for( i = 0; i<20; i++){
        aF = a->nachname[i];
        bF = b->nachname[i];

        if(aF == 0){
            return -1;
        }
        else if(bF == 0){
            return 1;
        }
        //gibt -1 zurueck, wenn der Nachname von dem ersten Parameter vorne als der vom zweiten Parameter
        else if(aF < bF){
            return -1;
        }
        //andersum
        else if (aF > bF)
        {
            return 1;
        }
    }
    //gibt 0 zurueck, wenn die Namen identisch sind
    return 0;
}




stud_type** sortieren(int (*compare)(stud_type const* a, stud_type const* b), stud_type** studenten_liste){
    stud_type** newList = malloc(sizeof(stud_type));

    if(*studenten_liste == NULL){
        return newList;
    }
    else{
        while(*studenten_liste != NULL){
            stud_type* currStud = *studenten_liste;
            stud_type* target = currStud;
            while(currStud){
                if(compare(target, currStud) == BIGGER){
                    target = currStud;
                }
                currStud = currStud->next;
            }
            if(*newList == NULL){
                //*newList = target;
                enqueue(newList, target->matnum, target->vorname, target->nachname);
            }else{
                stud_type* tmp = *newList;
                while(tmp->next){
                    tmp = tmp->next;
                }

                stud_type* tmp2 = malloc(sizeof(stud_type));
                tmp2->matnum = target->matnum;
                for(int i = 0; i<20; i++){
                    tmp2->vorname[i] = target->vorname[i];
                    tmp2->nachname[i] = target->nachname[i];
                }
                tmp2->next = NULL;

                tmp->next = tmp2;
            }

        dequeue(studenten_liste, target->matnum);
        }

    }
    return newList;
}

/* Auslesen eines Elementes
 *
 * Bekommt pointer auf den Listenstart
 * Bekommt MatNr des Studenten der ausgelesen werden soll
 *
 * Schreibt Vorname und Nachname in vorname und nachname
 */
bool get_student(stud_type const* studenten_liste, int matnum, char vorname[20], char nachname[20]) {
    /* Durchsuchen der DB */
    stud_type const* curr = studenten_liste;
    while (curr && curr->matnum < matnum) {
        curr = curr->next;
    }

    if (!curr || curr->matnum != matnum) {
        /* Rückgabewert: Fehler */
        return false;
    } else {
        strncpy(vorname, curr->vorname, 19);
        vorname[19] = '\0';
        strncpy(nachname, curr->nachname, 19);
        nachname[19] = '\0';
        /* Rückgabewert: OK */
        return true;
    }
}

static void test_empty(stud_type const* liste) {
    printf(">>> Test ob die Studentenliste leer ist ...\n");

    if(is_empty(liste)) {
        printf("    Die Studentenliste ist leer \n");
    } else {
        printf("    Die Studentenliste ist nicht leer \n");
    }
}

static void test_get(stud_type const* liste, int matnum) {
    printf(">>> Test, ob die Matrikelnummer %4i bereits erfasst wurde ...\n", matnum);

    char vorname[20];
    char nachname[20];
    if(get_student(liste, matnum, vorname, nachname)) {
        printf("    (**)Matrikelnummer %4i: %s %s\n", matnum, vorname, nachname);
    } else {
        printf("    Matrikelnummer %4i ist unbekannt\n", matnum);
    }
}

static void test_enqueue(stud_type** liste, int matnum, char const* vorname, char const* nachname) {
    printf(">>> Fuege neuen Studenten in die Liste ein: %s %s [%4i] ...\n", vorname, nachname, matnum);
    if(enqueue(liste, matnum, vorname, nachname)) {
        printf("    Matrikelnummer %4i eingefügt\n", matnum);
    } else {
        printf("    Matrikelnummer %4i konnte nicht eingefügt werden\n", matnum);
    }
}

static void test_dequeue(stud_type** liste, int matnum) {
    printf(">>> Loesche die Matrikelnummer %4i ...\n", matnum);

    if(dequeue(liste, matnum)) {
        printf("    Matrikelnummer %4i geloescht\n", matnum);
    } else {
        printf("    Matrikelnummer %4i war nicht erfasst\n", matnum);
    }
}

static void test_dump(stud_type const* liste) {
    printf(">>> Gebe alle erfassten Studenten aus ...\n");
    for(stud_type const* curr = liste; curr; curr = curr->next) {
        printf("    Matrikelnummer %4i: %s %s\n", curr->matnum, curr->vorname, curr->nachname);
    }
}

/* Test der Listenfunktionen  */
int main(void) {
    /* Initialisierung der Datenbank */
    stud_type* studenten_liste = NULL;

    test_empty(studenten_liste);
    test_enqueue(&studenten_liste, 1234, "Eddard", "Stark");
    test_get(studenten_liste, 1234);
    test_enqueue(&studenten_liste, 5678, "Jon", "Snow");
    test_get(studenten_liste, 1234);
    test_enqueue(&studenten_liste, 9999, "Tyrion", "Lannister");
    test_get(studenten_liste, 1235);
    test_enqueue(&studenten_liste, 1289, "Daenerys", "Targaryen");
    test_dequeue(&studenten_liste, 1234);
    test_empty(studenten_liste);
    test_get(studenten_liste, 5678);
    test_dequeue(&studenten_liste, 9998);
    test_enqueue(&studenten_liste, 1289, "Viserys", "Targaryen");
    test_dequeue(&studenten_liste, 5678);
    test_enqueue(&studenten_liste, 1, "Tywin", "Lannister");
    test_dump(studenten_liste);



    stud_type** vorname_liste = sortieren(compareFirstname, &studenten_liste);
    test_dump(*vorname_liste);
    stud_type** nachname_list = sortieren(compareLastname, vorname_liste);
    test_dump(*nachname_list);

    {
        /* Erzeuge sortierte Liste nach Vorname */
        /* Gebe Liste aus */
        /* Räume erzeugte Liste auf */
    }

    {
        /* Erzeuge sortierte Liste nach Nachname */
        /* Gebe Liste aus */
        /* Räume erzeugte Liste auf */
    }

    return 0;
}
