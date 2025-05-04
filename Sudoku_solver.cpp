#include <iostream>
#include <vector>
#include "GroebnerBasis.h"
#include "Polynomial.h"
using namespace std;

const int n = 3; // block size
const int p = n*n; // number of rows and columns 
const int m = n*n*n*n; // number of variables

vector<vector<int>> given_grid(p, vector<int>(p, 0));

bool detector(int x, int y) {
    int xr = x / p, yr = y / p;
    int xc = x % p, yc = y % p;
    int xrr = xr / n, yrr = yr / n;
    int xcc = xc / n, ycc = yc / n;
    return (xr == yr) || (xc == yc) || (xrr == yrr && xcc == ycc);
}

void solver() {
    vector<vector<int>> grid(p, vector<int>(p));
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) {
            grid[i][j] = i*p + j;
        }
    }

    // Generate polynomial equations encoding Sudoku rules
    vector<Polynomial> equations_1, equations_2, equations_3;
    for (int i = 0; i < m; i++) {
        Polynomial temp1, temp2;
        for (int j = 0; j < p; j++) {
            temp1 += generators[i][j];
            temp2 += reduce(generators[i], j);
        }
        equations_1.push_back(temp1 - 1);
        equations_1.push_back(temp2);
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = i+1; j < m; j++) {
            if (detector(i, j)) {
                Polynomial temp;
                for (int k = 0; k < p; k++) {
                    temp += generators[i][k] * generators[j][k];
                }
                equations_2.push_back(temp);
            }
        }
    }

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) {
            int value = given_grid[i][j];
            if (value != 0) {
                value--;
                for (int k = 0; k < p; k++) {
                    equations_3.push_back(generators[grid[i][j]][k] - (k == value ? 1 : 0));
                }
            }
        }
    }

    vector<Polynomial> equations;
    equations.insert(equations.end(), equations_1.begin(), equations_1.end());
    equations.insert(equations.end(), equations_2.begin(), equations_2.end());
    equations.insert(equations.end(), equations_3.begin(), equations_3.end());

    cout << "Total Equations: " << equations.size() << endl;

    // Solve the system of equations
    vector<Polynomial> gb = groebnerBasis(equations);

    if (gb.size() == 1) {
        cout << "No Solution" << endl;
    } 
    else if (gb.size() == m*p) {
        cout << "Unique Solution" << endl;
        vector<int> values = getUniqueSolution(gb);
        vector<vector<int>> answer(p, vector<int>(p));
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < p; j++) {
                answer[i][j] = values[grid[i][j]] + 1;
            }
        }
        printGrid(answer);
    }
    else {
        cout << "Multiple Solutions" << endl;
    }
}

vector<int> getUniqueSolution(const vector<Polynomial>& gb) {
    vector<string> terms;
    for (const auto& poly : gb) {
        terms.push_back(poly.toString());
    }
    cout << "Groebner Basis: ";
    for (const auto& term : terms) {
        cout << term << " ";
    }
    cout << endl;

    vector<int> values;
    for (int i = 0; i < terms.size(); i++) {
        int length = terms[i].size() - (1 + to_string(i).size());
        values.push_back(length == 0 ? 0 : 1);
    }
    return values;
}

void printGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    // Get the Sudoku grid from user
    cout << "Enter the Sudoku grid (0 for empty cells):" << endl;
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) {
            cin >> given_grid[i][j];
        }
    }

    solver();

    return 0;
}
