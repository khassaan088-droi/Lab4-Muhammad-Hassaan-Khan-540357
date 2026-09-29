#include <iostream>
#include <vector>
using namespace std;
struct Node {
    int id;
    Node* next;
    Node(int person_id) : id(person_id), next(nullptr) {}
};
class CircularLinkedList {
private:
    Node* head;
    void create_circle(int n) {
        if (n <= 0) return;
        head = new Node(1);
        Node* curr = head;
        for (int i = 2; i <= n; ++i) {
            curr->next = new Node(i);
            curr = curr->next;
        }
        curr->next = head; 
    }
public:
    CircularLinkedList(int n) : head(nullptr) {
        create_circle(n);
    }
    ~CircularLinkedList() {
        if (!head) return;
        Node* curr = head->next;
        head->next = nullptr; 
        while (curr) {
            Node* next_node = curr->next;
            delete curr;
            curr = next_node;
        }
    }
    std::pair<std::vector<int>, int> simulate_josephus(int k) {
        if (!head || k <= 0) return {{}, -1};
        Node* curr = head;
        while (curr->next != head) {
            curr = curr->next;
        }
        Node* prev = curr;
        curr = head;
        std::vector<int> eliminated_order;
   
        while (curr->next != curr) {
    
            for (int i = 0; i < k - 1; ++i) {
                prev = curr;
                curr = curr->next;
            }
            eliminated_order.push_back(curr->id);
            prev->next = curr->next;
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }

        int survivor = curr->id;
        delete curr;
        head = nullptr;
        return {eliminated_order, survivor};
    }
};

int main() {
  int N;
  int k;
  cout<<"Enter the N=";
  cin>>N;
  cout<<endl;
  cout<<"Enter the K=";
  cin>>k;


  CircularLinkedList circle(N);
    auto [order, survivor] = circle.simulate_josephus(k);

    std::cout << "=== Josephus Problem Simulation(Charge!!!) (N=" << N << ", k=" << k << ") ===\n";
    std::cout << "Abolition Order= ";
    for (int id : order) std::cout << id << " ";
    std::cout << "\nSurviving Person : " << survivor << "\n\n";

    return 0;
}