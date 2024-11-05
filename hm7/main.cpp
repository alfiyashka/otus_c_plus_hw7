#include <iostream>
#include <cassert>

#include "src/CommandParser.hpp"

using namespace std;


int main(int argc, const char* argv[])
{
  if (argc <= 1)
  {
    std::cerr<< "The package size is not defined!" << std::endl;
    return -1;
  }
  auto inputParameter = argv[1];
  const int packageSize = std::atoi(inputParameter);

  CommandParser parser(packageSize);
  parser.init();
  
  std::string cmd; 
  while (std::getline(cin, cmd))
  {
    parser.parse(cmd);
  }
  return 0;
}
