int IsLastOrder(int Order[], int len)
{
    if (Order == NULL || len <= 0)
    {
        return 0;
    }
    //确定根节点(数组最后一个数)
    int root = Order[len - 1];
    int i = 0;
    //找到第一个大于根结点的值
    for (; i < len - 1; i++)
    {
        if (Order[i] > root)
        {
            break;
        }
    }
    //现在i为第一个大于root的值得下标
    int j = i;
    //在右子树中如果存在小于根的值，则必然不是二叉搜索树
    for (; j < len - 1; j++)
    {
        if (Order[j] < root)
        {
            return 0;
        }
    }
    //递归判断左子树(如果左子树为空，则只需判断右子树）
    int left = 1;
    if (i > 0)
    {
        //左子树数组的长度为i
        left = IsLastOrder(Order, i);
    }
    //递归判断右子树(如果右子树为空，则只需判断左子树)
    int right = 1;
    if (i < len - 1)
    {
        //右子树数组的长度为len-i-1(要减去根结点)
        right = IsLastOrder(Order + i, len - i - 1);
    }
    return left&&right;
}