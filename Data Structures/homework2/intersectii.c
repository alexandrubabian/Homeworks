#include "intersectii.h"


// functie ajutatoare
void afiseaza_lista_intervale(ListaIntervale2D * lista) {
  int i;
  for (i = 0; i < lista -> dimensiune; i++) {
    Interval2D * interv = lista -> intervale[i];
    printf("{punct stanga x: %d, punct stanga y: %d, punct dreapta x: %d, punct dreapta y: %d}\n",
      interv -> punct_stanga -> x, interv -> punct_stanga -> y,
      interv -> punct_dreapta -> x, interv -> punct_dreapta -> y);
  }
}

ListaIntervale2D * citeste_intrare(char * nume_fisier_intrare) {
  ListaIntervale2D * lista;
  lista = malloc(sizeof(ListaIntervale2D));
  FILE * in = fopen(nume_fisier_intrare, "rt");
  if ( in == NULL) {
    printf("fisier inexistent");
    exit(0);
  }
  fscanf( in , "%d", & lista -> dimensiune);
  lista -> intervale = malloc(lista -> dimensiune * sizeof(Interval2D * ));
  for (int i = 0; i < lista -> dimensiune; i++) {
    lista -> intervale[i] = malloc(sizeof(Interval2D));
    lista -> intervale[i] -> punct_stanga = malloc(sizeof(Punct2D));
    lista -> intervale[i] -> punct_dreapta = malloc(sizeof(Punct2D));
    fscanf( in , "%d %d %d %d", & lista -> intervale[i] -> punct_stanga -> x,
    	&lista -> intervale[i] -> punct_stanga -> y, &
        lista -> intervale[i] -> punct_dreapta -> x, & lista -> intervale[i] -> punct_dreapta -> y);
  }
  // TODO citeste intervalele din fisierul dat ca parametru
  // si le salveaza in lista de intervale
  return lista;
}

// ! Functie pentru actualizarea in arbore
// ! O veti da ca parametru cand initializati arborele
void actualizare_cu_delta(Nod * nod, int v2) {
  nod -> info += v2;
}

// ! Functie pentru combinarea raspunsurilor in arbore
// ! O veti da ca parametru cand initializati arborele
int suma_raspunsurilor(int r1, int r2) {
  return r1 + r2;
}

int perpendicular(Interval2D * interval) {
  if (interval -> punct_stanga -> x == interval -> punct_dreapta -> x)
    return 1;
  return 0;
}

int orizontal(Interval2D * interval) {
  if (interval -> punct_stanga -> y == interval -> punct_dreapta -> y)
    return 1;
  return 0;
}
Interval * construct_interval(int st, int dr) {
  Interval * interval = malloc(sizeof(Interval));
  if (interval == NULL) {
    exit(1);
  }
  interval -> capat_stanga = st;
  interval -> capat_dreapta = dr;
  return interval;
}
int calculeaza_numar_intersectii(ListaIntervale2D * lista) {
  // TODO calculati numarul de intersectii folosind arbori de intervale conform enuntului
  // Hint: initializarea arborelui: 
  int maxim = 0, ok, contor = 0;
  ajutor ** vector, * aux;
  vector = malloc(sizeof(ajutor * ) * lista -> dimensiune * 2);
  for (int i = 0; i < lista -> dimensiune; i++) {
    vector[i * 2] = malloc(sizeof(ajutor));
    vector[i * 2 + 1] = malloc(sizeof(ajutor));
    vector[i * 2] -> x = lista -> intervale[i] -> punct_stanga -> x;
    vector[i * 2] -> y = lista -> intervale[i] -> punct_stanga -> y;
    vector[i * 2] -> pozitie = i;
    vector[i * 2 + 1] -> x = lista -> intervale[i] -> punct_dreapta -> x;
    vector[i * 2 + 1] -> y = lista -> intervale[i] -> punct_dreapta -> y;
    vector[i * 2 + 1] -> pozitie = i;
    vector[i * 2] -> perp = perpendicular(lista -> intervale[i]);
    vector[i * 2 + 1] -> perp = perpendicular(lista -> intervale[i]);
    if (lista -> intervale[i] -> punct_dreapta -> y > maxim)
      maxim = lista -> intervale[i] -> punct_dreapta -> y;
    if (lista -> intervale[i] -> punct_stanga -> y > maxim)
      maxim = lista -> intervale[i] -> punct_stanga -> y;
  }
  // aparitie=calloc(sizeof(int)*maxim);
  do {
    ok = 1;
    for (int i = 0; i < lista -> dimensiune * 2 - 1; i++)
      if (vector[i] -> x > vector[i + 1] -> x) {
        ok = 0;
        aux = vector[i];
        vector[i] = vector[i + 1];
        vector[i + 1] = aux;
      }
  } while (ok != 1);
  ArboreDeIntervale * arbore = construieste_arbore(0, maxim, 0, actualizare_cu_delta, suma_raspunsurilor);
  Interval * interval;
  for (int i = 0; i < lista -> dimensiune * 2; i++) {
    if (vector[i] -> x == lista -> intervale[vector[i] -> pozitie] -> punct_stanga -> x &&
      vector[i] -> x != lista -> intervale[vector[i] -> pozitie] -> punct_dreapta -> x) {
      interval = construct_interval(vector[i] -> y, vector[i] -> y);
      actualizare_interval_in_arbore(arbore, interval, 1);
    } else {
      if (vector[i] -> x == lista -> intervale[vector[i] -> pozitie] -> punct_dreapta -> x &&
        vector[i] -> x != lista -> intervale[vector[i] -> pozitie] -> punct_stanga -> x) {
        interval = construct_interval(vector[i] -> y, vector[i] -> y);
        actualizare_interval_in_arbore(arbore, interval, -1);
      } else {
        if (vector[i] -> x == lista -> intervale[vector[i] -> pozitie] -> punct_dreapta -> x &&
          vector[i] -> x == lista -> intervale[vector[i] -> pozitie] -> punct_stanga -> x &&
          vector[i] -> perp == 1) {
          //ma folosesc de faptul ca sortarea nu va muta elementele perpendiculare
          //aflate unele langa celelalte
          vector[i] -> perp = 0;
          vector[i + 1] -> perp = 0;
          interval = construct_interval(vector[i] -> y, vector[i + 1] -> y);
          contor = contor + interogare_interval_in_arbore(arbore, interval);
        }
      }
    }
  }
  for (int i = 0; i < lista -> dimensiune * 2; i++)
    free(vector[i]);
  free(vector);
  return contor;
  //Interval *interval = construct_interval(4, 5);
}

int maxi(int a, int b) {
  if (a > b)
    return a;
  return b;
}

int mini(int a, int b) {
  if (a < b)
    return a;
  return b;
}

int calculeaza_numar_intersectii_trivial(ListaIntervale2D * lista) {
  int contor = 0;
  // TODO: solutia triviala, verific fiecare segment cu fiecare segment daca se intersecteaza 
  for (int i = 0; i < lista -> dimensiune - 1; i++)
    for (int j = i + 1; j < lista -> dimensiune; j++)
      if (perpendicular(lista -> intervale[i]) == 1 && orizontal(lista -> intervale[j]) == 1) {
        if (lista -> intervale[i] -> punct_dreapta -> x <=
        	 maxi(lista -> intervale[j] -> punct_stanga -> x, lista -> intervale[j] -> punct_dreapta -> x) &&
        	 lista -> intervale[i] -> punct_dreapta -> x >=
        	 mini(lista -> intervale[j] -> punct_stanga -> x, lista -> intervale[j] -> punct_dreapta -> x) &&
          	 lista -> intervale[j] -> punct_dreapta -> y <= 
          	 maxi(lista -> intervale[i] -> punct_stanga -> y, lista -> intervale[i] -> punct_dreapta -> y) &&
          	 lista -> intervale[j] -> punct_dreapta -> y >=
          	 mini(lista -> intervale[i] -> punct_stanga -> y, lista -> intervale[i] -> punct_dreapta -> y))
          contor++;

      } else {
        if (perpendicular(lista -> intervale[j]) == 1 && orizontal(lista -> intervale[i]) == 1)
          if (lista -> intervale[j] -> punct_dreapta -> x <= maxi(lista -> intervale[i] -> punct_stanga -> x, lista -> intervale[i] -> punct_dreapta -> x) &&
            lista -> intervale[j] -> punct_dreapta -> x >= mini(lista -> intervale[i] -> punct_stanga -> x, lista -> intervale[i] -> punct_dreapta -> x) &&
            lista -> intervale[i] -> punct_dreapta -> y <= maxi(lista -> intervale[j] -> punct_stanga -> y, lista -> intervale[j] -> punct_dreapta -> y) &&
            lista -> intervale[i] -> punct_dreapta -> y >= mini(lista -> intervale[j] -> punct_stanga -> y, lista -> intervale[j] -> punct_dreapta -> y))
            contor++;
      }
  return contor;
}