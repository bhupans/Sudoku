#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class Polynomial {
public:
    Polynomial() {}

    Polynomial(const std::vector<int>& coefficients) : coefficients(coefficients) {}

    Polynomial& operator+=(const Polynomial& other) {
        if (coefficients.size() < other.coefficients.size()) {
            coefficients.resize(other.coefficients.size(), 0);
        }
        for (size_t i = 0; i < other.coefficients.size(); i++) {
            coefficients[i] += other.coefficients[i];
        }
        return *this;
    }

    Polynomial operator+(const Polynomial& other) const {
        Polynomial result = *this;
        result += other;
        return result;
    }

    Polynomial& operator-=(const Polynomial& other) {
        if (coefficients.size() < other.coefficients.size()) {
            coefficients.resize(other.coefficients.size(), 0);
        }
        for (size_t i = 0; i < other.coefficients.size(); i++) {
            coefficients[i] -= other.coefficients[i];
        }
        return *this;
    }

    Polynomial operator-(const Polynomial& other) const {
        Polynomial result = *this;
        result -= other;
        return result;
    }

    Polynomial& operator*=(const Polynomial& other) {
        std::vector<int> newCoefficients(coefficients.size() + other.coefficients.size() - 1, 0);
        for (size_t i = 0; i < coefficients.size(); i++) {
            for (size_t j = 0; j < other.coefficients.size(); j++) {
                newCoefficients[i + j] += coefficients[i] * other.coefficients[j];
            }
        }
        coefficients = std::move(newCoefficients);
        return *this;
    }

    Polynomial operator*(const Polynomial& other) const {
        Polynomial result = *this;
        result *= other;
        return result;
    }

    bool operator==(const Polynomial& other) const {
        return coefficients == other.coefficients;
    }

    bool operator!=(const Polynomial& other) const {
        return !(*this == other);
    }

    std::string toString() const {
        std::stringstream ss;
        bool first = true;
        for (int i = static_cast<int>(coefficients.size()) - 1; i >= 0; i--) {
            if (coefficients[i] != 0) {
                if (!first) {
                    ss << " + ";
                }
                if (coefficients[i] != 1 || i == 0) {
                    ss << coefficients[i];
                }
                if (i > 0) {
                    ss << "x^" << i;
                }
                first = false;
            }
        }
        if (first) {
            ss << "0";
        }
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);

private:
    std::vector<int> coefficients;
};

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    os << poly.toString();
    return os;
}

Polynomial reduce(const std::vector<Polynomial>& generators, int index) {
    Polynomial result;
    for (size_t i = 0; i < generators.size(); i++) {
        if (i != static_cast<size_t>(index)) {
            result += generators[i];
        }
    }
    return result;
}

std::vector<Polynomial> groebnerBasis(const std::vector<Polynomial>& equations) {
    // Implement Groebner basis algorithm here
    return equations;
}
