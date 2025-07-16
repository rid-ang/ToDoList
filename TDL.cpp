#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <thread>
 
#define clearBuffer() std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')
 
using std::cout;
using std::endl;
using std::string;
using std::vector;
namespace fs = std::filesystem;
 
 
/*
 
--------------------------------------------------------------------------
 
*/
 
 
/* Declerations */
 
void inMenu();
 
// ----------- //
 
class Task {
    public:
        int id;
        string content;
 
        /* Constructors */
        Task()
        {
            id = 0;
            content = "Empty";
        }
 
        Task(int id, string content)
        {
            this->id= id;
            this->content= content;
 
        }
 
};
 
class TDL{
    public:
        int tNumber;
        vector<Task> tasks;
        TDL(){
            this->tNumber = 1;
            tasks.emplace_back(Task());
        }
 
};
 
TDL createList()
{
    clearBuffer();
    TDL l1;
    string name;
    string fullname;
    cout << "Please type the name of the list, less than 40 characters!" << endl;
    bool flag=false;
    do {
        flag = false;
        getline(std::cin, name);
        if(name.length() >=40){
            cout << "Please try again, the name you've selected is too big!" << endl;
            flag = true;
            continue;
        }
        int i=0;
        while(i<name.length())
        {
            if(isalnum(name[i])){
                i++;}
            else{
                cout << "Please try again, you cannot use special characters!" << endl;
                flag = true;
                break;
            }
        }
        fullname = "lists/" + name + ".txt";
        if(fs::exists(fullname))
        {
            flag = true;
            cout << "The same file exists." << endl;
        }
    } while(flag == true);
 
    std::fstream activeList;
    activeList.open(fullname, std::ios::out);
    if(!activeList.is_open())
        cout << "Couldn't open file..." << endl;
    else {
        cout << name << " has been created succesfully!" << endl;
        cout << "Press any button to continue..." << endl;
        char x;
        x = getchar();
    }
 
    activeList.close();
    return l1;
}
 
 
/* Global variables */
string path = "./lists";
string activeDir;
int selectionIndex=0;
vector<TDL> tdls;
 
/* ---------------  */
 
 
void addTask(TDL &l1)
{
 
    std::fstream fp;
    fp.open(activeDir, std::ios::app);
    if(!fp){
        std::cerr << "Error" << endl;
        return;
    }
    std::system("cls");
    cout << "Type the task:" << endl;
    clearBuffer();
    string ans2;
    getline(std::cin,ans2);
    fp << l1.tNumber << ". "<< ans2 << '\n';
    fp.close();
    l1.tasks.emplace_back(Task(l1.tNumber,ans2));
    cout << "Task with ID: " << l1.tNumber++ << " and content: \"" << ans2 << "\" was added succesfully" << endl;
    }
 
void listTasks()
    {
        std::system("cls");
        std::ifstream fp;
        fp.open(activeDir);
        if(!fp){
            std::cerr << "Error" << endl;
            return;
        }
        string line="";
        while(getline(fp,line)){
            cout << line << endl;
        }
        cout << "Press any button to continue..." << endl;
        clearBuffer();
        char x;
        x = getchar();
 
        }
 
 
 
void removeTask(TDL& l1)
{
    if(l1.tasks.size() > 1){
        int ans=0;
        std::system("cls");
        std::ifstream fps;
        fps.open(activeDir);
        if(!fps){
            std::cerr << "Error" << endl;
            return;
        }
        string lin="";
        while(getline(fps,lin)){
            cout << lin << endl;
        }

        cout << "Which of the tasks above would you like to remove?" << endl;
        std::cin >> ans;
        std::ifstream fp;
        while(std::cin.fail() || ans > l1.tNumber) {
            std::cin.clear();
            clearBuffer();
            std::system("cls");
            cout << "Invalid input" << endl;
            std::cin >> ans;
        }
        string chr = std::to_string(ans);
        fp.open(activeDir);
        if(!fp){
            std::cerr << "Error" << endl;
            return;
        }
        string line ="";
        std::fstream fpt;
        fpt.open("tempFile.txt", std::ios::out);
        if(!fpt) {
            std::cerr << "Error creating the temp file!" << endl; return;
        }

 
        while(getline(fp,line))
        {
            if(line.substr(0, chr.size()) != chr)
            {
                fpt << line << '\n';
            }
        }
 
        fp.close();
        fpt.close();
        std::ofstream fp2;
        std::ifstream fpt2;
        fp2.open(activeDir, std::ios::out);
        fpt2.open("tempFile.txt");
        if(!fp2 || !fpt2){
            std::cerr << "Error opening the file" << endl; return;
        }
 
        while(getline(fpt2,line)){
            fp2 << line << '\n';
        }
 
        fpt2.close();
        if(std::remove("tempFile.txt") == 0){
            for(int i = 0 ; i<l1.tasks.size(); i++){
                if(l1.tasks[i].id == ans){
                    l1.tasks.erase(l1.tasks.begin() + ans);
                    cout << "Your task has been marked complete!" << endl;
                }
                    
             }
           
        }
 
        else
        std::cerr << "Error!";
        fp2.close();
        
        
    }
 
    else{
        cout << "There aren't any tasks in this list!" << endl;
        cout << "Press any button to continue..." << endl;
        clearBuffer();
        char x;
        x = getchar();
    }
 
 
 
 
}  
 
void menu(TDL &l1){
    std::system("cls");
    cout << "Welcome to the TDL! ";
    int ans;
    while(true){
        cout << "Please select one of the options below." 
        << endl << "1. See my to do list" << endl << 
        "2. Mark task completed" << endl << "3. Add to my to do list" 
        << endl << "4. Go Back" << endl;
        std::cin >> ans;
        if (std::cin.fail() || (ans>4 || ans<1)) {
            std::cin.clear();
            clearBuffer();
            std::system("cls");
            cout << "Invalid input, please enter a number between 1 and 4." << endl;
            continue;
            }
        else if(ans>=1 && ans<=4) {
            if(ans==1){
                listTasks();
            }
 
            if(ans==2){
                removeTask(l1);
            }
 
            if(ans==3){
                addTask(l1);
            }
            if(ans==4)
                inMenu();
        }
    }
}
 
 
 
void TDLSelection(){
    std::system("cls");
    string line;
    int i=0,ans=0;
    tdls.emplace_back(TDL());
    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            if(fs::is_empty(path)){
                cout << "No lists!" << endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            else{
                vector<fs::directory_entry> entries;
                cout << "Your lists:" << endl;
                for (const auto& entry : fs::directory_iterator(path)) 
                {
                    entries.push_back(entry);
                    cout << ++i << ". " << entry.path().filename().string() << endl;
                    TDL l1;
                    std::fstream fin;
                    fin.open(entry.path().string(),std::ios::in);
                    if(!fin){
                        cout << "File couldn't be opened!" << endl;
                    }
                    else{
                        string extractedString,iString;
                        while(getline(fin,line))
                        {
                            std::size_t pos = line.find(' '); 
                            if (pos != string::npos) {
                                iString = line.substr(0,pos-1);
                                extractedString = line.substr(pos + 1); }
                            int num = std::stoi(iString);
                            l1.tasks.emplace_back(Task(num,extractedString));
                            l1.tNumber=num+1;
                            
                        }
 
 
                    }
 
 
                    fin.close();
                    tdls.push_back(l1);
 
                }
 
                cout << i+1 <<". Go back" << endl;
                cout << "Please type the index of the list you want to choose" << endl;
                int ans;
                std::cin >> ans;
                while (std::cin.fail() || (ans>4 || ans<1)) {
                    std::cin.clear();
                    clearBuffer();
                    cout << "Please enter proper index." << endl;
                    std::cin>> ans;
                }
                while(ans>i+1 || ans <1){
                    cout << "Please enter proper index." << endl;
                    std::cin>> ans;
                }
 
 
                if (ans > 0 && ans <= entries.size()) 
                {
                    auto chosen_entry = entries[ans - 1];
                    activeDir = chosen_entry.path().string();
                    cout << "You selected: " << chosen_entry.path().filename().string() << endl;
                    selectionIndex = ans;
                } 
 
                else if(ans == entries.size()+1) 
                {
                    inMenu();
 
                }
 
 
                else 
                {
                    cout << "Invalid index" << endl;
                }
            }
 
        } else {
            cout << "The directory doesn't exist. Creating one." << endl;
            fs::create_directory(path);
        }
    } catch (const fs::filesystem_error& err) {
        std::cerr << "Filesystem error: " << err.what() << endl;
    }
}
 
 
void deleteList(){
    std::system("cls");
    string path = "./lists";
    string line;
    int i=0,ans=0;
    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            if(fs::is_empty(path))
                cout << "No lists!" << endl;
            else{
                vector<fs::directory_entry> entries;
                cout << "Your lists:" << endl;
                for (const auto& entry : fs::directory_iterator(path)) 
                {
                    entries.push_back(entry);
                    cout << ++i << ". " << entry.path().filename().string() << endl;
 
                }
 
                cout << "Please type the index of the list you want to delete" << endl;
                int ans;
                std::cin >> ans;
                while (std::cin.fail() || (ans>4 || ans<1)) {
                    std::cin.clear();
                    clearBuffer();
                    cout << "Please enter proper index." << endl;
                    std::cin>> ans;
                }
                while(ans>i || ans <1){
                    cout << "Please enter proper index." << endl;
                    std::cin>> ans;
                }
 
 
                if (ans > 0 && ans <= entries.size()) {
                    auto chosen_entry = entries[ans - 1];
                    if(fs::remove(chosen_entry.path()))
                        cout << "You deleted: " << chosen_entry.path().filename().string() << endl;
                        selectionIndex = -1;
                        activeDir = ""; 
                    clearBuffer();
                    cout << "Press any button to continue..." << endl;
                    char x;
                    x = getchar();
 
                } else {
                    cout << "Invalid index" << endl;
                }
            }
 
        } else {
            std::cerr << "Such directory doesn't exist." << endl;;
        }
    } catch (const fs::filesystem_error& err) {
        std::cerr << "Filesystem error: " << err.what() << endl;
    }
}
 
void inMenu(){
    if (!fs::exists("./lists"))
    fs::create_directory("./lists");
    int ans;
    bool flag=true;
    while(flag){
        std::system("cls");
        cout << "What do you want to do?" << endl;
        cout << "1. Create a new list" << endl;
        cout << "2. See my lists" << endl;
        cout << "3. Delete a list" << endl;
        cout << "4. Exit the program" << endl;
        std::cin >> ans;
        if (std::cin.fail() || (ans>4 || ans<1)) {
            std::cin.clear();
            clearBuffer();
            std::system("cls");
            cout << "Invalid input, please enter a number between 1 and 4." << endl;
            continue;
            }
        else if(ans>=1 && ans<=4) {
            if(ans==1){
                TDL l1 = createList();
            }
 
            if(ans==2){
                TDLSelection();
                if(!fs::is_empty(path)){
                    menu(tdls[selectionIndex]);
                    flag = false; }
            }
 
            if(ans==3){
                deleteList();
            }
            if(ans==4){ 
                cout << "Terminating program...";
                exit(1);
            }
        }
 
 
 
    }
 
 
}
 
 
 
 
 
 
 
int main(){
    inMenu();
 
 
}
