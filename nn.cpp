/*
*Dylan Carlson 2018
*Machine Learning
*Assignment 4
*/

#include <iostream>
#include <string>
#include <math.h>
#include "mat.h"

using namespace std;

const int TRAINING_ITERATIONS = 1;
const double LEARNING_RATE = .1;

void setBasics(int*, int*, int*, int*); //Function reads in total inputs, rows and column for the matrix from stdin
void setValuesf(Matrix*, bool); //Function sets the elements of the matrix from stdin
void setTargetValues(Matrix*, Matrix); //Function grabs the target values from the training matrix and assigns them to the target matrix
void neuralNetwork(Matrix, Matrix, int);//Multilayer Neural Network algorithm
void setWeights(Matrix*);//Sets random values to the weight matrix
void addBias(Matrix* bias, Matrix original);//add a bias column to a matrix
double sigmoid(int);//sigmoid function for the neural network


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

  ///Resize Training MATRIX
  train.narrow(train_cols - target_cols);
  train_cols = train.numCols();

  //Normalize the training matrix to have input values between 0-1
  train.normalizeCols();

  neuralNetwork(train, target, hidden_nodes);



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

/*
*Assigns random numbers to the initial weight matrix
*/
void setWeights(Matrix *weights){

  weights->rand(-.02,.05);

}

/*
*sigmoid function for the Neural Network
*/
double sigmoid(double val){

  return 1.0/(1.0 + exp(-4.0 * val));

}

/*
*
*/
void neuralNetwork(Matrix train, Matrix target, int hidden){
  Matrix weight1; //weight matrix between inputs and hidden nodes
  Matrix weight2; //weight matrix between hidden nodes and output nodes
  Matrix activations_h, activations_o;

  weight1 = new Matrix(train.numCols(), hidden);
  weight2 = new Matrix(hidden, target.numCols());

  setWeights(&weight1);
  setWeights(&weight2);

  for(int i = 0; i < TRAINING_ITERATIONS; i++){
    activations_h = train.dot(weight1);
    activations_h.map(sigmoid);

    Matrix activationBias_h = new Matrix(activations_h.numCols()+1, activations_h.numRows());
    addBias(&activationBias_h, activations_h);

    activations_o = activationBias_h.dot(weight2);
    activations_o.map(sigmoid);

    


  }

}

void addBias(Matrix* bias, Matrix original){

  for(int r = 0; r < bias->numRows(); r++){
    for(int c = 0; c < bias->numCols(); c++){
      if(c == 0){
        bias->set(r,c,-1.0);
        continue;
      }
      double element;
      element = original.get(r,c-1);
      bias->set(r,c, element);
    }
  }


}
