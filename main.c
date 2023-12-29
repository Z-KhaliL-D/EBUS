#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nom[50];
    char prenom[50];
    int tel;
    char mdp[10];
}Voyageur;

typedef struct NoeudReservation {
    int numero_reservation;
    int numero_bus;
    Voyageur voyageur;
    struct NoeudReservation* next;
}NoeudReservation;

typedef struct {
    NoeudReservation* top;
}PileReservation;

PileReservation pilereservation = { .top = NULL };
typedef struct {
    int numero;
    char destination[10];
    char prix[10];
    int places_disponibles;
} Bus;
    char avis[500];

typedef struct {
    int numero_reservation;
    int numero_bus;
    Voyageur voyageur;
} Reservation;

Bus buses[10];
NoeudReservation* reservationList = NULL;
int numero_reservation_disponible = 1;

void AjouterReservation(NoeudReservation** stack, NoeudReservation* reservation) {
    reservation->next = *stack;
    *stack = reservation;
}
NoeudReservation* PopReservation(NoeudReservation** stack) {
    if (*stack == NULL) {
        return NULL;
    }
    NoeudReservation* popped = *stack;
    *stack = popped->next;
    popped->next = NULL;
    return popped;
}

void CreerCompteVoyageur(Voyageur* voyageur) {
    printf("Entrez le nom du voyageur : ");
    scanf("%s", voyageur->nom);
    printf("Entrez le prénom du voyageur : ");
    scanf("%s", voyageur->prenom);
    printf("Entrer le numero de Telephone: ");
    scanf("%d", &voyageur->tel);
    printf("donner le mdp : ");
    scanf("%s", voyageur->mdp);
}

void CreerReservation() {
    int numero_bus;
    printf("Entrez le numéro du bus(1-10) : ");
    scanf("%d", &numero_bus);
    if (numero_bus < 1 || numero_bus > 10 || buses[numero_bus - 1].places_disponibles == 0) {
        printf("Le bus n'est pas disponible.\n");
        return;
    }

    NoeudReservation* nouvelle_reservation = malloc(sizeof(NoeudReservation));
    nouvelle_reservation->numero_reservation = numero_reservation_disponible++;
    nouvelle_reservation->numero_bus = numero_bus;
    CreerCompteVoyageur(&nouvelle_reservation->voyageur);
    buses[numero_bus - 1].places_disponibles--;

    nouvelle_reservation->next = reservationList;
    reservationList = nouvelle_reservation;

    AjouterReservation(&pilereservation.top, nouvelle_reservation);

    printf("La reservation a été cree avec succès. Numero de reservation : %d\n", nouvelle_reservation->numero_reservation);
}

void AfficherDetailsBus() {
    printf("Détails des bus :\n");
    for (int i = 0; i < 10; i++) {
        printf("Bus %d - Destination : %s, Places disponibles : %d    *   Prix : %s\n", buses[i].numero, buses[i].destination, buses[i].places_disponibles, buses[i].prix);
    }
}

void AfficherModifierDetailsReservation() {
    int numero_reservation;
    printf("Entrez le numero de reservation : ");
    scanf("%d", &numero_reservation);

    NoeudReservation* current = reservationList;
    while (current != NULL && current->numero_reservation != numero_reservation) {
        current = current->next;
    }
    if (current == NULL) {
        printf("La reservation n'existe pas.\n");
        return;
    }
    printf("Details de la reservation :\n");
    printf("Numéro de reservation : %d\n", current->numero_reservation);
    printf("Numéro du bus : %d\n", current->numero_bus);
    printf("Nom du voyageur : %s %s\n", current->voyageur.nom, current->voyageur.prenom);


    char choix;
    printf("Voulez-vous modifier le nom du voyageur ? (O/N) : ");
    scanf(" %c", &choix);
    if (choix == 'O' || choix == 'o') {
        printf("Entrez le nouveau nom du voyageur : ");
        scanf("%s", current->voyageur.nom);
    }
}

void LibererListeChainee(NoeudReservation* list) {
    while (list != NULL) {
        NoeudReservation* temp = list;
        list = list->next;
        free(temp);
    }
}
void LibererPile(NoeudReservation** stack) {
    while (*stack != NULL) {
        NoeudReservation* temp = *stack;
        *stack = (*stack)->next;
        free(temp);
    }
}
void EnvoyerVotreAvis() {
    printf("Entrez votre avis (max 500 caractères) : ");
    scanf(" %[^\n]",&avis);
    printf("Merci pour votre avis !\n");
}
char D[10][10] = {"Beja", "Nabeul", "Bizerte", "Ben Arous", "Sfax   ", "Jendouba", "Manouba", "Kairouan", "Sousse","Kef"};
char prix[10][10] = {"6 DT", "5 DT", "5 DT", "1.5 DT", "15 DT", "8 DT", "3 DT", "16DT", "10DT", "12DT"};
int main() {
    for (int i = 0; i < 10; i++) {
        buses[i].numero = i + 1;
        buses[i].places_disponibles = 50;
        strcpy(buses[i].destination, D[i]);
        strcpy(buses[i].prix, prix[i]);
    }

    int choix;
    do {
        printf("\nBIENVENUE au Menu *TUNIS*:\n");
        printf("1. Creer un nouveau compte voyageur\n");
        printf("2. Creer une nouvelle reservation\n");
        printf("3. Afficher les details des bus (num,destinations...)\n");
        printf("4. Afficher et modifier les details d'une reservation\n");
        printf("5. Nous envoyer votre avis\n");
        printf("0. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                {
                    Voyageur nouveau_voyageur;
                    CreerCompteVoyageur(&nouveau_voyageur);
                    printf("Compte cree avec succes!");
                }
                break;
            case 2:
                CreerReservation();
                break;
            case 3:
                AfficherDetailsBus();
                break;
            case 4:
                AfficherModifierDetailsReservation();
                break;
            case 5:
                EnvoyerVotreAvis();
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

    } while (choix != 0);

    LibererListeChainee(reservationList);
    LibererPile(&pilereservation.top);

    return 0;
}
