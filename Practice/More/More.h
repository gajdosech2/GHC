#include <fstream>
#include <iostream>
#include <string>
#include <numeric>
#include <vector>
#include <algorithm>

class More
{
public:
	static void Solve(std::string file_name)
	{
		More more;
		more.ReadInputFile(file_name);
		more.Dynamic();
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

	void Find()
	{
		std::vector<int> indices(slices.size());
		std::iota(indices.begin(), indices.end(), 0);
		if (std::accumulate(slices.begin(), slices.end(), 0) <= m)
		{
			best_choice = indices;
		}
		else
		{
			Brute(indices, std::vector<int>());
		}
	}

	void Brute(std::vector<int> available, std::vector<int> took)
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
					Brute(new_available, new_took);
				}
			}
		}
	}

	void Dynamic()
	{
		std::vector<std::vector<int>> table;
		table.push_back({});

		for (int i = 1; i <= m; i++)
		{
			std::vector<int> best(0);
			for (int j : table[i - 1])
			{
				best.push_back(j);
			}
			int score = Score(best);

			for (int j = 0; j < slices.size(); j++)
			{
				if (i - slices[j] >= 0 && 
					std::find(table[i - slices[j]].begin(), table[i - slices[j]].end(), j) == table[i - slices[j]].end())
				{
					std::vector<int> new_best;
					for (int type : table[i - slices[j]])
					{
						new_best.push_back(type);
					}
					new_best.push_back(j);
					int s = Score(new_best);
					if (s > score) 
					{
						best = new_best;
						score = s;
					}
				}
			}
			table.push_back(best);
		}
		best_choice = table[m];
		std::sort(best_choice.begin(), best_choice.end());
	}
};