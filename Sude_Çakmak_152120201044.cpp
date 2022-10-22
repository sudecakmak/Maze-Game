#include <iostream>
#include <stdlib.h>
#include <fstream> 
#include <ctime>  
#include <windows.h>
#include <conio.h> 

#define size 105

using namespace std;

void gotoxy(int x, int y)
{
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int value)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

int main()
{
	fstream file;
	int labyrinth_size;
	int i, j, key;
	char player_position[size][size], labyrinth[size][size];
	int a, b, t;
	int monster = 0, gold = 0, randomi, randomj;
	int numberofgolds = 0;
	bool constant = false;
	int *p = &j, *q = &i;

	file.open("outputWay.txt", ios::out);

	if (!file)
	{
		cout << "File open error!" << endl;
		exit(0);
	}

	cout << "Enter the labyrinth size (at least 10, at most 100): ";
	cin >> labyrinth_size;

	system("cls");

	srand(time(NULL));

	for (i = 0; i < labyrinth_size + 1; i++)
	{
		for (j = 0; j < labyrinth_size + 2; j++)
		{
			t = (rand() % 2) + 1;

			labyrinth[i][j] = 49;
		}
	}

	for (i = 0; i < labyrinth_size + 1; i++)
	{
		for (j = 0; j < labyrinth_size + 2; j++)
		{
			t = (rand() % 2) + 1;

			if (t == 1)
			{
				labyrinth[i + 1][j] = 48;
			}
			else if (t == 2)
			{
				labyrinth[i][j + 1] = 48;
			}
		}
	}


	for (i = 0; i < labyrinth_size + 1; i++)
	{
		for (j = 0; j < labyrinth_size + 2; j++)
		{
			if (monster != (labyrinth_size / 2) + 1)
			{
				randomi = (rand() % labyrinth_size) + 1;
				randomj = (rand() % labyrinth_size) + 1;

				monster++;
				labyrinth[randomi][randomj] = 38;
			}
			if (gold != static_cast<int>(labyrinth_size*2))
			{
				randomi = (rand() % labyrinth_size) + 1;
				randomj = (rand() % labyrinth_size) + 1;

				gold++;
				labyrinth[randomi][randomj] = 64;
			}

		}
	}


	for (i = 0; i < labyrinth_size + 1; i++)
	{
		for (j = 0; j < labyrinth_size + 2; j++)
		{
			if (j == 0 || i == 0 || j == labyrinth_size + 1)
			{
				labyrinth[i][j] = 49;
			}

			labyrinth[1][1] = 48;
		}
	}


	for (i = 0; i < labyrinth_size + 1; i++)
	{
		for (j = 0; j < labyrinth_size + 2; j++)
		{
			player_position[i][j] = labyrinth[i][j];
		}
	}


	do
	{
		cout << "Control the player by using arrow keys or W A S D !" << "\n";
		SetColor(14); cout << "@"; SetColor(15); cout << " => gold\t";
		SetColor(10); cout << " &"; SetColor(15); cout << " => monster" << "\n\n";

		file << "The Way Out of the Labyrinth" << endl;
		file << "  x" << "   y\n" << "---------";
		file << "\n" << "| 0 | 0 |";

		for (i = 0; i < labyrinth_size + 1; i++)
		{
			for (j = 0; j < labyrinth_size + 2; j++)
			{
				if (j == 0 || i == 0 || j == labyrinth_size + 1)
				{
					SetColor(0);
				}
				else if (labyrinth[i][j] == 64)
				{
					SetColor(14);
				}
				else if (labyrinth[i][j] == 38)
				{
					SetColor(10);
				}
				else if (labyrinth[i][j] == 49)
				{
					SetColor(12);
				}
				else if (labyrinth[i][j] == 48)
				{
					SetColor(9);
				}


				if (labyrinth_size > 10)
				{
					cout << " " << labyrinth[i][j];
				}
				else
				{
					cout << "\t" << labyrinth[i][j];
				}
			}
			cout << endl;
		}

		SetColor(15);

		if (labyrinth_size > 10)
		{
			a = 3; b = 4;
			gotoxy(a, b);
		}
		else
		{
			a = 16; b = 4;
			gotoxy(a, b);
		}

		for (i = 1; i < labyrinth_size; *q)
		{
			for (j = 1; j < labyrinth_size + 2; *p)
			{
				key = _getch();

				if ((key == 77 || key == 68 || key == 100) && player_position[i][j + 1] != 49)
				{
					if (labyrinth_size > 10)
					{
						a = a + 2;
					}
					else
					{
						a = a + 8;
					}

					*p = j++;
					constant = false;
				}
				else if ((key == 75 || key == 65 || key == 97) && player_position[i][j - 1] != 49)
				{
					if (labyrinth_size > 10)
					{
						a = a - 2;
					}
					else
					{
						a = a - 8;
					}

					*p = j--;
					constant = false;
				}
				else if ((key == 72 || key == 87 || key == 119) && player_position[i - 1][j] != 49)
				{
					b--;
					*q = i--;
					constant = false;
				}
				else if ((key == 80 || key == 83 || key == 115) && player_position[i + 1][j] != 49)
				{
					b++;
					*q = i++;
					constant = false;
				}
				else
				{
					constant = true;
				}

				gotoxy(a, b);

				if (key != 224 && constant == false)
				{
					file << "\n" << "| " << (i - 1) << " | " << (j - 1) << " |";
				}

				if (player_position[i][j] == 64)
				{
					player_position[i][j] = 48;
					cout << " \b";
					numberofgolds++;
				}

				if (player_position[i][j] == 38)
				{
					file.close();
					file.open("outputWay.txt", ios::out | ios::trunc);
					system("cls");
					numberofgolds = 0;
					
					for (i = 0; i < labyrinth_size + 1; i++)
					{
						for (j = 0; j < labyrinth_size + 2; j++)
						{
							player_position[i][j] = labyrinth[i][j];
						}
					}

					break;
				}

				if (i == (labyrinth_size))
					break;
			}
		}


	} while (i != (labyrinth_size));

	cout << "\n\n\n" << " You collect " << numberofgolds << " golds!" << "\n\n\n";
	file << "\n\n" << "You collect " << numberofgolds << " golds!" << endl << endl;

	file.close();

	system("pause");
	return 0;
}