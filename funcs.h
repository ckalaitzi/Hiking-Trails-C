#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct route {
    char start[51];
    int length;
    int uphill;
    int downhill;
    int max_altitude;
    int min_altitude;
    char end[51];
};

// Βοηθητικές συναρτήσεις
void swap(struct route *a, struct route *b) {
    struct route temp = *a;
    *a = *b;
    *b = temp;
}

int calculateTime(struct route r) {
    double time = (double)r.length / 65.0 + (double)r.uphill / 10.0;
    return (int)(time + 0.5); // Στρογγυλοποίηση
}

int calculateTimeReverse(struct route r) {
    double time = (double)r.length / 65.0 + (double)r.downhill / 10.0;
    return (int)(time + 0.5); // Στρογγυλοποίηση
}

double calculateExactTime(struct route r) {
    return (double)r.length / 65.0 + (double)r.uphill / 10.0;
}

double calculateExactTimeReverse(struct route r) {
    return (double)r.length / 65.0 + (double)r.downhill / 10.0;
}

void printRoute(struct route r, int isReverse) {
    if (isReverse) {
        printf("From %s to %s\n", r.end, r.start);
        printf("Uphill %d, Downhill %d\n", r.downhill, r.uphill);
        printf("Max altitude %d, Min altitude %d\n", r.max_altitude, r.min_altitude);
        printf("Length %d, Estimated time %d min\n\n", r.length, calculateTimeReverse(r));
    } else {
        printf("From %s to %s\n", r.start, r.end);
        printf("Uphill %d, Downhill %d\n", r.uphill, r.downhill);
        printf("Max altitude %d, Min altitude %d\n", r.max_altitude, r.min_altitude);
        printf("Length %d, Estimated time %d min\n\n", r.length, calculateTime(r));
    }
}

void printRouteToFile(struct route r, int isReverse, FILE *file) {
    if (isReverse) {
        fprintf(file, "From %s to %s\n", r.end, r.start);
        fprintf(file, "Uphill %d, Downhill %d\n", r.downhill, r.uphill);
        fprintf(file, "Max altitude %d, Min altitude %d\n", r.max_altitude, r.min_altitude);
        fprintf(file, "Length %d, Estimated time %d min\n\n", r.length, calculateTimeReverse(r));
    } else {
        fprintf(file, "From %s to %s\n", r.start, r.end);
        fprintf(file, "Uphill %d, Downhill %d\n", r.uphill, r.downhill);
        fprintf(file, "Max altitude %d, Min altitude %d\n", r.max_altitude, r.min_altitude);
        fprintf(file, "Length %d, Estimated time %d min\n\n", r.length, calculateTime(r));
    }
}


struct route* readFromInput(int *n) {
    scanf("%d", n);
    getchar(); // Κατανάλωση του newline
    
    // Δυναμική δέσμευση μνήμης για τον πίνακα μονοπατιών
    struct route *A = (struct route*)malloc(*n * sizeof(struct route));
    if (A == NULL) {
        printf("Memory allocation failed\n");
        *n = 0;
        return NULL;
    }
    
    for (int i = 0; i < *n; i++) {
        fgets(A[i].start, 51, stdin);
        A[i].start[strcspn(A[i].start, "\n")] = 0; // Αφαίρεση newline
        
        scanf("%d %d %d %d %d", 
              &A[i].length, 
              &A[i].uphill, 
              &A[i].downhill, 
              &A[i].max_altitude, 
              &A[i].min_altitude);
        getchar(); // Κατανάλωση του newline
        
        fgets(A[i].end, 51, stdin);
        A[i].end[strcspn(A[i].end, "\n")] = 0; // Αφαίρεση newline
    }
    
    return A;
}

void printData(struct route A[], int n) {
    // Ταξινόμηση με βάση το μήκος (φθίνουσα)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j].length < A[j + 1].length) {
                swap(&A[j], &A[j + 1]);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        // Εκτύπωση κανονικής φοράς
        printRoute(A[i], 0);
        
        // Εκτύπωση αντίστροφης φοράς αν δεν είναι κυκλικό
        if (strcmp(A[i].start, A[i].end) != 0) {
            printRoute(A[i], 1);
        }
    }
}

void findShort(struct route A[], int n) {
    int L;
    scanf("%d", &L);
    getchar(); // Κατανάλωση του newline
    
    // Ταξινόμηση με βάση το μήκος (φθίνουσα)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j].length < A[j + 1].length) {
                swap(&A[j], &A[j + 1]);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (A[i].length <= L) {
            // Εκτύπωση κανονικής φοράς
            printRoute(A[i], 0);
            
            // Εκτύπωση αντίστροφης φοράς αν δεν είναι κυκλικό
            if (strcmp(A[i].start, A[i].end) != 0) {
                printRoute(A[i], 1);
            }
        }
    }
}

void findLocation(struct route A[], int n) {
    char location[51];
    fgets(location, 51, stdin);
    location[strcspn(location, "\n")] = 0; // Αφαίρεση newline
    
    // Ταξινόμηση με βάση το μήκος (φθίνουσα)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j].length < A[j + 1].length) {
                swap(&A[j], &A[j + 1]);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        // Έλεγχος κανονικής φοράς
        if (strcmp(A[i].start, location) == 0) {
            printRoute(A[i], 0);
        }
        // Έλεγχος αντίστροφης φοράς
        else if (strcmp(A[i].end, location) == 0 && strcmp(A[i].start, A[i].end) != 0) {
            printRoute(A[i], 1);
        }
    }
}

void findUpHill(struct route A[], int n) {
    // Ταξινόμηση με βάση το μήκος (φθίνουσα)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j].length < A[j + 1].length) {
                swap(&A[j], &A[j + 1]);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (A[i].uphill > A[i].downhill) {
            printRoute(A[i], 0);
        }
    }
}

void findDownHill(struct route A[], int n) {
    // Ταξινόμηση με βάση το μήκος (φθίνουσα)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j].length < A[j + 1].length) {
                swap(&A[j], &A[j + 1]);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (A[i].downhill > A[i].uphill) {
            printRoute(A[i], 0);
        }
    }
}

void findAltitude(struct route A[], int n) {
    int min, max;
    scanf("%d %d", &min, &max);
    getchar(); // Κατανάλωση του newline
    
    // Ταξινόμηση με βάση το μήκος (φθίνουσα)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j].length < A[j + 1].length) {
                swap(&A[j], &A[j + 1]);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (A[i].min_altitude >= min && A[i].max_altitude <= max) {
            // Εκτύπωση κανονικής φοράς
            printRoute(A[i], 0);
            
            // Εκτύπωση αντίστροφης φοράς αν δεν είναι κυκλικό
            if (strcmp(A[i].start, A[i].end) != 0) {
                printRoute(A[i], 1);
            }
        }
    }
}

void findTimely(struct route A[], int n) {
    int T;
    scanf("%d", &T);
    getchar(); // Κατανάλωση του newline
    
    // Ταξινόμηση με βάση το μήκος (φθίνουσα)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j].length < A[j + 1].length) {
                swap(&A[j], &A[j + 1]);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        double exactTime = calculateExactTime(A[i]);
        double exactTimeReverse = calculateExactTimeReverse(A[i]);
        
        // Έλεγχος κανονικής φοράς
        if (exactTime <= T) {
            printRoute(A[i], 0);
        }
        
        // Έλεγχος αντίστροφης φοράς αν δεν είναι κυκλικό
        if (strcmp(A[i].start, A[i].end) != 0 && exactTimeReverse <= T) {
            printRoute(A[i], 1);
        }
    }
}


struct route* readFromFile(int *n) {
    char filename[100];
    scanf("%s", filename);
    getchar(); // Κατανάλωση του newline
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        *n = 0;
        return NULL;
    }
    
    fscanf(file, "%d", n);
    fgetc(file); // Κατανάλωση του newline
    
    // Δυναμική δέσμευση μνήμης για τον πίνακα μονοπατιών
    struct route *A = (struct route*)malloc(*n * sizeof(struct route));
    if (A == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        *n = 0;
        return NULL;
    }
    
    for (int i = 0; i < *n; i++) {
        fgets(A[i].start, 51, file);
        A[i].start[strcspn(A[i].start, "\n")] = 0; // Αφαίρεση newline
        
        fscanf(file, "%d %d %d %d %d", 
              &A[i].length, 
              &A[i].uphill, 
              &A[i].downhill, 
              &A[i].max_altitude, 
              &A[i].min_altitude);
        fgetc(file); // Κατανάλωση του newline
        
        fgets(A[i].end, 51, file);
        A[i].end[strcspn(A[i].end, "\n")] = 0; // Αφαίρεση newline
    }
    
    fclose(file);
    return A;
}

void saveData(struct route A[], int n) {
    char filename[100];
    scanf("%s", filename);
    getchar(); // Κατανάλωση του newline
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s for writing\n", filename);
        return;
    }
    
    // Ταξινόμηση με βάση το μήκος (φθίνουσα) - ίδια λογική με την printData
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j].length < A[j + 1].length) {
                swap(&A[j], &A[j + 1]);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        // Εγγραφή κανονικής φοράς στο αρχείο
        printRouteToFile(A[i], 0, file);
        
        // Εγγραφή αντίστροφης φοράς αν δεν είναι κυκλικό
        if (strcmp(A[i].start, A[i].end) != 0) {
            printRouteToFile(A[i], 1, file);
        }
    }
    
    fclose(file);
}

#endif
