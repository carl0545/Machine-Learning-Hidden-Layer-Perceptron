/*
*Dylan Carlson 2018
*Machine Learning
*Assignment 4
*/

#include <iostream>
#include <string>
#include "mat.h"

using namespace std;

void setBasics(int*, int*, int*, int*); //Function reads in total inputs, rows and column for the matrix from stdin


int main(){

  //////
  initRand();

  //////////INPUT OF TRAINING AND TESTING MATRIX///////
  int train_inputs, train_rows, train_cols, test_rows, test_cols;
  int target_rows, target_cols;
  int hidden_nodes;
  Matrix train, test, target;

  ///Training Matrix
  setBasics(&train_inputs, &train_rows, &train_cols, &hidden_nodes);

  cout << "Hidden nodes: " << hidden_nodes << endl;


}

/*
*Function reads in total inputs, rows and column for the matrix from stdin
*/
void setBasics(int *input, int *rows, int *cols, int *hidden){

  if(input != NULL){ //input not recieved for the testing matrix
    cin >> *input;
  }
  if(hidden != NULL){
    cin >> *hidden;
  }

  cin >> *rows;
  cin >> *cols;
}
