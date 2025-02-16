#include <iostream>
#include <algorithm>
#include <files.hpp>
#include <ctime>
#include <cstring>

std::string checkWord(std::string const& trial, std::string word, std::string &indice);
std::string menuOptions(std::string const& arg, std::string const& word);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    std::vector<std::string> words = getWords();
    std::string letters;
    for (char i = 0; i < 26; i++) letters.push_back(i + 'a');
    std::string word = words[rand() % words.size()];
    std::string trial;
    const unsigned short maxTrial = 5;
    unsigned short actualTrial = 0;

    if (argc == 2 && strcmp("cheat", argv[1]) == 0)
    {
        std::cout << word << std::endl;
    }
    
    do
    {   
        std::cout << "Entrez un mot (essais n°" << actualTrial << "): ";
        std::cin >> trial;

        // if the word begin with ., it's a command
        if (trial[0] == '.')
        {
            std::cout << menuOptions(trial, word);
            continue;
        }
        else if (trial.size() != 5)
        {
            std::cout << "Entrez un mot de 5 lettes." << std::endl;
            continue;
        }
        else if (trial == word)
        {
            std::cout << "Bravo, vous avez trouvé le mot : " << word << std::endl;
            break;
        }
        else if(actualTrial < maxTrial - 1)
        {
            if (std::find(words.begin(), words.end(), trial) == words.end()) {
                std::cout << "Le mot n'existe pas dans le dictionnaire." << std::endl;
                continue;
            }

            std::string indice = checkWord(trial, word, letters);
            
            std::cout << "Ce n'est pas le bon mot, réessayez. (" << indice << ")" << std::endl;

            std::cout << letters << std::endl;
        }
        else
        {
            std::cout << "Perdu ! Le mot était " << word << std::endl;
        }
        
        actualTrial++;
    } while (actualTrial < maxTrial);
    
    return EXIT_SUCCESS;
}

std::string checkWord(std::string const& trial, std::string word, std::string &letters)
{
    std::string result(5, '-');

    for (size_t i = 0; i < trial.size(); i++)
    {
        size_t pos = word.find(trial[i]);
        if (pos == i)
        {
            result[i] = trial[i];
            word[pos] = '0';
        }
        else if (pos != std::string::npos)
        {
            result[i] = '*';
            word[pos] = '0';
        }
        else
        {
            result[i] = '-';
            if (letters.find(trial[i]) != std::string::npos)
            {
                letters[letters.find(trial[i])] = '-';
            }
        }

    }
    return result;
}

std::string menuOptions(std::string const& arg, std::string const& word)
{
    if (arg == ".exit" || arg == ".quit")
    {
        std::cout << "Abandon du jeu\nLe mot était : " + word << std::endl;
        exit(0);
    }
    else if (arg == ".help")
    {
        return "Commandes disponibles :\n"
        ".quit / .exit : Quitter le jeu\n"
        ".help : Afficher ce message\n"
        ".cheat : Afficher le mot à trouver\n"
        ".reload_dico : Retélécharger le dictionnaire\n";
    }
    else if (arg == ".cheat")
    {
        return "Le mot à trouver est : " + word + "\n";
    }
    else if (arg == ".reload_dico")
    {
        getWords(true);
        return "Dictionnaire rechargé\n";
    }
    
    return "Commande inconnue\n";
}