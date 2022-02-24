#include <iostream>
#include <cstdio>
#include <string>
#include <map>

using namespace std;

int main(int argc, char** argv) {
  char *input = new char[100000 + 2];
  scanf("%s", input);
  string s(input);
  delete[] input;
  map<int, int> pesosDistintos;
  int pesoTotal = 0, pesoRelativo;

  //Calculo do peso total da string
  // O(n)
  for(char i : s){
    pesoTotal += (i - 96);
  }

  pesoRelativo = pesoTotal;
  string aux = s;

  for(size_t j = s.length(); j > 0; --j){
    for(size_t i = s.length(); i > 0; --i){
      pesosDistintos[pesoRelativo] ? ++pesosDistintos[pesoRelativo]: pesosDistintos[pesoRelativo] = 1,
      pesoRelativo -= (aux[i - 1] - 96),
      aux.pop_back();
    }
    pesoRelativo = pesoTotal = pesoTotal - (s[0] - 96),
    s = &s[1],
    aux = s;
  }

  cout << pesosDistintos.size() << endl;

  return 0;
}