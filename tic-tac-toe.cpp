// tic-tac-toe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> board; // 1=x, -1=o, 0=empty

// 1=x, -1=o, 0=tie

board bd = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

// 1=x win, -1=o win, 0=inconclusive

int eval(board x)
{
	if ((x[0][0] == x[0][1]) && (x[0][1] == x[0][2]) && (x[0][2] != 0))
	{
		return x[0][2];
	}
	else if ((x[1][0] == x[1][1]) && (x[1][1] == x[1][2]) && (x[1][2] != 0))
	{
		return x[1][2];
	}
	else if ((x[2][0] == x[2][1]) && (x[2][1] == x[2][2]) && (x[2][2] != 0))
	{
		return x[2][2];
	}
	else if ((x[0][0] == x[1][0]) && (x[1][0] == x[2][0]) && (x[2][0] != 0))
	{
		return x[0][0];
	}
	else if ((x[0][1] == x[1][1]) && (x[1][1] == x[2][1]) && (x[2][1] != 0))
	{
		return x[0][1];
	}
	else if ((x[0][2] == x[1][2]) && (x[1][2] == x[2][2]) && (x[2][2] != 0))
	{
		return x[0][2];
	}
	else if ((x[0][0] == x[1][1]) && (x[1][1] == x[2][2]) && (x[2][2] != 0))
	{
		return x[2][2];
	}
	else if ((x[0][2] == x[1][1]) && (x[1][1] == x[2][0]) && (x[2][0] != 0))
	{
		return x[0][2];
	}
	return 0;
}

// move returns {{xCoord, yCoord},result}
int maxD = 0;

pair<pair<int, int>, int> move(board m_bd, bool turn, int depth)
{
	if (depth > maxD) {
		cout << depth << endl;
		maxD = depth;
	}
	int imRes = eval(m_bd);
	if (imRes != 0)
	{
		return { {123, 321}, imRes };
	}
	// turn: true=x, false=o
	if (turn)
	{
		pair<int, int> bMove{ -2, -2 };
		int best = -1;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (m_bd[i][j] == 0)
				{
					board tBd = m_bd;
					tBd[i][j] = 1;
					pair<pair<int, int>, int> tRes = move(tBd, false, depth + 1);
					if (tRes.second >= best)
					{
						bMove.first = i;
						best = tRes.second;
						bMove.second = j;
					}
				}
			}
		}
		if (bMove.first == -2)
		{
			return { {123,223}, 0 };
		}
		return { bMove, best };
	}
	else
	{
		pair<int, int> bMove{ -2, -2 };
		int best = 1;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (m_bd[i][j] == 0)
				{
					board tBd = m_bd;
					tBd[i][j] = -1;
					pair<pair<int, int>, int> tRes = move(tBd, true, depth + 1);
					if (tRes.second <= best)
					{
						bMove.first = i;
						best = tRes.second;
						bMove.second = j;
					}
				}
			}
		}
		if (bMove.first == -2)
		{
			return { {123,323}, 0};
		}
		return { bMove, best };
	}
}

int main()
{
	bool mTurn;
	cout << "Who do you want to be (1=X, 0=O)? ";
	cin >> mTurn;
	if (mTurn)
	{
		while (true)
		{
			cout << "Enter your move: ";
			int x, y;
			cin >> x >> y;
			bd[x][y] = 1;
			pair<pair<int, int>, int> res = move(bd, false, 0);
			cout << "My move is (" << res.first.first << ", " << res.first.second << ")\n";
			bd[res.first.first][res.first.second] = -1;
			switch (res.second)
			{
			case -1:
				cout << "I'm sure I will win!!!\n";
				break;
			case 0:
				cout << "With optimal gameplay, this should be a tie.\n";
				break;
			case 1:
				cout << "You can win against me with optimal gameplay. :(\n";
				break;
			}
		}
	}
	else
	{
		while (true)
		{
			pair<pair<int, int>, int> res = move(bd, false,0);
			cout << "My move is (" << res.first.first << ", " << res.first.second << ")\n";
			bd[res.first.first][res.first.second] = 1;
			switch (res.second)
			{
			case -1:
				cout << "I'm sure I will win!!!\n";
				break;
			case 0:
				cout << "With optimal gameplay, this should be a tie.\n";
				break;
			case 1:
				cout << "You can win against me with optimal gameplay. :(\n";
				break;
			}
			cout << "Enter your move: ";
			int x, y;
			cin >> x >> y;
			bd[x][y] = -1;
		}
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
