#include <iostream>
#include <stdexcept>
using namespace std;

struct BinaryTreeNode
{
	int								m_nValue;
	BinaryTreeNode*			m_pLeft;
	BinaryTreeNode*			m_pRight;
};

//递归构建二叉树
BinaryTreeNode* ConstructCore(
	int* startPreOrder, int* endPreOrder,			//前序遍历序列
	int* startInOrder, int* endInOrder				//中序遍历序列
	);

BinaryTreeNode* Construct(int* preOrder, int* inOrder, int length)
{
	if (preOrder == NULL || inOrder == NULL || length <= 0)  //非法输入的处理
		return NULL;	
	return ConstructCore(preOrder, preOrder + length - 1,
		inOrder, inOrder + length - 1);
}

//递归构建二叉树
BinaryTreeNode* ConstructCore(
	int* startPreOrder, int* endPreOrder,			//前序遍历序列
	int* startInOrder, int* endInOrder				//中序遍历序列
	)
{
	//前序遍历序列的第一个数字就是根节点的值
	int rootValue = startPreOrder[0];
	//创建根节点，并对其初始化
	BinaryTreeNode* root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = NULL;												//左子树的根节点
	root->m_pRight = NULL;											//右子数的根节点

	if (startPreOrder == endPreOrder)							//递归到序列中只有一个节点值的时候
	{
		if (startInOrder == endInOrder  &&						//验证前序遍历序列 和 中序遍历序列 是否一致，不一致说明序列有问题
			*startPreOrder == *startInOrder)
			return root;
		else
			throw exception("无效的输入。");
	}

	//在中序遍历序列中找到根节点的值
	int* rootInOrder = startInOrder;
	while (rootInOrder <= endInOrder && *rootInOrder != rootValue)
	{
		++rootInOrder;
	}
	//如果没有在中序遍历序列中找到根节点的值，说明输入有问题
	if (rootInOrder == endInOrder && *rootInOrder != rootValue)
		throw exception("无效输入。");

	//计算左子树的节点数
	int leftLength = rootInOrder - startInOrder;
	//在前序遍历序列中找到最后一个左子树的节点的位置
	int* leftPreOrderEnd = startPreOrder + leftLength;

	if (leftLength > 0)
	{
		//构建左子树
		root->m_pLeft = ConstructCore(startPreOrder + 1, leftPreOrderEnd,
			startInOrder, rootInOrder - 1);
	}
	if (leftLength < endPreOrder - startPreOrder) //如果还有右子树存在
	{
		//构建右子树
		root->m_pRight = ConstructCore(leftPreOrderEnd + 1, endPreOrder,
			rootInOrder + 1, endInOrder);
	}

	return root;
}

//前序输入二叉树
void PrePrintBinaryTree(BinaryTreeNode*  binaryTree)
{
	if (binaryTree == NULL)
		return;
	//第一步输出根节点
	cout << binaryTree->m_nValue << "\t";
	//第二步输出左子树
	PrePrintBinaryTree(binaryTree->m_pLeft);
	//第三步输出右子树
	PrePrintBinaryTree(binaryTree->m_pRight);
}

//删除二叉树
void DeleteBinaryTree(BinaryTreeNode** binaryTree)
{
	if (binaryTree == NULL  || *binaryTree == NULL)
		return;
	//第一步删除左子树
	DeleteBinaryTree(  &((*binaryTree)->m_pLeft)    );
	//第二步删除右子树
	DeleteBinaryTree(  &((*binaryTree)->m_pRight)  );
	//第三步删除根节点
	delete (*binaryTree);
	*binaryTree = NULL;

}

int main()
{
	/*
	*		前序遍历为{1，2，4，7，3，5，6，8}
	*		中序遍历为{4，7，2，1，5，3，8，6}
	*/
	int preOrder[]	= { 1, 2, 4, 7, 3, 5, 6, 8 };
	int inOrder[] = { 4, 7, 2, 1, 5, 3, 8, 6 };
	int length = 8;
	BinaryTreeNode* binaryTree = NULL;

	try
	{
		binaryTree = Construct(preOrder, inOrder, length);
	}
	catch (const exception&  e)
	{
		//销毁构建不完全的二叉树
		DeleteBinaryTree(&binaryTree);
		cout << e.what() << endl;
	}

	PrePrintBinaryTree(binaryTree);
	cout << endl;

	DeleteBinaryTree(&binaryTree);
	PrePrintBinaryTree(binaryTree);

	system("pause");

	return 0;
}