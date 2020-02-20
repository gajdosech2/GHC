#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <numeric>
#include <unordered_set>
#include <glm/glm.hpp>

#include <Utils/Statistics.h>

#include "utils.h"

void UniqueGreedy(Global &global)
{
  auto &libs = global.libs;
  std::vector<int> libraries_id(libs.size());
  std::iota(libraries_id.begin(), libraries_id.end(), 0);

  const int CHOSEN_BOOKS_THRESHOLD = 0;

  std::sort(libraries_id.begin(), libraries_id.end(), [&](const int &i, const int &j)
  {
    const float cof = 0.7f;
    auto UniqueFunc = [](float f, float coef) { return (1 - f) * coef + (1 - coef); };
    float library_u_1 = UniqueFunc(LibraryUniqueness(global.libs[i], global), cof);
    float library_u_2 = UniqueFunc(LibraryUniqueness(global.libs[j], global), cof);
    return libs[i].signup_time * library_u_1 < libs[j].signup_time * library_u_2;
    //return libs[i].signup_time < libs[j].signup_time;
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

    if (chosen_books.size() > CHOSEN_BOOKS_THRESHOLD)
    {
      std::sort(chosen_books.begin(), chosen_books.end());
      libs[library_id].books_result = chosen_books;
      libs_result.push_back(library_id);
    }
  }
}

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
  std::sort(libraries_id.begin(), libraries_id.end(), [&](const int &i, const int &j)
  {
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

void AnalyzeData(Global &global)
{
  utils::Statistics<long long> signup_time;
  utils::Statistics<long long> book_num;
  utils::Statistics<long long> scores;
  utils::Statistics<double> books_uniqueness;
  utils::Statistics<long long> books_per_day;
  utils::Statistics<long long> shipping_days;
  for (const auto &lib : global.libs)
  {
    signup_time.Add(lib.signup_time);
    book_num.Add(lib.books.size());
    books_uniqueness.Add(LibraryUniqueness(lib, global));
    books_per_day.Add(lib.books_day);
    shipping_days.Add(lib.books.size() / lib.books_day);
  }
  std::cout << "signup_time:   " << signup_time.ToString() << std::endl;
  std::cout << "book_num:      " << book_num.ToString() << std::endl;
  std::cout << "library_score: " << books_uniqueness.ToString() << std::endl;
  std::cout << "books_per_day: " << books_per_day.ToString() << std::endl;
  std::cout << "shipping_days: " << shipping_days.ToString() << std::endl;

  utils::Statistics<double> books_duplicity;
  for (const auto &score : global.book_duplicity_scores)
  {
    books_duplicity.Add(score);
  }
  std::cout << "books_duplicit:" << books_duplicity.ToString() << std::endl;

  utils::Statistics<double> books_scores;
  for (const auto &score : global.scores)
  {
    books_scores.Add(score.second);
  }
  std::cout << "books_scores:  " << books_scores.ToString() << std::endl;
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
    std::cout << "\t" << run_name << "    days: " << global.days;
    std::cout << "    libraries: " << global.libs.size();
    std::cout << "    books: " << global.books << std::endl;
    AnalyzeData(global);
    std::cout << std::endl;
    //WriteFile(run_name, global);
    //std::cout << run_name << " score: " << GetFinalScore(global) << "\n";

    UniqueGreedy(global);
    WriteFile(run_name, global);
    std::cout << run_name << " score: " << GetFinalScore(global) << "\n";

  }
  return EXIT_SUCCESS;
}



