
#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Ορισμός της δομής route. Αποθηκεύει όλα τα δεδομένα για μια διαδρομή.
struct route {
    char start[51];      // Αρχική τοποθεσία
    int length;          // Μήκος διαδρομής
    int uphill;          // Συνολική υψομετρική ανάβαση
    int downhill;        // Συνολική υψομετρική κατάβαση
    int max_altitude;    // Μέγιστο υψόμετρο
    int min_altitude;    // Ελάχιστο υψόμετρο
    char end[51];        // Τελική τοποθεσία
};

// Βοηθητικές συναρτήσεις
void swap(struct route *a, struct route *b);
int calculateTime(struct route r);
int calculateTimeReverse(struct route r);
double calculateExactTime(struct route r);
double calculateExactTimeReverse(struct route r);
void printRoute(struct route r, int isReverse);
void printRouteToFile(struct route r, int isReverse, FILE *file);

// Συνάρτηση ταξινόμησης: Ταξινομεί φθίνουσα με βάση το μήκος.
void sortRoutesByLength(struct route A[], int n);

// Κύριες συναρτήσεις φόρτωσης και αποθήκευσης
struct route* readFromInput(int *n); // Φορτώνει δεδομένα από την τυπική είσοδο
struct route* readFromFile(int *n);  // Φορτώνει δεδομένα από αρχείο
void saveData(struct route A[], int n);    // Αποθηκεύει ταξινομημένα δεδομένα σε αρχείο

// Κύριες συναρτήσεις αναζήτησης και εκτύπωσης
void printData(struct route A[], int n);
void findShort(struct route A[], int n);
void findLocation(struct route A[], int n);
void findUpHill(struct route A[], int n);
void findDownHill(struct route A[], int n);
void findAltitude(struct route A[], int n);
void findTimely(struct route A[], int n);

#endif
