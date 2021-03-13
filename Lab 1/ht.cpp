/* 
* Troy Boone
* COMP285 Section 001
* 3/12/2021
* A file will be input into either a linear or chaining hashtable depending on user input. It
 * will then display the contents of the table.
*/
#include "fstream"
#include "iostream"
#include <vector>
#include <array>
std::vector<int> numberList; // Structure holding all the numbers in the file
using namespace std;

/*
 * Takes the file contents in numberList and sorts them using linear probing
 * @return the content of the file sorted using linear probing in a vector
 */
vector<int> linearProbing() {
  vector<int> buckets(numberList.size(), -1);
  int bucketIndex;
  bool notFound;
  for (int &i : numberList) {
    // Puts the number in the bucket matching the current iterations place value
    bucketIndex = abs(i) % 10;
    if(buckets[bucketIndex] == -1) {
      buckets[bucketIndex] = i;
    }else {
      notFound = true;
      while (notFound) {
        bucketIndex = ++bucketIndex % numberList.size();
        if(buckets[bucketIndex] == -1) {
          buckets[bucketIndex] = i;
          notFound = false;
        }

      }
    }
  }
return buckets;
}

/*
 * Takes the file contents in numberList and sorts them using chaining
 * @return the content of the file sorted using chaining in a array of vectors
 */
array<vector<int>, 10> chaining() {
  int bucketIndex;
  array<vector<int>, 10> buckets;

  for (int &i : numberList) {
    // Puts the number in the bucket matching the current iterations place value
    bucketIndex = abs(i) % 10;
    buckets[bucketIndex].push_back(i);
  }
  return buckets;
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
  cout << "Please enter 1 for Linear Probing, enter 2 for Chaining, enter anything else to exit "
       << endl;
  cin >> choice;

  switch (choice) {
    case 1: {
      vector<int> linearBuckets = linearProbing(); // I chose to return instead of void in case
      // later we add more to this file
      for (int i = 0; i < linearBuckets.size() ; ++i) {
        cout << "Index " << i << " = " <<linearBuckets[i]<< endl;
      }
      break;
    }
    case 2: {
      array<vector<int>, 10> chainingBuckets = chaining(); // I chose to return instead of void
      // in case later we add more to this file
      for (int i = 0; i < 10; ++i) {
        cout << "Bucket " << i << " = ";
        for (auto j: chainingBuckets[i]) {
          cout << j << ", ";
        }
        cout << endl;
      }
      break;
    }
    default:break;
  }

}

