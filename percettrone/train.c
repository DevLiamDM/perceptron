#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DATA 100000

// --- Funzione sigmoide numericamente stabile ---
long double sigmoid(long double z) {
    if (z >= 0.0L)
        return 1.0L / (1.0L + expl(-z));
    else {
        long double ez = expl(z);
        return ez / (1.0L + ez);
    }
}

int main() {
    // --- Allocazione dinamica (heap, non stack) ---
    long double (*X)[3] = malloc(MAX_DATA * sizeof *X);
    long double *y = malloc(MAX_DATA * sizeof *y);

    if (!X || !y) {
        printf("Errore: memoria insufficiente.\n");
        return 1;
    }

    // --- Lettura del dataset ---
    FILE *f = fopen("dataset.txt", "r");
    if (!f) {
        printf("Errore: impossibile aprire dataset.txt\n");
        free(X); free(y);
        return 1;
    }

    int n = 0;
    while (fscanf(f, "%Lf %Lf %Lf %Lf", &X[n][0], &X[n][1], &X[n][2], &y[n]) == 4) {
        if (n >= MAX_DATA - 1) {
            printf("⚠️  Avviso: raggiunto limite MAX_DATA (%d)\n", MAX_DATA);
            break;
        }
        n++;
    }
    fclose(f);

    if (n == 0) {
        printf("Errore: dataset vuoto o formattato male.\n");
        free(X); free(y);
        return 1;
    }

    printf("✅ Dati caricati: %d righe.\n", n);

    // --- Inizializzazione dei pesi ---
    long double w1 = 0.0L, w2 = 0.0L, w3 = 0.0L, b = 0.0L;

    FILE *s = fopen("weights.txt", "r");
    if (s) {
        if (fscanf(s, "%Lf %Lf %Lf %Lf", &w1, &w2, &w3, &b) == 4)
            printf("📖 Pesi letti da weights.txt\n");
        else
            printf("⚠️  Formato weights.txt non valido, si parte da zero.\n");
        fclose(s);
    } else {
        printf("ℹ️  Nessun file weights.txt trovato, si parte da zero.\n");
    }

    // --- Parametri di addestramento ---
    const long double lr = 0.00001L;
    const unsigned long long epochs = 1000000ULL; // << Ridotto per stabilità

    // --- Training loop ---
   

    for (unsigned long long e = 0; e < epochs; e++) {
        long double total_error = 0.0L;
        for (int i = 0; i < n; i++) {
            long double z = w1 * X[i][0] + w2 * X[i][1] + w3 * X[i][2] + b;

            // Clamping di sicurezza
            if (z > 1000.0L) z = 1000.0L;
            if (z < -1000.0L) z = -1000.0L;

            long double y_hat = sigmoid(z);
            long double error = y[i] - y_hat;

            // Aggiornamento pesi
            w1 += lr * error * X[i][0];
            w2 += lr * error * X[i][1];
            w3 += lr * error * X[i][2];
            b  += lr * error;

            total_error += fabsl(error);
        }

        if (e % 1000 == 0) {
            printf("Epoca %llu, errore medio: %.10Lf\n", e, total_error / n);
            fflush(stdout);
        }
    }

    // --- Stampa e salvataggio dei pesi ---
    printf("\n✅ Pesi finali:\n");
    printf("w1 = %.10Lf\n", w1);
    printf("w2 = %.10Lf\n", w2);
    printf("w3 = %.10Lf\n", w3);
    printf("b  = %.10Lf\n", b);

    FILE *fw = fopen("weights.txt", "w");
    if (!fw) {
        printf("Errore: impossibile creare weights.txt\n");
        free(X); free(y);
        return 1;
    }

    fprintf(fw, "%.15Lf %.15Lf %.15Lf %.15Lf\n", w1, w2, w3, b);
    fclose(fw);

    printf("💾 Pesi salvati in weights.txt\n");

    // --- Cleanup ---
    free(X);
    free(y);

    return 0;
}





/*#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DATA 100000

// Funzione sigmoide con long double
long double sigmoid(long double z) {
    return 1.0L / (1.0L + expl(-z));
}
    
int main() {
    long double X[MAX_DATA][3];
    long double y[MAX_DATA];
    int n = 0;

    FILE *f = fopen("dataset.txt", "r");
    if (!f) {
        printf("Errore: impossibile aprire dataset.txt\n");
        return 1;
    }

    // Legge i dati
    while (fscanf(f, "%Lf %Lf %Lf %Lf", &X[n][0], &X[n][1], &X[n][2], &y[n]) == 4) {
        n++;
    }
    fclose(f);

    // Inizializzazione dei pesi
    long double w1 = 0.0L, w2 = 0.0L, w3 = 0.0L, b = 0.0L;

    // Tenta di leggere i pesi precedenti se esistono
    FILE *s = fopen("weights.txt", "r");
    if (s) {
        if (fscanf(s, "%Lf %Lf %Lf %Lf", &w1, &w2, &w3, &b) == 4) {
            printf("Pesi letti da weights.txt:\n");
            printf("w1 = %.10Lf\n", w1);
            printf("w2 = %.10Lf\n", w2);
            printf("w3 = %.10Lf\n", w3);
            printf("b  = %.10Lf\n", b);
        } else {
            printf("Attenzione: formato di weights.txt non valido. Si parte da zero.\n");
        }
        fclose(s);
    } else {
        printf("Nessun file weights.txt trovato. Si parte da zero.\n");
    }

    // Parametri di addestramento
    long double lr = 0.00001L; 
    unsigned long long epochs = 10000000ULL; 

    // Training
    for (unsigned long long e = 0; e < epochs; e++) {
        long double total_error = 0.0L;

        for (int i = 0; i < n; i++) {
            long double z = w1 * X[i][0] + w2 * X[i][1] + w3 * X[i][2] + b;
            long double y_hat = sigmoid(z);
            long double error = y[i] - y_hat;

            // Aggiornamento pesi
            w1 += lr * error * X[i][0];
            w2 += lr * error * X[i][1];
            w3 += lr * error * X[i][2];
            b  += lr * error;

            total_error += fabsl(error);
        }

        if (e % 100000 == 0) {
            printf("Epoca %llu, errore medio: %.13Lf\n", e, total_error / n);
        }
    }

    printf("\nPesi finali:\n");
    printf("w1 = %.10Lf\n", w1);
    printf("w2 = %.10Lf\n", w2);
    printf("w3 = %.10Lf\n", w3);
    printf("b  = %.10Lf\n", b);

    // Salva i pesi su file
    FILE *fw = fopen("weights.txt", "w");
    if (!fw) {
        printf("Errore: impossibile creare weights.txt\n");
        return 1;
    }

    fprintf(fw, "%.15Lf %.15Lf %.15Lf %.15Lf\n", w1, w2, w3, b);
    fclose(fw);

    printf("Pesi salvati in weights.txt ✅\n");
    return 0;
}
*/