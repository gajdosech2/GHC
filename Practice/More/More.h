#include <fstream>
#include <iostream>
#include <string>
#include <numeric>
#include <vector>
#include <algorithm>
#include <map>

class More
{
public:
	static void Solve(std::string file_name)
	{
		More more;
		more.ReadInputFile(file_name);
		more.Greedy();
		more.Result();
		more.WriteToFile(file_name);
	}

private:
	std::vector<int> slices;
	int m = 0;

	std::vector<int> best_choice;
	int best_score = 0;

	void ReadInputFile(std::string file_name)
	{
		std::ifstream input;
		input.open("../in/" + file_name + ".in", std::ios::in);
		if (input.is_open())
		{
			std::string token;
			std::getline(input, token, ' ');
			m = std::stoi(token);
			std::getline(input, token, '\n');

			while (std::getline(input, token, ' '))
			{
				slices.push_back(std::stoi(token));
			}
			input.close();
		}
	}

	void WriteToFile(std::string file_name)
	{
		std::ofstream output;
		output.open("../out/" + file_name + ".out", std::ios::out);
		if (output.is_open())
		{
			output << best_choice.size() << std::endl;
			for (int type : best_choice)
			{
				output << type << " ";
			}
			output << std::endl;
			output.close();
		}
	}

	void Result()
	{
		std::cout << "Types: " << best_choice.size() << std::endl;
		std::cout << "Best: ";
		for (int type : best_choice)
		{
			std::cout << type << " ";
		}
		std::cout << std::endl;
		std::cout << "Score: " << Score(best_choice) << std::endl;
	}

	int Score(std::vector<int> choice)
	{
		int score = 0;
		for (int index : choice)
		{
			score += slices[index];
		}
		return score;
	}

	void Brute()
	{
		std::vector<int> indices(slices.size());
		std::iota(indices.begin(), indices.end(), 0);
		if (std::accumulate(slices.begin(), slices.end(), 0) <= m)
		{
			best_choice = indices;
		}
		else
		{
			Backtrack(indices, std::vector<int>());
		}
	}

	void Backtrack(std::vector<int> available, std::vector<int> took)
	{
		int current_score = Score(took);
		if (best_score == m)
		{
			return;
		}
		if (current_score > best_score)
		{
			best_score = current_score;
			best_choice = took;
		}
		if (!available.empty())
		{
			for (int index : available)
			{
				if (current_score + slices[index] <= m)
				{
					std::vector<int> new_available;
					for (int new_index : available)
					{
						if (new_index != index)
						{
							new_available.push_back(new_index);
						}
					}
					std::vector<int> new_took;
					for (int new_index : took)
					{
						new_took.push_back(new_index);
					}
					new_took.push_back(index);
					Backtrack(new_available, new_took);
				}
			}
		}
	}

	void Dynamic()
	{
		std::vector<int> scores(m + 1);
		std::vector<std::vector<int>> table(m + 1);
		table[0] = {};
		scores[0] = 0;
		for (int i = 1; i <= m; i++)
		{
			if (i % 1000 == 0)
			{
				std::cout << (int)((float)i / (float)m * 100) << "%" << std::endl;
			}
			std::vector<int> choice;
			for (int type : table[i - 1])
			{
				choice.push_back(type);
			}
			int score = scores[i - 1];
			for (int j = 0; j < slices.size(); j++)
			{
				int k = i - slices[j];
				if (i - slices[j] >= 0 &&
					std::find(table[k].begin(), table[k].end(), j) == table[k].end() &&
					scores[k] + slices[j] > score)
				{
					choice.clear();
					for (int type : table[k])
					{
						choice.push_back(type);
					}
					choice.push_back(j);
					score = scores[k] + slices[j];
				}
			}
			table[i] = choice;
			scores[i] = score;
		}
		best_choice = table[m];
		std::sort(best_choice.begin(), best_choice.end());
	}

	void Simple()
	{
		int score = 0;
		for (int i = 0; i < slices.size() && score != m; i++) 
		{
			if (score + slices[i] <= m)
			{
				score += slices[i];
				best_choice.push_back(i);
			}
		}
	}

	void Greedy()
	{
		std::vector<int> new_slices(slices.size());
		std::copy(slices.begin(), slices.end(), new_slices.begin());

		std::vector<int> indices(new_slices.size());
		std::iota(indices.begin(), indices.end(), 0);
		std::sort(indices.begin(), indices.end(),
			[&](int i, int j) { return new_slices[i] < new_slices[j]; });
		std::reverse(indices.begin(), indices.end());

		std::sort(new_slices.begin(), new_slices.end());
		std::reverse(new_slices.begin(), new_slices.end());

		int score = 0;
		for (int i = 0; i < new_slices.size() && score != m; i++)
		{
			if (score + new_slices[i] <= m)
			{
				score += new_slices[i];
				best_choice.push_back(indices[i]);
			}
		}
		std::sort(best_choice.begin(), best_choice.end());
	}
};