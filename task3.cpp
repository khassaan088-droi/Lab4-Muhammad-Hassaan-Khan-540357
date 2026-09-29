#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

struct BitNode {
    int bit; 
    BitNode* next;
    BitNode* prev;
    BitNode(int b) : bit(b), next(nullptr), prev(nullptr) {}
};

class BinaryDLL {
public:
    BitNode* head;
    BitNode* tail;

    BinaryDLL(std::string bit_string = "0") : head(nullptr), tail(nullptr) {
        parse_and_store(bit_string);
    }

    ~BinaryDLL() {
        BitNode* curr = head;
        while (curr) {
            BitNode* next_node = curr->next;
            delete curr;
            curr = next_node;
        }
    }

    void parse_and_store(std::string bit_string) {
        if (bit_string.empty()) bit_string = "0";
        
        
        int remainder = bit_string.length() % 8;
        if (remainder != 0) {
            bit_string = std::string(8 - remainder, '0') + bit_string;
        }

        for (char c : bit_string) {
            BitNode* new_node = new BitNode(c - '0');
            if (!head) {
                head = new_node;
                tail = new_node;
            } else {
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;
            }
        }
    }

    std::string display() const {
        std::string bit_str = raw_bits();
        std::string grouped = "";
        for (size_t i = 0; i < bit_str.length(); ++i) {
            if (i > 0 && i % 8 == 0) grouped += " ";
            grouped += bit_str[i];
        }
        return grouped;
    }

    std::string raw_bits() const {
        std::string bit_str = "";
        BitNode* curr = head;
        while (curr) {
            bit_str += std::to_string(curr->bit);
            curr = curr->next;
        }
        return bit_str;
    }

    BinaryDLL ones_complement() const {
        std::string flipped = "";
        BitNode* curr = head;
        while (curr) {
            flipped += (curr->bit == 1 ? "0" : "1");
            curr = curr->next;
        }
        return BinaryDLL(flipped);
    }

    BinaryDLL twos_complement() const {
        BinaryDLL ones = ones_complement();
        BinaryDLL one_dll("1");
        return add_binary_dll(ones, one_dll);
    }

    long long to_decimal() const {
        BitNode* curr = tail;
        long long decimal_val = 0;
        long long power = 0;
        while (curr) {
            decimal_val += curr->bit * std::pow(2, power);
            power++;
            curr = curr->prev;
        }
        return decimal_val;
    }

    // Friend function declaration for binary addition
    friend BinaryDLL add_binary_dll(const BinaryDLL& dll1, const BinaryDLL& dll2);
};

BinaryDLL add_binary_dll(const BinaryDLL& dll1, const BinaryDLL& dll2) {
    BitNode* curr1 = dll1.tail;
    BitNode* curr2 = dll2.tail;
    int carry = 0;
    std::string result_bits = "";

    while (curr1 || curr2 || carry) {
        int val1 = curr1 ? curr1->bit : 0;
        int val2 = curr2 ? curr2->bit : 0;

        int total = val1 + val2 + carry;
        carry = total / 2;
        result_bits += std::to_string(total % 2);

        if (curr1) curr1 = curr1->prev;
        if (curr2) curr2 = curr2->prev;
    }

    std::reverse(result_bits.begin(), result_bits.end());
    return BinaryDLL(result_bits);
}

BinaryDLL multiply_binary_dll(const BinaryDLL& dll1, const BinaryDLL& dll2) {
    long long dec2 = dll2.to_decimal();
    BinaryDLL result("0");
    BinaryDLL current_shifted(dll1.raw_bits());

    long long temp = dec2;
    while (temp > 0) {
        if (temp & 1) {
            result = add_binary_dll(result, current_shifted);
        }
        current_shifted = BinaryDLL(current_shifted.raw_bits() + "0");
        temp >>= 1;
    }
    return result;
}

int main() {
    std::string bb1,bb2;
    std::cout << "=== Binary Arithmetic via Doubly Linked List ===\n";
    std::cout<<"Enter the 1st Binary=";
    std::cin>>bb1;
    std::cout<<"Enter the 2nd Binary=";
    std::cin>>bb2;

    BinaryDLL b1(bb1); 
    BinaryDLL b2(bb2);  

    std::cout << "Binary 1             : " << b1.display() << " (Decimal: " << b1.to_decimal() << ")\n";
    std::cout << "Binary 2             : " << b2.display() << " (Decimal: " << b2.to_decimal() << ")\n";

    BinaryDLL ones_comp = b1.ones_complement();
    std::cout << "1's Complement (B1)  : " << ones_comp.display() << "\n";

    BinaryDLL twos_comp = b1.twos_complement();
    std::cout << "2's Complement (B1)  : " << twos_comp.display() << " (Decimal: " << twos_comp.to_decimal() << ")\n";
    BinaryDLL oness_comp = b2.ones_complement();
    std::cout << "1's Complement (B2)  : " << oness_comp.display() << "\n";

    BinaryDLL twoss_comp = b2.twos_complement();
    std::cout << "2's Complement (B2)  : " << twoss_comp.display() << " (Decimal: " << twoss_comp.to_decimal() << ")\n";

    BinaryDLL sum_dll = add_binary_dll(b1, b2);
    std::cout << "Binary Addition      : " << sum_dll.display() << " (Decimal: " << sum_dll.to_decimal() << ")\n";

    BinaryDLL prod_dll = multiply_binary_dll(b1, b2);
    std::cout << "Binary Multiplication: " << prod_dll.display() << " (Decimal: " << prod_dll.to_decimal() << ")\n";

    return 0;
}