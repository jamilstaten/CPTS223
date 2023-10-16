#include <map>
#include <iostream>
#include "TwitterData.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    string raw_data[5][6] = { {"rangerPower", "Smit", "Rick", "smitRick@gmail.com", "1117", "power lifting"},
                             {"kittyKat72", "Smith", "Kathryn", "kat@gmail.com", "56", "health"},
                             {"lexi5", "Anderson", "Alexis", "lexi5@gmail.com", "900", "education"},
                             {"savage1", "Savage", "Ken", "ksavage@gmail.com", "17", "president"},
                             {"smithMan", "Smith", "Rick", "rick@hotmail.com", "77", "olympics"} };

    TwitterData* twitter_data = new TwitterData[5];
    for (int i = 0; i < 5; ++i)
    {
        twitter_data[i].setUserName(raw_data[i][0]);
        twitter_data[i].setActualName(raw_data[i][2] + " " + raw_data[i][1]);
        twitter_data[i].setEmail(raw_data[i][3]);
        twitter_data[i].setNumTweets(stoi(raw_data[i][4]));
        twitter_data[i].setCategory(raw_data[i][5]);
    }

    // Scenario 1: Search based on UserName
    map<string, TwitterData> mapByUsername;
    for (int i = 0; i < 5; ++i)
    {
        mapByUsername[twitter_data[i].getUserName()] = twitter_data[i];
    }

    // Print the map content
    cout << "\n[UserName : TwitterData]\n";
    for (const auto& pair : mapByUsername)
    {
        cout << pair.first << " : " << pair.second.print() << endl;
    }

    // Find and print 'savage1'
    cout << "\nFind 'savage1':\n";
    if (mapByUsername.find("savage1") != mapByUsername.end())
    {
        cout << "savage1 : " << mapByUsername["savage1"].print() << endl;
        mapByUsername.erase("savage1");
    }
    else cout << "'savage1' not found.\n";

    // Scenario 2: Search based on EmailAddress
    map<string, TwitterData> mapByEmail;
    for (int i = 0; i < 5; ++i)
    {
        mapByEmail[twitter_data[i].getEmail()] = twitter_data[i];
    }

    // Print the map content
    cout << "\n[Email : TwitterData]\n";
    for (const auto& pair : mapByEmail)
    {
        cout << pair.first << " : " << pair.second.print() << endl;
    }

    // Find and print 'kat@gmail.com'
    cout << "\nFind 'kat@gmail.com':\n";
    if (mapByEmail.find("kat@gmail.com") != mapByEmail.end())
    {
        cout << "kat@gmail.com : " << mapByEmail["kat@gmail.com"].print() << endl;
        mapByEmail.erase("kat@gmail.com");
    }
    else cout << "'kat@gmail.com' not found.\n";

    delete[] twitter_data;
    return 0;
}
