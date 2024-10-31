// CS201L-Lab10b.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Matrix.h";

int main()
{
	//create input file stream & name it, open the file
	ifstream inFile;
	ofstream outFile;
	inFile.open("data.txt");
	outFile.open("report.txt");

	//verify the input file is good - if not exit
	if (!inFile.good()) {
		cout << "Error opening input file!\n";
		return -1;
	}
	if (!outFile.good()) {
		cout << "Error opening output file!\n";
		return -1;
	}

	string inputStr1, inputStr2;
	bool valid1 = false, valid2 = false;
	int count = 1;

	outFile << "Matrix Class!\n";
	while (getline(inFile, inputStr1)) {
		if (getline(inFile, inputStr2)) {
			outFile << setfill('-') << setw(100) << " " << setfill(' ') << endl;
			outFile << "Matrix Pair: " << count << endl;
			Matrix m1 = Matrix(0, 0);
			Matrix m2 = Matrix(0, 0);

			outFile << "\n\tPROCESSING FIRST MATRIX\n";
			//verify vector, if valid, printVector & processVector
			valid1 = m1.loadMatrix(inputStr1, outFile);
			if (valid1) {
				//m1.printMatrix(); //print
				outFile << m1;
				m1.showDetails(outFile); //reflex symm etc
			}


			outFile << "\n\n\tPROCESSING SECOND MATRIX\n";
			//verify vector, if valid, printVector & processVector
			valid2 = m2.loadMatrix(inputStr2, outFile);
			if (valid2) {
				//m2.printMatrix();
				outFile << m2;
				m2.showDetails(outFile);
			}

			outFile << "\n\n\tPROCESSING BOTH MATRICES\n";
			//if both vectors are valid, 
			if (valid1 && valid2) {
				//   if sizes are correct addTwoMatrices
				if (m1.getCol() != m2.getCol()) {
					outFile << "Matrices must be the same size to add and subtract." << endl;
				}
				else if (m1.getRow() != m2.getRow()) {
					outFile << "Matrices must be the same size to add and subtract." << endl;
				}
				else {
					outFile << "Addition: " << endl;
					Matrix sumMat = m1 + m2;
					outFile << sumMat;
					outFile << "Subtration: " << endl;
					Matrix diffMat = m1 - m2;
					outFile << diffMat;
				}
				if (m1.getCol() == m2.getRow()) {
					outFile << "Multiplication: " << endl;
					Matrix multMat = m1 * m2;
					outFile << multMat;
				}
				else {
					outFile << "Number of columns in the first matrix must be equal to the number of rows in the second matrix to multiply." << endl;
				}
			}
			else {
				outFile << "One of the vectors was invalid" << endl;
			}
			++count;
			outFile << "\n\n";
		}

	}
	inFile.close();
	outFile.close();
}
 
