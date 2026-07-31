#include<iostream>
#include<list>
#include<vector>
#include<string>

class Num
{
public:
	int num;
	bool changeable;
	Num(int num)
		:num(num)
	{
		changeable = num == 0 ? true : false;
	}
};

int main()
{
	//Input
	std::cout << "请输入题目(1.输入一行后按Enter    2.空格用0代表）:" << std::endl;
	std::cout << "   123456789  <- 序列" << std::endl << std::endl;

	//以行的形式输入数独
	std::vector<std::string> inputdata;
	inputdata.reserve(9);
	std::string inputrow;
	for (int i = 0; i < 9; ++i)
	{
		inputrow = "";
		std::cout << i + 1 << "行";
		std::getline(std::cin, inputrow);
		inputdata.emplace_back(inputrow);
	}

	std::vector<Num> nums;//生成二维数组
	nums.reserve(9 * 9);

	//将行的形式（string）转化为int数组
	for (size_t vectorcolumn = 0; vectorcolumn < inputdata.size(); vectorcolumn++)//9行循环9次
	{
		for (const char& c : inputdata[vectorcolumn])
		{
			if (isdigit(c))//检查是否为数字
			{
				nums.emplace_back(std::stoi(std::string(1, c)));//std::string(1,c)用c创造一个单个字符的string
			}
		}
	}
	std::cout << std::endl << "start solving……" << std::endl;

	unsigned int index = 0;
	bool established = true;//空格中的数字是否满足条件
	unsigned int established_numindex = 0;

	while (index < 9 * 9)
	{
		if (nums[index].changeable == true)
		{
			if (nums[index].num == 9)
			{
				established = false;
			}
			for (size_t i = nums[index].num + 1; i < 10; i++)
			{
				for (size_t row_nums = 0; row_nums < 9; row_nums++)
				{
					unsigned int row = index / 9;
					if (nums[row_nums + (row * 9)].num == i && index != row_nums + (row * 9))
					{
						established = false;
						break;
					}
				}
				if (!established)
				{
					if (i == 9)
					{
						established = false;
						break;
					}
					established = true;
					continue;
				}


				for (size_t column_nums = 0; column_nums < 9; column_nums++)
				{
					unsigned int column = index % 9;
					if (nums[column + (9 * column_nums)].num == i && index != column + (9 * column_nums))
					{
						established = false;
						break;
					}
				}
				if (!established)
				{
					if (i == 9)
					{
						established = false;
						break;
					}
					established = true;
					continue;
				}
				//square
				unsigned int square_row = (int(index / 9) / 3) * 3;
				unsigned int square_column = (int(index % 9) / 3) * 3;
				for (size_t row = 0; row < 3; row++)
				{
					for (size_t column = 0; column < 3; column++)
					{
						if (nums[square_column + column + (9 * (square_row + row))].num == i && index != square_column + column + (9 * (square_row + row)))
						{
							established = false;
							break;
						}
					}
				}
				if (!established)
				{
					if (i == 9)
					{
						established = false;
						break;
					}
					established = true;
					continue;
				}
				//
				nums[index].num = i;
				break;
			}
			if (!established)//回溯
			{
				nums[index].num = 0;
				--index;
				while (nums[index].changeable == false)
				{
					--index;
				}
				established = true;
				continue;
			}
		}
		else
		{
			++index;
			continue;
		}
		++index;
	}

	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			std::cout << nums[j + (9 * i)].num << " ";
		}
		printf("\n");
	}

	std::cin.get();
}