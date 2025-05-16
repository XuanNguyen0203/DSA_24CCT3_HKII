#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
const int p = 31;
const int m = 2000;
struct Company {
	string name;
	string profit_tax;
	string address;
};
struct HashTableSlot {
    Company company;
    bool is_occupied = false;
};
struct HashTable {
    HashTableSlot table[m];
};

vector<Company> readCompanyList(string file_name);
long long hashString(string company_name);
HashTable* createHashTable(vector<Company> list_company);
void insert(HashTable* hash_table, Company company);
Company* search(HashTable* hash_table, string company_name);

vector<Company> readCompanyList(string file_name) {
    vector<Company> Listcp;
    ifstream file(file_name);
    string line;
    while (getline(file, line)) {
        string name = "";
        string tax = "";
        string address = "";
        Company cp;
        int i = 0;
        while (i < line.size() && line[i] != '|') {
            name += line[i];
            i++;
        }
        cp.name = name;
        i++;
        while (i < line.size() && line[i] != '|') {
            tax += line[i];
            i++;
        }
        cp.profit_tax = tax;
        i++;
        while (i < line.size() && line[i] != '|') {
            address += line[i];
            i++;
        }
        cp.address = address;
        Listcp.push_back(cp);
    }
    return Listcp;
}
long long hashString(string company_name) {
    long long result = 0;
    int size = company_name.size();
    int p_pow = 1;
    if (size > 20) size = 20;
    for (int i = 0; i < size; i++) {
        result = (result + company_name[i] * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return result;
}
HashTable* createHashTable(vector<Company> list_company) {
    HashTable* tableCP = new HashTable();
    int NumCP = list_company.size();
    for (int i = 0; i < NumCP; i++) {
        insert(tableCP, list_company[i]);
    }
    return tableCP;
}
void insert(HashTable* hash_table, Company company) {
    long long hash_root = hashString(company.name) % m;
    long long hash = hash_root;
    int step = 0;
    while (hash_table->table[hash].is_occupied) {
        if (hash_table->table[hash].company.name == company.name) {
            return;
        }
        step++;
        if (step >= m) return;
        hash = (hash_root + step) % m;
    }
    hash_table->table[hash].company = company;
    hash_table->table[hash].is_occupied = true;
}
Company* search(HashTable* hash_table, string company_name) {
    long long hash_root = hashString(company_name) % m;
    long long hash = hash_root;
    int step = 0;
    while (hash_table->table[hash].is_occupied) {
        if (hash_table->table[hash].company.name == company_name)
            return &hash_table->table[hash].company;
        step++;
        hash = (hash_root + step) % m;
        if (step >= m) break;
    }
    return nullptr;
}
int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Usage: ./main MST.txt input.txt output.txt\n";
        return 1;
    }

    string mst_file = argv[1];
    string input_file = argv[2];
    string output_file = argv[3];

    ifstream inputFile(input_file);
    ofstream outputFile(output_file);
    vector<Company> ListCP = readCompanyList(mst_file);
    HashTable* table_hash = createHashTable(ListCP);

    string line;
    while (getline(inputFile, line)) {
        Company* cp = search(table_hash, line);
        if (cp != nullptr) {
            outputFile << cp->name << "|" << cp->profit_tax << "|" << cp->address << endl;
        }
    }
    inputFile.close();
    outputFile.close();
    return 0;
}