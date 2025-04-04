#include <stdio.h>
#define MAX_TERMS 100

typedef struct {
    float coef;
    int expon;
} polynomial;

polynomial terms[MAX_TERMS];
int avail = 0;

// Function to insert a term into the result polynomial
void attach(float coef, int expon) {
    if (coef != 0) {  // Ignore terms with zero coefficient
        terms[avail].coef = coef;
        terms[avail].expon = expon;
        avail++;
    }
}

// Function to subtract two polynomials
void subtract_polynomials(int startA, int finishA, int startB, int finishB) {
    int indexA = startA, indexB = startB;
    while (indexA <= finishA && indexB <= finishB) {
        if (terms[indexA].expon > terms[indexB].expon) {
            attach(terms[indexA].coef, terms[indexA].expon);
            indexA++;
        }
        else if (terms[indexA].expon < terms[indexB].expon) {
            attach(-terms[indexB].coef, terms[indexB].expon);
            indexB++;
        }
        else {  // Same exponent, subtract coefficients
            float diff = terms[indexA].coef - terms[indexB].coef;
            attach(diff, terms[indexA].expon);
            indexA++;
            indexB++;
        }
    }

    // Append remaining terms from A
    while (indexA <= finishA) {
        attach(terms[indexA].coef, terms[indexA].expon);
        indexA++;
    }

    // Append remaining terms from B (negated)
    while (indexB <= finishB) {
        attach(-terms[indexB].coef, terms[indexB].expon);
        indexB++;
    }
}

int main() {
    int m, n;
    scanf("%d", &m);
    int startA = avail;
    for (int i = 0; i < m; i++) {
        scanf("%f %d", &terms[avail].coef, &terms[avail].expon);
        avail++;
    }
    int finishA = avail - 1;

    scanf("%d", &n);
    int startB = avail;
    for (int i = 0; i < n; i++) {
        scanf("%f %d", &terms[avail].coef, &terms[avail].expon);
        avail++;
    }
    int finishB = avail - 1;

    int result_start = avail;
    subtract_polynomials(startA, finishA, startB, finishB);
    int result_end = avail - 1;

    // Output result
    if (result_start > result_end) {
        printf("0\n");  // Zero polynomial case
    }
    else {
        printf("%d\n", result_end - result_start + 1);
        for (int i = result_start; i <= result_end; i++) {
            printf("%.0f %d\n", terms[i].coef, terms[i].expon);
        }
    }
    return 0;
}