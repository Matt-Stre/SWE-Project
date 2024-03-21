#include <iostream>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class volunteer {
public:
    string name;
    string phoneNumber;
    string description;
    vector<string> keywordList;

    void addKeyword(string keyword);

};


void volunteer::addKeyword(string keyword) {
    this->keywordList.push_back(keyword);
}

vector<volunteer> getmatches(vector<string> keywordVector, vector<volunteer> volunteerOpportunities) {
    vector<volunteer> volVector;
    bool volAdded = false; //lets us break out of 3 loops if we add the opportunity
    for (int i = 0; i < volunteerOpportunities.size(); i++) { // for each volunteering opportunity
        volAdded = false;
        for (int j = 0; j < volunteerOpportunities[i].keywordList.size(); j++) { // for each keyword that that opportunity has
            for (int x = 0; x < keywordVector.size(); x++) { //for each user selected keyword
                if (volunteerOpportunities[i].keywordList[j] == keywordVector[x]) { //if the keywords match
                    volVector.push_back((volunteerOpportunities[i])); //add volunteering opportunity to our vector
                    volAdded = true;
                    break;
                }
                if (volAdded) {
                    break;
                }

            }
            if (volAdded) {
                break;
            }
        }
    }

    return volVector;
}


int main() {
    
  
    fstream fout;
    fout.open("Database.csv", ios::in | ios::app);
    string word;
    vector<volunteer> volunteerOpportunities;
    getline(fout, word); //skip first row

    
    while (getline(fout, word)) {
        string name, phoneNumber, description;
        volunteer newOpp;
        stringstream myword(word);

        //name
        getline(myword, word, ','); 
        if (word == "") { // otherwise an empty line is added at the end
            break;
        }
        newOpp.name = word;

        //phone number
        getline(myword, word, ','); 
        newOpp.phoneNumber = word;

        //description
        getline(myword, word, ','); 
        newOpp.description = word;
        

        //keywords
        string temp,temp2;
        getline(myword, temp, '\n');
        stringstream mystream(temp);
        while (getline(mystream, temp2, ','))
        {
            temp2.erase(remove(temp2.begin(), temp2.end(), '"'), temp2.end()); //remove quotes
            temp2.erase(remove(temp2.begin(), temp2.end(), ' '), temp2.end()); //remove spaces
            newOpp.addKeyword(temp2);
        }
        


        volunteerOpportunities.push_back(newOpp);
    }
    /*
    //test output
    for (int i = 0; i < volunteerOpportunities.size(); i++) {
        cout << volunteerOpportunities[i].name << endl;
        cout << volunteerOpportunities[i].phoneNumber << endl;
        cout << volunteerOpportunities[i].description << endl;
        for (int j = 0; j < volunteerOpportunities[i].keywordList.size(); j++) {
            cout << volunteerOpportunities[i].keywordList[j] << endl;
        }
        cout << endl;
    }
    */

    //---READING KEYWORDS---//

    //getting keywords from ui TODO
    vector<string> keywordVector{ "temp", "dog", "cat" }; //test vector
    vector<volunteer> volVector = getmatches(keywordVector, volunteerOpportunities);

    
    
    //test output
    for (int i = 0; i < volVector.size(); i++) {
        cout << volVector[i].name << endl;
    }
    

    //---SENDING VOLUNTEERING OPPORTUNITIES TO UI---//
    
    //TODO


    return 0;
}