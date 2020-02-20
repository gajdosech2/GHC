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
  std::unordered_set<int> used_books;
  
  std::vector<int> start_time(global.libs.size());
  std::vector<int> ready_time(global.libs.size());
        
  start_time[global.libs_result[0]] = 0;
  ready_time[global.libs_result[0]] = global.libs[global.libs_result[0]].signup_time;
  for (int i = 1; i < global.libs_result.size(); ++i) {
    const int lib_id = global.libs_result[i];
    const int prev_lib_id = global.libs_result[i - 1];
    start_time[lib_id] = ready_time[prev_lib_id];
    ready_time[lib_id] = start_time[lib_id] + global.libs[lib_id].signup_time;
  }

  for (int day = 0; day < global.days; ++day) {
    for (int lib_id = 0; lib_id < global.libs.size(); ++lib_id) {

      const int days_sending = (day - ready_time[lib_id]);
      if (days_sending >= 0) {
        for (int day_book = 0; day_book < global.libs[lib_id].books_day; ++day_book) {

          int book_nr = days_sending * global.libs[lib_id].books_day + day_book;
          if (book_nr >= global.libs[lib_id].books_result.size()) {
            break;
          }
          int book_id = global.libs[lib_id].books_result[book_nr];
          if (used_books.find(book_id) == used_books.end()) {
            final_score += global.scores[book_id].second;
            used_books.insert(book_id);
          }
        }
      }
    }
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