#include <json/Parser.h>
#include <json/Value.h>
#include <eni_types.h>
#include <iostream>
#include <fstream> // std::filebuf

using namespace std;
using namespace json;

void f3(const string &params_text) {
  Parser ps(params_text);
  Value params = ps.getRoot();

  Value ar = params["array"];
  Value u = ar[0][0];
  ar.print(std::cout);
  u.print(std::cout); puts("");

  Value age = params["age"];

  eni::Int a = age.asInt();
  std::cout << "age = " << a;puts("");
  eni::Int b(7122);
  eni::Int c = a*b;
  Value x(c);
  age.print(std::cout); puts("");
  x.print(std::cout); puts("");
}

int main(int argc, char* argv[]) {
  ifstream ifs (argv[1]);
  string s;
  getline(ifs, s, (char)ifs.eof());
  cout << s <<endl;

  if(strstr(argv[1], "ex3")) {
    f3(s);
    return 0;
  }
  return 1;
}
