#include "utils.h"
#include <fstream>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <glm/glm.hpp>

int ReadFile(std::string file, Global &global)
{
  int number;
  std::ifstream text_file;
  text_file.open(dataset_path + "/" + file + ".txt");
  if (!text_file.is_open())
  {
    return EXIT_FAILURE;
  }
  text_file >> global.books;
  text_file >> global.num_libraries;
  text_file >> global.days;

  std::vector<int> book_duplicity;
  book_duplicity.resize(global.books);

  for (int i = 0; i < global.books; i++)
  {
    int score_for_book;
    text_file >> score_for_book;
    global.scores.push_back(std::pair<int, int>(i, score_for_book));
  }

  for (int i = 0; i < global.num_libraries; i++)
  {
    Library l;
    text_file >> l.number_books;
    text_file >> l.signup_time;
    text_file >> l.books_day;
    for (int j = 0; j < l.number_books; j++)
    {
      int book_id;
      text_file >> book_id;
      l.books.push_back(book_id);
      book_duplicity[book_id] += 1;
    }
    global.libs.push_back(l);
  }

  global.book_duplicity_scores.resize(global.books);
  int book_dup_max = *std::max_element(book_duplicity.begin(), book_duplicity.end());
  for (int i = 0; i < global.books; ++i)
  {
    global.book_duplicity_scores[i] = (float)book_duplicity[i] / book_dup_max;
  }

  text_file.close();
}

std::vector<int> FilterLibraries(const Global &global)
{
  const auto &libs = global.libs;
  std::vector<int> libraries_id(libs.size());
  std::iota(libraries_id.begin(), libraries_id.end(), 0);
  libraries_id.erase(std::remove_if(libraries_id.begin(), libraries_id.end(),
      [&](const int lib_id)
  {
    return global.days < libs[lib_id].signup_time;
  }), libraries_id.end());
  return libraries_id;
}

float LibraryUniqueness(const Library &library, const Global &global)
{
  float score = 0;
  for (int book_id : library.books)
  {
    score += (1 - global.book_duplicity_scores[book_id]);
  }
  return score / library.number_books;
}

int GetFinalScore(const Global &global)
{
  int final_score = 0;
  int signup_start = 0;
  std::unordered_set<int> used_books;
  auto &libs = global.libs;
  for (auto &lib_index : global.libs_result)
  {
    const int num_of_days = glm::abs(global.days - signup_start - libs[lib_index].signup_time);
    const int num_of_processed_books = num_of_days * libs[lib_index].books_day;
    for (int book_id = 0; book_id < num_of_processed_books; ++book_id)
    {
      if (book_id >= libs[lib_index].number_books)
      {
        break;
      }
      const int book = global.scores[libs[lib_index].books_result[book_id]].second;
      if (used_books.find(book) == used_books.end())
      {
        final_score += book;
        used_books.insert(book);
      }
    }
    signup_start += num_of_days;
  }
  return final_score;
}

int WriteFile(std::string file, const Global &global)
{
  std::ofstream text_file;
  text_file.open(output_path + "/" + file + ".txt");
  if (!text_file.is_open())
  {
    return EXIT_FAILURE;
  }
  text_file << global.libs_result.size() << "\n";
  for (const int lib_id : global.libs_result)
  {
    const auto &lib = global.libs[lib_id];
    text_file << lib_id << " " << lib.books_result.size() << "\n";
    for (const int book_id : lib.books_result)
    {
      text_file << book_id << " ";
    }
    text_file << "\n";
  }
}