#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// ------------------------------------Filmu ar serialu katalogas-------------------------------------

// Struktura filmui aprasyti
struct Film {
    string name; // Filmo pavadinimas
    string year; // Isleidimo metai (tesktas)
    string genre; // Zanras
    string rating; // Ivertinimas (tekstas)
};

// Maksimalus filmu skaiicus
const int MAX = 100;

//Masyvas saugoti filmus
Film films[MAX];

//Kiek filmu turime dabar
int countFilms = 0;

// Duomenu nuskaitymas is failo
void loadFromFile() {
    ifstream file("films.txt");

    if (!file) {
        cout << "Failas nerastas!" << endl;
        return;
    }

    string line;

    // Skaitome kiekviena eilute is failo
    while (getline(file, line)) {
        stringstream ss(line); /*Is eilutes padarome srauta
        Stringstream skirtas padalyti eilute pagal skyrikli (pvz. ';')*/


        //Skaitome duomenis pagal ; skyrikli
        getline(ss, films[countFilms].name, ';');
        getline(ss, films[countFilms].year, ';');
        getline(ss, films[countFilms].genre, ';');
        getline(ss, films[countFilms].rating, ';');

        countFilms++; // Padidiname filmu skaiciu
    }
    file.close();
}

//Duomenu issaugojimas i faila
void saveToFile() {
    ofstream file("films.txt");

    for (int i = 0; i < countFilms; i++) {
        file << films[i].name << ";"
            << films[i].year << ";"
            << films[i].genre << ";"
            << films[i].rating << endl;
    }
    file.close();
}


//Visu filmu rodymas
void showFilms() {
    for (int i = 0; i < countFilms; i++) {
        cout << i + 1 << ": " << films[i].name << " | "
        << films[i].year << " | " << films[i].genre << " | "
        << films[i].rating << endl;
    }
}

// Naujo failo pridejimas
void addFilm() {
    cout << "Ivesk filmo pavadinima: ";
    getline(cin, films[countFilms].name);

    cout << "Ivesk metus: ";
    getline(cin, films[countFilms].year);

    cout << "Ivesk zanra: ";
    getline(cin, films[countFilms].genre);

    cout << "Ivesk ivertinima: ";
    getline(cin, films[countFilms].rating);

    countFilms++;

    saveToFile(); // Is karto issaugome

    cout << "Filmas pridetas" << endl;
}

//Filmo redagavimas
void editFilm() {

    showFilms();

    int index;

    cout << "Pasirinkite filmo numeri: ";
    cin >> index;

    index--;//Kad atitiktu masyvo indeksa

    if (index >= 0 && index < countFilms) {
        cin.ignore(); /*Kad getline veiktu
        cin.ignore reikalingas tam, kad pasalinti ENTER po cin >>
        be cin.gnore ivestis bus tuscia*/

        cout << "Naujas pavadinimas: ";
        getline(cin, films[index].name);

        cout << "Nauji metai: ";
        getline(cin, films[index].year);

        cout << "Naujas zanras: ";
        getline(cin, films[index].genre);

        cout << "Naujas ivertinimas: ";
        getline(cin, films[index].rating);

        saveToFile();

        cout << "Filmas Atnaujintas!" << endl;
    }else {
        cout << "Blogas numeris" << endl;
    }

}

//Filmo istrynimas
void deleteFilm() {

    showFilms();

    int index;
    cout << "Pasirinkite filmo numeri: " << endl;
    cin >> index;

    index--;

    if (index >= 0 && index < countFilms) {

        // Perkeliame elementus i kaire
        for (int i = index; i < countFilms - 1; i++) {
            films[i] = films[i + 1];
        }
        countFilms--;

        saveToFile();

        cout << "Filmas Istrintas!" << endl;
    }else {
        cout << "Blogas numeris" << endl;
    }
}

//Filtravimas pagal zanra
void filterByGenre() {
    cin.ignore();
    string genre;

    cout << "Ivesk zanra: ";
    getline(cin, genre);

    bool found = false;

    for (int i = 0; i < countFilms; i++) {
        if (films[i].genre == genre) {

            cout << films[i].name << " | "
                << films[i].year << " | "
                << films[i].genre << " | "
                << films[i].rating << endl;

            found = true;
        }
    }
    if (!found) {
        cout << "Filmai nerasti!" << endl;
    }
}

//Filtravimas pagal minimalu ivertninima
void filterByRating() {
    cin.ignore();

    double minRating;
    cout << "Ivesk minimalu ivertinima: ";
    cin >> minRating;

    bool found = false;

    for (int i = 0; i < countFilms; i++) {
        double filmRating = stod(films[i].rating); // Stod = Tekstas --> skaicius

        if (filmRating >= minRating) {

            cout << films[i].name << " | "
                << films[i].year << " | "
                << films[i].genre << " | "
                << films[i].rating << endl;

            found = true;
        }
    }
    if (!found) {
        cout << "Filmai nerasti!" << endl;
    }
}

int main() {

  loadFromFile();

    int pasirinkimas;

    do {
        cout << "--------MENIU-------" << endl;
        cout << "1 - Rodyti filmus" << endl;
        cout << "2 - Prideti filma" << endl;
        cout << "3 - Redaguoti filma" << endl;
        cout << "4 - Istrinti filma" << endl;
        cout << "5 - Filtruoti pagal zanra" << endl;
        cout << "6 - Filtruoti pagal ivertinima" << endl;
        cout << "0 - Iseiti" << endl;

        cout << "Pasirink norima veiksma: " << endl;
        cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1:
                showFilms();
                break;
            case 2:
                cin.ignore();
                addFilm();
                break;
            case 3:
                cin.ignore();
                editFilm();
                break;
            case 4:
                deleteFilm();
                break;
            case 5:
                filterByGenre();
                break;
            case 6:
                filterByRating();
                break;
            case 0:
                cout << "Isejimas is programos" << endl;
                break;
            default:
                cout << "Blogas pasirinkimas!" << endl;
        }

    }while (pasirinkimas != 0);

    return 0;
}
