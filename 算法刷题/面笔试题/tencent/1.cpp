#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 返回节点权值1个数比0的个数多一的路径数
     * @param root TreeNode类 权值为0和1的二叉树根节点
     * @return int整型
     */
    int pathNumber(TreeNode* root) {
        // write code here
        vector<string> vec;
        string s;
        dfs(root, vec, s);
        int res = 0;
        for (string s : vec){
            int cal0 = 0, cal1 = 0;
            for (char c : s){
                if (c == '0') cal0++;
                else cal1++;
            }
            if (cal1 - cal0 == 1) res++;
        }
        return res;
    }
    
    void dfs(TreeNode* root, vector<string> &vec, string &s){
        if (root){
            s += to_string(root->val);
            if (root->left == nullptr && root->right == nullptr) vec.push_back(s);
            dfs(root->left, vec, s);
            dfs(root->right, vec, s);
            s.erase(s.size()-1);
        }
    }
};

int main()
{
    TreeNode* root = new TreeNode(1);
    TreeNode* node1 = new TreeNode(0);
    TreeNode* node2 = new TreeNode(0);
    TreeNode* node3 = new TreeNode(1);
    TreeNode* node4 = new TreeNode(1);
    root->left = node1;
    root->right = node2;
    node1->left = node3;
    node1->right = node3;
    Solution s;
    int ret = s.pathNumber(root);
    cout << "ret = " << ret << endl;
}