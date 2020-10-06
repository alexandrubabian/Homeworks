#include "arbori_intervale.h"

Nod * creare_nod(int st, int dr) {
  Nod * nod;
  int m;
  nod = malloc(sizeof(Nod));
  nod -> info = 0;
  nod -> interval = malloc(sizeof(Interval));
  nod -> interval -> capat_stanga = st;
  nod -> interval -> capat_dreapta = dr;
  if (st < dr) {
    m = (st + dr) / 2;
    nod -> copil_stanga = creare_nod(st, m);
    nod -> copil_dreapta = creare_nod(m + 1, dr);
  }
  return nod;
}

ArboreDeIntervale * construieste_arbore(int capat_stanga, int capat_dreapta,
  int valoare_predifinita_raspuns_copil,
  void( * f_actualizare)(Nod * nod, int v_actualizare),
  int( * f_combinare_raspunsuri_copii)(int raspuns_stanga, int raspuns_dreapta)) {
  ArboreDeIntervale * arbore;
  arbore = malloc(sizeof(ArboreDeIntervale));
  arbore -> dimensiune = 0;
  arbore -> radacina = creare_nod(capat_stanga, capat_dreapta);
  arbore -> valoare_predifinita_raspuns_copil = valoare_predifinita_raspuns_copil;
  arbore -> f_actualizare = f_actualizare;
  arbore -> f_combinare_raspunsuri_copii = f_combinare_raspunsuri_copii;
  // TODO implementati functia de constructie a arborelui prezentata in enunt
  // TODO initializati campurile unui ArboreDeIntervale*
  return arbore;
}

void actualizare_interval_pentru_nod(ArboreDeIntervale * arbore, Nod * nod,
  Interval * interval, int v_actualizare) {
  if (interval -> capat_stanga <= nod -> interval -> capat_stanga &&
   nod -> interval -> capat_dreapta <= interval -> capat_dreapta)
    arbore -> f_actualizare(nod, v_actualizare);
  else {
    int m = (nod -> interval -> capat_stanga + nod -> interval -> capat_dreapta) / 2;
    if (interval -> capat_stanga <= m)
      actualizare_interval_pentru_nod(arbore, nod -> copil_stanga, interval, v_actualizare);
    if (m < interval -> capat_dreapta)
      actualizare_interval_pentru_nod(arbore, nod -> copil_dreapta, interval, v_actualizare);
    arbore -> f_actualizare(nod, v_actualizare);
  }
  // TODO implementati functia de actualizare pentru un nod
  // Hint: pentru a actualiza un nod cand este cazul folositi arbore->f_actualizare(nod, v_actualizare);

}

// Functia este deja implementata, se cheama functia de mai sus cu radacina arborelui
void actualizare_interval_in_arbore(ArboreDeIntervale * arbore,
  Interval * interval, int v_actualizare) {
  actualizare_interval_pentru_nod(arbore, arbore -> radacina, interval, v_actualizare);
}

int interogare_interval_pentru_nod(ArboreDeIntervale * arbore, Nod * nod, Interval * interval) {
  int valoare_stanga = 0, valoare_dreapta = 0;
  if (interval -> capat_stanga <= nod -> interval -> capat_stanga &&
   nod -> interval -> capat_dreapta <= interval -> capat_dreapta)
    return nod -> info;
  else {
    int m = (nod -> interval -> capat_stanga + nod -> interval -> capat_dreapta) / 2;
    if (interval -> capat_stanga <= m)
      valoare_stanga = interogare_interval_pentru_nod(arbore, nod -> copil_stanga, interval);
    if (m < interval -> capat_dreapta)
      valoare_dreapta = interogare_interval_pentru_nod(arbore, nod -> copil_dreapta, interval);
    return arbore -> f_combinare_raspunsuri_copii(valoare_stanga, valoare_dreapta);
  }
  // TODO implementati functia de interogare pentru un nod prezentata in enunt
  // Hint: cand vreti sa calculati combinarea raspunsurilor folositi
  // arbore->f_combinare_raspunsuri_copii(raspuns_copil_stanga, raspuns_copil_drepta)
}

// Functia este deja implementata, se cheama functia de mai sus cu radacina arborelui
int interogare_interval_in_arbore(ArboreDeIntervale * arbore, Interval * interval) {
  return interogare_interval_pentru_nod(arbore, arbore -> radacina, interval);
}

// ----- DOAR pentru bonus si DOAR daca considerati ca e necesara ----- //
void seteaza_info_in_nod_la_valoare_capat_dreapta(Nod * nod) {
  // TODO cred ca e destul de clar ce vrea sa faca functia asta
}

void seteaza_info_in_arbore_la_valoare_capat_dreapta(ArboreDeIntervale * arbore) {
  seteaza_info_in_nod_la_valoare_capat_dreapta(arbore -> radacina);
}