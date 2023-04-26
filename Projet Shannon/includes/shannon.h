#ifndef SHANNON_H
# define SHANNON_H

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>

typedef struct cell cell;
struct cell
{
	int ele1;
	int	ele2;
    int visited;
	cell *next;
};

typedef struct clist clist;
struct clist
{
    cell *first;
};

clist *clist_init();
int clist_size(clist *l);
void clist_add_sommet(clist *l, int news);
void clist_add_arete(clist *l, int new1, int new2);
void clist_del_sommet(clist *l, int todel);
void clist_del_arete(clist *l, int todel1, int todel2);
void clist_free(clist *l);
clist *clist_copy(clist *src);
int is_sommet_in_clist(clist *l, int e);
int is_arete_in_clist(clist *vulnerable, int a, int b);
void print_sommets(clist *l);
void print_sommets_indexe(clist *l);
void print_aretes(clist *l);

clist *get_voisins(clist *aretes, int sommet);
void visit(clist *sommets, int s);
int is_visited(clist *sommets, int s);
void explore(clist *sommets, clist *aretes, int s);
void reset_visited(clist *sommets);
int exist_chemin(clist *sommets, clist *aretes, int start, int end);
int is_arete_valid(clist *aretes, int nb_sommets, int a, int b);
void init_graph(clist *sommets, clist *aretes);

void get_lieur_move(clist *sommets, clist *protected, clist *vulnerable);
void get_casseur_move(clist *sommets, clist *current, clist *vulnerable);
void lets_play_human(clist *sommets, clist *current, clist *vulnerable, clist *protected, int start, int end, int order);

int is_casseur_winning(clist *sommets, clist *current, cell *totest, int start, int end);
int is_lieur_winning(clist *sommets, clist *protected, cell *totest, int start, int end);
void ia_protect(clist *protected, clist *vulnerable, cell *move);
void ia_breaks(clist *current, clist *vulnerable, cell *move);
void ia_plays_lieur(clist *sommets, clist *current, clist *protected, clist *vulnerable, int start, int end);
void ia_plays_casseur(clist *sommets, clist *current, clist *protected, clist *vulnerable, int start, int end);
void lets_play_machine(clist *sommets, clist *current, clist *vulnerable, clist *protected, int start, int end, int order, int role);


#endif