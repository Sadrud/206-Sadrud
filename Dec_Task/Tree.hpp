#include <ostream>

struct TreeNode {
	int value;
	TreeNode* left;
	TreeNode* right;

	TreeNode () : left(nullptr), right(nullptr) {}
	TreeNode (int val) : value(val), left(nullptr), right(nullptr) {}
	~TreeNode () {}
};

class Tree {
	public:
	TreeNode* root;
	Tree () : root(nullptr) {}
	
	int calculatePaths (TreeNode* node, int currentSum);
	int Process () { return calculatePaths (root, 0); }
	void add (int val, TreeNode* node);
};

void add (int val, TreeNode* node);
void del (TreeNode* node);
