/*
* Troy Boone
* COMP285 Section 001
* 2/5/2021
* Prompts the user for a data file and then displays a
* menu that gives the user the options to either seed the file, find the largest or smallest, or
* display the contents of the file
*/
#include "fstream"
#include "iostream"
#include <vector>
#include <random>
std::vector<int> numberList; // Structure holding all the numbers in the file
using namespace std;

/**
 * Prints the contents of numberList
 */
void print() {
  for (int &i : numberList) {
    cout << i << " ";
  }
}

/**
 * Iterates through the numberList and prints the smallest number and its location in the vector
 * in a recursive manner
 */
void min(int smallestN, int position, int smallestNLocation) {
  if(position == numberList.size()){
    cout <<"After going through " << position <<" iterations, the largest number is " << smallestN <<
         " at position " << smallestNLocation << endl;
    return;
  }else if(numberList[position] < smallestN){
    smallestNLocation = position + 1;
    smallestN = numberList[position];
  }
  return min(smallestN, ++position, smallestNLocation);
}

/**
 * Iterates through the numberList and prints the largest number and its location in the vector
 * in a recursive manner
 */
void max(int largestN, int position, int largestNLocation) {
  if(position == numberList.size()){
    cout <<"After going through " << position <<" iterations, the largest number is " << largestN <<
    " at position " << largestNLocation << endl;
    return;
  }else if(numberList[position] > largestN){
      largestNLocation = position + 1;
      largestN = numberList[position];
    }
    return max(largestN, ++position, largestNLocation);
  }



/**
 * Generate 50 random numbers and replaces whatever was in the file with the new contents
 * @param fileName
 */
void random(string fileName) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> distribution(0, 500);
  ofstream myFile;

  numberList.clear();
  for (int i = 0; i < 50; ++i) {
    numberList.push_back(distribution(gen));
  }

  myFile.open(fileName);
  for (int i : numberList) {
    myFile << i << " ";
  }
  myFile.close();

}

/**
 * Read the contents of the file
 * @param fileName
 */
void readFile(const string &fileName) {
  ifstream myFile;
  string test;
  myFile.open(fileName);
  if(!myFile.is_open()) {
    cout << "Could not open file " + fileName << endl;
    return;
  }
  while (getline(myFile, test, ' ')) {
    numberList.push_back(stoi(test));
  }
  myFile.close();
}

int main() {
  string fileName;
  int choice;

  cout << "What is the file name? \n";
  cin >> fileName;
  readFile(fileName);
  if(numberList.empty()){
    return 1;
  }
  cout
      << "Welcome\nEnter 1 to see items in file\nEnter 2 to find the smallest number\n"
         "Enter 3 to find the largest number\nEnter 4 to generate 50 random integers\n"
         "Enter any other number to exit\n";
  cin >> choice;
/*
 * TA stated interval means the position of the max or min
 */
  bool switchStop = true;
  while (switchStop) {
    switch (choice) {
      case 1: print();
        break;
      case 2:min(INT8_MAX,0,0);
        break;
      case 3:max(0,0,0);
        break;
      case 4: random(fileName);
        break;
      default: switchStop = false;
        exit(EXIT_SUCCESS);
        break;
    }
    cout << "\nEnter a new command" << endl;
    cin >> choice;
  }
}
