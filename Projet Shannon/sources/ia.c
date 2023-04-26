#include "../includes/shannon.h"

int     is_casseur_winning(clist *sommets, clist *current, cell *totest, int start, int end)
{
    int res;
    clist *tmp = clist_copy(current);
    assert(tmp);
    clist_del_arete(tmp, totest->ele1, totest->ele2);
    if (exist_chemin(sommets, tmp, start, end) == 0)
        res = 1;
    else
        res = 0;
    free(tmp);
    return (res);
}

int     is_lieur_winning(clist *sommets, clist *protected, cell *totest, int start, int end)
{
    int res;
    clist *tmp = clist_copy(protected);
    assert(tmp);
    clist_add_arete(tmp, totest->ele1, totest->ele2);
    if (exist_chemin(sommets, tmp, start, end) == 1)
        res = 1;
    else
        res = 0;
    free(tmp);
    return (res);
}

void    ia_protect(clist *protected, clist *vulnerable, cell *move)
{
    printf("\nMachine protege l'arete ");
    if (move->ele1 >= 1 && move->ele1 <= 26)
        printf("(%c,", move->ele1 + 64);
    else
        printf("(%i,", move->ele1);
    if (move->ele2 >= 1 && move->ele2 <= 26)
        printf("%c).\n", move->ele2 + 64);
    else
        printf("%i).\n", move->ele2);
    clist_add_arete(protected, move->ele1, move->ele2);
    clist_del_arete(vulnerable, move->ele1, move->ele2);
}

void    ia_breaks(clist *current, clist *vulnerable, cell *move)
{
    printf("\nMachine casse l'arete ");
    if (move->ele1 >= 1 && move->ele1 <= 26)
        printf("(%c,", move->ele1 + 64);
    else
        printf("(%i,", move->ele1);
    if (move->ele2 >= 1 && move->ele2 <= 26)
        printf("%c).\n", move->ele2 + 64);
    else
        printf("%i).\n", move->ele2);
    clist_del_arete(current, move->ele1, move->ele2);
    clist_del_arete(vulnerable, move->ele1, move->ele2);
}

void    ia_plays_lieur(clist *sommets, clist *current, clist *protected, clist *vulnerable, int start, int end)
{
    cell *tmp = vulnerable->first;
    while (tmp != NULL)
    {
        if (is_lieur_winning(sommets, protected, tmp, start, end) == 1)
        {
            ia_protect(protected, vulnerable, tmp);
            return;
        }
        tmp = tmp->next;
    }
    tmp = vulnerable->first;
    while (tmp != NULL)
    {
        if (is_casseur_winning(sommets, current, tmp, start, end) == 1)
        {
            ia_protect(protected, vulnerable, tmp);
            return;
        }
        tmp = tmp->next;
    }
    tmp = vulnerable->first;
    int n = rand() % clist_size(vulnerable) + 1;
    int i = 1;
    while (i < n)
    {
        i++;
        tmp = tmp->next;
    }
    ia_protect(protected, vulnerable, tmp);
}

void    ia_plays_casseur(clist *sommets, clist *current, clist *protected, clist *vulnerable, int start, int end)
{
    cell *tmp = vulnerable->first;
    while (tmp != NULL)
    {
        if (is_casseur_winning(sommets, current, tmp, start, end) == 1)
        {
            ia_breaks(current, vulnerable, tmp);
            return;
        }
        tmp = tmp->next;
    }
    tmp = vulnerable->first;
    while (tmp != NULL)
    {
        if (is_lieur_winning(sommets, protected, tmp, start, end) == 1)
        {
            ia_breaks(current, vulnerable, tmp);
            return;
        }
        tmp = tmp->next;
    }
    tmp = vulnerable->first;
    int n = rand() % clist_size(vulnerable) + 1;
    int i = 1;
    while (i < n)
    {
        i++;
        tmp = tmp->next;
    }
    ia_breaks(current, vulnerable, tmp);
}

void    lets_play_machine(clist *sommets, clist *current, clist *vulnerable, clist *protected, int start, int end, int order, int role)
{
    if (sommets == NULL || current == NULL || vulnerable == NULL || protected == NULL)
        return;
    while (1)
    {
        if (exist_chemin(sommets, protected, start, end) == 1)
        {
            printf("\nVictoire du lieur !\n");
            return;
        }
        if (exist_chemin(sommets, current, start, end) == 0)
        {
            printf("\nVictoire du casseur !\n");
            return;
        }
        printf("\nEtat actuel du graph :\nSommets : ");
        print_sommets(sommets);
        printf("Aretes : ");
        print_aretes(current);
        printf("dont les proteges : ");
        print_aretes(protected);
        if (start >= 1 && start <= 26)
            printf("Depart : %c\n", start + 64);
        else
            printf("Depart : %i\n", start);
        if (end >= 1 && end <= 26)
            printf("Arrivee : %c\n", end + 64);
        else
            printf("Arrivee : %i\n", end);
        if (order == 0)
        {
            if (role == 0)
                get_lieur_move(sommets, protected, vulnerable);
            if (role == 1)
                ia_plays_lieur(sommets, current, protected, vulnerable, start, end);
        }
        if (order == 1)
        {
            if (role == 0)
                ia_plays_casseur(sommets, current, protected, vulnerable, start, end);
            if (role == 1)
                get_casseur_move(sommets, current, vulnerable);
        }
        if (exist_chemin(sommets, protected, start, end) == 1)
        {
            printf("\nVictoire du lieur !\n");
            return;
        }
        if (exist_chemin(sommets, current, start, end) == 0)
        {
            printf("\nVictoire du casseur !\n");
            return;
        }
        printf("\nEtat actuel du graph :\nSommets : ");
        print_sommets(sommets);
        printf("Aretes : ");
        print_aretes(current);
        printf("dont les proteges : ");
        print_aretes(protected);
        if (start >= 1 && start <= 26)
            printf("Depart : %c\n", start + 64);
        else
            printf("Depart : %i\n", start);
        if (end >= 1 && end <= 26)
            printf("Arrivee : %c\n", end + 64);
        else
            printf("Arrivee : %i\n", end);
        if (order == 1)
        {
            if (role == 0)
                get_lieur_move(sommets, protected, vulnerable);
            if (role == 1)
                ia_plays_lieur(sommets, current, protected, vulnerable, start, end);
        }
        if (order == 0)
        {
            if (role == 0)
                ia_plays_casseur(sommets, current, protected, vulnerable, start, end);
            if (role == 1)
                get_casseur_move(sommets, current, vulnerable);
        }
    }
}