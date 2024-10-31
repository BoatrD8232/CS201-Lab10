#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Matrix {
	private:
		vector<vector<int>> data;
		int row;
		int col;
	public:
		Matrix(int inRow, int inCol);
		//vector<vector<int>> getMatrix();
		//void setMatrix(vector<vector<int>>);
		int getRow();
		// Adds a row to the vector
		void setRow(vector<int> inRow);
		int getCol();
		void setCol(int inCol);
		// Returns a value in the vector
		int getValue(int inRow, int inCol);
		// Sets a value in the vector
		void setValue(int inRow, int inCol, int value);
		// Loads the vector in the matrix class
		bool loadMatrix(string string, ofstream& out);
		void printMatrix();
		// Shows if the matrix is refelxive or symmetric
		void showDetails(ofstream& out);
		Matrix operator*(Matrix& rhs);
		Matrix operator+(Matrix rhs);
		//Matrix operator=(Matrix& rhs);
		Matrix operator-(Matrix& rhs);
		// Outputs the Matrix in a formatted manner
		friend ofstream& operator<<(ofstream& out, Matrix& rhs);
};