#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

// @Code Author: Maruf Rahman
using namespace std;

// Struct to hold information about each song
struct Song {
    string songTitle;
    string songArtist;
    string category;
    int publishYear;
};

// Class to manage the song catalog
class SongCatalogue {
private:
    vector<Song> catalogue; // Vector to store songs

public:
    // Method to add a song to the catalog
    void addSong() {
        Song newSong;
        cout << "Enter song title: ";
        getline(cin, newSong.songTitle);
        cout << "Enter artist name: ";
        getline(cin, newSong.songArtist);
        cout << "Enter song category: ";
        getline(cin, newSong.category);
        cout << "Enter published year: ";
        while (!(cin >> newSong.publishYear)) {
            cout << "Invalid input. Please enter a number for the year: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(); // Clear newline character
        catalogue.push_back(newSong);
    }

    // Method to display all songs in the catalog
    void displayCatalog() const {
        if (catalogue.empty()) {
            cout << "The catalog is empty.\n";
            return;
        }
        cout << "\nAll songs in the catalog:\n";
        for (const auto& song : catalogue) {
            cout << "Song Title: " << song.songTitle
                 << ", Artist: " << song.songArtist
                 << ", Category: " << song.category
                 << ", Published Year: " << song.publishYear << endl;
        }
    }

    // Method to search for a song by title
    void searchByTitle(const string& title) const {
        cout << "\nSearch Results:\n";
        bool found = false;
        for (const auto& song : catalogue) {
            if (song.songTitle == title) {
                cout << "Song Title: " << song.songTitle
                     << ", Artist: " << song.songArtist
                     << ", Category: " << song.category
                     << ", Published Year: " << song.publishYear << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Song not found.\n";
        }
    }

    // Method to save the catalog to a CSV file
    void saveCatalog(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << "Song Title,Song Artist,Song Category,Published Year\n";
            for (const auto& song : catalogue) {
                file << song.songTitle << "," << song.songArtist << "," << song.category << "," << song.publishYear << "\n";
            }
            file.close();
            cout << "Catalog saved to " << filename << "\n";
        } else {
            cout << "Unable to open the file for saving.\n";
        }
    }

    // Method to load the catalog from a CSV file
    void loadCatalog(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line, temp;
            getline(file, line); // Skip header row
            while (getline(file, line)) {
                stringstream ss(line);
                Song song;
                getline(ss, song.songTitle, ',');
                getline(ss, song.songArtist, ',');
                getline(ss, song.category, ',');
                getline(ss, temp);
                song.publishYear = stoi(temp);
                catalogue.push_back(song);
            }
            file.close();
            cout << "Catalog loaded from " << filename << "\n";
        } else {
            cout << "Unable to open the file for loading. Starting with an empty catalog.\n";
        }
    }
};

// Main function for user interaction
int main() {
    SongCatalogue catalog;
    string filename = "music_catalog.csv";

    // Load catalog from file
    catalog.loadCatalog(filename);

    int choice;
    string searchTitle;
    do {
        cout << "\nMusic Catalog Menu:\n";
        cout << "1. Add a new song to the catalog\n";
        cout << "2. Display all songs in the catalog\n";
        cout << "3. Search for a song by title\n";
        cout << "4. Save catalog to file\n";
        cout << "5. Quit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore(); // Clear newline character

        switch (choice) {
            case 1:
                catalog.addSong();
                break;
            case 2:
                catalog.displayCatalog();
                break;
            case 3:
                cout << "Enter the song title to search: ";
                getline(cin, searchTitle);
                catalog.searchByTitle(searchTitle);
                break;
            case 4:
                catalog.saveCatalog(filename);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
