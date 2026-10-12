#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Build BST from level order array
TreeNode* buildBSTFromLevelOrder(const vector<int>& values) {
    if (values.empty()) return nullptr;
    
    TreeNode* root = new TreeNode(values[0]);
    
    for (size_t i = 1; i < values.size(); i++) {
        TreeNode* node = new TreeNode(values[i]);
        TreeNode* current = root;
        
        // Insert node into BST
        while (true) {
            if (values[i] < current->val) {
                if (current->left == nullptr) {
                    current->left = node;
                    break;
                }
                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = node;
                    break;
                }
                current = current->right;
            }
        }
    }
    
    return root;
}

// Find kth largest element using reverse in-order traversal
int kthLargest = -1;
int visitCount = 0;

void reverseInOrder(TreeNode* node, int k) {
    if (node == nullptr || visitCount >= k) return;
    
    // Visit right subtree first (for descending order)
    reverseInOrder(node->right, k);
    
    // Process current node
    visitCount++;
    if (visitCount == k) {
        kthLargest = node->val;
        return;
    }
    
    // Visit left subtree
    reverseInOrder(node->left, k);
}

// Clean up memory
void deleteTree(TreeNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    vector<int> values;
    int input;
    
    // Read 7 values for BST nodes
    for (int i = 0; i < 7; i++) {
        cin >> input;
        values.push_back(input);
    }
    
    // Read k (cnt)
    int k;
    cin >> k;
    
    // Build BST
    TreeNode* root = buildBSTFromLevelOrder(values);
    
    // Find kth largest
    reverseInOrder(root, k);
    
    // Output result
    cout << kthLargest << endl;
    
    // Clean up
    deleteTree(root);
    
    return 0;
}