#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class HangmanWords
{
private:
    vector<string> words;

public:
    HangmanWords(const string &filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "Error opening file." << endl;
            exit(1);
        }

        // Initialize a vector with some words
        string word;

        while (file >> word)
        {
            words.push_back(word);
        }
        file.close();

        if (words.empty())
        {
            cerr << "No words found in the file." << endl;
            exit(1);
        }
    }

    string getRandomWord()
    {
        // Seed the random number generator
        srand(time(0));

        // Generate a random index within the bounds of the vector
        int randomIndex = rand() % words.size();

        // Retrieve and print the random word
        return words[randomIndex];
        // cout << "Random word: " << randomWord << endl;
    }
};

bool check_win(string word, string guessed_letters)
{
    for (char letter : word)
    {
        if (guessed_letters.find(letter) == string::npos)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    cout << "Welcome to My Hangman Game!\n";
    cout << "Are you ready to start? (Press Enter to continue)\n";
    cin.ignore(); // Waits for the user to press Enter
    cout << "Good luck!\n";

    // // Initialize a vector with some words
    // vector<string> words = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape"};

    HangmanWords game("hangmanWords.txt");
    string randomWord = game.getRandomWord();

    // The amount of guesses that player has
    int tries = 6;

    // The letters that user has guessed already
    string guessed_letters;

    while (tries > 0)
    {
        string guess;
        cout << "Guess a Letter: ";
        cin >> guess;

        if (guessed_letters.find(guess) != string::npos)
        {
            cout << "You have already guessed this letter. Try again.\n";
        }
        else if (randomWord.find(guess) != string::npos)
        {
            guessed_letters += guess;

            if (check_win(randomWord, guessed_letters))
            {
                cout << "Congratulations! You've won!\n";
                cout << "The word was: " << randomWord << endl;
                break;
            }

            cout << "Good guess! Keep Going!\n";
        }
        else
        {
            tries--;
            guessed_letters += guess;
            cout << "Wrong guess. Tries left: " << tries << "\n";
        }

        if (tries == 0)
        {
            cout << "Sorry, you've run out of tries. You lost.\n";
            cout << "The word was: " << randomWord << endl;
        }
    }

    return 0;
}
