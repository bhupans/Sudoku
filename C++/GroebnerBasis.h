#include <vector>
#include <string>

class Polynomial {
public:
    std::vector<int> coefficients;
    std::vector<std::vector<int>> exponents;

    Polynomial() {}

    Polynomial(const std::vector<int>& coefs, const std::vector<std::vector<int>>& exps)
        : coefficients(coefs), exponents(exps) {}

    Polynomial& operator+=(const Polynomial& other) {
        for (size_t i = 0; i < other.coefficients.size(); i++) {
            bool found = false;
            for (size_t j = 0; j < coefficients.size(); j++) {
                if (exponents[j] == other.exponents[i]) {
                    coefficients[j] += other.coefficients[i];
                    found = true;
                    break;
                }
            }
            if (!found) {
                coefficients.push_back(other.coefficients[i]);
                exponents.push_back(other.exponents[i]);
            }
        }
        return *this;
    }

    Polynomial operator+(const Polynomial& other) const {
        Polynomial result = *this;
        result += other;
        return result;
    }

    Polynomial& operator-=(const Polynomial& other) {
        for (size_t i = 0; i < other.coefficients.size(); i++) {
            bool found = false;
            for (size_t j = 0; j < coefficients.size(); j++) {
                if (exponents[j] == other.exponents[i]) {
                    coefficients[j] -= other.coefficients[i];
                    found = true;
                    break;
                }
            }
            if (!found) {
                coefficients.push_back(-other.coefficients[i]);
                exponents.push_back(other.exponents[i]);
            }
        }
        return *this;
    }

    Polynomial operator-(const Polynomial& other) const {
        Polynomial result = *this;
        result -= other;
        return result;
    }

    Polynomial& operator*=(const Polynomial& other) {
        std::vector<int> newCoefficients;
        std::vector<std::vector<int>> newExponents;
        for (size_t i = 0; i < coefficients.size(); i++) {
            for (size_t j = 0; j < other.coefficients.size(); j++) {
                std::vector<int> newExponent(exponents[i].size());
                for (size_t k = 0; k < exponents[i].size(); k++) {
                    newExponent[k] = exponents[i][k] + other.exponents[j][k];
                }
                newCoefficients.push_back(coefficients[i] * other.coefficients[j]);
                newExponents.push_back(newExponent);
            }
        }
        coefficients = std::move(newCoefficients);
        exponents = std::move(newExponents);
        return *this;
    }

    Polynomial operator*(const Polynomial& other) const {
        Polynomial result = *this;
        result *= other;
        return result;
    }

    bool operator==(const Polynomial& other) const {
        return coefficients == other.coefficients && exponents == other.exponents;
    }

    bool operator!=(const Polynomial& other) const {
        return !(*this == other);
    }

    std::string toString() const {
        std::string result;
        for (size_t i = 0; i < coefficients.size(); i++) {
            if (coefficients[i] != 0) {
                if (!result.empty()) {
                    result += " + ";
                }
                if (coefficients[i] != 1 || (coefficients.size() == 1 && exponents[i].empty())) {
                    result += std::to_string(coefficients[i]);
                }
                for (int exp : exponents[i]) {
                    result += "x" + std::to_string(exp + 1);
                }
            }
        }
        if (result.empty()) {
            result = "0";
        }
        return result;
    }
};

std::vector<Polynomial> groebnerBasis(const std::vector<Polynomial>& equations);
Polynomial reduce(const std::vector<Polynomial>& gb, const Polynomial& p);
