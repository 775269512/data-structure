
# Huffman压缩编码

## 1. 核心知识

（1） 树的存储结构
（2） 二叉树的三种遍历方法
（3） Huffman树、Huffman编码算法

## 2. 功能要求

1.  针对一幅BMP格式的图片文件，统计256种不同字节的重复次数，以每种字节重复次数作为权值，构造一颗有256个叶子节点的哈夫曼二叉树。

2.  利用上述哈夫曼树产生的哈夫曼编码对图片文件进行压缩。

3.  压缩后的文件与原图片文件同名，加上后缀.huf（保留原后缀），如pic.bmp
    压缩后pic.bmp.huf

## 3.分析与设计

使用Huffman算法实现图片压缩程序，可分为6个步骤。

（1）创建工程

创建HuffmanCompressCPro工程，定义入口函数int main()；

（2）读取原文件

读取文件，统计256种字节重复的次数；

（3）生成Huffman树

根据上一步统计的结果，构建Huffman树；

（4）生成Huffman编码

遍历Huffman树，记录256个叶子节点的路径，生成Huffman编码；

（5）压缩编码

使用Huffman编码，对原文件中的字节重新编码，获得压缩后的文件数据；

（6）保存文件

将编码过的数据，保存到文件“Pic.bmp.huf”中。

## 4. 数据结构的设计

1.记录统计256种不同字节的重复次数即权值使用整型数组：

> unsigned int weight[256];

2.二叉树的存储结构。使用结构体存储节点，使用数组存储树的节点，使用静态二叉链表方式存储二叉树。
```c++
struct HuffNode
{
	unsigned char ch;  //字节符
	int weight;  //字节出现频度
	int parent; //父节点
	int lchild;  //左孩子
	int rchild;  //右孩子
	char bits[256]; // 哈夫曼编码
};

// Huffman树
typedef char** HuffmanCode;
```

3.Huffman编码存储结构定义一个二维数组:

> typedef char** HuffmanCode;


4.压缩文件的算法的数据结构:

为正确解压文件，除了要保存原文件长度外，还要保存原文件中256种字节重复的次数，即权值。定义一个文件头，保存相关的信息：
```c++
struct FILESTRUCT
{
	int sum;
	int fileid;
};
```


## 5. 核心算法设计

**（1）构造Huffman树算法 **
```c++
int CreateHuffmanTree(HuffNode *huf_tree, int n)//构造huffman树
{
	int i;
	int s1, s2;
	for (i = n; i < 2 * n - 1; ++i)
	{
		select(huf_tree, i, &s1, &s2);		// 选择最小的两个结点
		huf_tree[s1].parent = i;            //原点双亲为i
		huf_tree[s2].parent = i;
		huf_tree[i].lchild = s1;               //新结点左子树是最小的s1
		huf_tree[i].rchild = s2;               //新结点右子树是最小s2
		huf_tree[i].weight = huf_tree[s1].weight + huf_tree[s2].weight;////新结点的权值
	}
	return OK;
}

void select(HuffNode *huf_tree, int n, int *s1, int *s2)//在HT[1~I-1】选择parent为零且为最小的两个数，序号分别为s1,s2
{
	// 找最小结点
	unsigned int i;
	unsigned long min = LONG_MAX;
	for (i = 0; i < n; i++)
		if (huf_tree[i].parent == -1 && huf_tree[i].weight < min)
		{
			min = huf_tree[i].weight;
			*s1 = i;//记录下标
		}
	huf_tree[*s1].parent = 1;   // 标记此结点已被选中

								// 找次小结点
	min = LONG_MAX;
	for (i = 0; i < n; i++)
	{
		if (huf_tree[i].parent == -1 && huf_tree[i].weight < min)
		{
			min = huf_tree[i].weight;
			*s2 = i;
		}
	}
}
```
**（2）生成Huffman编码算法 **
```c++
int HuffmanCoding(HuffNode *huf_tree, int n)
{
	int i;
	int cur, next, index;
	char code_tmp[256];		// 暂存编码，最多256个叶子，编码长度不超多255
	code_tmp[255] = '\0';

	for (i = 0; i < n; ++i)
	{
		index = 256 - 1;	// 编码临时空间初始化

							// 从叶子向根求编码
		for (cur = i, next = huf_tree[i].parent; next != -1; next = huf_tree[next].parent)
		{
			if (huf_tree[next].lchild == cur)
				code_tmp[--index] = '0';	// 左‘0’
			else
				code_tmp[--index] = '1';	// 右‘1’

			cur = next;

		}
		strcpy(huf_tree[i].bits, &code_tmp[index]);     // 正向保存编码到树结点相应域 index是第一个
	}
	return OK;
}

```
**（4）生成压缩文件算法：**
```int compress(HuffNode huf_tree[], int n, long flength, char *ifname, char *ofname)
{
	FILE * inFile = fopen(ifname, "rb");//打开要压缩文件
	FILE * outFile = fopen(ofname, "wb");//打开压缩后文件

	unsigned char temp = '\0';            //8bit临时的变量

	char buffer[256] = "\0";           //缓存流

	char tou[20];                     //文件后缀名字符数组
	int z = 0;
	int strLen = strlen(ifname);//文件后缀名长度
	for (int g = strLen - 1; g>0; g--)//获取文件后缀名（从后面获取）
	{
		if (ifname[g] == '.')//获取文件后缀名最后一个“.”
		{
			for (int k = g; k< strLen; k++)
			{
				z++;
				tou[z] = ifname[k];

			}
		}
	}

	tou[0] = z + '0';//获取文件后缀名长度(转成字符)
	fwrite((char *)&tou, sizeof(char), z + 1, outFile);//存文件头部
	fwrite(&flength, sizeof(long), 1, outFile);//存总长度
	fwrite(&n, sizeof(int), 1, outFile);//存字符的种类

	for (int i = 0; i < n; i++) {//存每个编号对应的字符,权重
		fwrite(&huf_tree[i].ch, sizeof(unsigned char), 1, outFile);
		fwrite(&huf_tree[i].weight, sizeof(long), 1, outFile);
		/*for (int f = 0; huf_tree[i].bits[f] == '0' || huf_tree[i].bits[f] == '1'; f++)
		{
		fwrite(&huf_tree[i].bits[f], sizeof(char), 1, outFile);
		}*/
	}


	while (fread(&temp, sizeof(unsigned char), 1, inFile))//文件不为空
	{
		for (int i = 0; i <n; i++)//找对应字符
		{
			if (temp == huf_tree[i].ch)
			{
				for (int f = 0; huf_tree[i].bits[f] == '0' || huf_tree[i].bits[f] == '1'; f++)//过滤掉非0非1的编码（数组带来的弊端）
				{
					strncat(buffer, &huf_tree[i].bits[f], 1);//给缓存流赋值
				}
			}

		}
		while (strlen(buffer) >= 8)//缓存流大于等于8个bits进入循环 
		{
			temp = 0;
			for (int i = 0; i < 8; i++)//每8个bits循环一次
			{
				temp = temp << 1;//左移1
				if (buffer[i] == '1')//如果是为1，就按位为1
				{
					temp = temp | 0x01;//在不影响其他位的情况下，最后位置1
				}
			}
			fwrite(&temp, sizeof(unsigned char), 1, outFile);//写入文件
			strcpy(buffer, buffer + 8);//将写入文件的bits删除
		}
	}
	int m = strlen(buffer);//将剩余不足为8的bits的个数给l
	if (m) {
		temp = 0;
		for (int i = 0; i < m; i++)
		{
			temp = temp << 1;//移动1
			if (buffer[i] == '1')//如果是为1，就按位为1
			{
				temp = temp | 0x01;
			}

		}
		temp <<= 8 - m;// // 将编码字段从尾部移到字节的高位
		fwrite(&temp, sizeof(unsigned char), 1, outFile);//写入最后一个
	}

	fclose(inFile);
	fclose(outFile);
	return 1;
}//compress
```
**（5）解压算法：**
```c++
int extract(HuffNode huf_tree[],  char *ifname, char *ofname)
{
	int i;
	char huozui;                          //文件后缀长度
	char tou[20];                         //文件后缀字符
	long flength;                         //文件总长度
	int n;                               //字符种类
	int node_num;                        //结点总数
	unsigned long writen_len = 0;		// 控制文件写入长度
	FILE *infile, *outfile;
	unsigned char code_temp;		// 暂存8bits编码
	unsigned int root;		// 保存根节点索引，供匹配编码使用

	infile = fopen(ifname, "rb");		// 以二进制方式打开压缩文件
	// 判断输入文件是否存在
	if (infile == NULL)
		return -1;

	//读取文件后缀名长度
	fread(&huozui, sizeof(char),1,infile);
	//字符转数字
	int huozui_du = huozui - '0';
	//读取文件后缀字符
	fread(&tou, sizeof(char), huozui_du, infile); //读取文件后缀字符
	fread(&flength, sizeof(long), 1, infile);    //读取文件总长度
	fread(&n, sizeof(int), 1, infile);          //读取字符种类

	node_num = 2 * n - 1;		// 根据字符种类数，计算建立哈夫曼树所需结点数 
		
	// 初始化后
	for (int a = 0; a < 512; a++)    
	{
		huf_tree[a].parent = -1;
		huf_tree[a].ch = NULL;
		huf_tree[a].weight = -1;
		huf_tree[a].lchild = -1;
		huf_tree[a].rchild = -1;
	}

	// 读取压缩文件前端的字符及对应权重，用于重建哈夫曼树
	for (i = 0; i < n; i++)
	{
		fread((char *)&huf_tree[i].ch, sizeof(unsigned char), 1, infile);		// 读入字符
		fread((char *)&huf_tree[i].weight, sizeof(long), 1, infile);	// 读入字符对应权重
	}

	CreateHuffmanTree(huf_tree, n);//构建哈夫曼仿真指针孩子父亲表示法
	HuffmanCoding(huf_tree, n);//生成哈夫曼编码


	//printf("\n");
	//for (int d = 0; d < 2 * n - 1; d++)//仅供测试
	//{
	//	printf("%4d: %4u,   %9d,  %9d,   %9d,  %9d       ", d, huf_tree[d].ch, huf_tree[d].count, huf_tree[d].parent, huf_tree[d].lch, huf_tree[d].rch);  /* 用于测试 */

	//	for (int f = 0; huf_tree[d].bits[f] == '0' || huf_tree[d].bits[f] == '1'; f++)
	//		printf("%c", huf_tree[d].bits[f]);
	//	printf("\n");
	//}

	strncat(ofname, tou, huozui_du);

	outfile = fopen(ofname, "wb");		// 打开压缩后将生成的文件
	root = node_num - 1;                //根结点的下标
	while (1)
	{
		fread(&code_temp, sizeof(unsigned char), 1, infile);		// 读取一个字符长度的编码

		// 处理读取的一个字符长度的编码（通常为8位）
		for (i = 0; i < 8; i++)
		{
			// 由根向下直至叶节点正向匹配编码对应字符（逆向）
			if (code_temp & 128)//128是1000 0000   按位与就是编码缓存的最高位是否为1
				root = huf_tree[root].rchild;//为1，root=右子树
			else
				root = huf_tree[root].lchild;//为0，root=左子树

			if (root < n)//0到n-1的左右子树为-1
			{
				fwrite(&huf_tree[root].ch, sizeof(unsigned char), 1, outfile);
				writen_len++;//已编译字符加一
				if (writen_len == flength) break;		// 控制文件长度，跳出内层循环
				root = node_num - 1;        // 复位为根索引，匹配下一个字符
			}
			code_temp <<= 1;		// 将编码缓存的下一位移到最高位，提供匹配
		}
		if (writen_len == flength) break;		// 控制文件长度，跳出外层循环
	}

   //关闭文件
	fclose(infile);
	fclose(outfile);
	return 1;
}//extract()
```

## 6. 开发环境

* Windows10_x64
* Microsoft Visual Studio 2017以上开发环境

## 7. 调试说明

调试主要内容为编写程序的语法正确性与否，程序逻辑的正确性与否。调试手段主要采用了Microsoft Visual Studio 2017集成开发环境中“调试（D）”菜单中的调试方法或手段。即：F5：启动调试；F11：逐语句调试；F12：逐过程调试；F9：切换断点；ctrl+B：新建断点等。并且根据VS2017的文本编辑器智能语法提示修改已知错误，然后启用调试，待调试通过检查运行结果，最后用边界值等进行多方面测试，保证程序的健壮性。

1. 在读取图片文件统计0-255个字符的权值的过程中，一开始采用了C\++的ifstream fin(“Pic.bmp”)文件流，然后通过while(fin>>ch){ cout<<ch;}测试输出文件字符码，就出现了无限循环，一直连续不断地输出6位十六进制的数。当时认为是文件流读取方式的原因，加了iOS::binary来控制采用二进制形式，还是没有解决。改用C语言的FILE *fp = fope( )终于可以正常读取输出文件字符码，但是还是没有找出C\++读取失败的原因。

2. 为了便于压缩，解压文件，节点增加huffman编码`char bits[256] `以及字节符`unsigned char ch`
文件压缩时将文件头部，总长度，字符种类和权重持久化，便于解压缩。

3. 编译时总是提示fopen，strcpy，strcat等函数存在不安全问题，采用了3中方法中一种屏蔽了该报错。即在文件开头添加：
> \#pragma warning(disable:4996)

## 8. 测试效果

使用屏幕截图编辑成bmp图片文件pic.bmp测试哈夫曼压缩程序效果截图如下
各图。图1为输入文件名压缩成功界面；图2为读取Pic.bmp产生的部分不同权值字节信息；图3、4为Pic.bmp生成的HuffmanTree结点信息；图5为生成的Huffman编码信息；图6为Pic.bmp压缩大小及压缩率。

图1：输入文件名压缩成功界面

![](https://ae01.alicdn.com/kf/HTB1svr2TOLaK1RjSZFxq6ymPFXaL.jpg)

图2压缩文件大小对比

![](https://ae01.alicdn.com/kf/HTB1TLnFTHvpK1RjSZPiq6zmwXXaz.jpg)

图3:文件解压

![](https://ae01.alicdn.com/kf/HTB18nHETH2pK1RjSZFsq6yNlXXag.jpg)

图4：源文件与解压文件对比

![](https://ae01.alicdn.com/kf/HTB16xPBTSzqK1RjSZPxq6A4tVXaL.jpg)

图5：对于jpg格式的压缩

![](https://ae01.alicdn.com/kf/HTB1CkzLTQvoK1RjSZFNq6AxMVXaE.jpg)
## 9. 综合分析和结论

（1）在哈弗曼编码的过程中，对字符按概率有大到小的顺序重新排列，应使合并后的新符号尽可能排在靠前的位置，这样可使合并后的新符号重复编码次数减少，使短码得到充分利用。

（2）哈弗曼编码效率相当高，对编码器的要求也简单得多。

（3）哈弗曼它保证了出现概率大的符号对应于短码，概率小的符号对应于长码，每次字符的最后两个码字总是最后一位码元不同，前面的各位码元都相同，每次字符的最长两个码字有相同的码长。

（4）哈弗曼的编法并不一定是唯一的。

（5）通过上述测试用例的效果截图，可以看出：使用哈夫曼编码对格式为bmp的图片文件的压缩比在50%左右，针对jpg格式图片压缩或出现图片严重失真现象。
## 10.项目原码
[github](https://github.com/ljyslyc/data-structure/tree/master/huffmanty)
