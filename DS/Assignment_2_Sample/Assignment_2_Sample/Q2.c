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

// Function to multiply two polynomials
void multiply_polynomials(int startA, int finishA, int startB, int finishB) {
    polynomial temp[MAX_TERMS] = { 0 };
    int temp_avail = 0;

    for (int i = startA; i <= finishA; i++) {
        for (int j = startB; j <= finishB; j++) {
            float new_coef = terms[i].coef * terms[j].coef;
            int new_expon = terms[i].expon + terms[j].expon;

            // Add to temp array
            int k;
            for (k = 0; k < temp_avail; k++) {
                if (temp[k].expon == new_expon) {
                    temp[k].coef += new_coef;
                    break;
                }
            }
            if (k == temp_avail) {
                temp[temp_avail].coef = new_coef;
                temp[temp_avail].expon = new_expon;
                temp_avail++;
            }
        }
    }

    // Sort temp in descending order of exponent
    for (int i = 0; i < temp_avail - 1; i++) {
        for (int j = i + 1; j < temp_avail; j++) {
            if (temp[i].expon < temp[j].expon) {
                polynomial swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }

    // Copy temp to terms
    for (int i = 0; i < temp_avail; i++) {
        attach(temp[i].coef, temp[i].expon);
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
    multiply_polynomials(startA, finishA, startB, finishB);
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