#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

vector<string> words = { "apple", "banana", "cherry", "orange", "grape", "pineapple", "strawberry", "blueberry" };

string getRandomWord() {
    srand(time(0));
    int index = rand() % words.size();
    return words[index];
}

bool containsChar(string word, char guess) {
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

void displayWord(string word, vector<char> guessedChars) {
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
    const int maxAttempts = 7;
    int incorrectGuesses = 0;
    vector<char> guessedChars;
    string word = getRandomWord();

    cout << "Welcome to Hangman!" << endl;
    cout << "Try to guess the word." << endl;

    while (incorrectGuesses < maxAttempts) {
        cout << drawHangman(incorrectGuesses) << endl;
        displayWord(word, guessedChars);

        if (guessedChars.size() > 0) {
            cout << "Guessed letters: ";
            for (char letter : guessedChars) {
                cout << letter << " ";
            }
            cout << endl;
        }

        cout << "Enter a letter: ";
        char guess;
        cin >> guess;
        cin.ignore(); // Ignore newline character

        if (containsChar(word, guess)) {
            cout << "Correct guess!" << endl;
        }
        else {
            cout << "Incorrect guess!" << endl;
            incorrectGuesses++;
        }

        guessedChars.push_back(guess);

        bool foundAllLetters = true;
        for (char letter : word) {
            if (find(guessedChars.begin(), guessedChars.end(), letter) == guessedChars.end()) {
                foundAllLetters = false;
                break;
            }
        }

        if (foundAllLetters) {
            cout << "Congratulations! You guessed the word: " << word << endl;
            break;
        }
    }

    if (incorrectGuesses >= maxAttempts) {
        cout << drawHangman(incorrectGuesses) << endl;
        cout << "You lose! The word was: " << word << endl;
    }

    return 0;
}
