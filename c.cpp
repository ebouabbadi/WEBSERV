#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  vector<string> myArray = {"Hello", "World", "!"};

  // Add a character to the first string
  myArray[0].push_back('.');

  // Add a character to the second string
  myArray[1] += " Today";

  for (int i = 0; i < myArray.size(); i++) {
    cout << myArray[i] << " ";
  }

  return 0;
}
