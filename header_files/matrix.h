#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class Matrix {
public:
    std::vector<std::vector<double>> elements;
    int rows, columns;

    Matrix(int rows, int columns) : rows(rows), columns(columns) {
        this->elements.resize(rows, std::vector<double>(columns));
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                this->elements[i][j] = 0;
            }
        }
    }

    Matrix(int rows, int columns, std::vector<double> elements_vector) :  rows(rows), columns(columns){

        this->elements.resize(rows, std::vector<double>(columns));
        
        int elements_vector_size = elements_vector.size();

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if(i*rows + j >= elements_vector_size) this->elements[i][j] = 0; 
                else this->elements[i][j] = elements_vector[i*rows + j];
            }
        }
    } 

    void setElementAt(int row, int column, double element) {
        elements.at(row).at(column) = element;
    }

    double getElementAt(int row, int column) {
        return elements.at(row).at(column);
    }

    void print() {
        for(auto row : elements) {
            for(auto element : row) {
                std::cout << element << " "; 
            }
            std::cout << "\n";
        }
    }

    Matrix transp() {
        Matrix transp(rows, columns);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                transp.setElementAt(i, j, getElementAt(j, i));
            }
        }
        return transp;
    }

    Matrix operator + (Matrix m) {
        Matrix result(rows, columns);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                result.setElementAt(i, j, getElementAt(i, j) + m.getElementAt(i, j));
            }
        }
        return result;
    }

    Matrix operator - (Matrix m) {
        Matrix result(rows, columns);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                result.setElementAt(i, j, getElementAt(i, j) - m.getElementAt(i, j));
            }
        }
        return result;
    }

    Matrix operator * (double a) {
        Matrix result(rows, columns);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                result.setElementAt(i, j, result.getElementAt(i, j) * a);
            }
        }
        return result;
    }

    Matrix operator * (Matrix m) {
        Matrix result(rows, m.columns);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < m.columns; j++) {
                double curElement = 0;
                for(int k = 0; k < columns; k++) {
                    curElement += getElementAt(i, k) * m.getElementAt(k, j);
                }
                result.setElementAt(i, j, curElement);
            }
        }
        return result;
    }

    // static methods
    static Matrix identity(int rows, int columns) {
        Matrix identity(rows, columns);
        for(int i = 0; i < rows; i++) {
            identity.setElementAt(i, i, 1);
        }
        return identity;
    }

};

#endif