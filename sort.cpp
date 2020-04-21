// I refuse to do this in C

#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "sort.h"

using namespace std;

// C++ doesn't need any help to be bad style

char **sort(char *c_arg, int *len) {
  auto arg = string(c_arg);
  istringstream iss(arg);
  auto args = vector<string>();
  copy(istream_iterator<string>(iss), istream_iterator<string>(),
       back_inserter(args));

  sort(args.begin(), args.end(),
       [](string x, string y) { return stof(x) < stof(y); });

  auto c_args = vector<char *>();
  for (auto &arg : args) {
    auto c_arg = new char[arg.size() + 1];
    strcpy(c_arg, arg.c_str());
    c_args.push_back(c_arg);
  }

  auto ret = new char *[c_args.size()];
  memcpy(ret, c_args.data(), sizeof(char *) * c_args.size());
  *len = c_args.size();

  return ret;
}
