#include "../includes/shannon.h"

clist   *get_voisins(clist *aretes, int sommet)
{
    clist *voisins = clist_init();
    if (aretes == NULL)
        return (voisins);
    cell *tmp = aretes->first;
    while (tmp != NULL)
    {
        if (tmp->ele1 == sommet)
            clist_add_sommet(voisins, tmp->ele2);
        if (tmp->ele2 == sommet)
            clist_add_sommet(voisins, tmp->ele1);
        tmp = tmp->next;
    }
    return (voisins);
}

void    visit(clist *sommets, int s)
{
    if (sommets == NULL)
        return;
    cell *tmp = sommets->first;
    while (tmp != NULL)
    {
        if (tmp->ele1 == s)
            tmp->visited = 1;
        tmp = tmp->next;
    }
}

int     is_visited(clist *sommets, int s)
{
    if (sommets == NULL)
        return (-1);
    cell *tmp = sommets->first;
    while (tmp != NULL)
    {
        if (tmp->ele1 == s && tmp->visited == 1)
            return (1);
        if (tmp->ele1 == s && tmp->visited == 0)
            return (0);
        tmp = tmp->next;
    }
    return (-1);
}

void    explore(clist *sommets, clist *aretes, int s)
{
    if (sommets == NULL || aretes == NULL)
        return;
    visit(sommets, s);
    clist *voisins = get_voisins(aretes, s);
    cell *tmp = voisins->first;
    while (tmp != NULL)
    {
        if (is_visited(sommets, tmp->ele1) == 0)
            explore(sommets, aretes, tmp->ele1);
        tmp = tmp->next;
    }
    free(voisins);
}

void    reset_visited(clist *sommets)
{
    if (sommets == NULL)
        return;
    cell *tmp = sommets->first;
    while (tmp != NULL)
    {
        tmp->visited = 0;
        tmp = tmp->next;
    }
}

int     exist_chemin(clist *sommets, clist *aretes, int start, int end)
{
    if (sommets == NULL || aretes == NULL)
        return (-1);
    explore(sommets, aretes, start);
    int res = is_visited(sommets, end);
    reset_visited(sommets);
    return (res);
}

int     is_arete_valid(clist *aretes, int nb_sommets, int a, int b)
{
    if (a == 0 && b == 0)
        return (0);
    if (a == b)
    {
        printf("Erreur : veuillez entrez deux sommets differents.\n");
        return (0);
    }
    if (a < 1 || a > nb_sommets || b < 1 || b > nb_sommets)
    {
        printf("Erreur : au moins un des sommets ne fait pas partie du graph.\n");
        return (0);
    }
    if (aretes == NULL)
        return (-1);
    cell *tmp = aretes->first;
    while (tmp != NULL)
    {
        if ((tmp->ele1 == a && tmp->ele2 == b) || (tmp->ele1 == b && tmp->ele2 == a))
        {
            printf("Erreur : cette arete est deja enregistree.\n");
            return (0);
        }
        tmp = tmp->next;
    }
    return (1);
}

void    init_graph(clist *sommets, clist *aretes)
{
    if (sommets == NULL || aretes == NULL)
        return;
    int nb_sommets = -1;
    printf("Entrez le nombre de sommets.\n");
    while (nb_sommets < 2)
    {
        scanf("%i", &nb_sommets);
        if (nb_sommets < 2)
            printf("Erreur : nombre de sommets incorrect, reessayez.\n");
    }
    int i = 1;
    while (i <= nb_sommets)
    {
        clist_add_sommet(sommets, i);
        i++;
    }
    int a = 1, b = 1;
    while (a != 0 || b != 0)
    {
        printf("\nEntrez deux sommets l'un apres l'autre selon leur numéro associé pour enregistrer l'arete entre ces deux sommets (exemple : 1 puis 2 pour lier A et B) ou entrez deux fois 0 pour finaliser le graph.\n");
        printf("Sommets : ");
        print_sommets_indexe(sommets);
        printf("Aretes : ");
        print_aretes(aretes);
        scanf("%d%d", &a, &b);
        if (is_arete_valid(aretes, nb_sommets, a, b) == 1)
            clist_add_arete(aretes, a, b);
    }
    printf("Le graph est pret.\n");
}