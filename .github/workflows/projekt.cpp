#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

vector<char> usedLetters; // Zoznam už hádaných písmen

string getRandomWord(const vector<string>& words, int minLength, int maxLength) {
    vector<string> filteredWords;
    for (const string& word : words) {
        if (word.length() >= minLength && word.length() <= maxLength) {
            filteredWords.push_back(word);
        }
    }
    srand(time(0));
    int index = rand() % filteredWords.size();
    return filteredWords[index];
}

bool containsChar(const string& word, char guess) {
    return word.find(guess) != string::npos;
}

string drawHangman(int neuhadol) {
    string hangman;
    if (neuhadol == 1) {
        hangman = "  ____\n ║    ║\n ║\n ║\n ║\n_║_\n";
    }
    else if (neuhadol == 2) {
        hangman = "  ____\n |    |\n |    O\n |\n |\n_|_\n";
    }
    else if (neuhadol == 3) {
        hangman = "  ____\n |    |\n |    O\n |    |\n |\n_|_\n";
    }
    else if (neuhadol == 4) {
        hangman = "  ____\n |    |\n |    O\n |   /|\n |\n_|_\n";
    }
    else if (neuhadol == 5) {
        hangman = "  ____\n |    |\n |    O\n |   /|\\\n |\n_|_\n";
    }
    else if (neuhadol == 6) {
        hangman = "  ____\n |    |\n |    O\n |   /|\\\n |   /\n_|_\n";
    }
    else if (neuhadol == 7) {
        hangman = "  ____\n |    |\n |    O\n |   /|\\\n |   / \\\n_|_\n";
    }
    return hangman;
}

void displayWord(const string& word, const vector<char>& guessedChars) {
    for (char letter : word) {
        if (find(guessedChars.begin(), guessedChars.end(), letter) != guessedChars.end()) {
            cout << letter << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}

bool alreadyGuessed(char guess) {
    for (char letter : usedLetters) {
        if (letter == guess) {
            return true; // Písmeno už bolo hádané
        }
    }
    return false; // Písmeno ešte nebolo hádané
}

void addToUsedLetters(char guess) {
    usedLetters.push_back(guess); // Pridáme písmeno do zoznamu už hádaných
}

int main() {
    vector<string> words;
    string word;

    // Otvoríme súbor "slova.txt" na čítanie
    ifstream file("slova.txt");

    // Skontrolujeme, či sa súbor otvoril úspešne
    if (!file.is_open()) {
        cout << "Nepodarilo sa otvorit subor!" << endl;
        return 1;
    }

    // Načítame slová zo súboru do vektora
    while (file >> word) {
        words.push_back(word);
    }

    // Zatvoríme súbor
    file.close();

    int minLength, maxLength;
    char levelChoice;

    // Výber obtiažnosti na začiatku programu
    cout << "Vitej v hre Obesenec!" << endl;
    cout << "Vyber obtiaznost:" << endl;
    cout << "1 - Lahka uroven (4 pismena)" << endl;
    cout << "2 - Stredna uroven (5-6 pismen)" << endl;
    cout << "3 - Tazka uroven (7-10 pismen)" << endl;

    cin >> levelChoice;

    switch (levelChoice) {
    case '1':
        minLength = maxLength = 4;
        break;
    case '2':
        minLength = 5;
        maxLength = 6;
        break;
    case '3':
        minLength = 7;
        maxLength = 10;
        break;
    default:
        cout << "Nespravny vyber obtiaznosti. Ukoncujem program." << endl;
        return 1;
    }
    system("cls");

    string wordToGuess = getRandomWord(words, minLength, maxLength);

    const int maxAttempts = 7;
    int neuhadol = 0;
    vector<char> guessedChars;
    usedLetters.clear(); // Vyprázdnenie zoznamu už hádaných písmen

    cout << "Skus uhadnut skryte slovo." << endl;

    while (neuhadol < maxAttempts) {
        cout << drawHangman(neuhadol) << endl;
        displayWord(wordToGuess, guessedChars);

        if (!guessedChars.empty()) {
            cout << "Hadane pismena: ";
            for (char letter : guessedChars) {
                cout << letter << " ";
            }
            cout << endl;
        }
        cout << "Hadaj pismeno: ";
        char guess;
        cin >> guess;
        cin.ignore(); // Ignorujeme nový riadok

        if (containsChar(wordToGuess, guess)) {
            cout << "Spravne uhadnute!" << endl;
        }
        else if (alreadyGuessed(guess)) {
            cout << "Toto pismeno si uz mal!" << endl;
        }
        else {
            cout << "Neuhadol si!" << endl;
            addToUsedLetters(guess); // Pridáme písmeno do zoznamu už hádaných
            neuhadol++;
        }

        guessedChars.push_back(guess);

        bool foundAllLetters = true;
        for (char letter : wordToGuess) {
            if (find(guessedChars.begin(), guessedChars.end(), letter) == guessedChars.end()) {
                foundAllLetters = false;
                break;
            }
        }

        if (foundAllLetters) {
            cout << "Gratulujem! Uhadol si skryte slovo: " << wordToGuess << endl;
            break;
        }
    }

    if (neuhadol >= maxAttempts) {
        cout << drawHangman(neuhadol) << endl;
        cout << "Neuhadol si! Skryte slovo bolo: " << wordToGuess << endl;
    }

    return 0;
}
