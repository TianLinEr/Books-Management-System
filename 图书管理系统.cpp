#include <bits/stdc++.h>
#include<cstdlib>
#include <graphics.h> 
#define MAX 1000000
using namespace std;
TCHAR MIMA[] = L"kaifa2021";
ofstream fp1;
ofstream fp2;
struct book
{
	TCHAR namebook[50];
	TCHAR number[30];
	TCHAR area[30];
	TCHAR residue[10];//剩余图书数量 
};
struct stu
{
	TCHAR namestu[50];
	TCHAR id[30];
	TCHAR namebook[50];
	TCHAR timestart[20];
	TCHAR timeend[20];
}; 
struct bookc
{
	char namebook[50];
	char number[30];
	char area[30];
	char residue[10];//剩余图书数量 
};
struct stuc
{
	char namestu[50];
	char id[30];
	char namebook[50];
	char timestart[20];
	char timeend[20];
};
struct booksum
{
	struct book p[MAX];
	struct bookc q[MAX];
	int size;
}sum;
struct booksum_
{
	struct stu p[MAX];
	struct stuc q[MAX];
	int size;
}sum1;
void read(booksum_*, booksum*);
void write1(booksum*,int);
void write2(booksum_*,int);
void show();//菜单 
void show1();
void show2();
void show3();
void add(booksum *);//添加
void amend(booksum *);//修改
void del(booksum *);//删除
void find(booksum *);//查找
void rent(booksum_ *,booksum *);//租借
void back(booksum_ *,booksum *);//还回 
void empty(booksum_ *,booksum *,int);//清空 
void showall(booksum *);//显示全部 
void showrent(booksum_ *);//显示租借   
int seek(booksum *,TCHAR[]);//查找是否存在 
int seek1(booksum *,TCHAR[]);
int seek2(booksum_ *,TCHAR[]);
int seek3(booksum_ *,TCHAR[], TCHAR[]);
int seek4(booksum_*, TCHAR[]);
int cmp(TCHAR[],TCHAR[]);
void TCHARtochar(TCHAR*, char*);
void chartoTCHAR( char*,TCHAR*);
void And(string, string,char[]);

int main()
{
	sum.size =0;
	sum1.size =0;
	read(&sum1,&sum);
	initgraph(640, 480);
	while(1)
	{
		cleardevice();
		setbkcolor(WHITE);
		setlinestyle(PS_SOLID, 1);
		setbkmode(TRANSPARENT); 
		sept:
		show();
		ExMessage mag;
		while (1)
		{
			if (peekmessage(&mag, EM_MOUSE))
			{
				switch (mag.message)
				{
				case WM_LBUTTONDOWN:
				{
					if (mag.x >= 360 && mag.x <= 640)
					{
						if (mag.y >= 240 && mag.y <= 280)
						{
							sept1:
							show1();
							ExMessage mag;
							while (1)
							{
								if (peekmessage(&mag, EM_MOUSE))
								{
									switch (mag.message)
									{
									case WM_LBUTTONDOWN:
									{
										if (mag.x >= 240 && mag.x <= 360)
										{
											if (mag.y >= 60 && mag.y <= 110)
												add(&sum);
											else if (mag.y >= 120 && mag.y <= 170)
												amend(&sum);
											else if ((mag.y >= 180 && mag.y <= 230))
												del(&sum);
											else if ((mag.y >= 240 && mag.y <= 290))
												find(&sum);
											else if ((mag.y >= 300 && mag.y <= 350))
												showall(&sum);
											else if ((mag.y >= 360 && mag.y <= 410))
												goto sept;
											goto sept1;
										}
										break;
									}
									default:
										break;
									}
								}
							}
						}		
						else if (mag.y >= 290 && mag.y <= 340)
						{
							sept2:
							show2();
							ExMessage mag;
							while (1)
							{
								if (peekmessage(&mag, EM_MOUSE))
								{
									switch (mag.message)
									{
									case WM_LBUTTONDOWN:
									{
										if (mag.x >= 240 && mag.x <= 360)
										{
											if ((mag.y >= 110 && mag.y <= 150))
												rent(&sum1,&sum);
											else if ((mag.y >= 170 && mag.y <= 220))
												back(&sum1,&sum);
											else if ((mag.y >= 230 && mag.y <= 280))
												showrent(&sum1);
											else if ((mag.y >= 290 && mag.y <= 330))
												goto sept;
											goto sept2;
										}
										break;
									}
									default:
										break;
									}
								}
							}
						}	
						else if ((mag.y >= 350 && mag.y <= 400))
						{
							sept3:
							show3();
							ExMessage mag;
							while (1)
							{
								if (peekmessage(&mag, EM_MOUSE))
								{
									switch (mag.message)
									{
									case WM_LBUTTONDOWN:
									{
										if (mag.x >= 240 && mag.x <= 360)
										{
											if ((mag.y >= 210 && mag.y <= 280))
												empty(&sum1, &sum,1);
											else if ((mag.y >= 290 && mag.y <= 380))
												empty(&sum1, &sum,2);
											else if ((mag.y >= 130 && mag.y <= 200))
												goto sept;
											goto sept3;
										}
										break;
									}
									default:
										break;
									}
								}
							}
						}
						else if ((mag.y >= 410 && mag.y <= 460))
						{
							cleardevice();
							IMAGE img;
							loadimage(&img, L"./结束.jfif", 640, 480);
							putimage(0, 0, &img);
							system("pause");
							closegraph();
							return 0;
						}
						}	
						break;
					}
					default:
						break;
				}
			}
		}
	} 
} 

void read(booksum_* sum1, booksum* sum)
{
	char buff[50];
	ifstream fp1("book.txt");
	ifstream fp2("stu.txt");
	int i = 1;
	while (!fp1.eof())
	{
		if (i <= 4)
		{
			fp1.getline(buff, 50);
			if (i == 1)
			{
				strcpy_s(sum->q[sum->size].namebook, strlen(buff)+1, buff);
				chartoTCHAR(sum->q[sum->size].namebook, sum->p[sum->size].namebook);
			}
			else if (i == 2)
			{
				strcpy_s(sum->q[sum->size].number, strlen(buff) + 1, buff);
				chartoTCHAR(sum->q[sum->size].number, sum->p[sum->size].number);
			}

			else if (i == 3)
			{
				strcpy_s(sum->q[sum->size].area, strlen(buff) + 1, buff);
				chartoTCHAR(sum->q[sum->size].area, sum->p[sum->size].area);
			}
			else if (i == 4)
			{
				strcpy_s(sum->q[sum->size].residue, strlen(buff) + 1, buff);
				chartoTCHAR(sum->q[sum->size].residue, sum->p[sum->size].residue);
				sum->size++;
			}
			i++;
		}
		else
			i -= 4;
	}
	i = 1;
	while (!fp2.eof())
	{
		if (i <= 5)
		{
			fp2.getline(buff, 50);
			if (i == 1)
			{
				strcpy_s(sum1->q[sum1->size].namestu, strlen(buff) + 1, buff);
				chartoTCHAR(sum1->q[sum1->size].namestu, sum1->p[sum1->size].namestu);
			}
			else if (i == 2)
			{
				strcpy_s(sum1->q[sum1->size].id, strlen(buff) + 1, buff);
				chartoTCHAR(sum1->q[sum1->size].id, sum1->p[sum1->size].id);
			}
			else if (i == 3)
			{
				strcpy_s(sum1->q[sum1->size].namebook, strlen(buff) + 1, buff);
				chartoTCHAR(sum1->q[sum1->size].namebook, sum1->p[sum1->size].namebook);
			}
			else if (i == 4)
			{
				strcpy_s(sum1->q[sum1->size].timestart, strlen(buff) + 1, buff);
				chartoTCHAR(sum1->q[sum1->size].timestart, sum1->p[sum1->size].timestart);
			}
			else if (i == 5)
			{
				strcpy_s(sum1->q[sum1->size].timeend, strlen(buff) + 1, buff);
				chartoTCHAR(sum1->q[sum1->size].timeend, sum1->p[sum1->size].timeend);
				sum1->size++;
			}
			i++;
		}
		else
			i -= 5;
	}
	return;
}
void write1( booksum* sum,int a)
{
	fp1.open("book.txt", ios::app);
	if (fp1.is_open())
	{
		int i = 1;
		while (fp1.is_open())
		{
			if (i == 1)
				fp1 << sum->q[a].namebook << endl;
			else if(i==2)
				fp1 << sum->q[a].number << endl;
			else if (i == 3)
				fp1 << sum->q[a].area << endl;
			else if (i == 4)
			{	
				fp1 << sum->q[a].residue << endl;
				break;
			}
			i++;
		}
		fp1.close();
	}
	return;
}
void write2(booksum_* sum1,int a)
{
	fp2.open("stu.txt",ios::app);
	if (fp2.is_open())
	{
		int i = 1;
		while (fp2.is_open())
		{
			if (i == 1)
				fp2 << sum1->q[a].namestu << endl;
			else if (i == 2)
				fp2 << sum1->q[a].id << endl;
			else if (i == 3)
				fp2 << sum1->q[a].namebook << endl;
			else if (i == 4)
				fp2 << sum1->q[a].timestart << endl;
			else if (i == 5)
			{
				fp2 << sum1->q[a].timeend << endl;
				break;
			}
			i++;
		}
		fp2.close();
	}
	return;
}
void show()
{
	cleardevice();
	IMAGE img;
	loadimage(&img, L"./主页.jfif", 640, 480);
	putimage(0, 0, &img);
	settextstyle(50, 0, L"楷体");
	settextcolor(GREEN);
	LPCTSTR arr[4];
	arr[0] = L"图书系统";
	arr[1] = L"租借系统";
	arr[2] = L"清空图书";
	arr[3] = L"退出系统";
	for (int i = 0; i < 4; i++)
	{
		int width = 200 - textwidth((arr[i])) / 2;
		int height = 100 - textheight(arr[i]) / 2;
		outtextxy(300 + width, 140 + 70 * i + height, arr[i]);
	}
}
void show1()
{
	cleardevice();
	IMAGE img;
	loadimage(&img, L"./3.jfif", 640, 480);
	putimage(0, 0, &img);
	settextstyle(35, 0, L"楷体");
	settextcolor(BLACK);
	LPCTSTR arr[6];
	arr[0] = L"添加图书";
	arr[1] = L"修改图书";
	arr[2] = L"删除图书";
	arr[3] = L"查找图书";
	arr[4] = L"显示全部图书";
	arr[5] = L"返回主菜单";
	for (int i = 0; i < 6; i++)
	{
		int width = 110 - textwidth((arr[i])) / 2;
		int height = 17 - textheight(arr[i]) / 2;
		outtextxy(200 + width, 60+60*i + height, arr[i]);
	}

}
void show2()
{
	cleardevice();
	IMAGE img;
	loadimage(&img, L"./2.jfif", 640, 480);
	putimage(0, 0, &img);
	settextstyle(40, 0, L"楷体");
	settextcolor(BROWN);
	LPCTSTR arr[4];
	arr[0] = L"租借图书";
	arr[1] = L"返还图书";
	arr[2] = L"显示租借图书";
	arr[3] = L"返回主菜单";
	for (int i = 0; i < 4; i++)
	{
		int width = 110 - textwidth((arr[i])) / 2;
		int height = 17 - textheight(arr[i]) / 2;
		outtextxy(200 + width, 100 + 70 * i + height, arr[i]);
	}
}
void show3()
{
	cleardevice();
	IMAGE img;
	loadimage(&img, L"./1.jfif", 640, 480);
	putimage(0, 0, &img);
	settextstyle(60, 0, L"楷体");
	settextcolor(RED);
	LPCTSTR arr[3];
	arr[0] = L"返回主菜单";
	arr[1] = L"清空图书";
	arr[2] = L"清空租借信息";
	for (int i = 0; i < 3; i++)
	{
		int width = 110 - textwidth((arr[i])) / 2;
		int height = 50 - textheight(arr[i]) / 2;
		outtextxy(200 + width, 100 + 70 * i + height, arr[i]);
	}
}
void add(booksum *sum)
{
	cleardevice();
	if(sum->size ==MAX)
	{
		settextstyle(50, 0, L"楷体");
		settextcolor(RED);
		outtextxy(0, 0, L"本系统图书库已满");
		return;
	}
	else
	{
		outtextxy(50, 50, L"图书名字：");
		outtextxy(50, 100, L"图书编号:");
		outtextxy(50, 150, L"图书区域:");
		outtextxy(50, 200, L"剩余图书数量:");
		InputBox(sum->p[sum->size].namebook, 40, L"图书名字：", L"添加图书");
		int b = seek(sum, sum->p[sum->size].namebook);
		if (b != -1)
		{
			InputBox(sum->p[sum->size].residue, 40, L"剩余图书数量：", L"添加图书");
			TCHARtochar(sum->p[sum->size].residue, sum->q[sum->size].residue);
			string A, B;
			char C[50];
			memset(C, 0, sizeof(C));
			char* a = sum->q[sum->size].residue;
			char* c = sum->q[b].residue;
			A = a;
			B = c;
			And(A, B ,C);
			strcpy_s(sum->q[b].residue, 10, C);
			chartoTCHAR(sum->q[b].residue, sum->p[b].residue);
			fp1.open("book.txt", ios::out);
			fp1.close();
			for (int i = 0; i < (sum->size); i++)
				write1(sum, i);
			return;
		}
		TCHARtochar(sum->p[sum->size].namebook,sum->q[sum->size].namebook);
		InputBox(sum->p[sum->size].number, 40, L"图书编号：", L"添加图书");
		TCHARtochar(sum->p[sum->size].number, sum->q[sum->size].number);
		int a = seek1(sum, sum->p[sum->size].number);
		while ( a != -1)
		{
			outtextxy(50, 250, L"该编号不正确,请重新输入");
			InputBox(sum->p[sum->size].number, 40, L"图书编号：", L"添加图书");
			TCHARtochar(sum->p[sum->size].number, sum->q[sum->size].number);
		}	
		InputBox(sum->p[sum->size].area, 40, L"图书区域：", L"添加图书");
		TCHARtochar(sum->p[sum->size].area, sum->q[sum->size].area);
		InputBox(sum->p[sum->size].residue, 40, L"剩余图书数量：", L"添加图书");
		TCHARtochar(sum->p[sum->size].residue, sum->q[sum->size].residue);
		write1(sum,sum->size);
		sum->size ++;
		outtextxy(50, 250, L"添加成功");
	}
}
void amend(booksum *sum)
{
	cleardevice();
	outtextxy(50, 50, L"请输入想要修改的图书名字:");
	TCHAR name[50];
	InputBox(name, 40, L"图书名字：", L"修改图书");
	int a=seek(sum,name);
	if(a==-1)
		outtextxy(20, 100, L"查无此书，请保证图书名字输入正确");
	else
	{
		cleardevice();
		outtextxy(50, 50, L"请输入修改后的名字：");
		outtextxy(50, 100, L"图书编号:");
		outtextxy(50, 150, L"图书区域:");
		outtextxy(50, 200, L"剩余图书数量:");
		InputBox(sum->p[a].namebook, 40, L"修改后图书名字：", L"修改图书");
		TCHARtochar(sum->p[a].namebook, sum->q[a].namebook);
		InputBox(sum->p[a].number, 40, L"图书编号：", L"修改图书");
		TCHARtochar(sum->p[a].number, sum->q[a].number);
		InputBox(sum->p[a].area, 40, L"图书区域：", L"修改图书");
		TCHARtochar(sum->p[a].area, sum->q[a].area);
		InputBox(sum->p[a].residue, 40, L"剩余图书数量：", L"修改图书");
		TCHARtochar(sum->p[a].residue, sum->q[a].residue);
		fp2.open("book.txt", ios::out);
		fp2.close();
		for (int i = 0; i < (sum->size); i++)
			write1(sum,i);
		outtextxy(50, 250, L"修改成功");
	} 
}
void del(booksum *sum)
{
	cleardevice();
	outtextxy(50, 50, L"请输入想要删除的图书名字:");
	TCHAR name[50];
	InputBox(name, 40, L"图书名字：", L"删除图书");
	int a=seek(sum,name);
	if(a==-1)
		outtextxy(50, 100, L"查无此书，请保证图书名字输入正确");
	else
	{
		fp1.open("book.txt", ios::out);
		fp1.close();
		for (int i = a; i < (sum->size); i++)
		{
			sum->p [i]=sum->p [i+1];
			sum->q[i] = sum->q[i + 1];
		}
		outtextxy(50, 100, L"删除成功");
		sum->size --;
		for (int i = 0; i < (sum->size); i++)
			write1(sum, i);
	} 
	system("pause");
	return;
}
void find(booksum *sum)
{
	cleardevice();
	settextstyle(30, 0, L"宋体");
	outtextxy(20, 50, L"请输入要查找的图书名字");
	outtextxy(20, 100, L"如果要查找图书编号，请输入“此图书无名字”");
	TCHAR name[50];
	TCHAR number[20];
	TCHAR b[50] = L"此图书无名字";
	int a;
	InputBox(name, 40, L"图书名字：", L"查找图书");
	if(*name == *b)
	{
		outtextxy(20, 150, L"请输入要查找的图书编号");
		InputBox(number, 40, L"图书编号：", L"查找图书");
		a=seek1(sum,number);
	}
	else 
		a = seek(sum, name);
	if(a == -1)
		outtextxy(20, 200, L"未找到此书，请确保图书名字或编号正确");
	else
	{
		cleardevice();
		outtextxy(50, 50, L"查找完毕");
		outtextxy(50, 100, sum->p [a].namebook);
		outtextxy(50, 150, sum->p [a].number);
		outtextxy(50, 200, sum->p [a].area);
		outtextxy(50, 250, sum->p [a].residue);
	}	
	system("pause");
	return;
}
void rent(booksum_ *sum1,booksum *sum)
{
	cleardevice();
	TCHAR namebook[50];
	int a;
	outtextxy(50, 50, L"请输入学生姓名:");
	outtextxy(50, 100, L"请输入学生学号:");
	outtextxy(50, 150, L"请输入图书名字:");
	InputBox(sum1->p [sum1->size ].namestu, 40, L"学生姓名：", L"租借图书"); 
	TCHARtochar(sum1->p[sum1->size ].namestu, sum1->q[sum1->size].namestu);
	InputBox(sum1->p [sum1->size ].id, 40, L"学生学号：", L"租借图书");
	int b = seek4(sum1, sum1->p[sum->size].id);
	while ( b != -1)
	{
		outtextxy(50, 250, L"该学号不正确");
		InputBox(sum1->p[sum1->size].id, 40, L"学生学号：", L"租借图书");
		b = seek4(sum1, sum1->p[sum->size].id);
	}
	TCHARtochar(sum1->p[sum1->size].id, sum1->q[sum1->size].id);
	InputBox(namebook, 40, L"图书名字：", L"租借图书");
	a=seek(sum,namebook);
	if(a==-1)
		outtextxy(50, 200, L"查无此书");
	else
	{
		do
		{
			outtextxy(50, 250, L"请输入租借日期:");
			outtextxy(50, 300, L"请输入归还日期:");
			InputBox(sum1->p [sum1->size ].timestart, 40, L"租借日期:", L"租借图书");
			TCHARtochar(sum1->p[sum1->size].timestart, sum1->q[sum1->size].timestart);
			InputBox(sum1->p [sum1->size ].timeend, 40, L"归还日期:", L"租借图书");
			TCHARtochar(sum1->p[sum1->size].timeend, sum1->q[sum1->size].timeend);
		} while (*sum1->q[sum1->size].timestart == NULL || *sum1->q[sum1->size].timeend == NULL);
		TCHARtochar(namebook, sum1->q[sum1->size].namebook);
		chartoTCHAR(sum1->q[sum1->size].namebook, sum1->p[sum1->size].namebook);
		if((*sum->q[a].residue)=='0')
			outtextxy(50, 350, L"书库已无此图书");
		else
		{
			a = seek(sum, sum1->p[sum1->size].namebook);
			int len = strlen(sum->q[a].residue);
			long long int k = 0;
			int j[20];
			memset(j, 0, sizeof(j));
			for (int i = 0; i < len; i++)
				k = k * 10 + (sum->q[a].residue[i] - '0');
			k--;
			for (int i = 0;k > 0; i++)
			{
				j[i] = k % 10;
				k /= 10;
			}
			while(j[len - 1] == 0)
				len--;
			for (int i = 0; i < len; i++)
				sum->q[a].residue[i] = j[len-i-1] + '0';
			chartoTCHAR(sum->q[a].residue, sum->p[a].residue);
			fp1.open("book.txt", ios::out);
			fp1.close();
			for (int i = 0; i < (sum->size); i++)
				write1(sum, i);
			outtextxy(50, 350, L"租借成功");
			write2(sum1,sum1->size);
			sum1->size ++;
		}
	}
	system("pause");
}
void back(booksum_ *sum1,booksum *sum)
{
	cleardevice();
	TCHAR name[50];
	TCHAR namebook[50];
	int a,b;
	outtextxy(50,50, L"请输入学生姓名");
	InputBox(name, 40, L"学生名字：", L"还回图书");
	a=seek2(sum1,name);
	if(a==-1)
		outtextxy(50, 100, L"该学生没有借出图书");
	else
	{
		InputBox(namebook, 40, L"图书名字：", L"还回图书");
		b=seek3(sum1,namebook,name);
		if(b==-1)
			outtextxy(50, 150, L"该学生没有借出该图书");
		else
		{
			int c = seek(sum, namebook);
			int len = strlen(sum->q[c].residue);
			long long int k = 0;
			int j[20];
			memset(j, 0, sizeof(j));
			for (int i = 0; i < len; i++)
				k = k * 10 + (sum->q[c].residue[i] - '0');
			k++;
			for (int i = 19; k>0; i--)
			{
				j[i] = k % 10;
				k /= 10;
			}
			len = 20;
			for (int i = 0;; i++)
			{
				if (j[i] == 0)
					len--;
				else 
					break;
			}	
			for (int i = len-1; i >= 0; i--)
				sum->q[c].residue[len-i-1] = j[19-i] + '0';
			chartoTCHAR(sum->q[c].residue, sum->p[c].residue);
			fp1.open("book.txt", ios::out);
			fp1.close();
			for (int i = 0; i < (sum->size); i++)
				write1(sum, i);
			outtextxy(50, 150, L"归还成功");
			fp2.open("stu.txt", ios::out);
			fp2.close();
			for (int i = b; i < (sum1->size); i++)
			{
				sum1->p[i] = sum1->p[i + 1];
				sum1->q[i] = sum1->q[i + 1];
			}
			sum1->size --;
			for (int i = 0; i < (sum1->size); i++)
				write2(sum1, i);
		}	
	}
	system("pause");
} 
void empty(booksum_* sum1, booksum* sum, int n)
{
	cleardevice();
	TCHAR k[20];
	outtextxy(50, 50, L"请输入密码：");
	InputBox(k, 40, L"密码：", L"清空图书");
	if (*k != *MIMA)
	{
		outtextxy(50, 100, L"输入错误");
		return;
	}
	else
	{
		if (n == 1)
		{
			sum->size = 0;
			fp1.open("book.txt", ios::out);
			fp1.close();
			outtextxy(50, 150, L"删除成功");
			system("pause");
		}
		else if (n == 2)
		{
			sum1->size = 0;
			fp2.open("stu.txt", ios::out);
			fp2.close();
			outtextxy(50, 150, L"删除成功");
			system("pause");
		}
		return;
	}
}
void showall(booksum * sum)
{
	cleardevice();
	if(sum->size ==0)
		outtextxy(50, 50, L"系统中还没有图书");
	else
	{
		settextstyle(20, 0, L"隶书");
		int k = sum->size;
		int s = 0;
		for(int i=0;i<k;i++)
		{
			if (i>=24)
			{
				s++;
				k -= 24;
				i = 0;
				system("pause");
				cleardevice();
			}
			else
			{
				outtextxy(0, i * 20, sum->p [i+s*24].namebook);
				outtextxy(160 ,i * 20, sum->p [i+s*24].number);
				outtextxy(320,i * 20, sum->p [i+s*24].area);
				outtextxy(480,i * 20, sum->p [i+s*24].residue);
			}
		}
	} 
	system("pause");
}
void showrent(booksum_ * sum1)
{
	cleardevice();
	settextcolor(RED);
	if(sum1->size ==0)
		outtextxy(50, 50, L"系统中还没有借出图书");
	else
	{
		settextcolor(BLACK);
		settextstyle(20, 0, L"隶书");
		int s = 0;
		int k = sum1->size;
		for(int i=0;i<k;i++)
		{
			if (i >= 24)
			{
				i = 0;
				k -= 24;
				s++;
				system("pause");
				cleardevice();
			}
			else
			{
				outtextxy(10, i*20, sum1->p[i+s*24].namestu);
				outtextxy(130, i*20, sum1->p[i+s*24].id);
				outtextxy(250, i*20, sum1->p[i+s*24].namebook);
				outtextxy(370, i * 20, sum1->p[i+s*24].timestart);
				outtextxy(490, i * 20, sum1->p[i+s*24].timeend);
			}
		}
	} 
	system("pause");
} 
int cmp(TCHAR name1[50], TCHAR name2[50])
{
	int a=_tcslen(name1);
	int b = _tcslen(name2);
	if (a == b)
		return a;
	return -1;
}
int seek(booksum *sum,TCHAR name[50])
{
	for(int i=0;i<(sum->size );i++)
		if (*sum->p[i].namebook == *name)
		{
			int a = cmp(sum->p[i].namebook, name);
			if(a!=-1)
				for (; a >= 0; a--)
				{
					if (sum->p[i].namebook[a] != name[a])
						break;
					if (a == 0)
						return i;
				}
		}
	return -1;
}
int seek1(booksum *sum,TCHAR number[50])
{
	for(int i=0;i<(sum->size );i++)
		if(*sum->p [i].number==*number)
		{
			int a = cmp(sum->p[i].number, number);
			if (a != -1)
				for (; a >= 0; a--)
				{
					if (sum->p[i].number[a] != number[a])
						break;
					if (a == 0)
						return i;
				}
		}
	return -1;
}
int seek2(booksum_ *sum1,TCHAR name[50])
{
	for(int i=0;i<(sum1->size );i++)
		if(*sum1->p[i].namestu==*name)
		{
			int a = cmp(sum1->p[i].namestu, name);
			if (a != -1)
				for (; a >= 0; a--)
				{
					if (sum1->p[i].namestu[a] != name[a])
						break;
					if (a == 0)
						return i;
				}
		}
	return -1;
}
int seek3(booksum_ *sum1,TCHAR namebook[50], TCHAR name[50])
{
	for(int i=0;i<(sum1->size); i++)
		if(*sum1->p[i].namestu==*name)
		{
			int a = cmp(sum1->p[i].namestu, name);
			if (a != -1)
				for (; a >= 0; a--)
				{
					if (sum1->p[i].namestu[a] != name[a])
						break;
					if (a == 0)
						if(*sum1->p [i].namebook==*namebook)
						{
							int a = cmp(sum1->p[i].namebook, namebook);
							if (a != -1)
								for (; a >= 0; a--)
								{
									if (sum1->p[i].namebook[a] != namebook[a])
										break;
									if (a == 0)
										return i;
								}
						}
				}
		}
	return -1;
}
int seek4(booksum_* sum1, TCHAR id[50])
{
	for (int i = 0; i < (sum1->size); i++)
		if (*sum1->p[i].id == *id)
		{
			int a = cmp(sum1->p[i].id, id);
			if (a != -1)
				for (; a >= 0; a--)
				{
					if (sum1->p[i].id[a] != id[a])
						break;
					if (a == 0)
						return i;
				}
		}
	return -1;
}
void TCHARtochar(TCHAR* tchar, char* _char)
{
	int iLength;
	//获取字节长度   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char    
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}
void chartoTCHAR(char* _char, TCHAR* tchar)
{
	int iLength;

	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}
void And(string str1, string str2,char A[50])
{
	int a[250], b[250], len;
	int i;
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	a[0] = str1.length();
	for (i = 1; i <= a[0]; i++)
	{
		a[i] = str1[a[0] - i] - '0';
	}
	b[0] = str2.length();
	for (i = 1; i <= b[0]; i++)
	{
		b[i] = str2[b[0] - i] - '0';
	}
	len = (a[0] > b[0] ? a[0] : b[0]);
	for (i = 1; i <= len; i++)
	{
		a[i] += b[i];
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
	len++;
	while ((a[len] == 0) && (len > 1))
		len--;
	for (i = len; i >= 1; i--)
		A[len-i] = a[i]+'0';
}
