#include <iostream>
#include <vector>
#include <string>
#include <bitset>
using namespace std;

vector<string> CR0{"PE", "MP", "EM", "TS", "ET", "NE", "", "", "", "", "", "", "", "", "", "", "WP", "", "AM", "", "", "", "", "", "", "", "", "", "", "NW", "CD", "PG"};
// vector<string> CR1(32, "");
// vector<string> CR2(32, "");
vector<string> CR3{"", "", "", "PWT", "PCD", ""};
vector<string> CR4{"VME", "PVI", "TSD", "DE", "PSE", "PAE", "MCE", "PGE", "PCE", "OSFXSR", "OSXMMEXCPT", "UMIP", "LA57", "VMXE", "SMXE", "", "FSGSBASE", "PCIDE", "OSXSAVE", "", "SMEP", "SMAP", "PKE", "CET", "PKS"};
vector<unsigned long> mask{1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648};
void readCR0(unsigned long cr0) {
    cout << "read CR0 : 0x" << hex << cr0 << endl;
    for (int i= 0;i < CR0.size();i++) {
        if (CR0[i] != "" && (cr0 & mask[i])) {
            cout << dec << "     bit " << i << " " << CR0[i] << endl;
        }
    }
    cout << endl;
}

void readCR3(unsigned long cr3) {
    cout << "read CR3 : 0x" << hex << cr3 << endl;
    for (int i= 0;i < CR3.size();i++) {
        if (CR3[i] != "" && (cr3 & mask[i])) {
            cout << dec << "     bit " << i << " " << CR3[i] << endl;
        }
    }
    cout << "    Page-Directory Base: 0x" << hex << (cr3>>12) << endl;
    cout << endl;
}

void readCR4(unsigned long cr4) {
    cout << "read CR4 : 0x" << hex << cr4 << endl;
    for (int i= 0;i < CR4.size();i++) {
        if (CR4[i] != "" && (cr4 & mask[i])) {
            cout << dec << "     bit " << i << " " << CR4[i] << endl;
        }
    }
    cout << endl;
}

unsigned long convert(string str) {
    unsigned long res = 0;
    for (auto c : str) {
        unsigned long cur = 0;
        if (c >= '0' && c <= '9') cur = c-'0';
        else if (c >= 'a' && c <= 'f') cur = c-'a'+10;
        res *=16;
        res += cur;
    }
    return res;
}

int main(int argc, char** argv)
{
    if (argc != 3) return -1;
    unsigned long val = convert(string(argv[2]));
    string reg = argv[1];
    if (reg == "cr0") {
        readCR0(val);
    } else if (reg == "cr3") {
        readCR3(val);
    } else if (reg == "cr4") {
        readCR4(val);
    }
    return 0;
}
