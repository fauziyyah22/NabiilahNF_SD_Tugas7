#include <iostream>
#include <string>

using namespace std;

// Fungsi untuk menampilkan identitas
void identitas() {
    cout << "\nProgram Mengukur Maksimal Depth pada Binary Tree CPP Program";
    cout << "\nNama     : Nabiilah Nur Fauziyyah";
    cout << "\nNPM      : 2310631170105";
    cout << "\nKelas    : 2C - Informatika" << "\n";
}

// Merepresentasikan setiap simpul dalam pohon
struct Node {
    char label;
    Node *right, *left, *parent;
};

// root adalah pointer yang menunjuk ke simpul akar dari pohon
Node *root = NULL;

// Fungsi ini memeriksa apakah pohon kosong, yaitu jika root bernilai NULL
bool emptyTree() {
    return root == NULL;
}

// Fungsi ini membuat simpul root dari pohon dengan label yang diberikan
void createTree(char label) {
    if (root) { // Jika pohon sudah ada, fungsi akan memberikan pesan bahwa pohon sudah dibuat
        cout << "Tree sudah dibuat" << endl;
    } else { // Jika pohon belum ada, simpul root akan dibuat dan diinisialisasi dengan label yang diberikan
        root = new Node();
        root->label = label;
        root->left = NULL;
        root->right = NULL;
        root->parent = NULL;
        cout << label << " Berhasil menjadi root" << endl;
    }
}

// Fungsi ini mencari simpul dengan label tertentu dalam pohon
Node* search(Node* node, char label) { // Menerima simpul saat ini sebagai argumen
    if (!node) { // Jika simpul dengan label yang dicari ditemukan, fungsi akan mengembalikan pointer ke simpul tersebut
        return NULL;
    }
    if (node->label == label) { // Jika tidak ditemukan, fungsi akan mengembalikan NULL
        return node;
    }
    // Pencarian dilakukan secara rekursif di subtree kiri dan kanan
    Node* leftSearch = search(node->left, label);
    if (leftSearch) {
        return leftSearch;
    }
    return search(node->right, label);
}

// Fungsi ini digunakan untuk memasukkan simpul baru ke dalam pohon
Node* insert(char label, char parentLabel, string child) {
    if (emptyTree()) {
        cout << "Tree masih kosong, Tolong dibuat dulu!" << endl;
        return NULL;
    }

    Node* parentNode = search(root, parentLabel);
    if (!parentNode) {
        cout << "Parent node tidak ditemukan!" << endl;
        return NULL;
    }
    // Jika semua syarat terpenuhi, simpul  baru akan dibuat dan ditambahkan
    // ke pohon sebagai anak kiri atau kanan dari simpul induk
    if (child == "left") {
        if (parentNode->left) {
            cout << "Anak bagian kiri dari node " << parentNode->label << " sudah ada isinya!" << endl;
        } else {
            Node* newNode = new Node();
            newNode->label = label;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->parent = parentNode;
            parentNode->left = newNode;
            cout << "Label " << label << " berhasil dibuat di anak kiri dari node " << parentNode->label << endl;
            return newNode;
        }
    } else if (child == "right") {
        if (parentNode->right) {
            cout << "Anak bagian kanan dari node " << parentNode->label << " sudah ada isinya!" << endl;
        } else {
            Node* newNode = new Node();
            newNode->label = label;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->parent = parentNode;
            parentNode->right = newNode;
            cout << "Label " << label << " berhasil dibuat di anak kanan dari node " << parentNode->label << endl;
            return newNode;
        }
    }
    return NULL;
}

// Fungsi ini digunakan untuk memperbarui label sebuah simpul dalam pohon
void updateLabel(char label, Node* node) {
    if (emptyTree()) {
        cout << "Buat tree terlebih dahulu!" << endl;
    } else {
        if (!node) {
            cout << "Tidak ada node ini atau masih kosong!" << endl;
        } else { // Jika simpul ditemukan, labelnya akan diperbarui dengan label baru yang diberikan
            cout << "Label sebelumnya = " << node->label << endl;
            node->label = label;
            cout << "Label setelahnya = " << node->label << endl;
        }
    }
}

// Fungsi ini digunakan untuk mencetak label sebuah simpul dalam pohon
void retrieveLabel(Node* node) {
    if (!node) {
        cout << "Tidak ada Node ini atau masih kosong" << endl;
    } else {
        cout << "Label dari node ini adalah " << node->label << endl;
    }
}

// Fungsi ini digunakan untuk menghapus subtree yang dimulai dari sebuah simpul
void deleteSub(Node* node) {
    if (node != NULL) {
        if (node != root && node == node->parent->left) {
            node->parent->left = NULL;
        }
        deleteSub(node->left);
        if (node != root && node == node->parent->right) {
            node->parent->right = NULL;
        }
        deleteSub(node->right);
        if (node == root) {
            root = NULL;
            delete root;
        } else {
            delete node;
        }
    }
}

// Fungsi ini digunakan untuk menghapus seluruh pohon
void clearTree(Node* node) {
    if (node != NULL) {
        if (node != root && node == node->parent->left) {
            node->parent->left = NULL;
        }
        clearTree(node->left);
        if (node != root && node == node->parent->right) {
            node->parent->right = NULL;
        }
        clearTree(node->right);
        if (node == root) {
            root = NULL;
            delete root;
        } else {
            delete node;
        }
    }
}

// Fungsi - fungsi ini digunakan untuk melakukan traversal pada pohon
// Simpul saat ini, anak kiri, anak kanan
void preOrder(Node* node) {
    if (!node) {
        return;
    } else {
        cout << node->label << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
}
// Anak kiri, anak kanan, simpul saat ini
void postOrder(Node* node) {
    if (!node) {
        return;
    } else {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->label << " ";
    }
}
// Anak kiri, simpul saat ini, anak kanan
void inOrder(Node* node) {
    if (!node) {
        return;
    } else {
        inOrder(node->left);
        cout << node->label << " ";
        inOrder(node->right);
    }
}

// Fungsi ini digunakan untuk menghitung kedalaman maksimal dari pohon
int maxDepth(Node* node) {
    if (node == NULL) {
        return 0;
    } else { // Rekursi untuk menghitung kedalaman dari subtree kiri dan kanan
        int leftDepth = maxDepth(node->left);
        int rightDepth = maxDepth(node->right);
        return max(leftDepth, rightDepth) + 1; // Mengembalikan kedalaman maksimal dari pohon
    }
}

// Fungsi utama program yang melakukan interaksi pengguna
int main() {
    char label, parentLabel;
    string child;
    int choice;

    cout << "Masukkan label untuk root: ";
    cin >> label;
    createTree(label);

    while (true) {
        cout << "\n1. Tambah node\n2. Pre-order traversal\n3. In-order traversal\n4. Post-order traversal\n5. Cari node\n6. Hapus subtree\n7. Hitung kedalaman maksimal\n8. Keluar\nPilih: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Masukkan label node baru: ";
                cin >> label;
                cout << "Masukkan label parent node: ";
                cin >> parentLabel;
                cout << "Masukkan posisi (left/right): ";
                cin >> child;
                insert(label, parentLabel, child);
                break;
            case 2:
                cout << "Pre-order traversal: ";
                preOrder(root);
                cout << endl;
                break;
            case 3:
                cout << "In-order traversal: ";
                inOrder(root);
                cout << endl;
                break;
            case 4:
                cout << "Post-order traversal: ";
                postOrder(root);
                cout << endl;
                break;
            case 5:
                cout << "Masukkan label node yang dicari: ";
                cin >> label;
                Node* foundNode;
                foundNode = search(root, label);
                if (foundNode) {
                    cout << "Node dengan label " << label << " ditemukan." << endl;
                } else {
                    cout << "Node dengan label " << label << " tidak ditemukan." << endl;
                }
                break;
            case 6:
                cout << "Masukkan label node yang akan dihapus subtree-nya: ";
                cin >> label;
                Node* nodeToDelete;
                nodeToDelete = search(root, label);
                if (nodeToDelete) {
                    deleteSub(nodeToDelete);
                    cout << "Subtree dengan root " << label << " telah dihapus." << endl;
                } else {
                    cout << "Node tidak ditemukan!" << endl;
                }
                break;
            case 7:
                cout << "Kedalaman maksimal tree: " << maxDepth(root) << endl;
                break;
            case 8:
                clearTree(root);
                cout << "Tree berhasil dibersihkan." << endl;
                identitas();
                return 0;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    }
}

