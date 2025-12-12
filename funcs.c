
#include "funcs.h"

// Βοηθητική συνάρτηση: Ανταλλάσσει τα περιεχόμενα δύο δομών.
void swap(struct route *a, struct route *b) {
    struct route temp = *a;
    *a = *b;
    *b = temp;
}

// Υπολογίζει τον εκτιμώμενο χρόνο (κανονική φορά: Length/65 + Uphill/10) με στρογγυλοποίηση.
int calculateTime(struct route r) {
    double time = (double)r.length / 65.0 + (double)r.uphill / 10.0;
    return (int)(time + 0.5); 
}

// Υπολογίζει τον εκτιμώμενο χρόνο (αντίστροφη φορά: Length/65 + Downhill/10) με στρογγυλοποίηση.
int calculateTimeReverse(struct route r) {
    double time = (double)r.length / 65.0 + (double)r.downhill / 10.0;
    return (int)(time + 0.5); 
}

// Υπολογίζει τον ακριβή χρόνο (κανονική φορά).
double calculateExactTime(struct route r) {
    return (double)r.length / 65.0 + (double)r.uphill / 10.0;
}

// Υπολογίζει τον ακριβή χρόνο (αντίστροφη φορά).
double calculateExactTimeReverse(struct route r) {
    return (double)r.length / 65.0 + (double)r.downhill / 10.0;
}

// Εκτυπώνει τα δεδομένα μιας διαδρομής στην οθόνη. Ελέγχει για κανονική/αντίστροφη φορά.
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

// Εκτυπώνει τα δεδομένα μιας διαδρομής σε αρχείο. Ελέγχει για κανονική/αντίστροφη φορά.
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

// Ταξινομεί τον πίνακα των διαδρομών φθίνουσα με βάση το μήκος (length).
void sortRoutesByLength(struct route A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j].length < A[j + 1].length) {
                swap(&A[j], &A[j + 1]);
            }
        }
    }
}

// Διαβάζει τον αριθμό και τα δεδομένα των διαδρομών από την τυπική είσοδο (stdin)
// και δεσμεύει δυναμικά μνήμη για τον πίνακα Α.
struct route* readFromInput(int *n) {
    scanf("%d", n);
    getchar(); // Κατανάλωση του newline
    
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

// Εκτυπώνει όλες τις διαδρομές (κανονική και αντίστροφη φορά)
// Ο πίνακας θεωρείται ήδη ταξινομημένος κατά μήκος.
void printData(struct route A[], int n) {
    for (int i = 0; i < n; i++) {
        printRoute(A[i], 0);
        if (strcmp(A[i].start, A[i].end) != 0) {
            printRoute(A[i], 1);
        }
    }
}

// Αναζητά και εκτυπώνει διαδρομές με μήκος μικρότερο ή ίσο του L.
void findShort(struct route A[], int n) {
    int L;
    scanf("%d", &L);
    getchar(); // Κατανάλωση του newline
    
    for (int i = 0; i < n; i++) {
        if (A[i].length <= L) {
            printRoute(A[i], 0);
            if (strcmp(A[i].start, A[i].end) != 0) {
                printRoute(A[i], 1);
            }
        }
    }
}

// Αναζητά και εκτυπώνει διαδρομές που ξεκινούν ή τελειώνουν στην δοθείσα τοποθεσία.
void findLocation(struct route A[], int n) {
    char location[51];
    fgets(location, 51, stdin);
    location[strcspn(location, "\n")] = 0; // Αφαίρεση newline
    
    for (int i = 0; i < n; i++) {
        if (strcmp(A[i].start, location) == 0) {
            printRoute(A[i], 0); // Κανονική φορά
        }
        else if (strcmp(A[i].end, location) == 0 && strcmp(A[i].start, A[i].end) != 0) {
            printRoute(A[i], 1); // Αντίστροφη φορά
        }
    }
}

// Αναζητά και εκτυπώνει διαδρομές όπου η ανάβαση υπερτερεί της κατάβασης (uphill > downhill).
void findUpHill(struct route A[], int n) {
    for (int i = 0; i < n; i++) {
        if (A[i].uphill > A[i].downhill) {
            printRoute(A[i], 0);
        }
    }
}

// Αναζητά και εκτυπώνει διαδρομές όπου η κατάβαση υπερτερεί της ανάβασης (downhill > uphill).
void findDownHill(struct route A[], int n) {
    for (int i = 0; i < n; i++) {
        if (A[i].downhill > A[i].uphill) {
            printRoute(A[i], 0);
        }
    }
}

// Αναζητά και εκτυπώνει διαδρομές των οποίων τα υψόμετρα βρίσκονται εντός του δοθέντος εύρους [min, max].
void findAltitude(struct route A[], int n) {
    int min, max;
    scanf("%d %d", &min, &max);
    getchar(); // Κατανάλωση του newline
    
    for (int i = 0; i < n; i++) {
        if (A[i].min_altitude >= min && A[i].max_altitude <= max) {
            printRoute(A[i], 0);
            if (strcmp(A[i].start, A[i].end) != 0) {
                printRoute(A[i], 1);
            }
        }
    }
}

// Αναζητά και εκτυπώνει διαδρομές (κανονική ή αντίστροφη φορά) των οποίων ο ακριβής χρόνος είναι <= T.
void findTimely(struct route A[], int n) {
    int T;
    scanf("%d", &T);
    getchar(); // Κατανάλωση του newline
    
    for (int i = 0; i < n; i++) {
        double exactTime = calculateExactTime(A[i]);
        double exactTimeReverse = calculateExactTimeReverse(A[i]);
        
        if (exactTime <= T) {
            printRoute(A[i], 0);
        }
        
        if (strcmp(A[i].start, A[i].end) != 0 && exactTimeReverse <= T) {
            printRoute(A[i], 1);
        }
    }
}

// Διαβάζει τον αριθμό και τα δεδομένα των διαδρομών από αρχείο.
// Δεσμεύει δυναμικά μνήμη για τον πίνακα Α.
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

// Αποθηκεύει τις ταξινομημένες διαδρομές (κανονική και αντίστροφη φορά) σε αρχείο.
// Ο πίνακας θεωρείται ήδη ταξινομημένος κατά μήκος.
void saveData(struct route A[], int n) {
    char filename[100];
    scanf("%s", filename);
    getchar(); // Κατανάλωση του newline
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s for writing\n", filename);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        printRouteToFile(A[i], 0, file);
        if (strcmp(A[i].start, A[i].end) != 0) {
            printRouteToFile(A[i], 1, file);
        }
    }
    
    fclose(file);
}
