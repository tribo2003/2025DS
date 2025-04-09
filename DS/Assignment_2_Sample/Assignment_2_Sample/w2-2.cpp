#include <iostream>
#include <vector>
#include <iomanip> // 用於 std::fixed 和 std::setprecision
#include <algorithm> // 用於 std::sort 和 std::find_if

const int MAX_TERMS = 100;

struct PolynomialTerm {
    float coef;
    int expon;
};

// 儲存多項式項的向量
std::vector<PolynomialTerm> terms;

// Function to insert a term into the result polynomial
void attach(float coef, int expon) {
    if (coef != 0) {  // Ignore terms with zero coefficient
        terms.push_back({coef, expon});
    }
}

// Function to multiply two polynomials
void multiply_polynomials(int startA, int finishA, int startB, int finishB) {
    std::vector<PolynomialTerm> temp;

    for (int i = startA; i <= finishA; i++) {
        for (int j = startB; j <= finishB; j++) {
            float new_coef = terms[i].coef * terms[j].coef;
            int new_expon = terms[i].expon + terms[j].expon;

            // Check if the exponent already exists in temp
            auto it = std::find_if(temp.begin(), temp.end(),
                [new_expon](const PolynomialTerm& term) { return term.expon == new_expon; });

            if (it != temp.end()) {
                it->coef += new_coef; // Update coefficient if exponent exists
            } else {
                temp.push_back({new_coef, new_expon}); // Add new term
            }
        }
    }

    // Sort temp in descending order of exponent
    std::sort(temp.begin(), temp.end(), [](const PolynomialTerm& a, const PolynomialTerm& b) {
        return a.expon > b.expon; // Descending order
    });

    // Copy temp to terms
    for (const auto& term : temp) {
        attach(term.coef, term.expon);
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
    multiply_polynomials(startA, finishA, startB, finishB);
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