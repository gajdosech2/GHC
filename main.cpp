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

  std::set<int> used_book_ids;
  global.libs_result.reserve(global.libs.size());
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

    if (!chosen_books.empty())
    {
      std::sort(chosen_books.begin(), chosen_books.end());
      global.libs[library_id].books_result = chosen_books;
      global.libs_result.push_back(library_id);
    }
  }
}

int main(int argc, char *argv[])
{
  std::cout << "Hello world!";
  std::vector<std::string> files =
  {
    "a_example",
    "b_read_on",
    "c_incunabula",
    "d_tough_choices",
    "e_so_many_books",
    "f_libraries_of_the_world"
  };
  for (std::string run_name : files)
  {
    Global global;
    ReadFile(run_name, global);
    SimpleGreedy(global);
    WriteFile(run_name, global);
  }
  return EXIT_SUCCESS;
}



