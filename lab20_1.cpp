#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream file(filename);
    char name[100];
    string namess;
    int score1, score2, score3;
    int i = 0;
    while (getline(file, namess)) {
        char grade[] = "%[^:]: %d %d %d";
        sscanf(namess.c_str(), grade, name, &score1, &score2, &score3);
        names.push_back(name);
        scores.push_back(score1 + score2 + score3);
        grades.push_back(score2grade(scores[i]));
        i++;
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cin >> command;
    if(toUpperStr(command) == "GRADE" or toUpperStr(command) == "NAME"){
    cin.ignore();
    getline(cin,key);
    }
}

void searchName(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key){
    bool found = false;
    for(size_t i = 0; i < names.size(); ++i){
        if(toUpperStr(names[i]) == toUpperStr(key)){
            found = true;
            cout << "---------------------------------" << endl;
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------" << endl;
        }
    }
    if(!found){
        cout << "---------------------------------" << endl;
        cout << "Cannot found." << endl;
        cout << "---------------------------------" << endl;
    }
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for (size_t i = 0; i < names.size(); ++i) {
        if (grades[i] == key[0]) {
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    } 
    if (!found) {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
 
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}