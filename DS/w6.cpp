#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : data(x), left(nullptr), right(nullptr) {}
};


TreeNode* buildTree(const vector<int>& node) {
    if((node.empty())||(node[0]==-1)){   
        return nullptr;
    } 
    vector<TreeNode*> tree(node.size(),nullptr);
    
    for(int i=0; i<node.size(); i++){
        if(node[i]==(-1)){      //跳過-1
            continue;
        }

        if(tree[i]==nullptr){
            tree[i]=new TreeNode(node[i]);
        }

        int l=2*i+1;
        int r=2*i+2;

        if((l<node.size())&&node[l]!=-1){
            tree[l]=new TreeNode(node[l]);
            tree[i]->left=tree[l];
        }

        if((r<node.size())&&(node[r]!=-1)){
            tree[r]=new TreeNode(node[r]);
            tree[i]->right=tree[r];
        }
    }
    
    return tree[0];
}


void inorder(TreeNode* root){
    if(root!=nullptr){
        inorder(root->left);
        cout<<(root->data)<<" ";
        inorder(root->right);    
    }
}

void preorder(TreeNode* root){
    if(root!=nullptr){
        cout<<(root->data)<<" ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TreeNode* root){
    if(root!=nullptr){
        postorder(root->left);
        postorder(root->right);
        cout<<(root->data)<<" ";
    }
}

/*邊找邊存 到最後沒有*/
bool search(TreeNode* root, int target, vector<int>& cumul) {
    
    //走到最後了
    if (root==nullptr){  //還沒有
        return false;
    }

    cumul.push_back(root->data);
    
    if((root->data)==target){
        return true;
    }

    //還沒到最後也還沒找到 找子樹 其一有就true
    if((search(root->left,target,cumul))||(search(root->right,target,cumul))){
        return true;
    }
    
    //子樹沒找到 刪掉剛存的
    cumul.pop_back();

    //還沒最後 還沒找到 子樹此條路徑也沒有 (用在line87判斷式)
    return false;
}

int main() {
    int n,target;
    cin>>n;
    
    vector<int>location(n);
    for (int i=0; i<n; i++) {
        cin>>location[i];
    }

    cin>>target;
    
    TreeNode* root=buildTree(location);
    
    inorder(root);
    cout<<endl;

    preorder(root);
    cout<<endl;

    postorder(root);
    cout<<endl;
    
    

    vector<int> cumul;
    if(search(root,target,cumul)==true){
        int sum=0;
        for(int i=0;i<cumul.size();i++){
            sum+=cumul[i];
        }
        cout<<sum;
    }else{
        cout<<(-1);
    }
    
    return 0;
}