#include <iostream>
#include <fstream>

const std::string dataset_path = "../../../input/";
const std::string output_path = "../../../output/";

int main(int argc, char *argv[])
{
  std::string line;
  std::ifstream text_file;
  text_file.open(dataset_path + "/test_file.txt");
  if (!text_file.is_open()) {
    return 1;
  }
  while (!text_file.eof())
  {
    text_file >> line;
    std::cout << line;
  }
  text_file.close();

  std::cout << "Hello world!";

  return 0;
}
