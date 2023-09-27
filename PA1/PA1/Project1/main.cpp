/*
Linked List:
Advantage: Linked list can easily have elements added and removed allowing really
easy insertion and deletion especially when creating the add and delete command function
Disadvantage: Each node requires additional memory which could cause memory overhead
if program is too large and leads to slower execuiton times
Array: 
Advantage: It was very useful that arrays allow random access making it easy to retrieve
profiles and excess memory inst being wasted because of use of array instead of other data structure
Disadvantage: The amout of profiles is fixed and deleting or inserting new profiles into the middle
of the array is either impossible or way too ineffecient
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Node.hpp"
#include <ctime>
#include <cstdlib>
#include <algorithm>

template <typename T1, typename T2>
class Node {
public:
    T1 command;
    T2 description;
    Node* next;

    Node(T1 c, T2 d) : command(c), description(d), next(nullptr) {}
};
// List class with two parameters
template <typename T1, typename T2>
class List {
private:
    Node<T1, T2>* head;
public:
    List() : head(nullptr) {}
    ~List();

    void insertAtFront(T1 command, T2 description);
    bool removeNode(T1 command);
    Node<T1, T2>* getRandomNode();
    Node<T1, T2>* getHead() const { return head; }
};

// Implement the List class member functions
template <typename T1, typename T2>
List<T1, T2>::~List() {
    Node<T1, T2>* current = head;
    while (current != nullptr) {
        Node<T1, T2>* next = current->next;
        delete current;
        current = next;
    }
}

template <typename T1, typename T2>
void List<T1, T2>::insertAtFront(T1 command, T2 description) {
    Node<T1, T2>* newNode = new Node<T1, T2>(command, description);
    newNode->next = head;
    head = newNode;
}

template <typename T1, typename T2>
bool List<T1, T2>::removeNode(T1 command) {
    Node<T1, T2>* current = head;
    Node<T1, T2>* prev = nullptr;

    while (current != nullptr) {
        if (current->command == command) {
            if (prev == nullptr) {
                head = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

template <typename T1, typename T2>
Node<T1, T2>* List<T1, T2>::getRandomNode() {
    int size = 0;
    Node<T1, T2>* current = head;
    while (current != nullptr) {
        size++;
        current = current->next;
    }

    int randomIndex = std::rand() % size;
    current = head;
    for (int i = 0; i < randomIndex; ++i) {
        current = current->next;
    }
    return current;
}

void loadCommands(List<std::string, std::string>& commandsList) {
    std::ifstream file("commands.csv");
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(",");
        std::string command = line.substr(0, pos);
        std::string description = line.substr(pos + 1);
        commandsList.insertAtFront(command, description);
    }
    file.close();
}

struct UserProfile {
    std::string name;
    int points;
};

void loadProfiles(std::vector<UserProfile>& profiles) {
    std::ifstream file("profiles.csv");
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(",");
        std::string name = line.substr(0, pos);
        int points = std::stoi(line.substr(pos + 1));
        profiles.push_back({ name, points });
    }
    file.close();
}

void saveProfiles(const std::vector<UserProfile>& profiles) {
    std::ofstream file("profiles.csv");
    for (const auto& profile : profiles) {
        file << profile.name << "," << profile.points << std::endl;
    }
    file.close();
}

bool isQuestionAsked(const std::vector<std::string>& askedQuestions, const std::string& question) {
    for (const auto& q : askedQuestions) {
        if (q == question) {
            return true;
        }
    }
    return false;
}

template <typename T1, typename T2>
void saveCommands(const List<T1, T2>& commandsList) {
    std::ofstream file("commands.csv");
    Node<T1, T2>* current = commandsList.getHead();  // Use the getter here
    while (current != nullptr) {
        file << current->command << "," << "\"" << current->description << "\"" << std::endl;
        current = current->next;
    }
    file.close();
}


int main() {
    std::srand(std::time(nullptr));
    List<std::string, std::string> commandsList;
    loadCommands(commandsList);

    std::vector<UserProfile> profiles;
    loadProfiles(profiles);
    int choice;

    do {
        std::cout << "Main Menu:\n";
        std::cout << "1. Game Rules\n";
        std::cout << "2. Play Game\n";
        std::cout << "3. Load Previous Game\n";
        std::cout << "4. Add Command\n";
        std::cout << "5. Remove Command\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Game Rules: Match Linux commands to their descriptions to earn points.\n";
            break;
        case 2: {
            std::string name;
            std::cout << "Enter your name: ";
            std::cin >> name;

            int numQuestions;
            std::cout << "Enter the number of questions (between 5 and 30): ";
            std::cin >> numQuestions;

            int points = 0;
            for (int i = 0; i < numQuestions; ++i) {
                Node<std::string, std::string>* questionNode = commandsList.getRandomNode();
                std::cout << "Command: " << questionNode->command << std::endl;

                // Get two random descriptions
                Node<std::string, std::string>* randomNode1 = commandsList.getRandomNode();
                while (randomNode1->command == questionNode->command) {
                    randomNode1 = commandsList.getRandomNode();
                }

                Node<std::string, std::string>* randomNode2 = commandsList.getRandomNode();
                while (randomNode2->command == questionNode->command || randomNode2->command == randomNode1->command) {
                    randomNode2 = commandsList.getRandomNode();
                }

                // Shuffle and display the three descriptions
                std::vector<std::string> options = { questionNode->description, randomNode1->description, randomNode2->description };
                std::random_shuffle(options.begin(), options.end());

                for (int j = 0; j < 3; ++j) {
                    std::cout << j + 1 << ". " << options[j] << std::endl;
                }

                int answer;
                std::cout << "Your answer: ";
                std::cin >> answer;

                if (options[answer - 1] == questionNode->description) {
                    std::cout << "Correct!\n";
                    points++;
                }
                else {
                    std::cout << "Incorrect!\n";
                    points--;
                }
            }

            profiles.push_back({ name, points });
            bool profileExists = false;
            for (auto& profile : profiles) {
                if (profile.name == name) {
                    profile.points += points;  // Update the points for the existing profile
                    profileExists = true;
                    break;
                }
            }
            if (!profileExists) {
                profiles.push_back({ name, points });  // Add a new profile if it doesn't exist
            }

            break;
        }

        case 3: {
            std::string name;
            std::cout << "Enter your profile name: ";
            std::cin >> name;

            int existingPoints = 0;
            bool profileFound = false;

            // Search for the profile in the profiles vector
            for (const auto& profile : profiles) {
                if (profile.name == name) {
                    existingPoints = profile.points;
                    profileFound = true;
                    break;
                }
            }

            if (!profileFound) {
                std::cout << "Profile not found. Returning to main menu.\n";
                break;
            }

            std::cout << "Welcome back, " << name << "! You have " << existingPoints << " points.\n";

            int numQuestions;
            std::cout << "Enter the number of questions (between 5 and 30): ";
            std::cin >> numQuestions;

            int points = existingPoints;
            for (int i = 0; i < numQuestions; ++i) {
                Node<std::string, std::string>* questionNode = commandsList.getRandomNode();
                std::cout << "Command: " << questionNode->command << std::endl;

                // Get two random descriptions
                Node<std::string, std::string>* randomNode1 = commandsList.getRandomNode();
                while (randomNode1->command == questionNode->command) {
                    randomNode1 = commandsList.getRandomNode();
                }

                Node<std::string, std::string>* randomNode2 = commandsList.getRandomNode();
                while (randomNode2->command == questionNode->command || randomNode2->command == randomNode1->command) {
                    randomNode2 = commandsList.getRandomNode();
                }

                // Shuffle and display the three descriptions
                std::vector<std::string> options = { questionNode->description, randomNode1->description, randomNode2->description };
                std::random_shuffle(options.begin(), options.end());

                for (int j = 0; j < 3; ++j) {
                    std::cout << j + 1 << ". " << options[j] << std::endl;
                }

                int answer;
                std::cout << "Your answer: ";
                std::cin >> answer;

                if (options[answer - 1] == questionNode->description) {
                    std::cout << "Correct!\n";
                    points++;
                }
                else {
                    std::cout << "Incorrect!\n";
                    points--;
                }
            }

            // Update the user's points in the profiles vector
            for (auto& profile : profiles) {
                if (profile.name == name) {
                    profile.points = points;
                    std::cout << "Your updated points: " << points << std::endl;
                    break;
                }
            }

            break;
        }


        case 4: {
            std::string command, description;
            std::cout << "Enter the command: ";
            std::cin >> command;
            std::cout << "Enter the description: ";
            std::cin >> description;
            commandsList.insertAtFront(command, description);
            std::cout << "Command succesfully added.";
            break;
        }
        case 5: {
            std::string command;
            std::cout << "Enter the command to remove: ";
            std::cin >> command;
            commandsList.removeNode(command);
            std::cout << "Command succesfully removed.";
            break;
        }
        case 6:
            saveProfiles(profiles);
            saveCommands(commandsList);
            std::cout << "Exiting the game.\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}

