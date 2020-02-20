#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <numeric>
#include <unordered_set>
#include <glm/glm.hpp>

#include "utils.h"

void NotSimpleGreedy(Global &global)
{
  auto &libs = global.libs;
  std::vector<int> libraries_id = FilterLibraries(global);
  std::sort(libraries_id.begin(), libraries_id.end(), [&](const int &i, const int &j)
  {
    if (libs[i].signup_time == libs[j].signup_time)
    {
      return libs[i].books_day > libs[j].books_day;
    }
    return libs[i].signup_time < libs[j].signup_time;
  });

  std::set<int> used_book_ids;
  auto &libs_result = global.libs_result;
  libs_result.reserve(libs.size());
  for (int library_id : libraries_id)
  {
    std::vector<int> chosen_books;
    for (int book_id : libs[library_id].books)
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
      libs[library_id].books_result = chosen_books;
      libs_result.push_back(library_id);
    }
  }
}

void SimpleGreedy(Global &global)
{
  auto &libs = global.libs;
  std::vector<int> libraries_id = FilterLibraries(global);
  std::sort(libraries_id.begin(), libraries_id.end(), [&](const int &i, const int &j) { return libs[i].signup_time < libs[j].signup_time;});

  std::set<int> used_book_ids;
  auto &libs_result = global.libs_result;
  libs_result.reserve(libs.size());
  for (int library_id : libraries_id)
  {
    std::vector<int> chosen_books;
    for (int book_id : libs[library_id].books)
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
      libs[library_id].books_result = chosen_books;
      libs_result.push_back(library_id);
    }
  }
}

int main(int argc, char *argv[])
{
  std::vector<std::string> files =
  {
    "a_example",
    "b_read_on",
    "c_incunabula",
    "d_tough_choices",
    "e_so_many_books",
    "f_libraries_of_the_world"
  };
  for (std::string &run_name : files)
  {
    Global global;
    ReadFile(run_name, global);
    SimpleGreedy(global);
    WriteFile(run_name, global);
    //std::cout << run_name << " score: " << GetFinalScore(global) << "\n";
  }
  return EXIT_SUCCESS;

}



