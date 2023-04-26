#include "../includes/shannon.h"

clist    *clist_init()
{
    clist *l = malloc(sizeof(*l));
    assert(l);
    l->first = NULL;
    return (l);
}

int     clist_size(clist *l)
{
    int i = 0;
    if (l == NULL)
        return (i);
    cell *tmp = l->first;
    while (tmp != NULL)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}

void    clist_add_sommet(clist *l, int news)
{
    if (l == NULL)
        return;
    cell *tmp;
    cell *newcell = malloc(sizeof(newcell));
    assert(newcell);
    newcell->ele1 = news;
    newcell->ele2 = 0;
    newcell->visited = 0;
    newcell->next = NULL;
    if (l->first == NULL)
        l->first = newcell;
    else
    {
        tmp = l->first;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = newcell;
    }
}

void    clist_add_arete(clist *l, int new1, int new2)
{
    if (l == NULL)
        return;
    cell *tmp;
    cell *newcell = malloc(sizeof(newcell));
    assert(newcell);
    newcell->ele1 = new1;
    newcell->ele2 = new2;
    newcell->visited = 0;
    newcell->next = NULL;
    if (l->first == NULL)
        l->first = newcell;
    else
    {
        tmp = l->first;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = newcell;
    }
}

void    clist_del_sommet(clist *l, int todel)
{
    if (l == NULL || l->first == NULL)
        return;
    cell *tmp = l->first;
    cell *prev;
    if (tmp != NULL && tmp->ele1 == todel)
    {
        l->first = tmp->next;
        free(tmp);
        return;
    }
    while (tmp != NULL && tmp->ele1 != todel)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free(tmp);
}

void    clist_del_arete(clist *l, int todel1, int todel2)
{
    if (l == NULL || l->first == NULL)
        return;
    cell *tmp = l->first;
    cell *prev;
    if (tmp != NULL && (tmp->ele1 == todel1 && tmp->ele2 == todel2))
    {
        l->first = tmp->next;
        free(tmp);
        return;
    }
    while (tmp != NULL && (tmp->ele1 != todel1 || tmp->ele2 != todel2))
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free(tmp);
}

clist   *clist_copy(clist *src)
{
    clist *dst = clist_init();
    if (src == NULL)
        return (dst);
    cell *tmp = src->first;
    while (tmp != NULL)
    {
        clist_add_arete(dst, tmp->ele1, tmp->ele2);
        tmp = tmp->next;
    }
    return (dst);
}

int     is_sommet_in_clist(clist *l, int e)
{
    if (l == NULL)
        return (-1);
    cell *tmp = l->first;
    while (tmp != NULL)
    {
        if (tmp->ele1 == e)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

int     is_arete_in_clist(clist *vulnerable, int a, int b)
{
    if (vulnerable == NULL)
        return (-1);
    cell *tmp = vulnerable->first;
    while (tmp != NULL)
    {
        if ((tmp->ele1 == a && tmp->ele2 == b) || (tmp->ele1 == b && tmp->ele2 == a))
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

void    print_sommets(clist *l)
{
    if (l == NULL || l->first == NULL)
    {
        printf("{}\n");
        return;
    }
    cell *tmp = l->first;
    printf("{");
    while (tmp != NULL)
    {
        if (tmp->ele1 >= 1 && tmp->ele1 <= 26)
            printf("%c", tmp->ele1 + 64);
        else
            printf("%i", tmp->ele1);
        if (tmp->next != NULL)
            printf(", ");
        tmp = tmp->next;
    }
    printf("}\n");
}

void    print_sommets_indexe(clist *l)
{
    if (l == NULL || l->first == NULL)
    {
        printf("{}\n");
        return;
    }
    cell *tmp = l->first;
    printf("{");
    while (tmp != NULL)
    {
        if (tmp->ele1 >= 1 && tmp->ele1 <= 26)
            printf("(%c:%i)", tmp->ele1 + 64, tmp->ele1);
        else
            printf("(%i:%i)", tmp->ele1, tmp->ele1);
        if (tmp->next != NULL)
            printf(", ");
        tmp = tmp->next;
    }
    printf("}\n");
}

void    print_aretes(clist *l)
{
    if (l == NULL || l->first == NULL)
    {
        printf("{}\n");
        return;
    }
    cell *tmp = l->first;
    printf("{");
    while (tmp != NULL)
    {
        if (tmp->ele1 >= 1 && tmp->ele1 <= 26)
            printf("(%c,", tmp->ele1 + 64);
        else
            printf("(%i,", tmp->ele1);
        if (tmp->ele2 >= 1 && tmp->ele2 <= 26)
            printf("%c)", tmp->ele2 + 64);
        else
            printf("%i)", tmp->ele2);
        if (tmp->next != NULL)
            printf(", ");
        tmp = tmp->next;
    }
    printf("}\n");
}