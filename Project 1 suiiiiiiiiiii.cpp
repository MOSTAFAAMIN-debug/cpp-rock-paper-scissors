#include <iostream>
#include <string>


using namespace std;

enum enGameChoice { Stone = 1, Paper, Scissors };
enum enWinner { Player1 = 1, Computer, Draw };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName = "";
};

struct stGameResults
{
	short GameRounds = 0;
	short Player1Wins = 0;
	short Computer2WinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

enGameChoice ReadPlayerChoice()
{
	short choice;
	do
	{
		cout << "\nYour Choice: [1]: Stone, [2]: Paper, [3]: Scissors ? ";
		cin >> choice;

	} while (choice < 1 || choice > 3);

	return (enGameChoice)choice;
}

enWinner GetRoundWinner(enGameChoice Player1Choice, enGameChoice ComputerChoice)
{
	if (Player1Choice == ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (Player1Choice)
	{
	case enGameChoice::Stone:
		if (ComputerChoice == enGameChoice::Scissors)
			return enWinner::Player1;
		break;

	case enGameChoice::Paper:
		if (ComputerChoice == enGameChoice::Stone)
			return enWinner::Player1;
		break;

	case enGameChoice::Scissors:
		if (ComputerChoice == enGameChoice::Paper)
			return enWinner::Player1;
		break;
	}

	return enWinner::Computer;
}

void SetScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("Color 2F");
		break;

	case enWinner::Computer:
		system("Color 4F");
		cout << "\a";
		break;

	case enWinner::Draw:
		system("Color 6F");
		break;
	}
}

string ChoiceToString(enGameChoice Choice)
{
	switch (Choice)
	{
	case enGameChoice::Stone:
		return "Stone";
	case enGameChoice::Paper:
		return "Paper";
	case enGameChoice::Scissors:
		return "Scissors";
	default:
		return "";
	}
}

string WinnerToString(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		return "Player 1";
	case enWinner::Computer:
		return "Computer";
	case enWinner::Draw:
		return "Draw";
	default:
		return "";
	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	SetScreenColor(RoundInfo.Winner);
	cout << "\n------------ __Round [" << RoundInfo.RoundNumber << "]__ ------------\n";
	cout << "Player1 Choice : " << ChoiceToString(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice: " << ChoiceToString(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
	cout << "---------------------------------------\n";
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;

	short Player1WinCount = 0;
	short ComputerWinCount = 0;
	short DrawCount = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";

		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = (enGameChoice)RandomNumber(1, 3);
		RoundInfo.Winner = GetRoundWinner(RoundInfo.Player1Choice, RoundInfo.ComputerChoice);
		RoundInfo.WinnerName = WinnerToString(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinCount++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinCount++;
		else
			DrawCount++;

		PrintRoundResults(RoundInfo);
	}

	stGameResults GameResults;
	GameResults.GameRounds = HowManyRounds;
	GameResults.Player1Wins = Player1WinCount;
	GameResults.Computer2WinTimes = ComputerWinCount;
	GameResults.DrawTimes = DrawCount;

	if (Player1WinCount > ComputerWinCount)
		GameResults.GameWinner = enWinner::Player1;
	else if (ComputerWinCount > Player1WinCount)
		GameResults.GameWinner = enWinner::Computer;
	else
		GameResults.GameWinner = enWinner::Draw;

	GameResults.WinnerName = WinnerToString(GameResults.GameWinner);

	return GameResults;
}


void ShowGameOverScreen()
{
	cout << "\n--------------------------------------------------\n";
	cout << "                 +++ Game Over +++                \n";
	cout << "--------------------------------------------------\n";
}

void PrintGameResults(stGameResults GameResults)
{
	cout << "\n----------------- [ Game Results ] -----------------\n";
	cout << "Game Rounds        : " << GameResults.GameRounds << endl;
	cout << "Player1 Win times  : " << GameResults.Player1Wins << endl;
	cout << "Computer Win times : " << GameResults.Computer2WinTimes << endl;
	cout << "Draw times         : " << GameResults.DrawTimes << endl;
	cout << "Final Winner       : " << GameResults.WinnerName << endl;
	cout << "----------------------------------------------------\n";
}


void ResetScreen()
{
	system("cls");
	system("color 0F"); 
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();

		short HowManyRounds = 0;
		cout << "How Many Rounds 1 to 10 ? ";
		cin >> HowManyRounds;

		stGameResults GameResults = PlayGame(HowManyRounds);

		ShowGameOverScreen();
		PrintGameResults(GameResults);

		cout << "\nDo you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}
