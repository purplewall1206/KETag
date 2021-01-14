#include <iostream>
#include <vector>
using namespace std;

vector<string> PDPTE{"present", "", "", "PWT", "PCD"};
vector<string> PDE{"present", "R/W", "U/S", "PWT", "PCD", "Accessed", "Dirty", "PS","Global", "", "", "", "PAT"};
// vector<string> PDE4M{"present", "R/W", "U/S", "PWT", "PCD", "Accesed", "Dirty", "PS-Page size", "Gloabl", "", "", "", "PAT", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
// vector<string> PDE4K{"present", "R/W", "U/S", "PWT", "PCD", "Accessed", "", "PS-Page size", "Global", "", "", "", "PAT", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
vector<string> PTE{"present", "R/W", "U/S", "PWT", "PCD", "Accessed", "Dirty", "PAT", "Gloabl", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
vector<unsigned long> mask{1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648};

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

void readPDPTE(unsigned long content) {
    cout << "read PDPTE" << endl;
    if (content & mask[0] == 0) {
        cout << "    not present" << endl;
        return ;
    }
    cout << "    bit 0 " << PDPTE[0] << endl;
    unsigned long rsvd = (content & 0b00110) >> 1;
    cout << "    bit 1-2 rsvd " << hex << rsvd << endl;
    if (content & mask[3])
        cout << "    bit 3 " << PDPTE[3] << endl;
    if (content & mask[4])
        cout << "    bit 4 " << PDPTE[4] << endl;
    rsvd = (content & 0b000111100000) >> 5;
    cout << "    bit 5-8 rsvd. " << hex << rsvd << endl;
    cout << "  Address of page directory : 0x" << hex << (content >> 12) << endl;
}

// void readPDE2M(unsigned long content) {
//     // 这里需要整体调整一下
//     cout << "read PDE-4M" << endl;
//     if (content & 1 == 0) {
//         cout << "    not present" << endl;
//         return ;
//     }
    
//     for (int i = 0;i < 32;i++) {
//         if (PDE2M[i] != "" && (content & mask[i])) {
//             cout << "    bit " << i << " " << PDE2M[i] << endl;
//         }
//         if (i == 1 && content & mask[1] == 0) {
//             // 如果这里是0
//             cout << "    bit " << i << " " << PDE2M[i] << " - R" << endl; 
//         }
//         if (i == 2 && content & mask[2] == 0) {
//             // 如果这里是0
//             cout << "    bit " << i << " " << PDE2M[i] << " - U" << endl; 
//         }
//     } 
//     cout << endl;
//     cout << "  Address of 2MB page frame : 0x" << hex << (content >> 13) << endl;
// }

void readPDE(unsigned long content) {
    cout << "read PDE" << endl;
    if (content & 1 == 0) {
        cout << "    not present" << endl;
        return ;
    }
    int isHuge = 0;
    if (content & mask[7]) {
        cout << "  2M big page" << endl;
        isHuge = 1;
    }
    for (int i = 0;i < 32;i++) {
        if (i == 12 && isHuge == 0) continue;
        if (PDE[i] != "" && (content & mask[i])) {
            cout << "    bit " << i << " " << PDE[i] << endl;
        }
        if (i == 1 && content & mask[1] == 0) {
            // 如果这里是0
            cout << "    bit " << i << " " << PDE[i] << " - R" << endl; 
        }
        if (i == 2 && content & mask[2] == 0) {
            // 如果这里是0
            cout << "    bit " << i << " " << PDE[i] << " - U" << endl; 
        }
    }
    cout << endl;
    if (isHuge) {
        cout << "  Address of 2MB page frame: 0x" << hex << (content >> 21) << endl;
    } else {
        unsigned long ptaddr = content >> 13;
        cout << "  Address of page table: 0x" << hex << ptaddr << endl;
    }
    
}

void readPTE(unsigned long content) {
    cout << "read PTE" << endl;
    if (content & 1 == 0) {
        cout << "    not present" << endl;
        return ;
    }
    for (int i = 0;i < 32;i++) {
        if (PTE[i] != "" && (content & mask[i])) {
            cout << "    bit " << i << " " << PTE[i] << endl;
        }
        if (i == 1 && content & mask[1] == 0) {
            // 如果这里是0
            cout << "    bit " << i << " " << PTE[i] << " - R" << endl; 
        }
        if (i == 2 && content & mask[2] == 0) {
            // 如果这里是0
            cout << "    bit " << i << " " << PTE[i] << " - U" << endl; 
        }
    }
    cout << endl;
    unsigned long pageframe = (content >> 12);
    cout << "  Address of 4KB page frame: 0x" << hex << pageframe << endl;
}

int main(int argc, char** argv) {
    if (argc != 3) return 0;
    string t = argv[1];
    unsigned long content = convert(argv[2]);
    if (t == "pdpte") {
        readPDPTE(content);
    } else if (t == "pde") {
        readPDE(content);
    } else if (t == "pte") {
        readPTE(content);
    }
    
    return 0;
}