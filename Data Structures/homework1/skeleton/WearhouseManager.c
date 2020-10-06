#include <stdio.h>

#include "WearhouseManager.h"


Package * create_package(long priority,
  const char * destination) {
  Package * pachet_covidel19;
  pachet_covidel19 = malloc(sizeof(Package));
  pachet_covidel19 -> priority = priority;
  //pachet_covid19->destination=NULL;
  if (destination != NULL) {
    pachet_covidel19->destination=malloc(sizeof(char)*100);
    //pachet_covid19 -> destination = strdup(destination);
    strcpy(pachet_covidel19->destination,destination);
  } else
    pachet_covidel19 -> destination = NULL;
  return pachet_covidel19;
}

void destroy_package(Package * package) {
  if (package -> destination != NULL)
    free(package -> destination);
  free(package);
}

Manifest * create_manifest_node(void) {
  Manifest * inventar_covid19;
  inventar_covid19 = malloc(sizeof(Manifest));
  //inventar_covid19->package=malloc(sizeof(Package));
  inventar_covid19 -> package = NULL;
  inventar_covid19 -> next = NULL;
  inventar_covid19 -> prev = NULL;
  return inventar_covid19;
}

void destroy_manifest_node(Manifest * manifest_node) {
  //free(manifest_node->package->destination);
  if (manifest_node -> package != NULL)
    destroy_package(manifest_node -> package);
  free(manifest_node);
}

Wearhouse * create_wearhouse(long capacity) {
  Wearhouse * casa_covid19;
  if (capacity == 0) {
    casa_covid19 = NULL;
    return casa_covid19;
  }
  casa_covid19 = malloc(sizeof(Wearhouse));
  casa_covid19 -> packages = malloc(sizeof(Package * ) * capacity);
  casa_covid19 -> size = 0;

  casa_covid19 -> capacity = capacity;
  return casa_covid19;
}

Wearhouse * open_wearhouse(const char * file_path) {
  ssize_t read_size;
  char * line = NULL;
  size_t len = 0;
  char * token = NULL;
  Wearhouse * w;

  FILE * fp = fopen(file_path, "r");
  if (fp == NULL)
    goto file_open_exception;

  if ((read_size = getline( & line, & len, fp)) != -1) {
    token = strtok(line, ",\n ");
    w = create_wearhouse(atol(token));

    free(line);
    line = NULL;
    len = 0;
  }

  while ((read_size = getline( & line, & len, fp)) != -1) {
    token = strtok(line, ",\n ");
    long priority = atol(token);
    token = strtok(NULL, ",\n ");
    Package * p = create_package(priority, token);
    w -> packages[w -> size++] = p;

    free(line);
    line = NULL;
    len = 0;
  }

  free(line);

  fclose(fp);
  return w;

  file_open_exception:
    return NULL;
}

long wearhouse_is_empty(Wearhouse * w) {
  if (w -> size == 0)
    return 1;
  return 0;
}

long wearhouse_is_full(Wearhouse * w) {
  if (w -> size == w -> capacity)
    return 1;
  return 0;
}

long wearhouse_max_package_priority(Wearhouse * w) {
  long maxim = 0;
  for (int i = 0; i < w -> size; i++)
    if (w -> packages[i] -> priority > maxim)
      maxim = w -> packages[i] -> priority;
  return maxim;

}

long wearhouse_min_package_priority(Wearhouse * w) {
  long minim = 9;
  for (int i = 0; i < w -> size; i++)
    if (w -> packages[i] -> priority < minim)
      minim = w -> packages[i] -> priority;
  return minim;
}

void wearhouse_print_packages_info(Wearhouse * w) {
  for (long i = 0; i < w -> size; i++) {
    printf("P: %ld %s\n",
      w -> packages[i] -> priority,
      w -> packages[i] -> destination);
  }
  printf("\n");
}

void destroy_wearhouse(Wearhouse * wearhouse) {
  for (int i = 0; i < wearhouse -> size; i++)
    destroy_package(wearhouse -> packages[i]);
  free(wearhouse -> packages);
  free(wearhouse);
}

Robot * create_robot(long capacity) {
  Robot * robot_covid19;
  /*if(capacity==0){
  	robot_covid19=NULL;
  	return NULL;
  }*/
  robot_covid19 = malloc(sizeof(Robot));
  robot_covid19 -> size = 0;
  robot_covid19 -> capacity = capacity;
  robot_covid19 -> manifest = NULL; 
  robot_covid19 ->next = NULL;
  //if(capacity!=0)
  //robot_covid19->manifest=create_manifest_node();
  return robot_covid19;
}

int robot_is_full(Robot * robot) {
  if (robot -> size == robot -> capacity)
    return 1;
  return 0;
}

int robot_is_empty(Robot * robot) {
  if (robot -> size == 0)
    return 1;
  return 0;
}

Package * robot_get_wearhouse_priority_package(Wearhouse * w, long priority) {
  if (!(priority >= 0))
    return NULL;
  for (int i = 0; i < w -> size; i++)
    if (w -> packages[i] -> priority == priority)
      return w -> packages[i];
  return NULL;
}

void robot_remove_wearhouse_package(Wearhouse * w, Package * package) {
  int i = 0;
  //gaseste in wearhouse pachetul package
  while (w -> packages[i] != package) {
    i++;
  }
  //eliminare de element dintr-un vector fara dealocare
  for (int j = i; j < w -> size - 1; j++)
    w -> packages[j] = w -> packages[j + 1];
  w -> size--;
}

void robot_load_one_package(Robot * robot, Package * package) {
  Manifest * aux, * ajutor, * inainte;
  int contor = 0;
  if (robot -> manifest == NULL) {
  	//cazul in care in robot nu este niciun pachet
    robot -> manifest = create_manifest_node();
    robot -> manifest -> package = package;
  } else {
    if (robot -> size < robot -> capacity) {
    	//daca inca nu s-a atins capacitatea maxima a robotului,
    	//parcurg itinerariul lui pana ajung la pozitia in care trb inserat
      aux = robot -> manifest;
      while (aux -> next != NULL && aux -> package -> priority > package -> priority) {
        aux = aux -> next;
      }
      if (aux -> next == NULL) { //introducere final
        ajutor = malloc(sizeof(Manifest));
        ajutor -> next = NULL;
        if (aux -> package -> priority > package -> priority) { //adaugare final
          ajutor -> package = package;
          ajutor -> prev = aux;
          aux -> next = ajutor;
        } else if (aux -> package -> priority == package -> priority && strcmp(aux -> package -> destination, package -> destination) <= 0) {
          //tot la final
          ajutor -> package = package;
          ajutor -> prev = aux;
          aux -> next = ajutor;
        } else if (aux -> prev != NULL) { //penultimul
          ajutor -> prev = aux -> prev;
          ajutor -> next = aux;
          aux -> prev -> next = ajutor;
          ajutor -> package = package;
          aux -> prev = ajutor;
        } else if (aux -> prev == NULL) {
        	//un singur pachet
          ajutor -> next = aux;
          aux -> prev = ajutor;
          ajutor -> prev = NULL;
          robot -> manifest = ajutor;
          ajutor -> package = package;
        }
      } else {
      	//nu are legatura ca e la final
        ajutor = malloc(sizeof(Manifest));
        ajutor -> package = package;
        if (aux -> prev == NULL) {
        	//daca s-a oprit while-ul pe primul element din cauza conditiei de prioritate
          if (aux -> package -> priority < package -> priority) {
            //adaugi pe primul element 
            ajutor -> next = aux;
            aux -> prev = ajutor;
            ajutor -> prev = NULL;
            robot -> manifest = ajutor;
          } else if (aux -> package -> priority == package -> priority) {
            while (aux != NULL && aux -> package -> priority == package -> priority && contor == 0) {
              if (strcmp(package -> destination, aux -> package -> destination) <= 0) {
                if (aux -> prev != NULL) {
                  contor = 1;
                  ajutor -> next = aux;
                  ajutor -> prev = aux -> prev;
                  aux -> prev -> next = ajutor;
                  aux -> prev = ajutor;
                } else if (aux -> prev == NULL) {
                  contor = 1;
                  ajutor -> next = aux;
                  aux -> prev = ajutor;
                  ajutor -> prev = NULL;
                  robot -> manifest = ajutor;
                }
              }
              inainte = aux;
              aux = aux -> next;

            }
            //am folosit un contor cu argumentul ca poate sa dea de prioritati egale de n ori, dar pachetul
            //poate e nevoie sa fie inserat la n-i
            if (contor == 0) {
              ajutor -> prev = inainte;
              inainte -> next = ajutor;
              ajutor -> next = NULL;
            }
          }
        } else {
        	//acelasi procedeu,cautarea fiind facuta in mijlocul listei
          if (aux -> package -> priority < package -> priority) {
            ajutor -> next = aux;
            ajutor -> prev = aux -> prev;
            aux -> prev -> next = ajutor;
            aux -> prev = ajutor;
          }

          if (aux -> package -> priority == package -> priority)
            while (aux != NULL && aux -> package -> priority == package -> priority && contor == 0) {
              if (strcmp(package -> destination, aux -> package -> destination) <= 0) {
                contor = 1;
                ajutor -> next = aux;
                ajutor -> prev = aux -> prev;
                aux -> prev -> next = ajutor;
                aux -> prev = ajutor;
              }
              aux = aux -> next;
            }
        }
      }
    }
  }
  //indiferent de pozitia in care se introduce un pachet, size-ul creste
  robot -> size++;
}

long robot_load_packages(Wearhouse * wearhouse, Robot * robot) {
  long maxim = 0, first;
  Package * pachet_covid19 = NULL;
  while (wearhouse -> size != 0 && robot -> size != robot -> capacity) {
    first = wearhouse_max_package_priority(wearhouse);
    pachet_covid19 = robot_get_wearhouse_priority_package(wearhouse, first);
    robot_load_one_package(robot, pachet_covid19);
    robot_remove_wearhouse_package(wearhouse, pachet_covid19);
    maxim++;
  }
  return maxim;
}

Package * robot_get_destination_highest_priority_package(Robot * robot,
  const char * destination) {
  Manifest * covid;
  if (robot -> manifest == NULL)
    return NULL;
  covid = robot -> manifest;
  while (covid != NULL) {
    if (strcmp(covid -> package -> destination, destination) == 0)
      return covid -> package;
    covid = covid -> next;
  }
  return NULL;

}

void destroy_robot(Robot * robot) {
  Manifest *prev;
  prev=robot->manifest;
  while(robot->manifest!=NULL)
  {
  	robot->manifest=robot->manifest->next;
  	destroy_manifest_node(prev);
  	prev=robot->manifest;
  }
  //destroy_manifest_node(robot->manifest);
  //free(robot -> manifest);
  free(robot);
}

void robot_unload_packages(Truck * truck, Robot * robot) {
  Manifest * aux, * auxiliar, * auxtruck;
  aux = robot -> manifest;
  while (truck -> size < truck -> capacity && aux != NULL && robot -> size > 0) {
    if (strcmp(aux -> package -> destination, truck -> destination) == 0) {
      auxtruck = truck -> manifest;
      if (auxtruck == NULL) {
        auxtruck = malloc(sizeof(Manifest));
        auxtruck -> next = NULL;
        auxtruck -> prev = NULL;
        auxtruck -> package = aux -> package;
        truck -> manifest = auxtruck;
      } else {
        while (auxtruck -> next != NULL) {
          auxtruck = auxtruck -> next;
        }
        auxtruck -> next = malloc(sizeof(Manifest));
        auxtruck -> next -> prev = auxtruck;
        auxtruck -> next -> package = aux -> package;
        auxtruck -> next -> next = NULL;
      }
      //sus am facut adaugarea in tir, iar dedesubt sunt eliminate pachetele din robot
      if (aux -> next != NULL) {
        if (aux -> prev != NULL) {
          auxiliar = aux;
          auxiliar -> prev -> next = aux -> next;
          auxiliar -> next -> prev = aux -> prev;
          aux = aux -> next;
          //free(auxiliar);
        } else if (aux -> prev == NULL) {
          auxiliar = aux;
          aux -> next -> prev = NULL;
          robot -> manifest = aux -> next;
          aux = aux -> next;
          //free(auxiliar);
        }
      } else if (aux -> next == NULL) {
        if (aux -> prev == NULL) {
          robot -> manifest = NULL;
          aux = NULL;
        } else {
          auxiliar = aux;
          auxiliar -> prev -> next = NULL;
          //free(auxiliar);
          aux = NULL;
        }
      }
      truck -> size++;
      robot -> size--;
    } else
      aux = aux -> next;
  }
}

// Attach to specific truck
int robot_attach_find_truck(Robot * robot, Parkinglot * parkinglot) {
  int found_truck = 0;
  long size = 0;
  Truck * arrived_iterator = parkinglot -> arrived_trucks -> next;
  Manifest * m_iterator = robot -> manifest;

  while (m_iterator != NULL) {
    while (arrived_iterator != parkinglot -> arrived_trucks) {
      size = truck_destination_robots_unloading_size(arrived_iterator);
      if (strncmp(m_iterator -> package -> destination, arrived_iterator -> destination, MAX_DESTINATION_NAME_LEN) == 0 &&
        size < (arrived_iterator -> capacity - arrived_iterator -> size)) {
        found_truck = 1;
        break;
      }

      arrived_iterator = arrived_iterator -> next;
    }

    if (found_truck)
      break;
    m_iterator = m_iterator -> next;
  }

  if (found_truck == 0)
    return 0;

  Robot * prevr_iterator = NULL;
  Robot * r_iterator = arrived_iterator -> unloading_robots;
  while (r_iterator != NULL) {
    Package * pkg = robot_get_destination_highest_priority_package(r_iterator, m_iterator -> package -> destination);
    if (m_iterator -> package -> priority >= pkg -> priority)
      break;
    prevr_iterator = r_iterator;
    r_iterator = r_iterator -> next;
  }

  robot -> next = r_iterator;
  if (prevr_iterator == NULL)
    arrived_iterator -> unloading_robots = robot;
  else
    prevr_iterator -> next = robot;

  return 1;
}

void robot_print_manifest_info(Robot * robot) {
  Manifest * iterator = robot -> manifest;
  while (iterator != NULL) {
    printf(" R->P: %s %ld\n", iterator -> package -> destination, iterator -> package -> priority);
    iterator = iterator -> next;
  }

  printf("\n");
}

Truck * create_truck(const char * destination, long capacity, long transit_time, long departure_time) {
  Truck * tir_cu_corona;
  tir_cu_corona = malloc(sizeof(Truck));
  if (destination != NULL) {
    tir_cu_corona -> destination = malloc(sizeof(char) * 100);
    strcpy(tir_cu_corona -> destination, destination);
  }
  //denumiri sugestive
  tir_cu_corona -> manifest = NULL;
  tir_cu_corona -> unloading_robots = NULL;
  tir_cu_corona -> capacity = capacity;
  tir_cu_corona -> in_transit_time = 0;
  tir_cu_corona -> size = 0;
  tir_cu_corona -> departure_time = departure_time;
  tir_cu_corona -> transit_end_time = transit_time;
  tir_cu_corona -> next = NULL;
  return tir_cu_corona;
}

int truck_is_full(Truck * truck) {
  if (truck -> size == truck -> capacity)
    return 1;
  return 0;
}

int truck_is_empty(Truck * truck) {
  if (truck -> size == 0)
    return 1;
  return 0;
}

long truck_destination_robots_unloading_size(Truck * truck) {
  long maxim = 0;
  Robot * aux = truck -> unloading_robots;
  while (aux != NULL) {
    Manifest * auxcovid;
    auxcovid = aux -> manifest;
    while (auxcovid != NULL) {
      if (strcmp(auxcovid -> package -> destination, truck -> destination) == 0) {
        maxim = maxim + aux -> size;
        //conditie de iesire din al doilea while ca sa treaca la robotul urmator asociat tirului
        auxcovid = NULL;
      } else
        auxcovid = auxcovid -> next;
    }
    aux = aux -> next;
  }
  return maxim;
}

void truck_print_info(Truck * truck) {
  printf("T: %s %ld %ld %ld %ld %ld\n", truck -> destination, truck -> size, truck -> capacity,
    truck -> in_transit_time, truck -> transit_end_time, truck -> departure_time);

  Manifest * m_iterator = truck -> manifest;
  while (m_iterator != NULL) {
    printf(" T->P: %s %ld\n", m_iterator -> package -> destination, m_iterator -> package -> priority);
    m_iterator = m_iterator -> next;
  }

  Robot * r_iterator = truck -> unloading_robots;
  while (r_iterator != NULL) {
    printf(" T->R: %ld %ld\n", r_iterator -> size, r_iterator -> capacity);
    robot_print_manifest_info(r_iterator);
    r_iterator = r_iterator -> next;
  }
}

void destroy_truck(Truck * truck) {
	Robot *prev;
  prev=truck->unloading_robots;
  while(truck->unloading_robots!=NULL)
  {
  	truck->unloading_robots=truck->unloading_robots->next;
  	destroy_robot(prev);
  	prev=truck->unloading_robots;
  }
  //free(truck->destination);
  free(truck);
}

Parkinglot * create_parkinglot(void) {
  Parkinglot * loc;
  loc = malloc(sizeof(Parkinglot));
  loc -> arrived_trucks = malloc(sizeof(Truck));
  loc -> arrived_trucks -> next = loc -> arrived_trucks;
  loc -> departed_trucks = malloc(sizeof(Truck));
  loc -> departed_trucks -> next = loc -> departed_trucks;
  loc -> pending_robots = malloc(sizeof(Robot));
  loc -> pending_robots -> next = loc -> pending_robots;
  loc -> standby_robots = malloc(sizeof(Robot));
  loc -> standby_robots -> next = loc -> standby_robots;
  return loc;
}

Parkinglot * open_parckinglot(const char * file_path) {
  ssize_t read_size;
  char * line = NULL;
  size_t len = 0;
  char * token = NULL;
  Parkinglot * parkinglot = create_parkinglot();

  FILE * fp = fopen(file_path, "r");
  if (fp == NULL)
    goto file_open_exception;

  while ((read_size = getline( & line, & len, fp)) != -1) {
    token = strtok(line, ",\n ");
    // destination, capacitym transit_time, departure_time, arrived
    if (token[0] == 'T') {
      token = strtok(NULL, ",\n ");
      char * destination = token;

      token = strtok(NULL, ",\n ");
      long capacity = atol(token);

      token = strtok(NULL, ",\n ");
      long transit_time = atol(token);

      token = strtok(NULL, ",\n ");
      long departure_time = atol(token);

      token = strtok(NULL, ",\n ");
      int arrived = atoi(token);

      Truck * truck = create_truck(destination, capacity, transit_time, departure_time);

      if (arrived)
        truck_arrived(parkinglot, truck);
      else
        truck_departed(parkinglot, truck);

    } else if (token[0] == 'R') {
      token = strtok(NULL, ",\n ");
      long capacity = atol(token);

      Robot * robot = create_robot(capacity);
      parkinglot_add_robot(parkinglot, robot);

    }

    free(line);
    line = NULL;
    len = 0;
  }
  free(line);

  fclose(fp);
  return parkinglot;

  file_open_exception:
    return NULL;
}

void parkinglot_add_robot(Parkinglot * parkinglot, Robot * robot) {
  Robot * aux, * comparare, * prev;
  if (robot -> size == 0) {
  	//aceeasi metoda de adaugare atat pt stanby cat si pt pending
    aux = robot;
    if (parkinglot -> standby_robots -> next == parkinglot -> standby_robots) {
      aux -> next = parkinglot -> standby_robots;
      parkinglot -> standby_robots -> next = aux;
    } else {
      comparare = parkinglot -> standby_robots -> next;
      prev = parkinglot -> standby_robots;
      while (comparare -> next != parkinglot -> standby_robots && comparare -> capacity >= robot -> capacity) {
        comparare = comparare -> next;
        prev = prev -> next;
      }
      if (comparare -> next == parkinglot -> standby_robots) {
        if (comparare -> capacity >= robot -> capacity) {
          comparare -> next = aux;
          aux -> next = parkinglot -> standby_robots;
        } else {
          prev -> next = aux;
          aux -> next = comparare;
        }
      } else {
        prev -> next = aux;
        aux -> next = comparare;
      }
    }
  } else {
    aux = robot;
    if (parkinglot -> pending_robots -> next == parkinglot -> pending_robots) {
      aux -> next = parkinglot -> pending_robots;
      parkinglot -> pending_robots -> next = aux;
    } else {
      comparare = parkinglot -> pending_robots -> next;
      prev = parkinglot -> pending_robots;
      while (comparare -> next != parkinglot -> pending_robots && comparare -> size >= robot -> size) {
        comparare = comparare -> next;
        prev = prev -> next;
      }
      if (comparare -> next == parkinglot -> pending_robots) {
        if (comparare -> size >= robot -> size) {
          comparare -> next = aux;
          aux -> next = parkinglot -> pending_robots;
        } else {
          prev -> next = aux;
          aux -> next = comparare;
        }
      } else {
        prev -> next = aux;
        aux -> next = comparare;
      }
    }
  }
}

void parkinglot_remove_robot(Parkinglot * parkinglot, Robot * robot) {
  Robot * pricinacovid, * prev;
  if (robot -> size == 0) {
    if (parkinglot -> standby_robots -> next == parkinglot -> standby_robots)
      return;
    pricinacovid = parkinglot -> standby_robots -> next;
    prev = parkinglot -> standby_robots;
    while (pricinacovid -> next != parkinglot -> standby_robots && pricinacovid != robot) {
      prev = prev -> next;
      pricinacovid = pricinacovid -> next;
    }
    if (prev == parkinglot -> standby_robots && robot == pricinacovid) {
      parkinglot -> standby_robots -> next = pricinacovid -> next;
      //un singur element in lista	
      //free(pricinacovid);
      return;
    }
    if (pricinacovid == robot) {
      prev -> next = pricinacovid -> next;
      //free(pricinacovid);
      return;
    }
  } else {
    if (parkinglot -> pending_robots -> next == parkinglot -> pending_robots)
      return;
    pricinacovid = parkinglot -> pending_robots -> next;
    prev = parkinglot -> pending_robots;
    while (pricinacovid -> next != parkinglot -> pending_robots && pricinacovid != robot) {
      prev = prev -> next;
      pricinacovid = pricinacovid -> next;
    }
    if (prev == parkinglot -> pending_robots && robot == pricinacovid) {
      //un singur element in lista
      parkinglot -> pending_robots -> next = pricinacovid -> next;
      //prev->next=prev;
      //free(pricinacovid);
      return;
    }
    if (pricinacovid == robot) {
      prev -> next = pricinacovid -> next;
      //free(pricinacovid);
      return;
    }
  }
}

int parckinglot_are_robots_peding(Parkinglot * parkinglot) {
  if (parkinglot -> pending_robots -> next == parkinglot -> pending_robots)
    return 0;
  return 1;
}

int parkinglot_are_arrived_trucks_empty(Parkinglot * parkinglot) {
  Truck * coronavirus;
  coronavirus = parkinglot -> arrived_trucks -> next;
  if (coronavirus == parkinglot -> arrived_trucks)
    return 1;
  while (coronavirus != parkinglot -> arrived_trucks) {
    if (truck_is_empty(coronavirus) == 0)
      return 0;
    coronavirus = coronavirus -> next;
  }
  return 1;
}

int parkinglot_are_trucks_in_transit(Parkinglot * parkinglot) {
  if (parkinglot -> departed_trucks -> next == parkinglot -> departed_trucks)
    return 0;
  return 1;
}

void destroy_parkinglot(Parkinglot * parkinglot) {
  Truck *prev;
  prev=parkinglot -> arrived_trucks;
  while(parkinglot -> arrived_trucks!=parkinglot->arrived_trucks->next)
  {
  	parkinglot -> arrived_trucks=parkinglot -> arrived_trucks->next;
  	destroy_truck(prev);
  	prev=parkinglot -> arrived_trucks;
  }
  prev=parkinglot -> departed_trucks;
  while(parkinglot -> departed_trucks!=parkinglot->departed_trucks->next)
  {
  	parkinglot -> departed_trucks=parkinglot -> departed_trucks->next;
  	destroy_truck(prev);
  	prev=parkinglot -> departed_trucks;
  }
  Robot *rprev;
  rprev=parkinglot -> standby_robots;
  while(parkinglot -> standby_robots!=parkinglot->standby_robots->next)
  {
  	parkinglot -> standby_robots=parkinglot -> standby_robots ->next;
  	destroy_robot(rprev);
  	rprev=parkinglot -> standby_robots;
  }
  rprev=parkinglot -> pending_robots;
  while(parkinglot -> pending_robots!=parkinglot -> pending_robots -> next)
  {
  	parkinglot -> pending_robots=parkinglot -> pending_robots ->next;
  	destroy_robot(rprev);
  	rprev=parkinglot -> pending_robots;
  }
  free(parkinglot);
  
}

void parkinglot_print_arrived_trucks(Parkinglot * parkinglot) {
  Truck * iterator = parkinglot -> arrived_trucks -> next;
  while (iterator != parkinglot -> arrived_trucks) {

    truck_print_info(iterator);
    iterator = iterator -> next;
  }

  printf("\n");

}

void parkinglot_print_departed_trucks(Parkinglot * parkinglot) {
  Truck * iterator = parkinglot -> departed_trucks -> next;
  while (iterator != parkinglot -> departed_trucks) {
    truck_print_info(iterator);
    iterator = iterator -> next;
  }
  printf("\n");

}

void parkinglot_print_pending_robots(Parkinglot * parkinglot) {
  Robot * iterator = parkinglot -> pending_robots -> next;
  while (iterator != parkinglot -> pending_robots) {
    printf("R: %ld %ld\n", iterator -> size, iterator -> capacity);
    robot_print_manifest_info(iterator);
    iterator = iterator -> next;
  }
  printf("\n");

}

void parkinglot_print_standby_robots(Parkinglot * parkinglot) {
  Robot * iterator = parkinglot -> standby_robots -> next;
  while (iterator != parkinglot -> standby_robots) {
    printf("R: %ld %ld\n", iterator -> size, iterator -> capacity);
    robot_print_manifest_info(iterator);
    iterator = iterator -> next;
  }
  printf("\n");

}

void truck_departed(Parkinglot * parkinglot, Truck * truck) {
  Truck * aux, * prev;
  aux = parkinglot -> arrived_trucks -> next;
  prev = parkinglot -> arrived_trucks;
  while (aux != parkinglot -> arrived_trucks && aux != truck) {
    aux = aux -> next;
    prev = prev -> next;
  }
  if (aux != parkinglot -> arrived_trucks && aux == truck)
    prev -> next = aux -> next;
  aux = parkinglot -> departed_trucks -> next;
  prev = parkinglot -> departed_trucks;
  if (aux == prev) {
    //lista este goala
    parkinglot -> departed_trucks -> next = truck;
    truck -> next = parkinglot -> departed_trucks;
  } else {
    while (aux -> next != parkinglot -> departed_trucks && aux -> departure_time < truck -> departure_time) {
      aux = aux -> next;
      prev = prev -> next;
    }
    if (aux -> departure_time >= truck -> departure_time) {
      prev -> next = truck;
      truck -> next = aux;
      //adaugare normala
    } else {
      //adaugare la final
      aux -> next = truck;
      truck -> next = parkinglot -> departed_trucks;
    }
  }
}

void truck_arrived(Parkinglot * parkinglot, Truck * truck) {
  if (parkinglot == NULL || truck == NULL) return;
  Truck * aux, * prev;
  aux = parkinglot -> departed_trucks -> next;
  prev = parkinglot -> departed_trucks;
  while (aux != parkinglot -> departed_trucks && aux != truck) {
    aux = aux -> next;
    prev = prev -> next;
  }
  if (aux != parkinglot -> departed_trucks && aux == truck)
    prev -> next = aux -> next;

  aux = parkinglot -> arrived_trucks -> next;
  prev = parkinglot -> arrived_trucks;
  truck -> size = 0;
  free(truck -> manifest);
  truck -> manifest = NULL;
  if (aux == prev) {
    //lista este goala
    parkinglot -> arrived_trucks -> next = truck;
    truck -> next = parkinglot -> arrived_trucks;
  } else {
    while (aux -> next != parkinglot -> arrived_trucks) {
      if (strcmp(aux -> destination, truck -> destination) > 0) {
        prev -> next = truck;
        truck -> next = aux;
        return;
      } else if (strcmp(aux -> destination, truck -> destination) == 0 && aux -> departure_time > truck -> departure_time) {
        prev -> next = truck;
        truck -> next = aux;
        return;
      } else {
        aux = aux -> next;
        prev = prev -> next;
      }
    }
    if (aux -> next == parkinglot -> arrived_trucks) {
      if (strcmp(aux -> destination, truck -> destination) > 0) {
        prev -> next = truck;
        truck -> next = aux;
      } else if (strcmp(aux -> destination, truck -> destination) == 0 && aux -> departure_time > truck -> departure_time) {
        prev -> next = truck;
        truck -> next = aux;
      } else {
        aux -> next = truck;
        truck -> next = parkinglot -> arrived_trucks;
      }
    }
  }
  // TODO: 3.5
  // Search through departed list, if exists node is found remove it
  // Note: this must remove the node not deallocate it

}

void truck_transfer_unloading_robots(Parkinglot * parkinglot, Truck * truck) {
  Robot * aux, * prev;
  aux = truck -> unloading_robots;
  while (aux != NULL) {
    prev = aux;
    aux = aux -> next;
    parkinglot_add_robot(parkinglot, prev);
  }
  truck -> unloading_robots = NULL;
  //trebuie dealocati toti
}

// Depends on parking_turck_departed
void truck_update_depatures(Parkinglot * parkinglot, long day_hour) {
  Truck * aux, * prev;
  aux = parkinglot -> arrived_trucks -> next;
  prev = parkinglot -> arrived_trucks;
  while (aux != parkinglot -> arrived_trucks) {
    if (aux -> departure_time == day_hour) {
      truck_departed(parkinglot, aux);
      aux = prev -> next;
    } else {
      aux = aux -> next;
      prev = prev -> next;
    }
  }
}

// Depends on parking_turck_arrived
void truck_update_transit_times(Parkinglot * parkinglot) {
  Truck * aux, * prev;
  prev = parkinglot -> departed_trucks;
  aux = parkinglot -> departed_trucks -> next;
  while (aux != parkinglot -> departed_trucks) {
    aux -> in_transit_time++;
    if (aux -> in_transit_time == aux -> transit_end_time) {
      aux -> in_transit_time = 0;
      truck_arrived(parkinglot, aux);
      aux = prev -> next;
    } else {
      aux = aux -> next;
      prev = prev -> next;
    }
  }
}

void robot_swarm_collect(Wearhouse * wearhouse, Parkinglot * parkinglot) {
  Robot * head_robot = parkinglot -> standby_robots;
  Robot * current_robot = parkinglot -> standby_robots -> next;
  while (current_robot != parkinglot -> standby_robots) {

    // Load packages from wearhouse if possible
    if (!robot_load_packages(wearhouse, current_robot)) {
      break;
    }

    // Remove robot from standby list
    Robot * aux = current_robot;
    head_robot -> next = current_robot -> next;
    current_robot = current_robot -> next;

    // Add robot to the
    parkinglot_add_robot(parkinglot, aux);
  }
}

void robot_swarm_assign_to_trucks(Parkinglot * parkinglot) {

  Robot * current_robot = parkinglot -> pending_robots -> next;

  while (current_robot != parkinglot -> pending_robots) {
    Robot * aux = current_robot;
    current_robot = current_robot -> next;
    parkinglot_remove_robot(parkinglot, aux);
    int attach_succeded = robot_attach_find_truck(aux, parkinglot);
    if (!attach_succeded)
      parkinglot_add_robot(parkinglot, aux);
  }
}

void robot_swarm_deposit(Parkinglot * parkinglot) {
  Truck * arrived_iterator = parkinglot -> arrived_trucks -> next;
  while (arrived_iterator != parkinglot -> arrived_trucks) {
    Robot * current_robot = arrived_iterator -> unloading_robots;
    while (current_robot != NULL) {
      robot_unload_packages(arrived_iterator, current_robot);
      Robot * aux = current_robot;
      current_robot = current_robot -> next;
      arrived_iterator -> unloading_robots = current_robot;
      parkinglot_add_robot(parkinglot, aux);
    }
    arrived_iterator = arrived_iterator -> next;
  }
} 