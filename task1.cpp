#include <iostream>
#include <string>

using namespace std;
struct SongNode {
    int songId;
    string name;
    string duration;
    SongNode* prev;
    SongNode* next;
    SongNode(int id, string songName, string songDuration) {
        songId = id;
        name = songName;
        duration = songDuration;
        prev = nullptr;
        next = nullptr;
    }
};

class Playlist {
private:
    SongNode* head;
    SongNode* tail;
    SongNode* current; 

public:
    Playlist() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    
    void addSong(int id, string name, string duration) {
        SongNode* newNode = new SongNode(id, name, duration);
        if (!head) {
            head = tail = current = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "SuccessFully Added: '" << name << "' (ID: " << id << ")\n";
    }
    void deleteSong(int id) {
        SongNode* curr = head;
        while (curr != nullptr) {
            if (curr->songId == id) {
                if (curr == head) {
                    head = curr->next;
                    if (head) head->prev = nullptr;
                }
                if (curr == tail) {
                    tail = curr->prev;
                    if (tail) tail->next = nullptr;
                }
                if (curr->prev) curr->prev->next = curr->next;
                if (curr->next) curr->next->prev = curr->prev;

                if (current == curr) {
                    current = curr->next ? curr->next : curr->prev;
                }
                delete curr;
                cout << "\n Deleted song ID " << id << ".\n";
                return;
            }
            curr = curr->next;
        }
        cout << "\nSorry!Song ID " << id << " not found.\n";
    }
    void displayForward() {
        if (!head) {
            cout << "\nPlaylist is empty.\n";
            return;
        }
        SongNode* curr = head;
        cout << "\n--- Playlist (Forward) ---\n";
        while (curr != nullptr) {
            cout << "ID: " << curr->songId << " | Name: " << curr->name 
                 << " | Duration: " << curr->duration;
            if (curr == current) cout << " [▶ CURRENT]";
            cout << "\n";
            curr = curr->next;
        }
        cout << "=============\n";
    }
    void displayBackward() {
        if (!tail) {
            cout << "\nPlaylist is empty.\n";
            return;
        }
        SongNode* curr = tail;
        cout << "\n=== Playlist (Backward) ===\n";
        while (curr != nullptr) {
            cout << "ID: " << curr->songId << " | Name: " << curr->name 
                 << " || Duration: " << curr->duration;
            if (curr == current) cout << " Current Song-->";
            cout << "\n";
            curr = curr->prev;
        }
        cout << "---------------------------\n";
    }
    void searchSong(int id) {
        SongNode* curr = head;
        while (curr != nullptr) {
            if (curr->songId == id) {
                cout<<"=======The Found Details======="<<endl;
                cout << "\n ID: " << curr->songId 
                     << " | Name: " << curr->name 
                     << " | Duration: " << curr->duration << "\n";
                return;
            }
            curr = curr->next;
        }
        cout << "\nError!Song ID " << id << " not found.\n";
    }
    void playNext() {
        if (!current) {
            cout << "\n[Player] No song currently playing.\n";
            return;
        }
        if (current->next) {
            current = current->next;
            cout << "\n[Now Playing] " << current->name << " (" << current->duration << ")\n";
        } else {
            cout << "\n[Player] You have reached the end of the playlist.\n";
        }
    }
    void playPrevious() {
        if (!current) {
            cout << "\n[Player] No song currently playing.\n";
            return;
        }
        if (current->prev) {
            current = current->prev;
            cout << "\n[Now Playing] " << current->name << " (" << current->duration << ")\n";
        } else {
            cout << "\n[Player] You are at the beginning of the playlist.\n";
        }
    }

    void reversePlaylist() {
        if (!head || !head->next) {
            cout << "\nPlaylist is too short to reverse.\n";
            return;
        }
        SongNode* curr = head;
        tail = head; 
        SongNode* prevNode = nullptr;
        SongNode* nextNode = nullptr;

        while (curr != nullptr) {
            nextNode = curr->next;
            curr->next = prevNode;
            curr->prev = nextNode;
            prevNode = curr;
            curr = nextNode;
        }
        head = prevNode; 
        cout << "\n[Success] Playlist reversed successfully!\n";
    }

    ~Playlist() {
        SongNode* curr = head;
        while (curr != nullptr) {
            SongNode* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }
};

int main() {
    Playlist myPlaylist;

    cout << "Loading initial songs into the playlist...\n";
    myPlaylist.addSong(1, "Ed Sheran-Perfect", "3:20");
    myPlaylist.addSong(2, "Chaap Tilak", "3:23");
    myPlaylist.addSong(3, "Hymn in the Weekend", "3:35");
    cout << "-------------------------------------------\n";

    int choice;
    do {
        cout << "\n========= PLAYLIST MANAGEMENT SYSTEM =========\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song by ID\n";
        cout << "3. Display Playlist Forward\n";
        cout << "4. Display Playlist Backward\n";
        cout << "5. Search Song by ID\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Reverse Playlist\n";
        cout << "9. Exit\n";
        cout << "Enter your choice (1-9): ";
        
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                int id;
                string name, duration;
                cout << "Enter Song ID (integer): ";
                cin >> id;
                cout << "Enter Song Name (string): ";
                cin.ignore(); 
                getline(cin, name);
                cout << "Enter Duration (minutes:seconds, e.g., 3:45): ";
                cin >> duration;
                myPlaylist.addSong(id, name, duration);
                break;
            }
            case 2: {
                int id;
                cout << "Enter Song ID to delete: ";
                cin >> id;
                myPlaylist.deleteSong(id);
                break;
            }
            case 3:
                myPlaylist.displayForward();
                break;
            case 4:
                myPlaylist.displayBackward();
                break;
            case 5: {
                int id;
                cout << "Enter Song ID to search: ";
                cin >> id;
                myPlaylist.searchSong(id);
                break;
            }
            case 6:
                myPlaylist.playNext();
                break;
            case 7:
                myPlaylist.playPrevious();
                break;
            case 8:
                myPlaylist.reversePlaylist();
                break;
            case 9:
                cout << "\nExiting Playlist Manager. Goodbye!\n";
                break;
            default:
                cout << "\n[Error] Invalid choice. Please select between 1 and 9.\n";
        }
    } while (choice != 9);

    return 0;
}