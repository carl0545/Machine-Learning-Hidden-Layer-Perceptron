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

const int TRAINING_ITERATIONS = 10000;
const double ETA = .1;

void setBasics(int*, int*, int*, int*); //Function reads in total inputs, rows and column for the matrix from stdin
void setValuesf(Matrix*, bool, bool); //Function sets the elements of the matrix from stdin
void setTargetValues(Matrix*, Matrix); //Function grabs the target values from the training matrix and assigns them to the target matrix
void neuralNetwork(Matrix, Matrix, Matrix, int);//Multilayer Neural Network algorithm
void setWeights(Matrix*);//Sets random values to the weight matrix
void addBias(Matrix* bias, Matrix original);//add a bias column to a matrix
double sigmoid(int);//sigmoid function for the neural network
double threshold(double val); //calculates whether to fire or not fire
void printOutput(Matrix, Matrix);//print output in assignment format

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
  setValuesf(&train, true, true);



  ///Testing Matrix
  setBasics(NULL, &test_rows, &test_cols, NULL);
  test_cols++; //bias
  test = new Matrix(test_rows, test_cols, "test");
  setValuesf(&test, true, false);

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

  neuralNetwork(train, target, test, hidden_nodes);



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
void setValuesf(Matrix *m, bool bias, bool input){

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

  weights->rand(-.05,.05);

}

/*
*sigmoid function for the Neural Network
*/
double sigmoid(double val){

  return (1.0/(1.0 + exp(-4.0 * val)));

}

/*
*
*/
void neuralNetwork(Matrix train, Matrix target, Matrix test, int hidden){
  Matrix weight1; //weight matrix between inputs and hidden nodes
  Matrix weight2; //weight matrix between hidden nodes and output nodes
  Matrix activations_h, activations_o;

  weight1 = new Matrix(train.numCols(), hidden);
  weight2 = new Matrix(hidden + 1, target.numCols());

  setWeights(&weight1);
  setWeights(&weight2);


  for(int i = 0; i < TRAINING_ITERATIONS; i++){

    activations_h = train.dot(weight1);
    activations_h.map(sigmoid);


    Matrix activationBias_h = new Matrix(activations_h.numRows(), activations_h.numCols()+1);
    addBias(&activationBias_h, activations_h);


    activations_o = activationBias_h.dot(weight2);
    activations_o.map(sigmoid);


    ////Back Propogate
    Matrix delta_o, delta_h, update_w1, update_w2;

    delta_o = new Matrix((Matrix(target).sub(activations_o)).mult(activations_o).mult(Matrix(activations_o).scalarPreSub(1.0)));
    delta_h = new Matrix((Matrix(activationBias_h).mult(Matrix(activationBias_h).scalarPreSub(1.0)).mult(Matrix(delta_o).dotT(weight2))));


    delta_h.narrow(delta_h.numCols()-1);

    update_w1 = new Matrix((train.Tdot(delta_h)).scalarMult(ETA));
    update_w2 = new Matrix((activationBias_h.Tdot(delta_o)).scalarMult(ETA));


    weight1.add(update_w1);
    weight2.add(update_w2);





  }

  Matrix newTest = Matrix(test);

  test.normalizeCols();

  activations_h = test.dot(weight1);
  activations_h.map(sigmoid);

  Matrix activationBias_h = new Matrix(activations_h.numRows(), activations_h.numCols()+1);
  addBias(&activationBias_h, activations_h);

  activations_o = activationBias_h.dot(weight2);
  activations_o.map(sigmoid);

  activations_o.map(threshold);

  printOutput(newTest, activations_o);







}
/*
*Threshold function utlilized within the perceptronAlg function
* Returns 1 if above zero, or returns 0 if not
*/
double threshold(double val){

  if(val <= .5){
    return 0;
  }
  else{
    return 1.0;
  }


}

void addBias(Matrix* bias, Matrix original){

  for(int r = 0; r < bias->numRows(); r++){
    for(int c = 0; c < bias->numCols(); c++){
      if(c == bias->numCols()-1){
        bias->set(r,c,-1.0);
        continue;
      }
      double element;
      element = original.get(r,c);
      bias->set(r,c, element);
    }
  }


}

/*
*Self made print function to match the neccesary required output template
*for the assignment
*/
void printOutput(Matrix train, Matrix fin){

 for(int r = 0; r < train.numRows(); r++){
   for(int c = 0; c < train.numCols(); c++){
     if(c == 0) continue;
     printf ("%.2f", train.get(r,c));
     cout << " ";
   }
   for(int c = 0; c < fin.numCols(); c++){
     printf ("%.2f", fin.get(r,c));
     cout << " ";
   }
   cout << endl;
 }

}
