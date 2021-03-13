/*
* Troy Boone
* COMP285 Section 001
* 2/5/2021
* Prompts the user for a data file and then displays a
* menu that gives the user the options to either seed the file, find the largest or smallest, or
* display the contents of the file. The numbers stored will be sorted smallest -> largest using
 * radix sorting
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

/*
 * Sorts the numberList using the Radix sorting algorithm.
 */
void radixSort() {
  int largestN = 0;

  //Find the largest number
  for (int i:numberList) {
    largestN = max(i, largestN);
  }
  int maxDigits = to_string(largestN).size();
  // Create an array with 10 'buckets' (Each bucket is a vector)
  vector<int> buckets[10];
  int pow10 = 1;
  int bucketIndex;
  int arrayIndex;
  // Loop repeats the size of the largest numbers place value
  for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++) {
    for (int i = 0; i < numberList.size(); i++) {
      // Puts the number in the bucket matching the current iterations place value
      bucketIndex = abs(numberList[i] / pow10) % 10;
      buckets[bucketIndex].push_back(numberList[i]);
    }
    arrayIndex = 0;
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < buckets[i].size(); j++) {
        numberList[arrayIndex++] = buckets[i][j]; // Place back in vector
      }
      buckets[i].clear();
    }
    pow10 *= 10; // Move to next place value
  }

}

/**
 * Returns the number at the beginning of the sorted vector (the min)
 */
void min() {
  cout << "After going through " << 0 << " iterations, the smallest number is " << numberList[0] <<
       " at position " << 0 << endl;
}

/**
 * Returns the number at the end of the sorted vector (the max)
 */
void max() {
  cout << "After going through " << 0 << " iterations, the largest number is " <<
       numberList[numberList.size() - 1] <<
       " at position " << numberList.size() << endl;
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
  if(numberList.empty()) {
    return 1;
  }
  cout
      << "Welcome\nEnter 1 to see items in file\nEnter 2 to find the smallest number\n"
         "Enter 3 to find the largest number\nEnter 4 to generate 50 random integers\n"
         "Enter 5 to sort the array using Radix Sorting Algorithm\nEnter any other number to "
         "exit\n";
  cin >> choice;
/*
 * TA stated interval means the position of the max or min
 */
  bool switchStop = true;
  bool sortedFlag = false;
  while (switchStop) {
    switch (choice) {
      case 1: print();
        break;
      case 2:
        if(!sortedFlag){
          radixSort();
          sortedFlag = true;
        }
        min();
        break;
      case 3:
        if(!sortedFlag){
          radixSort();
          sortedFlag = true;
        }
        max();
        break;
      case 4:
        random(fileName);
        sortedFlag = false;
        break;
      case 5: radixSort();
        sortedFlag = true;
        break;
      default: switchStop = false;
        exit(EXIT_SUCCESS);
    }
    cout << "\nEnter a new command" << endl;
    cin >> choice;
  }
}
