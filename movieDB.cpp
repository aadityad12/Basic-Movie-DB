//Date: 4th Feb
#include <iostream>
#include <fstream>

using namespace std;

struct Movie {
    string title;
    double gross;
    string director;
    string releaseDate;
    int runTime;
};

int numberOfLines(ifstream &);
void populateMovieFromFile(ifstream&, Movie&);
void displayMovie(const Movie&);
Movie* createDatabase(int&);
bool caseInsensitiveCmp(string, string);
void findMovie(Movie*, int);
void saveToFile(const Movie&);
bool promptToContinue();
void displayFavorites();

ifstream inFile;

int main() {
    int numMovies;
    Movie *ptr = createDatabase(numMovies);
    delete[] ptr;
    displayFavorites();
}

/*
RECEIVES: object of filestream 
RETURNS: int
FUNCTION: counts the number of lines in the file */
int numberOfLines(ifstream &inFile) {
    int count = 0;
    string line;
    while(getline(inFile, line)) {
        count++;
    }
    inFile.clear();
    inFile.seekg(0);
    return count;
}

/*
RECEIVES: object of filestream, object of type movie (by reference)
RETURNS: nothing
FUNCTION: reads file and populates the movie object accordingly*/
void populateMovieFromFile(ifstream &inFile, Movie& movie) {
    getline(inFile, movie.title, ',');
    string grossStr;
    getline(inFile, grossStr, ',');
    movie.gross = stod(grossStr);
    getline(inFile, movie.director, ',');
    getline(inFile, movie.releaseDate, ',');
    string runTimeInt;
    getline(inFile, runTimeInt);
    movie.runTime = stoi(runTimeInt);
}

/*
RECEIVES: int number of movies (by reference)
RETURNS: a pointer to an array of movie objects
FUNCTION: creates a database of movie objects from the file*/
Movie* createDatabase(int& numMovies) {
    string filename;
    do {
        cout << "Please enter filename: ";
        cin >> filename;
        inFile.open(filename);
        if (!inFile) {
            cout << "ERROR!! Please try again" << endl;
        }
    } while (!inFile);

    numMovies = numberOfLines(inFile);
    Movie *ptr = new Movie[numMovies];
    for (int i = 0; i < numMovies; i++) {
        populateMovieFromFile(inFile, ptr[i]);
    }
    inFile.close();
    findMovie(ptr, numMovies);
    return ptr;
}

/*
RECEIVES: two strings - the movie name inputted and the name existing
in the database
RETURNS: bool 
FUNCTION: converts both strings that are accepted to lowercase (to remove
case-sensetivity) and then compares them. Returns true if they are equal,
false otherwise*/
bool caseInsensitiveCmp(string inputName, string dataBaseName) {
    for (int i = 0; i < inputName.length(); i++) {
        inputName[i] = tolower(inputName[i]);
    }
    for (int i = 0; i < dataBaseName.length(); i++) {
        dataBaseName[i] = tolower(dataBaseName[i]);
    }
    return (inputName == dataBaseName);
}

/*
RECEIVES: a pointer to database of movies and number of movies as int
RETURNS: nothing
FUNCTION: searches for movie in the database and displays if succssful
if yes then furteher asks if it should be saved or not*/
void findMovie(Movie* ptr, int numMovies) {
   bool condition = true;
    while (condition) {
        cout << "Enter a movie title to search: ";
        string input;
        cin.ignore();
        getline(cin, input);
        bool found = false; 
        for (int i = 0; i < numMovies; i++) {
            if (caseInsensitiveCmp(input, ptr[i].title)) {
                displayMovie(ptr[i]);
                found = true; 
                cout << "Would you like to save the above movie? (Y or N): ";
                char choice;
                cin >> choice;
                choice = tolower(choice);
                if (choice == 'y') {
                    saveToFile(ptr[i]);
                }
                break; 
            }
        }
        if (!found) {
            cout << "Error: '" << input 
                 << "' not found in database. Please try again." << endl;
        }
        condition = promptToContinue();
    }
}

/*
RECEIVES:
RETURNS:
FUNCTION: */
void displayMovie(const Movie& movie) {
    cout << "\n    Title: " << movie.title << endl;
    cout << "    Gross Total: " << movie.gross << " billion dollars" << endl;
    cout << "    Director: " << movie.director << endl;
    cout << "    Release date: " << movie.releaseDate << endl;
    cout << "    Runtime: " << movie.runTime << " minutes\n" << endl;
}

/*
RECEIVES: a constant movie object (by reference)
RETURNS: nothing
FUNCTION: saves all details of a movie object into "favorites.txt"*/
void saveToFile(const Movie& movie) {
    ofstream outFile("favorites.txt", ios::app);
    if (outFile) {
        outFile << movie.title << ", " << movie.gross << ", " 
                << movie.director << ", " << movie.releaseDate << ", " 
                << movie.runTime << endl;
    }
}

/*
RECEIVES:
RETURNS:
FUNCTION: */
bool promptToContinue() {
    cout << "Would you like to exit? (Y/N): ";
    char exit;
    cin >> exit;
    return tolower(exit) != 'y'; 
}

/*
RECEIVES: nothing
RETURNS: bool
FUNCTION: asks the user if they want to continue, and returns a bool val
according to their response*/
void displayFavorites() {
    ifstream favoritesFile("favorites.txt");
    if (!favoritesFile) {
        cout << "\nNo favorite movies saved.\n";
        return;
    }

    cout << "\nYour saved movies are:\n";

    Movie movie;
    string grossStr, runTimeStr;

    while (getline(favoritesFile, movie.title, ',') &&
           getline(favoritesFile, grossStr, ',') &&
           getline(favoritesFile, movie.director, ',') &&
           getline(favoritesFile, movie.releaseDate, ',') &&
           getline(favoritesFile, runTimeStr)) {
        
        movie.gross = stod(grossStr);
        movie.runTime = stoi(runTimeStr);

        displayMovie(movie);  // Displays with the correct format
    }

    favoritesFile.close();
}
