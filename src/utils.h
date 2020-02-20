#pragma once

#include <string>
#include <vector>

const std::string dataset_path = "../../../input/";
const std::string output_path = "../../../output/";

struct Library
{
  int number_books;
  int signup_time;
  int books_day;
  std::vector<int> books;
  std::vector<int> books_result;
};

struct Global
{
  int books;
  int num_libraries;
  int days;
  std::vector<std::pair<int, int>> scores;
  std::vector<float> book_duplicity_scores;

  std::vector<Library> libs;
  std::vector<int> libs_result;
};

std::vector<int> FilterLibraries(const Global &global);
int GetFinalScore(const Global &global);
int ReadFile(std::string file, Global &global);
int WriteFile(std::string file, const Global &global);