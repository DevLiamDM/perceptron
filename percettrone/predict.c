#include <stdio.h>
#include <math.h>

// Funzione sigmoide
double sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

int main() {
    double w1, w2, w3, b;

    FILE *f = fopen("weights.txt", "r");
    if (!f) {
        printf("Errore: impossibile aprire weights.txt. Devi prima eseguire il training.\n");
        return 1;
    }

    fscanf(f, "%lf %lf %lf %lf", &w1, &w2, &w3, &b);
    fclose(f);

    double peso, eta, altezza;
    printf("Inserisci peso (kg): ");
    scanf("%lf", &peso);
    printf("Inserisci eta (anni): ");
    scanf("%lf", &eta);
    printf("Inserisci altezza (cm): ");
    scanf("%lf", &altezza);

    double z = w1*peso + w2*eta + w3*altezza + b;
    double pred = sigmoid(z);

    printf("\nProbabilita' maschio: %.2f%%\n", pred * 100);
    printf("Classificazione: %s\n", pred > 0.5 ? "MASCHIO" : "FEMMINA");

    return 0;
}
