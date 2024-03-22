
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

string getRandomWord(const vector<string>& words) {
    srand(time(0));
    int index = rand() % words.size();
    return words[index];
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

    string wordToGuess = getRandomWord(words);

    const int maxAttempts = 7;
    int neuhadol = 0;
    vector<char> guessedChars;

    cout << "Vitej v hre Obesenec!" << endl;
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
        else {
            cout << "Neuhadol si!" << endl;
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
