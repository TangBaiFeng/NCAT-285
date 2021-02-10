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
 * Iterates through the numberList
 * @return the smallest number
 */
int min() {
  int smallest = INT_MAX;
  for (int &i : numberList) {
    if(i < smallest) {smallest = i;}
  }
  return smallest;
}
/**
 *  Iterates through numberList
 * @return the largest number
 */
int max() {
  int largest = 0;
  for (int &i : numberList) {
    if(i > largest) {largest = i;}
  }
  return largest;
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
void readFile(const string& fileName){
  ifstream myFile;
  string test;
  myFile.open(fileName);
  if(!myFile.is_open()) {
    cout << "Could not open file " + fileName << endl;
    exit(EXIT_FAILURE);
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
  cout
      << "Welcome\nEnter 1 to see items in file\nEnter 2 to find the smallest number\n"
         "Enter 3 to find the largest number\nEnter 4 to generate 50 random integers\n"
         "Enter any other number to exit\n";
  cin >> choice;
/*
 * TODO: figure out what he wants for intervals. Is it runtime or is it the N time it runs in?
 */
  bool switchStop = true;
  while (switchStop) {
    switch (choice) {
      case 1: print();
        break;
      case 2: cout << min();
        break;
      case 3: cout << max();
        break;
      case 4: random(fileName);
        break;
      default: switchStop = false;
        break;
    }
    cout << "\nEnter a new number" << endl;
    cin >> choice;
  }
}
