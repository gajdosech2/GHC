#include <iostream>
#include <fstream>
#include <vector>
#include <map>
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

int GetFinalScore() {
  int final_score = 0;
  int start_time = 0;
  for (auto& lib_index : libs_result) {
    for (int i = 0; i < glm::min(days - start_time, libs[lib_index].number_books); ++i) {
      libs[lib_index].books
      final_score += 
    }
  }
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
  text_file.open(dataset_path + "/" + file + ".txt");
  if (!text_file.is_open())
  {
    return EXIT_FAILURE;
  }
  text_file << libs_result.size() << "\n";
  for (const int lib_id : libs_result)
  {
    const auto &lib = libs[lib_id];
    text_file << lib_id << " " << lib.books_result.size();

  }
}

int main(int argc, char *argv[])
{
  std::cout << "Hello world!";
  const std::string run_name = "a_example";
  ReadFile(run_name);
  WriteFile(run_name);
  return 0;
}



