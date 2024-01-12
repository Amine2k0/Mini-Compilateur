#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include <Windows.h>
#include <shlobj.h>
#include <sstream>
#include <iomanip>
#include <unordered_set>
#include <functional>

using namespace std;

class Transition {
public:
    int et_dep;
    int et_arr;
    char sym;
};

class Automate {
public:
    vector<char> Alphabet;
    int EtatInitial;
    vector<int> EtatsFinaux;
    vector<Transition> Trans;

    Automate() {
        EtatInitial = 0;
    }

    void reset() {
        Alphabet.clear();
        EtatInitial = 0;
        EtatsFinaux.clear();
        Trans.clear();
    }

    void lire() {
        int N_alph;
        int N_EF;
        int N_trans;

        cout << "Saisir le nombre d'alphabet: ";
        cin >> N_alph;
        Alphabet.resize(N_alph);

        for (int i = 0; i < N_alph; i++) {
            cout << "Saisir alphabet: ";
            cin >> Alphabet[i];
        }

        cout << "Saisir Etat initial: ";
        cin >> EtatInitial;

        cout << "Saisir le nombre d'etats finaux: ";
        cin >> N_EF;
        EtatsFinaux.resize(N_EF);

        for (int i = 0; i < N_EF; i++) {
            cout << "Saisir Etat final: ";
            cin >> EtatsFinaux[i];
        }

        cout << "Saisir le nombre de transitions: ";
        cin >> N_trans;
        Trans.resize(N_trans);

        for (int i = 0; i < N_trans; i++) {
            cout << "Saisir etat depart: ";
            cin >> Trans[i].et_dep;

            cout << "Saisir etat arrive: ";
            cin >> Trans[i].et_arr;

            cout << "Saisir symbole: ";
            cin >> Trans[i].sym;
        }
    }
    void afficher() const {
        cout << "Alphabets: ";
        for (char c : Alphabet) {
            cout << c << " ";
        }
        cout << std::endl;

        cout << "Etat initial: " << EtatInitial << std::endl;

        cout << "Etats finaux: ";
        for (int etat : EtatsFinaux) {
            cout << etat << " ";
        }
        cout << std::endl;

        cout << "Transitions:" << std::endl;
        for (const Transition& trans : Trans) {
            cout << "Etat depart: " << trans.et_dep << ", ";
            cout << "Etat arrive: " << trans.et_arr << ", ";
            cout << "Symbole: " << trans.sym << std::endl;
        }
    }
    bool check(string A) const {
        const char* charArray = A.c_str();
        int Etat = EtatInitial;
        string desktopPath = "c:/Users/saide/OneDrive/Desktop/Compilation_tests/";
        string file = desktopPath + "Tested_Words.txt";
        ofstream outputFile(file, std::ios::app);

        for (int i = 0; charArray[i] != '\0'; i++) {
            int non_ex = 0;
            for (const Transition& trans : Trans) {
                if (Etat == trans.et_dep && charArray[i] == trans.sym) {
                    Etat = trans.et_arr;
                    non_ex = 1;
                    break;
                }
            }

            if (non_ex == 0) {
                // Define a fixed-width field for the word
                int wordFieldWidth = 20;

                // Format the output with setw for the word field
                outputFile << std::left << std::setw(wordFieldWidth) << A;

                outputFile << " N'est pas accepté " << std::endl;
                return false;
            }
        }

        bool accepted = false;
        for (int etat : EtatsFinaux) {
            if (Etat == etat) {
                accepted = true;
                break;
            }
        }

        // Define a fixed-width field for the word
        int wordFieldWidth = 20;

        // Format the output with setw for the word field
        outputFile << std::left << std::setw(wordFieldWidth) << A;

        if (accepted) {
            outputFile << " Est accepté ";
        }
        else {
            outputFile << " N'est pas accepté ";
        }

        outputFile << std::endl;

        return accepted;
    }

    void Ajouter_T() {
        Transition newTransition;

        cout << "Saisir etat depart: ";
        cin >> newTransition.et_dep;

        cout << "Saisir etat arrive: ";
        cin >> newTransition.et_arr;

        cout << "Saisir symbole: ";
        cin >> newTransition.sym;

        Trans.push_back(newTransition);
    }

    void lire_txt() {
        ifstream file("Automate.txt");
        if (!file.is_open()) {
            cout << "Failed to open file!" << endl;
        }
        else {
            string line;
            int i = 0;

            Alphabet.clear();
            EtatsFinaux.clear();
            Trans.clear();

            while (getline(file, line)) {
                const char* charArray = line.c_str();
                if (line.empty()) {
                    break;
                }
                else if (i == 0) {
                    for (int j = 0; charArray[j] != '\0'; j++) {
                        Alphabet.push_back(charArray[j]);
                    }
                }
                else if (i == 1) {
                    EtatInitial = charArray[0] - '0';
                }
                else if (i == 2) {
                    for (int j = 0; charArray[j] != '\0'; j++) {
                        if (charArray[j] != ' ') {
                            EtatsFinaux.push_back(charArray[j] - '0');
                        }
                    }
                }
                else {
                    Transition tr;
                    int nbr = 0;
                    for (int j = 0; charArray[j] != '\0'; j++) {
                        if (charArray[j] != ' ') {
                            if (nbr == 0) {
                                tr.et_dep = charArray[j] - '0';
                                nbr++;
                            }
                            else if (nbr == 1) {
                                tr.et_arr = charArray[j] - '0';
                                nbr++;
                            }
                            else {
                                tr.sym = charArray[j];
                            }
                        }
                    }
                    Trans.push_back(tr);
                }

                i++;
            }
            file.close();
        }
    }
    void Ajouter_Aut_txt() {
        string desktopPath = "Automate.txt";
        string file = desktopPath;
        ofstream outputFile(file, std::ios::app);

        int etdep;
        int etarr;
        string symb;

        cout << "saisir Etat depart :";
        cin >> etdep;
        cout << "saisir Etat arrive :";
        cin >> etarr;
        cout << "saisir symbole :";
        cin >> symb;
        outputFile << etdep << " ";
        outputFile << etarr << " ";
        outputFile << symb << endl;
    }
    void checker_mots_txt(const std::string& fileName, Automate& automate) {
        char desktopDir[MAX_PATH];

        if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_DESKTOP, NULL, 0, desktopDir))) {
            std::wstringstream wss;
            wss << desktopDir;
            wss << L"\\" << std::wstring(fileName.begin(), fileName.end());

            std::wstring fullFilePath = wss.str();
            std::string filePath(fullFilePath.begin(), fullFilePath.end());

            std::ifstream file(filePath);
            if (file.is_open()) {
                std::string line;
                while (std::getline(file, line)) {
                    line = removeSpaces(line);
                    if (line.empty()) {
                        break;
                    }
                    else {
                        if (automate.check(line)) {
                            std::cout << line << " Accepted: " << std::endl;
                        }
                        else {
                            std::cout << line << " Not accepted: " << std::endl;
                        }
                    }
                }
                file.close();
            }
            else {
                std::cerr << "Failed to open the file." << std::endl;
            }
        }
    }
    string removeSpaces(const std::string& str) {
        string result;
        result.reserve(str.size());
        for (char c : str) {
            if (!std::isspace(c)) {
                result.push_back(c);
            }
        }
        return result;
    }
    Automate* aut_complement(){
        Automate* aut=new Automate();  
        for(int i=0;i<Alphabet.size();i++)
                  {
                    aut->Alphabet[i]=Alphabet[i];

                  }
        aut->EtatInitial=EtatInitial;
        for(int i=0;i<Trans.size();i++){
            aut->Trans.push_back(Trans[i]);
            }
        int etatcourante=aut->EtatInitial;
        bool exist1=false;
        bool exist2=false;
        Transition transi;
        for(Transition& tr:aut->Trans){
            if(etatcourante == tr.et_dep && tr.sym=='a'){
                  exist1=true;
                if(etatcourante == tr.et_dep && tr.sym=='b'){
                  exist2=true;
                }
                else{
                  exist2=false;
            }
            
                  exist1=false;

                  if(exist1==false){
                    transi.et_dep=etatcourante;
                    transi.sym='a';
                    transi.et_arr=2;
                  }
            
        }} }

    /*void afficher_mots4() {
        vector<string> mots;
        for (int j = 0; j < 5; j++) {
            int Etat = EtatInitial;
            char* charArray = new char[4];
            int i = 0;
            bool final = false;
            while (i != 4) {
                for (const Transition& trans : Trans) {
                    if (Etat == trans.et_dep) {
                        Etat = trans.et_arr;
                        charArray[i] = trans.sym;
                        i++;
                        for (int etat : EtatsFinaux) {
                            if (Etat == etat && i != 4) {
                                Etat = trans.et_dep;
                                i--;
                            }
                        }
                        if (i == 4) {
                            for (int etat : EtatsFinaux) {
                                if (Etat == etat) {
                                    final = true;
                                    break;
                                }
                            }
                            if (final == true)
                                break;
                        }
                    }
                }
            }
            if (i == 4 && final == true) {
                mots.push_back(string(charArray, 4));
            }
            for (string s : mots) {
                cout << s << endl;
            }

            delete[] charArray;
        }
    }*/
   /* void afficher_mots_4() {
        unordered_set<string> words;

        
        function<void(int, int, string)> genereMotsDFS = [&](int Etat, int size_mot, string motcourant) {
            if (size_mot == 4) {
                if (find(EtatsFinaux.begin(), EtatsFinaux.end(), Etat) != EtatsFinaux.end()) {
                    words.insert(motcourant);
                }
                return;
            }

            for (const Transition& trans : Trans) {
                if (trans.et_dep == Etat) {
                    string newWord = motcourant + trans.sym;
                    genereMotsDFS(trans.et_arr, size_mot + 1, newWord);
                }
            }
        };

        genereMotsDFS(EtatInitial, 0, "");

        for (const std::string& word : words) {
            cout << word << std::endl;
        }
    }
*/

     
};


int main() {
    

    Automate Aut;
    int n = 1;
    string test;
    string nomf;

    while (n != 5) {
        system("cls");

        cout << "__________________________________________" << endl;
        cout << "||                  MENU                ||" << endl;
        cout << "------------------------------------------" << endl;
        cout << endl;
        cout << "1. lire Automate" << endl;
        cout << "2. Afficher l'automate" << endl;
        cout << "3. Tester mot" << endl;
        cout << "4. Ajouter transition" << endl;
        cout << "5. Tester mots a partir d'un fichier text" << endl;
        cout << "6. Voir tous les mots de longueur 4 possible" << endl;
        cout << "0. Quitter" << endl;
        cout << "__________________________________________" << endl;
        cout << "Votre choix : ";
        cin >> n;

        switch (n) {
        case 1:
            Aut.reset();
            Aut.lire_txt();
            break;
        case 2:
            Aut.afficher();
            break;
        case 3:
            cout << "Entrez le mot à tester : ";
            cin >> test;
            if (Aut.check(test)) {
                cout << "accepte" << endl;
            }
            else {
                cout << "non accepte" << endl;
            }
            break;
        case 4:
            Aut.Ajouter_Aut_txt();
            break;
        case 5:
            cout << "saisir le nom du fichier (avec le .txt) :";
            cin >> nomf;
            Aut.checker_mots_txt(nomf, Aut);
            break;
        case 6:
           // Aut.afficher_mots_4();
           cout<< "4mots";
            break;
        case 0:
            break;
        default:
            cout << "Saisie incorrecte." << endl;
            break;
        }

        cout << "Appuyez sur Enter pour continuer...";
        cin.ignore();
        cin.get();
    }
    return 0;
    
}

