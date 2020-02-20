#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <numeric>
#include <unordered_set>
#include <glm/glm.hpp>

const std::string dataset_path = "../../../input/";
const std::string output_path = "../../../output/";


int books;
int num_libraries;
int days;
std::vector<std::pair<int, int>> scores;

struct Library
{
  int number_books;
  int signup_time;
  int books_day;
  std::vector<int> books;
  std::vector<int> books_result;

  int Score()
  {
    int score = 0;
    for (int id : books)
    {
      score += scores[id].second;
    }
    return score;
  }
};

std::vector<Library> libs;
std::vector<int> libs_result;

int GetFinalScore()
{
  int final_score = 0;

  std::unordered_set<int> used_books;
  std::vector<int> start_time(libs.size());
  std::vector<int> ready_time(libs.size());

  start_time[libs_result[0]] = 0;
  ready_time[libs_result[0]] = libs[libs_result[0]].signup_time;
  for (int i = 1; i < libs_result.size(); ++i) {
    const int lib_id = libs_result[i];
    const int prev_lib_id = libs_result[i - 1];
    start_time[lib_id] = start_time[prev_lib_id] + libs[prev_lib_id].signup_time;
    ready_time[lib_id] = start_time[lib_id] + libs[lib_id].signup_time;
  }

  for (int day = 0; day < days; ++day) {
    for (int lib_id = 0; lib_id < libs.size(); ++lib_id) {
      if (ready_time[lib_id] <= day) {
        for (int day_book = 0; day_book < libs[lib_id].books_day; ++day_book) {
          int book_nr = (day - ready_time[lib_id]) * libs[lib_id].books_day + day_book;
          if (book_nr >= libs[lib_id].books_result.size()) {
            break;
          }
          int book_id = libs[lib_id].books_result[book_nr];
          const int book = scores[book_id].second;
          if (used_books.find(book) == used_books.end()) {
            final_score += book;
            used_books.insert(book);
          }
        }
      }
    }
  }
  return final_score;
}

int ReadFile(std::string file)
{
  int number;
  std::ifstream text_file;
  text_file.open(dataset_path + "/" + file + ".txt");
  if (!text_file.is_open())
  {
    return EXIT_FAILURE;
  }
  text_file >> books;
  text_file >> num_libraries;
  text_file >> days;

  for (int i = 0; i < books; i++)
  {
    int score_for_book;
    text_file >> score_for_book;
    scores.push_back(std::pair<int, int>(i, score_for_book));
  }

  for (int i = 0; i < num_libraries; i++)
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
    }
    libs.push_back(l);
  }
  text_file.close();
}

int WriteFile(std::string file)
{
  std::ofstream text_file;
  text_file.open(output_path + "/" + file + ".txt");
  if (!text_file.is_open())
  {
    return EXIT_FAILURE;
  }
  text_file << libs_result.size() << "\n";
  for (const int lib_id : libs_result)
  {
    const auto &lib = libs[lib_id];
    text_file << lib_id << " " << lib.books_result.size() << "\n";
    for (const int book_id : lib.books_result)
    {
      text_file << book_id << " ";
    }
    text_file << "\n";
  }
}

void NotSoSimpleGreedy()
{
  std::vector<int>libraries_id(libs.size());
  std::iota(libraries_id.begin(), libraries_id.end(), 0);
  std::sort(libraries_id.begin(), libraries_id.end(), [](const int &i, const int &j)
  {
    if (libs[i].signup_time == libs[j].signup_time)
    {
      return libs[i].books_day > libs[j].books_day;
    }
    return libs[i].signup_time < libs[j].signup_time;
  });

  std::set<int> used_book_ids;
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

void SimpleGreedy()
{
  std::vector<int>libraries_id(libs.size());
  std::iota(libraries_id.begin(), libraries_id.end(), 0);
  std::sort(libraries_id.begin(), libraries_id.end(), [](const int &i, const int &j) { return libs[i].signup_time < libs[j].signup_time;});

  std::set<int> used_book_ids;
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
    scores.clear();
    libs.clear();
    libs_result.clear();
    ReadFile(run_name);
    NotSoSimpleGreedy();
    std::cout << "File '" << run_name << "' score is :" << GetFinalScore() << std::endl;
    WriteFile(run_name);
  }
  return EXIT_SUCCESS;

}



