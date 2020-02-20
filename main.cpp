#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <numeric>
#include <glm/glm.hpp>

#include "utils.h"

void SimpleGreedy(Global &global)
{
  std::vector<int>libraries_id(global.libs.size());
  std::iota(libraries_id.begin(), libraries_id.end(), 0);
  std::sort(libraries_id.begin(), libraries_id.end(), [&](const int &i, const int &j) {return global.libs[i].signup_time < global.libs[j].signup_time; });

  global.libs_result = libraries_id;
  std::set<int> used_book_ids;
  for (int library_id : libraries_id)
  {
    std::vector<int> chosen_books;
    for (int book_id : global.libs[library_id].books)
    {
      if (used_book_ids.empty() || used_book_ids.find(book_id) == used_book_ids.end())
      {
        chosen_books.push_back(book_id);
        used_book_ids.insert(book_id);
      }
    }
    std::sort(chosen_books.begin(), chosen_books.end());
    global.libs[library_id].books_result = chosen_books;
  }
}

int main(int argc, char *argv[])
{
  std::cout << "Hello world!";
  const std::string run_name = "a_example";
  Global global;
  ReadFile(run_name, global);
  SimpleGreedy(global);
  WriteFile(run_name, global);
  return 0;
}



