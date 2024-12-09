#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <cctype>
#include <cstring>
#include <regex>
using namespace std;

void displayBoard(const vector<char>& board) {
    cout << "\n";
    for (int i = 0; i < 9; i += 3) {
        cout << " " << (board[i] == ' ' ? char('1' + i) : board[i]) << " | "
             << (board[i + 1] == ' ' ? char('1' + i + 1) : board[i + 1]) << " | "
             << (board[i + 2] == ' ' ? char('1' + i + 2) : board[i + 2]) << "\n";
        if (i < 6) cout << "---+---+---\n";
    }
    cout << "\n";
}


char checkWinner(const vector<char>& board) {
    const int winConditions[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Горизонтальные
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Вертикальные
        {0, 4, 8}, {2, 4, 6}             // Диагональные
    };

    for (const auto& condition : winConditions) {
        if (board[condition[0]] == board[condition[1]] &&
            board[condition[1]] == board[condition[2]] &&
            board[condition[0]] != ' ') {
            return board[condition[0]];
        }
    }

    for (const char& cell : board) {
        if (cell == ' ') return ' ';
    }

    return 'T'; // Ничья
}

void ticTacToe() {
    vector<char> board(9, ' ');
    char currentPlayer = 'X';

    cout << "Добро пожаловать в игру Крестики-Нолики!" << endl;
    cout << "Игрок X начинает. Выберите клетку (1-9):" << endl;

    bool gameOn = true;
    while (gameOn) {
        displayBoard(board);

        int move;
        cout << "Игрок " << currentPlayer << ", ваш ход: ";
        cin >> move;

        if (move < 1 || move > 9 || board[move - 1] != ' ') {
            cout << "Недопустимый ход. Попробуйте снова." << endl;
            continue;
        }

        board[move - 1] = currentPlayer;

        char winner = checkWinner(board);
        if (winner == 'X' || winner == 'O') {
            displayBoard(board);
            cout << "Игрок " << winner << " победил!" << endl << endl;
            gameOn = false;
        } else if (winner == 'T') {
            displayBoard(board);
            cout << "Ничья!" << endl << endl;
            gameOn = false;
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

bool isUnique(int num) {
    bool digits[10] = {false};
    while (num > 0) {
        int digit = num % 10;
        if (digits[digit]) return false;
        digits[digit] = true;
        num /= 10;
    }
    return true;
}

void checkNumber(int guess, int secret, int &contentMatch, int &positionMatch) {
    contentMatch = 0;
    positionMatch = 0;

    int guessDigits[4];
    int secretDigits[4];

    for (int i = 3; i >= 0; --i) {
        guessDigits[i] = guess % 10;
        secretDigits[i] = secret % 10;
        guess /= 10;
        secret /= 10;
    }

    for (int i = 0; i < 4; ++i) {
        if (guessDigits[i] == secretDigits[i]) {
            positionMatch++;
        }
        for (int j = 0; j < 4; ++j) {
            if (guessDigits[i] == secretDigits[j]) {
                contentMatch++;
                break;
            }
        }
    }
}

void findNumber() {
    vector<int> possibleNumbers;
    for (int i = 1000; i <= 9999; ++i) {
        if (isUnique(i)) {
            possibleNumbers.push_back(i);
        }
    }

    int attemptCount = 0;
    bool found = false;

    while (!found && !possibleNumbers.empty()) {
        int guess = possibleNumbers[0];
        attemptCount++;

        cout << endl << "Попытка #" << attemptCount << ": " << guess << endl;
        cout << "Запишите правильные числа и правильное количество позиций: ";
        int contentMatch, positionMatch;
        cin >> contentMatch >> positionMatch;

        if (positionMatch == 4) {
            cout << endl << "Число найдено: " << guess << endl;
            cout << "Количество итераций: " << attemptCount << endl;
            found = true;
        }
        else {
            vector<int> newPossibleNumbers;
            for (int num : possibleNumbers) {
                int cm, pm;
                checkNumber(num, guess, cm, pm);
                if (cm == contentMatch && pm == positionMatch) {
                    newPossibleNumbers.push_back(num);
                }
            }
            possibleNumbers = newPossibleNumbers;
        }
    }

    if (!found) {
        cout << "Число не найдено." << endl;
    }
}

void findNumber1() {
    cout << "Правила игры:" << endl;
    cout << "Вам нужно найти спрятанное число от 1 до 10, компьютер скрывает число, а вы должны найти число задавая вопросы." << endl;
    cout << "Пример:" << endl << "Вы задаете вопрос '< 5'" << endl << "Компьютер возвращает вам True или False в зависимости от спрятанного числа." << endl;
    cout << "Если вы догадываетесь что какое-либо число правильный ответ вы должны ввести в таком формате: 'x', x = ваше число" << endl;
    cout << "В случае если ваш ответ правильно, игра завершится!" << endl << endl;

    unsigned short int choiceNumber = rand() % 10, temp, i = 0;
    char question;
    string inputLine;

	bool end = false;
	while (!end) {
    	cout << "Ваш вопрос или ответ: "; getline(cin, inputLine);
    	regex numberRegex("^[0-9]+$");
    	if (!inputLine.empty() && !isdigit(inputLine[0])) {
    	    question = inputLine[0];
    	    temp = stoi(inputLine.substr(2));
    	    i++;
    	    
    	    if (question == '<' && choiceNumber < temp) cout << "True\n";
    	    else if (question == '<' && !(choiceNumber < temp)) cout << "False\n";
    	    else if (question == '>' && choiceNumber > temp) cout << "True\n";
    	    else if (question == '>' && !(choiceNumber > temp)) cout << "False\n";
    	    else if (question == '=' && choiceNumber == temp) {cout << "Вы нашли число! Спасибо за игру! Количество попыток: " << i << endl << endl; end = true;}
    	    else if (question == '=' && choiceNumber != temp) cout << "False\n";
    	}
    	else if (!inputLine.empty() && regex_match(inputLine, numberRegex)) {
    	    temp = stoi(inputLine);
    	    if (temp > 10) cout << "Введите число от 1 до 10\n";
    	    else {
    	        if (temp == choiceNumber) {cout << "Вы нашли число! Спасибо за игру! Количество попыток: " << i << endl << endl; end = true;}
    	        else {cout << "False\n"; i++;}
    	    }
    	}
    }
}

void findNumber2() {
    cout << "Правила игры:" << endl;
    cout << "Вам нужно найти спрятанное число от 1 до 100, компьютер скрывает число, а вы должны найти число задавая вопросы." << endl;
    cout << "Пример:" << endl << "Вы задаете вопрос '< 50'" << endl << "Компьютер возвращает вам True или False в зависимости от спрятанного числа." << endl;
    cout << "Если вы догадываетесь что какое-либо число правильный ответ вы должны ввести в таком формате: 'x', x = ваше число" << endl;
    cout << "В случае если ваш ответ правильно, игра завершится!" << endl << endl;

    unsigned short int choiceNumber = rand() % 100, temp, i = 0;
    char question;
    string inputLine;

	bool end = false;
	while (!end) {
    	cout << "Ваш вопрос или ответ: "; getline(cin, inputLine);
    	regex numberRegex("^[0-9]+$");
    	if (!inputLine.empty() && !isdigit(inputLine[0])) {
    	    question = inputLine[0];
    	    temp = stoi(inputLine.substr(2));
    	    i++;
    	    
    	    if (question == '<' && choiceNumber < temp) cout << "True\n";
    	    else if (question == '<' && !(choiceNumber < temp)) cout << "False\n";
    	    else if (question == '>' && choiceNumber > temp) cout << "True\n";
    	    else if (question == '>' && !(choiceNumber > temp)) cout << "False\n";
    	    else if (question == '=' && choiceNumber == temp) {cout << "Вы нашли число! Спасибо за игру! Количество попыток: " << i << endl << endl; end = true;}
    	    else if (question == '=' && choiceNumber != temp) cout << "False\n";
    	}
    	else if (!inputLine.empty() && regex_match(inputLine, numberRegex)) {
    	    temp = stoi(inputLine);
    	    if (temp > 100) cout << "Введите число от 1 до 100\n";
    	    else {
    	        if (temp == choiceNumber) {cout << "Вы нашли число! Спасибо за игру! Количество попыток: " << i << endl << endl; end = true;}
    	        else {cout << "False\n"; i++;}
    	    }
    	}
    }
}

void findNumberMenu() {
	unsigned short int n;
	cout << endl << "Добро пожаловать в игру найди число" << endl;
	cout << "Пожалуйста выберите диапазон поиска для игры:" << endl;
	cout << "- если хотите от 1 до 10, то введите 1" << endl;
	cout << "- если хотите от 1 до 100, то введите 2" << endl;
	cout << "Ваш выбор: "; cin >> n;
	cin.ignore();
	if (n == 1) findNumber1();
	else if (n == 2) findNumber2();
	else cout << "Ошибка! Перезапустите игру!";
}

int main() {
    srand(time(0));
    bool end = false;
    while (!end) {
        unsigned short int gamenum;
        cout << "Выберите игру:" << endl;
        cout << "1. Корова-бык" << endl;
        cout << "2. Найди число" << endl;
        cout << "3. Крестики-Нолики" << endl;
        cout << endl << "Чтобы выйти из игры введите 0" << endl;
        cout << endl << "Наберите код игры: "; cin >> gamenum;

        if (gamenum == 1) findNumber();
        else if (gamenum == 2) findNumberMenu();
        else if (gamenum == 3) ticTacToe();
        else if (gamenum == 0) end = true;
        else cout << endl << "Ошибка, игра с данным кодом не найдено!" << endl;
    }
}
