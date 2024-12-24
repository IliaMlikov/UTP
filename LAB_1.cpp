#include <iostream>

using namespace std;

int main() {

  int digitals[10];
  int S = 0;


  for (int i = 0; i < 10; i++) {
    cin >> digitals[i]; 
    S = S+digitals[i];
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 9; j++) {
      if (digitals[j] < digitals[j + 1]) {
        int b = digitals[j];
        digitals[j] = digitals[j + 1];
        digitals[j + 1] = b;
      }
    }
  }

  for (int i = 0; i < 10; i++) {
    cout << digitals[i] << " ";
  }
  cout << digitals[0] <<" ";
}    