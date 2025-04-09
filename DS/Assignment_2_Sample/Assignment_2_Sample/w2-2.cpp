#include <iostream>
#include <vector>
#include <iomanip> // 用於 std::fixed 和 std::setprecision

const int MAX_TERMS = 100;

struct PolynomialTerm {
    float coef;
    int expon;
};

std::vector<PolynomialTerm> terms; // 使用 vector 來存儲多項式項

// Function to insert a term into the result polynomial
void attach(float coef, int expon) {
    if (coef != 0) {  // Ignore terms with zero coefficient
        terms.push_back({coef, expon});
    }
}

// Function to subtract two polynomials
void subtract_polynomials(int startA, int finishA, int startB, int finishB) {
    int indexA = startA, indexB = startB;
    while (indexA <= finishA && indexB <= finishB) {
        if (terms[indexA].expon > terms[indexB].expon) {
            attach(terms[indexA].coef, terms[indexA].expon);
            indexA++;
        } else if (terms[indexA].expon < terms[indexB].expon) {
            attach(-terms[indexB].coef, terms[indexB].expon);
            indexB++;
        } else {  // Same exponent, subtract coefficients
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

    std::cin >> m;
    int startA = terms.size();
    for (int i = 0; i < m; i++) {
        PolynomialTerm term;
        std::cin >> term.coef >> term.expon;
        terms.push_back(term);
    }
    int finishA = terms.size() - 1;

    std::cin >> n;
    int startB = terms.size();
    for (int i = 0; i < n; i++) {
        PolynomialTerm term;
        std::cin >> term.coef >> term.expon;
        terms.push_back(term);
    }
    int finishB = terms.size() - 1;

    int result_start = terms.size(); // 記錄結果的起始位置
    subtract_polynomials(startA, finishA, startB, finishB);
    int result_end = terms.size() - 1; // 記錄結果的結束位置

    // Output result
    if (result_start > result_end) {
        std::cout << "0\n";  // Zero polynomial case
    } else {
        std::cout << result_end - result_start + 1 << '\n';
        // 使用 setprecision 來格式化輸出
        for (int i = result_start; i <= result_end; i++) {
            std::cout << std::fixed << std::setprecision(0) << terms[i].coef << ' ' << terms[i].expon << '\n';
        }
    }
    return 0;
}