/*
* Troy Boone
* COMP285 Section 001
* 2/5/2021
* Prompts the user for a data file and then displays a
* menu that gives the user the option to either view the file content or exit the program
*/
#include "fstream"
#include "iostream"
using namespace std;

int main() {
  ifstream myfile;
  int tenIntegers[10] = {};
  int count = 0;
  string test;
  string fileName;
  int choice;

  cout << "What is the file name? \n";
  cin >> fileName;
  myfile.open(fileName);

  if(!myfile.is_open()) {
    cout << "Could not open file " + fileName << endl;
    return 1; // 1 indicates error
  }
  while (getline(myfile, test, ' ')) {
    tenIntegers[count++] = stoi(test);
  }
  myfile.close();

  cout << "Welcome\nEnter 1 to see items in file\nEnter any other number to exit\n";
  cin >> choice;

  if(choice == 1) {
    for (int i = 0; i < 10; ++i) {
      cout << tenIntegers[i] << " ";
    }
  }else {
    return 0;
  }
}