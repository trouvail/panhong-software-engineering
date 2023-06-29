#include <iostream>
#include <fstream>
#include <cstring>
#include <random>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <string>

#define EASY_MODEL 1
#define NORMAL_MODEL 2
#define HARD_MODEL 3
#define MAX_SPACE 64 // 数独中允许的最大空格数
#define MIN_SPACE 20 // 数独中允许的最小空格数

const int maxNumerOfFinality = 1e6 + 10; // 最大终局数量
const int theDimensionOfSudoku = 10;	   // 数独的维度
const int N = 17;		   // 加上空格后数独的维度
const int GRID_SIZE = 9;   // 数独的维度

int theStoreOfStep[80][theDimensionOfSudoku];			 // 存储平移步数的数据结构
int Permutation[maxNumerOfFinality][theDimensionOfSudoku]; // 存储数独终局排列结果的数据结构

using namespace std;

// 生成临时的排列组合，target存储生成的结果，line用于记录已生成的排列组合的行数
void tempPermutate(int src[], int begin, int end, int target[6][3], int& line)
{
	if (begin > end)
		begin = end;
	if (begin == end)
	{
		for (int i = 0; i <= end; i++)
			target[line][i] = src[i];
		line++;
	}
	else
	{
		for (int i = begin; i <= end; i++)
		{
			// 交换次序
			swap(src[i], src[begin]);
			tempPermutate(src, begin + 1, end, target, line);
			swap(src[i], src[begin]);
		}
	}
}

// 根据临时的排列组合生成每一步移动的规则
void toSwap(int temp1[2][2], int temp2[6][3], int temp3[6][3], int maxNum, int moveStep[80][theDimensionOfSudoku])
{
	int cnt = 0;
	for (int i = 0; i < 2; i++)
	{
		//  二三行有两个排列，二选一
		for (int j = 0; j < 6; j++)
		{
			//  四五六行有六个全排列，六选一
			for (int k = 0; k < 6; k++)
			{
				//  七八九行有六个全排列，六选一
				for (int r = 0; r < 8; r++)
				{
					//  每个排列有8个元素（首元素不动）
					if (r < 2)
						moveStep[cnt][r] = temp1[i][r];
					else if (r < 5)
						moveStep[cnt][r] = temp2[j][r - 2];
					else
						moveStep[cnt][r] = temp3[k][r - 5];
				}
				cnt++;
				if (cnt >= maxNum)
					return;
			}
		}
	}
}

// 生成全排列
void generateAll(int src[], int begin, int end, int target[maxNumerOfFinality][theDimensionOfSudoku], int& line, int maxNum)
{
	if (begin > end) // 防止输入错误，导致越界
		begin = end;

	if (begin == end) //  终止条件
	{
		for (int i = 0; i <= end; i++)
			target[line][i] = src[i];
		line++;
	}
	else
	{
		for (int i = begin; i <= end; i++)
		{
			if (line >= maxNum)
				return;
			swap(src[i], src[begin]);
			generateAll(src, begin + 1, end, target, line, maxNum);
			swap(src[i], src[begin]);
		}
	}
}

// 生成最终的终局
void generateGame(string filePath, int num)
{
	ofstream fout;
	fout.open(filePath);

	int source2[] = { 1, 4, 7 }, source3[] = { 2, 5, 8 };
	int temp1[2][2], temp2[6][3], temp3[6][3];
	int line2 = 0, line3 = 0;
	temp1[0][0] = 3, temp1[0][1] = 6;
	temp1[1][0] = 6, temp1[1][1] = 3;
	tempPermutate(source2, 0, 2, temp2, line2);
	tempPermutate(source3, 0, 2, temp3, line3);
	toSwap(temp1, temp2, temp3, min(num, 72), theStoreOfStep);

	int source[] = { 5, 1, 2, 9, 8, 7, 4, 3, 6 };
	int line = 0;
	generateAll(source, 1, 8, Permutation, line, num / 72 + 1);
	for (int cnt = 0; cnt < num; cnt++)
	{
		//通过平移，生成数独终局
		int pl = cnt / 72;
		int ml = cnt % 72;
		char temp[200];
		int temp_site = 0;
		memset(temp, 0, sizeof(char) * 200);
		for (int i = 0; i < 9; i++)
		{
			temp[temp_site] = Permutation[pl][i] + '0';
			temp_site++;
			if (i == 8)
			{
				temp[temp_site] = '\n';
				temp_site++;
			}
			else
			{
				temp[temp_site] = ' ';
				temp_site++;
			}
		}
		for (int i = 1; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				int site = (j + theStoreOfStep[ml][i - 1]) % 9;
				temp[temp_site] = Permutation[pl][site] + '0';
				temp_site++;
				if (j == 8)
				{
					temp[temp_site] = '\n';
					temp_site++;
				}
				else
				{
					temp[temp_site] = ' ';
					temp_site++;
				}
			}
		}
		int index = 0;
		while (temp[index] != 0)
		{
			fout << temp[index];
			index++;
		}
		if (cnt != num - 1)
		{
			fout << "\n";
		}
	}
}

// 用于生成新的数独游戏
void generateNewGame(string inputPath, string outputPath, int num, bool setHardOrNot, int difficulty = EASY_MODEL,
	int minSpace = MIN_SPACE, int maxSpace = MAX_SPACE, bool theOneSolve = false)
{
	char thisGame[9][9] = { 0 };
	srand(time(nullptr));
	ifstream fin;
	fin.open(inputPath);
	ofstream fout;
	fout.open(outputPath);
	for (int cnt = 0; cnt < num; cnt++)
	{
		//读取终局
		if (fin.eof())
		{
			fin.clear();
			fin.seekg(0, ios::beg);
		}
		bool err = false;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				fin >> thisGame[i][j];
				if (thisGame[i][j] == '.')
				{
					err = true;
					break;
				}
			}
		}
		if (err)
		{
			cnt--;
			continue;
		}
		//生成游戏
		if (theOneSolve)
		{
		}
		else
		{
			int num_space = 0;
			if (setHardOrNot)
			{
				switch (difficulty)
				{
				case EASY_MODEL:
					//20~31空
					num_space = rand() % 12 + 20;
					break;
				case NORMAL_MODEL:
					//32~47空
					num_space = rand() % 16 + 32;
					break;
				case HARD_MODEL:
					//48~64空
					num_space = rand() % 17 + 48;
					break;
				default:
					break;
				}
			}
			else
			{
				num_space = rand() % (maxSpace - minSpace + 1) + minSpace;
			}
			random_device rd;
			mt19937 r_eng(rd());
			bool ret = false;
			cout << cnt << " " << num_space << endl;
			for (int i = 0; i < num_space; i++)
			{
				int row = r_eng() % 9;
				int col = r_eng() % 9;
				if (thisGame[row][col] != '.')
				{
					thisGame[row][col] = '.';
				}
				else
				{
					if (!ret)
					{
						ret = true;
						for (int m = 0; m < 9; m++)
						{
							bool if_break = false;
							for (int n = 0; n < 9; n++)
							{
								if (thisGame[m][n] != '.')
								{
									thisGame[m][n] = '.';
									if_break = true;
									break;
								}
							}
							if (if_break)
								break;
						}
					}
					else
					{
						ret = false;
						for (int m = 8; m >= 0; m--)
						{
							bool if_break = false;
							for (int n = 8; n >= 0; n--)
							{
								if (thisGame[m][n] != '.')
								{
									thisGame[m][n] = '.';
									if_break = true;
									break;
								}
							}
							if (if_break)
								break;
						}
					}
				}
			}
		}
		//写入游戏文件
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				fout << thisGame[i][j] << " ";
			}
			fout << thisGame[i][8] << endl;
		}
		fout << endl;
	}
	fin.close();
	fout.close();
}

void playGamez(string inputPath, string outputPath)
{
	ifstream inputfile(inputPath);

	ofstream outputfile(outputPath);

	string line;
	while (getline(inputfile, line))
	{
		outputfile << line << endl;
	}

	inputfile.close();
	outputfile.close();
}

bool FindEmptyCell(const vector<vector<int> >& grid, int& row, int& col)
{
	for (row = 0; row < GRID_SIZE; ++row)
	{
		for (col = 0; col < GRID_SIZE; ++col)
		{
			if (grid[row][col] == 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool IsSafe(const vector<vector<int> >& grid, int row, int col, int num)
{
	// 检查行是否存在重复数字
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		if (grid[row][i] == num)
		{
			return false;
		}
	}

	// 检查列是否存在重复数字
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		if (grid[i][col] == num)
		{
			return false;
		}
	}

	// 检查 3x3 方框是否存在重复数字
	int startRow = row - row % 3;
	int startCol = col - col % 3;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (grid[startRow + i][startCol + j] == num)
			{
				return false;
			}
		}
	}

	return true;
}

bool SolveSudoku(vector<vector<int> >& grid)
{
	int row, col;
	if (!FindEmptyCell(grid, row, col))
	{
		// 所有单元格已填满，数独已解决
		return true;
	}

	for (int num = 1; num <= GRID_SIZE; ++num)
	{
		if (IsSafe(grid, row, col, num))
		{
			// 尝试填入数字
			grid[row][col] = num;

			// 递归求解剩余的数独
			if (SolveSudoku(grid))
			{
				return true;
			}

			// 如果当前数字导致无解，则回溯
			grid[row][col] = 0;
		}
	}

	// 无解
	return false;
}

void SolveMultipleSudokus(const string& inputPath, const string& outputPath)
{
	ifstream inputFile(inputPath);
	ofstream outputFile(outputPath);

	if (!inputFile)
	{
		cout << "无法打开输入文件: " << inputPath << endl;
		return;
	}

	if (!outputFile)
	{
		cout << "无法打开输出文件: " << outputPath << endl;
		return;
	}

	vector<vector<int> > grid(GRID_SIZE, vector<int>(GRID_SIZE, 0));

	string line;
	int sudokuCount = 0;
	while (getline(inputFile, line))
	{
		if (line.empty())
		{
			// 忽略空行
			continue;
		}

		grid.clear();
		grid.resize(GRID_SIZE, vector<int>(GRID_SIZE, 0));

		for (int row = 0; row < GRID_SIZE; ++row)
		{
			getline(inputFile, line);
			int col = 0; // 用来存放到的位置
			for (int col_mid = 0; col_mid < N; ++col_mid)
			{
				char ch = line[col_mid];
				if (ch == '.')
				{
					grid[row][col] = 0;
				}
				else if (ch == ' ')
				{
					continue;
				}
				else
				{
					grid[row][col] = ch - '0';
				}
			}
		}

		// 求解数独
		if (SolveSudoku(grid))
		{
			++sudokuCount;
			// 写入求解结果到输出文件
			outputFile << "数独 #" << sudokuCount << ":\n";
			for (int row = 0; row < GRID_SIZE; ++row)
			{
				for (int col = 0; col < GRID_SIZE; ++col)
				{
					outputFile << grid[row][col];
				}
				outputFile << "\n";
			}
			outputFile << "\n";
		}
		else
		{
			cout << "无法解决数独 #" << sudokuCount + 1 << endl;
		}
	}

	inputFile.close();
	outputFile.close();

	cout << "已完成求解，共解决 " << sudokuCount << " 个数独。" << endl;
}

int playGame(string input_path, string output_path)
{
	string inputPath = input_path;
	string outputPath = output_path;

	SolveMultipleSudokus(inputPath, outputPath);

	return 0;
}

int main(int n_argc, char* argv[])
{
	//解析参数
	vector<string> argvList;
	if (n_argc <= 1)
	{
		// cout << n_argc << endl;
		cout << "请重新运行本程序并输入参数！" << endl;
		return 0;
	}
	for (int i = 0; i < n_argc; i++)
		argvList.push_back(argv[i]);
	if (argvList[1] == "-c")
	{
		//生成终局文件
		int num = atoi(argvList[2].c_str());
		string generate_path = "./end_game.txt";
		generateGame(generate_path, num);
	}
	else if (argvList[1] == "-s")
	{
		//读取棋盘文件并求解
		string game_path = argvList[2];
		string output_path = "./sudoku.txt";
		playGamez(game_path, output_path);
	}
	else if (argvList[1] == "-n")
	{
		//生成游戏
		int num = atoi(argvList[2].c_str());
		string input_path = "./end_game.txt";
		string generate_path = "./game.txt";
		if (argvList.size() == 3)
		{
			//生成指定数量的游戏
			generateNewGame(input_path, generate_path, num, false);
		}
		else if (argvList.size() > 3)
		{
			if (argvList[3] == "-m")
			{
				//生成指定难度的游戏
				int difficulty = atoi(argvList[4].c_str());
				generateNewGame(input_path, generate_path, num, true, difficulty);
			}
			else if (argvList[3] == "-r")
			{
				//生成指定空格数量范围的游戏
				string scope = argvList[4];
				size_t pos = scope.find('~');
				int min_space = atoi(scope.substr(0, pos).c_str());
				int max_space = atoi(scope.substr(pos + 1, scope.size()).c_str());
				generateNewGame(input_path, generate_path, num, false, EASY_MODEL, min_space, max_space);
			}
			else if (argvList[3] == "-u")
			{
				//生成唯一解的游戏
				generateNewGame(input_path, generate_path, num, false, EASY_MODEL, MIN_SPACE, MAX_SPACE, true);
			}
		}
	}
	else
	{
		cout << "请重新运行本程序并输入正确参数！" << endl;
		return 0;
	}
	return 0;
}