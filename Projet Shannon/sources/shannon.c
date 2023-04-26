#include "../includes/shannon.h"

void    get_lieur_move(clist *sommets, clist *protected, clist *vulnerable)
{
    if (sommets == NULL || protected == NULL || vulnerable == NULL)
        return;
    printf("\nTour du lieur : entrez deux sommets pour proteger l'arete correspondante.\nCoups possibles : ");
    print_aretes(vulnerable);
    printf("Rappel : ");
    print_sommets_indexe(sommets);
    int a, b, v = 0;
    while (v != 1)
    {
        scanf("%d%d", &a, &b);
        if (is_arete_in_clist(vulnerable, a, b) == 1)
        {
            clist_del_arete(vulnerable, a, b);
            clist_add_arete(protected, a, b);
            v = 1;
        }
        else
            printf("Erreur : coup invalide. Reessayez :\n");
    }
}

void    get_casseur_move(clist *sommets, clist *current, clist *vulnerable)
{
    if (sommets == NULL || current == NULL || vulnerable == NULL)
        return;
    printf("\nTour du casseur : entrez deux sommets pour detruire l'arete correspondante.\nCoups possibles : ");
    print_aretes(vulnerable);
    printf("Rappel : ");
    print_sommets_indexe(sommets);
    int a, b, v = 0;
    while (v != 1)
    {
        scanf("%d%d", &a, &b);
        if (is_arete_in_clist(vulnerable, a, b) == 1)
        {
            clist_del_arete(current, a, b);
            clist_del_arete(vulnerable, a, b);
            v = 1;
        }
        else
            printf("Erreur : coup invalide, reessayez.\n");
    }
}

void    lets_play_human(clist *sommets, clist *current, clist *vulnerable, clist *protected, int start, int end, int order)
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
            get_lieur_move(sommets, protected, vulnerable);
        if (order == 1)
            get_casseur_move(sommets, current, vulnerable);
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
            get_lieur_move(sommets, protected, vulnerable);
        if (order == 0)
            get_casseur_move(sommets, current, vulnerable);
    }
}



int     main()
{
    clist *sommets = clist_init();
    clist *aretes = clist_init();
    int start, end, order, mode, role, quit;
    printf("\nBienvenue dans le jeu de Shannon !\n\nInitialisation du graph :\n");
    init_graph(sommets, aretes);
    while (1)
    {
        clist *vulnerable = clist_copy(aretes);
        clist *current = clist_copy(aretes);
        clist *protected = clist_init();
        mode = -1;
        role = -1;
        order = -1;
        quit = -1;
        printf("\nChoisissez le sommet de depart.\n");
        print_sommets_indexe(sommets);
        int v = 0;
        while (v != 1)
        {
            scanf("%d", &start);
            if (is_sommet_in_clist(sommets, start) == 1)
                v = 1;
            else
                printf("Erreur : sommet invalide, reessayez.\n");
        }
        printf("\nChoisissez le sommet d'arrivee.\n");
        print_sommets_indexe(sommets);
        v = 0;
        while (v != 1)
        {
            scanf("%d", &end);
            if (is_sommet_in_clist(sommets, end) == 1 && end != start)
                v = 1;
            else
                printf("Erreur : sommet invalide, reessayez.\n");
    }
        printf("\nEntrez 0 pour jouer contre un autre joueur ou 1 pour jouer contre la machine.\n");
        while (mode != 0 && mode != 1)
        {
            scanf("%d", &mode);
            if (mode != 0 && mode != 1)
                printf("Erreur : choix invalide. Reessayez :\n");
        }
        if (mode == 1)
        {
            printf("\nEntrez 0 pour jouer le lieur ou 1 pour jouer le casseur.\n");
            while (role != 0 && role != 1)
            {
                scanf("%d", &role);
                if (role != 0 && role != 1)
                    printf("Erreur : choix invalide. Reessayez :\n");
            }
        }
        printf("\nEntrez 0 pour donner l'initiative au lieur ou 1 pour donner l'initiative au casseur.\n");
        while (order != 0 && order != 1)
        {
            scanf("%d", &order);
            if (order != 0 && order != 1)
                printf("Erreur : choix invalide. Reessayez :\n");
        }
        if (mode == 0)
            lets_play_human(sommets, current, vulnerable, protected, start, end, order);
        if (mode == 1)
            lets_play_machine(sommets, current, vulnerable, protected, start, end, order, role);
        printf("\nEntrez 1 pour rejouer une partie sur le meme graph ou 0 pour quitter le jeu de Shannon.\n");
        while (quit != 0 && quit != 1)
        {
            scanf("%d", &quit);
            if (quit != 0 && quit != 1)
                printf("Erreur : choix invalide, reessayez.\n");
        }
        if (quit == 0)
            return (0);
        if (quit == 1)
        {
            free(vulnerable);
            free(current);
            free(protected);
        }
    }
    return (0);
}