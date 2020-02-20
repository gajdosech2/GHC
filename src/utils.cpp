#include "utils.h"
#include <fstream>
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

  global.book_duplicity.resize(global.books);

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
      global.book_duplicity[book_id] += 1;
    }
    global.libs.push_back(l);
  }
  text_file.close();
}

int GetFinalScore(const Global &global)
{
  int final_score = 0;
  int signup_start = 0;
  for (auto &lib_index : global.libs_result)
  {
    const int num_of_processed_books = glm::min(global.days - signup_start, global.libs[lib_index].number_books);
    for (int book_id = 0; book_id < num_of_processed_books; ++book_id)
    {
      final_score += global.libs[lib_index].books_result[book_id];
    }
    signup_start += num_of_processed_books;
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