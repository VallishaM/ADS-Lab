#include <iostream>
	using namespace std;
	

	class TwoThreeNode
	{
	    int *keys;
	    int t;
	    TwoThreeNode **C;
	    int n;
	    bool leaf;
	

	public:
	    TwoThreeNode(bool _leaf);
	    void traverse();
	    TwoThreeNode *search(int k);
	    void insertNonFull(int k);
	    void splitChild(int i, TwoThreeNode *y);
	    friend class TwoThreeTree;
	};
	

	class TwoThreeTree
	{
	    TwoThreeNode *root;
	    int t;
	

	public:
	    TwoThreeTree()
	    {
	        root = NULL;
	        t = 2;
	    }
	

	    void traverse()
	    {
	        if (root != NULL)
	            root->traverse();
	    }
	

	    TwoThreeNode *search(int k)
	    {
	        return (root == NULL) ? NULL : root->search(k);
	    }
	

	    void insert(int k);
	};
	

	TwoThreeNode::TwoThreeNode(bool leaf1)
	{
	    t = 2;
	    leaf = leaf1;
	    keys = new int[2 * t - 1];
	    C = new TwoThreeNode *[2 * t];
	    n = 0;
	}
	

	void TwoThreeTree::insert(int k)
	{
	    if (root == NULL)
	    {
	        root = new TwoThreeNode(true);
	        root->keys[0] = k;
	        root->n = 1;
	    }
	    else
	    {
	        if (root->n == 2 * t - 1)
	        {
	            TwoThreeNode *s = new TwoThreeNode(false);
	            s->C[0] = root;
	            s->splitChild(0, root);
	            int i = 0;
	            if (s->keys[0] < k)
	                i++;
	            s->C[i]->insertNonFull(k);
	            root = s;
	        }
	        else
	            root->insertNonFull(k);
	    }
	}
	

	void TwoThreeNode::insertNonFull(int k)
	{
	

	    int i = n - 1;
	    if (leaf == true)
	    {
	        while (i >= 0 && keys[i] > k)
	        {
	            keys[i + 1] = keys[i];
	            i--;
	        }
	        keys[i + 1] = k;
	        n = n + 1;
	    }
	    else
	    {
	        while (i >= 0 && keys[i] > k)
	            i--;
	        if (C[i + 1]->n == 2 * t - 1)
	        {
	            splitChild(i + 1, C[i + 1]);
	            if (keys[i + 1] < k)
	                i++;
	        }
	        C[i + 1]->insertNonFull(k);
	    }
	}
	

	void TwoThreeNode::splitChild(int i, TwoThreeNode *y)
	{
	

	    TwoThreeNode *z = new TwoThreeNode(y->leaf);
	    z->n = t - 1;
	    for (int j = 0; j < t - 1; j++)
	        z->keys[j] = y->keys[j + t];
	    if (y->leaf == false)
	    {
	        for (int j = 0; j < t; j++)
	            z->C[j] = y->C[j + t];
	    }
    }
void TwoThreeNode::traverse()
	{
	

	    int i;
	    for (i = 0; i < n; i++)
	    {
	        if (leaf == false)
	            C[i]->traverse();
	        cout << " " << keys[i];
	    }
	    if (leaf == false)
	        C[i]->traverse();
	}
	

	TwoThreeNode *TwoThreeNode::search(int k)
	{
	    int i = 0;
	    while (i < n && k > keys[i])
	        i++;
	    if (keys[i] == k)
	        return this;
	

	    if (leaf == true)
	        return NULL;
	    return C[i]->search(k);
	}
	

	

	

	int main()
	{
	    TwoThreeTree t;
	

	    cout << "Enter number of nodes to insert: ";
	    int n;
	    cin >> n;
	    for (int i = 0; i < n; i++)
	    {
	        cout << "Enter node " << i + 1 << " : ";
	        int node;
	        cin >> node;
	        t.insert(node);
	        cout << "Tree is \n";
	        t.traverse();
	        cout << endl;
	    }
	

	    return 0;
	}
