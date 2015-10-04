#include <iostream>
#include <stdexcept>
using namespace std;

struct BinaryTreeNode
{
	int								m_nValue;
	BinaryTreeNode*			m_pLeft;
	BinaryTreeNode*			m_pRight;
};

//�ݹ鹹��������
BinaryTreeNode* ConstructCore(
	int* startPreOrder, int* endPreOrder,			//ǰ���������
	int* startInOrder, int* endInOrder				//�����������
	);

BinaryTreeNode* Construct(int* preOrder, int* inOrder, int length)
{
	if (preOrder == NULL || inOrder == NULL || length <= 0)  //�Ƿ�����Ĵ���
		return NULL;	
	return ConstructCore(preOrder, preOrder + length - 1,
		inOrder, inOrder + length - 1);
}

//�ݹ鹹��������
BinaryTreeNode* ConstructCore(
	int* startPreOrder, int* endPreOrder,			//ǰ���������
	int* startInOrder, int* endInOrder				//�����������
	)
{
	//ǰ��������еĵ�һ�����־��Ǹ��ڵ��ֵ
	int rootValue = startPreOrder[0];
	//�������ڵ㣬�������ʼ��
	BinaryTreeNode* root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = NULL;												//�������ĸ��ڵ�
	root->m_pRight = NULL;											//�������ĸ��ڵ�

	if (startPreOrder == endPreOrder)							//�ݹ鵽������ֻ��һ���ڵ�ֵ��ʱ��
	{
		if (startInOrder == endInOrder  &&						//��֤ǰ��������� �� ����������� �Ƿ�һ�£���һ��˵������������
			*startPreOrder == *startInOrder)
			return root;
		else
			throw exception("��Ч�����롣");
	}

	//����������������ҵ����ڵ��ֵ
	int* rootInOrder = startInOrder;
	while (rootInOrder <= endInOrder && *rootInOrder != rootValue)
	{
		++rootInOrder;
	}
	//���û������������������ҵ����ڵ��ֵ��˵������������
	if (rootInOrder == endInOrder && *rootInOrder != rootValue)
		throw exception("��Ч���롣");

	//�����������Ľڵ���
	int leftLength = rootInOrder - startInOrder;
	//��ǰ������������ҵ����һ���������Ľڵ��λ��
	int* leftPreOrderEnd = startPreOrder + leftLength;

	if (leftLength > 0)
	{
		//����������
		root->m_pLeft = ConstructCore(startPreOrder + 1, leftPreOrderEnd,
			startInOrder, rootInOrder - 1);
	}
	if (leftLength < endPreOrder - startPreOrder) //�����������������
	{
		//����������
		root->m_pRight = ConstructCore(leftPreOrderEnd + 1, endPreOrder,
			rootInOrder + 1, endInOrder);
	}

	return root;
}

//ǰ�����������
void PrePrintBinaryTree(BinaryTreeNode*  binaryTree)
{
	if (binaryTree == NULL)
		return;
	//��һ��������ڵ�
	cout << binaryTree->m_nValue << "\t";
	//�ڶ������������
	PrePrintBinaryTree(binaryTree->m_pLeft);
	//���������������
	PrePrintBinaryTree(binaryTree->m_pRight);
}

//ɾ��������
void DeleteBinaryTree(BinaryTreeNode** binaryTree)
{
	if (binaryTree == NULL  || *binaryTree == NULL)
		return;
	//��һ��ɾ��������
	DeleteBinaryTree(  &((*binaryTree)->m_pLeft)    );
	//�ڶ���ɾ��������
	DeleteBinaryTree(  &((*binaryTree)->m_pRight)  );
	//������ɾ�����ڵ�
	delete (*binaryTree);
	*binaryTree = NULL;

}

int main()
{
	/*
	*		ǰ�����Ϊ{1��2��4��7��3��5��6��8}
	*		�������Ϊ{4��7��2��1��5��3��8��6}
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
		//���ٹ�������ȫ�Ķ�����
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