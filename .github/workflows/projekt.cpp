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

string drawHangman(int incorrectGuesses) {
    string hangman;
    if (incorrectGuesses == 1) {
        hangman = "  ____\n |    |\n |\n |\n |\n_|_\n";
    }
    else if (incorrectGuesses == 2) {
        hangman = "  ____\n |    |\n |    O\n |\n |\n_|_\n";
    }
    else if (incorrectGuesses == 3) {
        hangman = "  ____\n |    |\n |    O\n |    |\n |\n_|_\n";
    }
    else if (incorrectGuesses == 4) {
        hangman = "  ____\n |    |\n |    O\n |   /|\n |\n_|_\n";
    }
    else if (incorrectGuesses == 5) {
        hangman = "  ____\n |    |\n |    O\n |   /|\\\n |\n_|_\n";
    }
    else if (incorrectGuesses == 6) {
        hangman = "  ____\n |    |\n |    O\n |   /|\\\n |   /\n_|_\n";
    }
    else if (incorrectGuesses == 7) {
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
        cout << "Nepodarilo sa otvoriť súbor!" << endl;
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
    int incorrectGuesses = 0;
    vector<char> guessedChars;

    cout << "Welcome to Hangman!" << endl;
    cout << "Try to guess the word." << endl;

    while (incorrectGuesses < maxAttempts) {
        cout << drawHangman(incorrectGuesses) << endl;
        displayWord(wordToGuess, guessedChars);

        if (!guessedChars.empty()) {
            cout << "Guessed letters: ";
            for (char letter : guessedChars) {
                cout << letter << " ";
            }
            cout << endl;
        }

        cout << "Enter a letter: ";
        char guess;
        cin >> guess;
        cin.ignore(); // Ignorujeme nový riadok

        if (containsChar(wordToGuess, guess)) {
            cout << "Correct guess!" << endl;
        }
        else {
            cout << "Incorrect guess!" << endl;
            incorrectGuesses++;
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
            cout << "Congratulations! You guessed the word: " << wordToGuess << endl;
            break;
        }
    }

    if (incorrectGuesses >= maxAttempts) {
        cout << drawHangman(incorrectGuesses) << endl;
        cout << "You lose! The word was: " << wordToGuess << endl;
    }

    return 0;
}
