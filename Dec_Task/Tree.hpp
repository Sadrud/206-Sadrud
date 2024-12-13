#include <ostream>
#include <string>

struct TreeNode {
	int value;
	TreeNode* left;
	TreeNode* right;

	TreeNode () : left(nullptr), right(nullptr) {}
	TreeNode (int val) : value(val), left(nullptr), right(nullptr) {}
	~TreeNode () {}
};

int calculatePaths (TreeNode* node, int number);
int Process (TreeNode* node);

TreeNode* TListFill (int lenLevel);
TreeNode* connect (TreeNode* parentList, TreeNode* childList);
TreeNode* addNode (int value, TreeNode* prev);
void add (TreeNode* node, int quantity);
void del (TreeNode* node);
void printTree (TreeNode* root, int depth);
