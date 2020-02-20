#include <iostream>
#include <fstream>
#include <vector>
#include <map>

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

int main(int argc, char *argv[])
{
  std::cout << "Hello world!";
  ReadFile("a_example");
  return 0;
}



