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
void setValuesf(Matrix*, bool); //Function sets the elements of the matrix from stdin
void setTargetValues(Matrix*, Matrix); //Function grabs the target values from the training matrix and assigns them to the target matrix

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
  train_cols++; //bias
  train = new Matrix(train_rows, train_cols, "train");
  setValuesf(&train, true);


  ///Testing Matrix
  setBasics(NULL, &test_rows, &test_cols, NULL);
  test_cols++; //bias
  test = new Matrix(test_rows, test_cols, "test");
  setValuesf(&test, true);

  ///Target Matrix
  target_cols = train_cols - test_cols;
  target_rows = train_rows;

  target = new Matrix(target_rows, target_cols, "target");

  setTargetValues(&target, train);

  target.print();

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


/*
*Function sets the elements of the matrix from stdin
*/
void setValuesf(Matrix *m, bool bias){

  if(bias){
    for(int r = 0; r < m->numRows(); r++){
      for(int c = 0; c < m->numCols(); c++){
        if(c == 0){
          m->set(r,c,-1.0);
          continue;
        }
        double element;
        cin >> element;
        m->set(r,c, element);
      }
    }

  }

  else{

    for(int r = 0; r < m->numRows(); r++){
      for(int c = 0; c < m->numCols(); c++){
        double element;
        cin >> element;
        m->set(r,c, element);
      }
    }
  }


}

/*
*Function grabs the target values from the training matrix and assigns them to the target matrix
*/
void setTargetValues(Matrix *target, Matrix training){
  int starting_col;

  starting_col = training.numCols() - target->numCols();

  for(int r = 0; r < target->numRows(); r++){
    for(int c = starting_col; c - starting_col < target->numCols(); c++){
      target->set(r,c - starting_col, training.get(r,c));
    }
  }


}
