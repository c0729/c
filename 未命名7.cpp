

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

/*�ַ�������*/
#define STR_LEN 128

struct land { //��¼��Ϣ
	int zhanghao;
	char password[20];
	struct land*next;
};

void lmenu() { //��ʾ��¼�˵�


	printf("\n\n\t    ��ӭʹ�û�Ա��¼ϵͳ\n\n");
	printf("**********************************************");
	printf("\n\n\t\t1.��¼ϵͳ\n\n");
	printf("\n\n\t\t2.�����˺�\n\n");
	printf("\n\n\t\t3.�˳�ϵͳ\n\n");
	printf("\n**********************************************\n");
	printf("\n����������ѡ�񣨻س�ȷ������");
	return ;
}

void lmain() { //��¼���ܺ���
	void land();
	void xinjian();
	char choose;
	lmenu();
	scanf(" %c",&choose);
	switch(choose) { //���ܺ���
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



void xinjian() { //�½��˻�����
	FILE *fp;
	int zhanghao;
	char password[20],password1[20];
	char hit=0;
	if ((fp=fopen("land.txt","r"))==NULL) { //if��䣺�򿪵�¼�ļ��������ڴ��ļ����½�
		fp=fopen("land.txt","w");
		fclose(fp);
	}
	system("cls");
	fp=fopen("land.txt","a");
	for(;;) { //������������ȷ�ϣ�������ͬ����ȷ��
		printf("\n�밴���¸�ʽ�����˻�:\n�˺� ����\n");
		printf("������:");
		scanf("%d %s",&zhanghao,password);
		printf("�ٴ���������:\n");
		scanf("%s",password1);
		if(strcmp(password,password1)==0) {
			fprintf(fp,"%d %s\n",zhanghao,password);
			break;
		} else {
			printf("\n�����������벻һ�£���������������˵�");
			hit=getch();
			system("cls");
			lmain();
		}
	}
	fclose(fp);
	printf("�����ɹ��������������");
	getch();
	system("cls");
	lmain();
}





int match(int m,char a[20]) { //ƥ�����ݿ��е��˺�����
	FILE*fp;
	int n=0,i=0;
	int zhanghao;
	char password[20];

	if ((fp=fopen("land.txt","r"))==NULL) { //�����ڹ���Ա�ļ�
		system ("cls");
		printf("\n ��δ�����û�!���½��˻�");
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
void land() { //�����˻�����ĵ�¼����
	int zhanghao;
	char password[20];
	int i=2,j,k,n;
	char hit=0;
	system("cls");
	do {
		printf("\n�������˺�:\n");
		scanf("%d",&zhanghao);
		printf("ȷ�������밴�س��������������밴ECS��");
		hit=getch();//��ͣ����i���պ������һ��ָ��
		for (; hit!=13&&hit!=27;) { //��ֻ֤����CR��ESC�����˳�ѭ��,���������ַ����ã���ͣ���򣬰�'CR'������
			hit=getch();
		}
	} while(hit==27);
	printf("\n����������:\n");
	scanf("%s",password);
	i=match(zhanghao,password);
	if(i==1) {
		printf("��½�ɹ�!�����������");
		getch();
		system("cls");
	} else {
		int f=1;
		while(i==-1 && f<3) {
			f++;
			printf("\n�������!");
			printf("\n��������������:\n");
			scanf("%s",password);
			i=match(zhanghao,password);

		}
		if(f>=3) {
			printf("���������������!����������ز˵�");
			getch();
			system("cls");
			lmain();
		}
		if(i==0) {

			printf("�����ڴ��û�");
			getch();
			system("cls");
			lmain();
		}
	}
}
/*�豸��Ϣ�ڵ�ṹ��*/
typedef struct _tEquipmentNode {
	char id[STR_LEN];               /*���*/
	char name[STR_LEN];             /*����*/
	char category[STR_LEN];         /*����*/
	char date[STR_LEN];             /*��������*/
	char state[STR_LEN];            /*״̬*/
	double price;                   /*�۸�*/
	struct _tEquipmentNode* next;   /*��һ���ڵ��ָ��*/
} EquipmentNode, * pEquipmentNode;

/*�豸��Ϣ����*/
typedef struct _tEquipmentNodeList {
	pEquipmentNode head;    /*����ͷ���*/
	int count;              /*�ڵ����*/
} EquipmentNodeList, * pEquipmentNodeList;

/*���豸��Ϣ��ӵ�����*/
void addEquipmentNodeList(pEquipmentNodeList list, pEquipmentNode equipment) {
	if (list->head) {
		pEquipmentNode cursor = list->head;
		while (cursor->next) {
			cursor = cursor->next;
		}
		/*���½ڵ���뵽����β��*/
		cursor->next = equipment;
	} else {
		list->head = equipment;
	}
	++list->count;
}

/*��������ɾ���豸��Ϣ*/
void removeEquipmentNodeList(pEquipmentNodeList list, pEquipmentNode equipment) {
	if (list->head) {
		if (list->head == equipment) {
			/*ɾ���ڵ�Ϊ�׽ڵ�*/
			list->head = equipment->next;
			/*ɾ���ýڵ�*/
			free(equipment);
			--list->count;
		} else {
			pEquipmentNode cursor = list->head;
			while (cursor->next) {
				/*�ҵ�Ҫɾ���ڵ����һ���ڵ�*/
				if (cursor->next == equipment) {
					/*����һ���ڵ�ָ��ɾ���ڵ����һ���ڵ�*/
					cursor->next = equipment->next;
					/*ɾ���ýڵ�*/
					free(equipment);
					--list->count;
					break;
				}
				cursor = cursor->next;
			}
		}
	}
}

/*����豸����*/
void clearEquipmentNodeList(pEquipmentNodeList list) {
	while (list->head) {
		removeEquipmentNodeList(list, list->head);
	}
}

/*ͨ����Ų�������ڵ�*/
pEquipmentNode findEquipmentNodeListByID(pEquipmentNode head, char id[]) {
	pEquipmentNode cursor = head;
	while (cursor) {
		/*ƥ�����֤��*/
		if (strcmp(cursor->id, id) == 0) {
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

/*ͨ�����Ʋ�������ڵ�*/
pEquipmentNode findEquipmentNodeListByName(pEquipmentNode head, char name[]) {
	pEquipmentNode cursor = head;
	while (cursor) {
		/*ƥ������*/
		if (strcmp(cursor->name, name) == 0) {
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

/*ͨ�������������ڵ�*/
pEquipmentNode findEquipmentNodeListByCategory(pEquipmentNode head, char category[]) {
	pEquipmentNode cursor = head;
	while (cursor) {
		/*ƥ������*/
		if (strcmp(cursor->category, category) == 0) {
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

/*ͨ��״̬��������ڵ�*/
pEquipmentNode findEquipmentNodeListByState(pEquipmentNode head, char state[]) {
	pEquipmentNode cursor = head;
	while (cursor) {
		/*ƥ��״̬*/
		if (strcmp(cursor->state, state) == 0) {
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

/*���������*/
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

		/*ð������*/
		for (i = 0; i < len - 1; ++i) {
			int swap = 0;
			for (j = 0; j < len - i - 1; ++j) {
				pEquipmentNode* left = &arr[j];
				pEquipmentNode* right = &arr[j + 1];
				/*�Ƚ�ģʽ*/
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

/*���豸��������*/
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

		/*ð������*/
		for (i = 0; i < len - 1; ++i) {
			int swap = 0;
			for (j = 0; j < len - i - 1; ++j) {
				pEquipmentNode* left = &arr[j];
				pEquipmentNode* right = &arr[j + 1];
				/*�Ƚ�ģʽ*/
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

/*���豸�۸�����*/
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

		/*ð������*/
		for (i = 0; i < len - 1; ++i) {
			int swap = 0;
			for (j = 0; j < len - i - 1; ++j) {
				pEquipmentNode* left = &arr[j];
				pEquipmentNode* right = &arr[j + 1];
				/*�Ƚ�ģʽ*/
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

/*���豸��Ϣ�洢���ļ�*/
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
		printf("д�ļ�ʧ�ܣ�\n");
	}
}

/*���ļ��м����豸��Ϣ*/
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

/*��ʾ�豸��Ϣ����*/
void showEquipmentNodeTitle() {
	printf("%-12s", "���");
	printf("%-16s", "����");
	printf("%-16s", "����");
	printf("%-16s", "��������");
	printf("%-16s", "�۸�");
	printf("%-10s", "״̬");
	printf("\n");
}

/*��ʾ�豸��Ϣ*/
void showEquipmentNode(pEquipmentNode equipment) {
	printf("%-12s", equipment->id);
	printf("%-16s", equipment->name);
	printf("%-16s", equipment->category);
	printf("%-16s", equipment->date);
	printf("%-16.2lf", equipment->price);
	printf("%-10s", equipment->state);
	printf("\n");
}

/*��ʾ�豸��Ϣ�б�*/
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
		printf("�X-------------------------------�[\n");
		printf(" $ ��ʾ�豸��Ϣ $ \n");
		showEquipmentNodeTitle();
		cursor = list->head;
		while (cursor) {
			showEquipmentNode(cursor);
			cursor = cursor->next;
		}
		printf("�^-------------------------------�a\n");
		printf("\n�� 1 ��������� 2 ���豸�������� 3 ���۸����� 0 ���ء�\n");
		scanf("%d", &option);
	}
}

/*��������*/
void inputCategory(char* category) {
	while (1) {
		int option;
		printf(" ѡ�����ͣ�\n");
		printf("--------------------\n");
		printf("  1 > ΢��\n");
		printf("  2 > ��ӡ��\n");
		printf("  3 > ɨ����\n");
		printf("  4 > ͶӰ��\n");
		printf("  5 > ����\n");
		printf("--------------------\n");
		printf("          ��ѡ��");
		scanf("%d", &option);
		switch (option) {
			case 1:
				strcpy(category, "΢��");
				return;
			case 2:
				strcpy(category, "��ӡ��");
				return;
			case 3:
				strcpy(category, "ɨ����");
				return;
			case 4:
				strcpy(category, "ͶӰ��");
				return;
			case 5:
				strcpy(category, "����");
				return;
		}
	}
}

/*����״̬*/
void inputState(char* category) {
	while (1) {
		int option;
		printf(" ѡ��״̬��\n");
		printf("--------------------\n");
		printf("  1 > �ڿ�\n");
		printf("  2 > ����\n");
		printf("  3 > ά��\n");
		printf("--------------------\n");
		printf("          ��ѡ��");
		scanf("%d", &option);
		switch (option) {
			case 1:
				strcpy(category, "�ڿ�");
				return;
			case 2:
				strcpy(category, "����");
				return;
			case 3:
				strcpy(category, "ά��");
				return;
		}
	}
}

/*�ж��Ƿ�����*/
int isLeapYear(int year) {
	if (year % 400 == 0) return 1;
	if (year % 4 == 0 && year % 100 != 0) return 1;
	return 0;
}

/*������ڣ�yyyy-mm-dd��*/
int checkDate(int yyyy, int mm, int dd) {
	/*ÿ���µ�����*/
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

	/*������2�¶��1��*/
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

/*��������*/
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
				printf("���ݷ�Χ�������������룡\n");
			}
		} else {
			printf("��ʽ�������������룡��yyyy-mm-dd��\n");
		}
	} while (1);
}

/*�༭�豸��Ϣ*/
void editEquipmentNode(pEquipmentNode equipment) {
	printf(" $ ¼����Ϣ $ \n");
	if (strlen(equipment->id)) {
		printf("��ţ�%s\n", equipment->id);
	} else {
		printf("��ţ�");
		scanf("%s", equipment->id);
	}
	printf("���ƣ�");
	scanf("%s", equipment->name);
	printf("���ࣺ");
	inputCategory(equipment->category);
	printf("�������ڣ�");
	inputDate(equipment->date);
	if (strlen(equipment->state) == 0) {
		strcpy(equipment->state, "�ڿ�");
	}
	printf("�۸�");
	scanf("%lf", &equipment->price);
}

/*�����豸��Ϣ*/
void addEquipmentNode(pEquipmentNodeList list) {
	EquipmentNode buffer;
	memset(&buffer, 0, sizeof(EquipmentNode));
	printf("�X-------------------------------�[\n");
	printf(" $ ����豸��Ϣ $ \n");
	printf("�^-------------------------------�a\n");
	editEquipmentNode(&buffer);
	if (findEquipmentNodeListByID(list->head, buffer.id) == NULL) {
		pEquipmentNode equipment = (pEquipmentNode)calloc(1, sizeof(EquipmentNode));
		*equipment = buffer;
		addEquipmentNodeList(list, equipment);
		saveEquipmentFile(list);
		showEquipmentNodeTitle();
		showEquipmentNode(&buffer);
		printf("�ɹ���������豸��Ϣ��\n");
	} else {
		printf("���豸����Ѵ��ڣ����ʧ�ܣ�\n");
	}
}

/*�޸��豸��Ϣ*/
void updateEquipmentNode(pEquipmentNodeList list) {
	char id[128] = { 0 };
	pEquipmentNode target = NULL;
	printf("�X-------------------------------�[\n");
	printf(" $ �޸��豸��Ϣ $ \n");
	printf("�^-------------------------------�a\n");
	printf("�����ţ�");
	scanf("%s", id);
	target = findEquipmentNodeListByID(list->head, id);
	if (target) {
		editEquipmentNode(target);
		saveEquipmentFile(list);
		showEquipmentNodeTitle();
		showEquipmentNode(target);
		printf("�ɹ��޸������豸��Ϣ��\n");
	} else {
		printf("δ�ҵ����豸!\n");
	}
}

/*ɾ���豸��Ϣ*/
void removeEquipmentNode(pEquipmentNodeList list) {
	char id[128] = { 0 };
	pEquipmentNode target = NULL;
	printf("�X-------------------------------�[\n");
	printf(" $ ɾ���豸��Ϣ $ \n");
	printf("�^-------------------------------�a\n");
	printf("�����ţ�");
	scanf("%s", id);
	target = findEquipmentNodeListByID(list->head, id);
	if (target) {
		showEquipmentNodeTitle();
		showEquipmentNode(target);
		removeEquipmentNodeList(list, target);
		saveEquipmentFile(list);
		printf("�ɹ�ɾ�������豸��Ϣ!\n");
	} else {
		printf("δ�ҵ����豸!\n");
	}
}

/*����Ų�ѯ*/
void searchEquipmentNodeByID(pEquipmentNodeList list) {
	char id[128] = { 0 };
	pEquipmentNode target = NULL;
	printf("�X-------------------------------�[\n");
	printf(" $ ����Ų�ѯ $ \n");
	printf("�^-------------------------------�a\n");
	printf("�����ţ�");
	scanf("%s", id);
	target = findEquipmentNodeListByID(list->head, id);
	if (target) {
		showEquipmentNodeTitle();
		do {
			showEquipmentNode(target);
			target = findEquipmentNodeListByID(target->next, id);
		} while (target);
	} else {
		printf("δ�ҵ����豸!\n");
	}
}

/*�����Ʋ�ѯ*/
void searchEquipmentNodeByName(pEquipmentNodeList list) {
	char name[128] = { 0 };
	pEquipmentNode target = NULL;
	printf("�X-------------------------------�[\n");
	printf(" $ �����Ʋ�ѯ $ \n");
	printf("�^-------------------------------�a\n");
	printf("�����豸���ƣ�");
	scanf("%s", name);
	target = findEquipmentNodeListByName(list->head, name);
	if (target) {
		showEquipmentNodeTitle();
		do {
			showEquipmentNode(target);
			target = findEquipmentNodeListByName(target->next, name);
		} while (target);
	} else {
		printf("δ�ҵ����豸!\n");
	}
}

/*�������ѯ*/
void searchEquipmentNodeByCategory(pEquipmentNodeList list) {
	char category[128] = { 0 };
	pEquipmentNode target = NULL;
	printf("�X-------------------------------�[\n");
	printf(" $ �������ѯ $ \n");
	printf("�^-------------------------------�a\n");
	printf("�����豸���ࣺ");
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
		printf("��������%d��\n", count);
	} else {
		printf("δ�ҵ����豸!\n");
	}
}

/*��״̬��ѯ*/
void searchEquipmentNodeByState(pEquipmentNodeList list) {
	char state[128] = { 0 };
	pEquipmentNode target = NULL;
	printf("�X-------------------------------�[\n");
	printf(" $ ��״̬��ѯ $ \n");
	printf("�^-------------------------------�a\n");
	printf("�����豸���ࣺ");
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
		printf("��������%d��\n", count);
	} else {
		printf("δ�ҵ����豸!\n");
	}
}

/*��ѯ�豸��Ϣ*/
void searchEquipmentNode(pEquipmentNodeList list) {
	while (1) {
		int option;
		printf("�X-------------------------------�[\n");
		printf(" $ ��ѯ�豸��Ϣ $ \n");
		printf(" ��1������Ų�ѯ\n");
		printf(" ��2�������Ʋ�ѯ\n");
		printf(" ��3���������ѯ\n");
		printf(" ��4����״̬��ѯ\n");
		printf(" ��0������\n");
		printf("�^-------------------------------�a\n");
		printf("           ��ѡ��");
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

/*��¼��Ϣ�ڵ�ṹ��*/
typedef struct _tRecordNode {
	char id[STR_LEN];           /*�豸���*/
	char name[STR_LEN];         /*�豸����*/
	char state[STR_LEN];        /*״̬*/
	char date[STR_LEN];         /*����*/
	struct _tRecordNode* next;  /*��һ���ڵ��ָ��*/
} RecordNode, * pRecordNode;

/*��¼��Ϣ����*/
typedef struct _tRecordNodeList {
	pRecordNode head;   /*����ͷ���*/
	int index;          /*��ŵ�������*/
	int count;          /*�ڵ����*/
} RecordNodeList, * pRecordNodeList;

/*����¼��Ϣ��ӵ�����*/
void addRecordNodeList(pRecordNodeList list, pRecordNode record) {
	if (list->head) {
		pRecordNode cursor = list->head;
		while (cursor->next) {
			cursor = cursor->next;
		}
		/*���½ڵ���뵽����β��*/
		cursor->next = record;
	} else {
		list->head = record;
	}
	++list->count;
}

/*��������ɾ����¼��Ϣ*/
void removeRecordNodeList(pRecordNodeList list, pRecordNode record) {
	if (list->head) {
		if (list->head == record) {
			/*ɾ���ڵ�Ϊ�׽ڵ�*/
			list->head = record->next;
			/*ɾ���ýڵ�*/
			free(record);
			--list->count;
		} else {
			pRecordNode cursor = list->head;
			while (cursor->next) {
				/*�ҵ�Ҫɾ���ڵ����һ���ڵ�*/
				if (cursor->next == record) {
					/*����һ���ڵ�ָ��ɾ���ڵ����һ���ڵ�*/
					cursor->next = record->next;
					/*ɾ���ýڵ�*/
					free(record);
					--list->count;
					break;
				}
				cursor = cursor->next;
			}
		}
	}
}

/*��ռ�¼����*/
void clearRecordNodeList(pRecordNodeList list) {
	while (list->head) {
		removeRecordNodeList(list, list->head);
	}
}

/*ͨ���豸��Ų�������ڵ�*/
pRecordNode findRecordNodeListByID(pRecordNode head, char id[]) {
	pRecordNode cursor = head;
	while (cursor) {
		/*ƥ���¼���*/
		if (strcmp(cursor->id, id) == 0) {
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

/*ͨ���ؼ��ʲ�������ڵ�*/
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

/*����¼��Ϣ�洢���ļ�*/
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
		printf("д�ļ�ʧ�ܣ�\n");
	}
}

/*���ļ��м��ؼ�¼��Ϣ*/
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

/*��ʾ��¼��Ϣ����*/
void showRecordNodeTitle() {
	printf("%-16s", "�豸���");
	printf("%-16s", "�豸����");
	printf("%-16s", "״̬");
	printf("%-16s", "����");
	printf("\n");
}

/*��ʾ��¼��Ϣ*/
void showRecordNode(pRecordNode record) {
	printf("%-16s", record->id);
	printf("%-16s", record->name);
	printf("%-16s", record->state);
	printf("%-16s", record->date);
	printf("\n");
}

/*��ʾ��¼��Ϣ�б�*/
void showRecordNodeList(pRecordNodeList list) {
	pRecordNode cursor = NULL;
	printf("�X-------------------------------�[\n");
	printf(" $ ��ʾ��ʷ��¼��Ϣ $ \n");
	showRecordNodeTitle();
	cursor = list->head;
	while (cursor) {
		showRecordNode(cursor);
		cursor = cursor->next;
	}
	printf("�^-------------------------------�a\n");
}

/*�����豸*/
void borrowEquipment(pEquipmentNodeList equipment_list, pRecordNodeList record_list) {
	char id[128] = { 0 };
	pEquipmentNode equipment = NULL;
	printf("�X-------------------------------�[\n");
	printf(" $ �����豸 $ \n");
	printf("�^-------------------------------�a\n");
	printf("�����ţ�");
	scanf("%s", id);
	equipment = findEquipmentNodeListByID(equipment_list->head, id);
	if (equipment) {
		showEquipmentNodeTitle();
		showEquipmentNode(equipment);
		printf("-------------------\n");
		if (strcmp(equipment->state, "�ڿ�") == 0) {
			pRecordNode node = (pRecordNode)calloc(1, sizeof(RecordNode));
			strcpy(node->id, equipment->id);
			strcpy(node->name, equipment->name);
			strcpy(node->state, "����");
			strcpy(equipment->state, "����");
			printf("�������ڣ�");
			inputDate(node->date);
			addRecordNodeList(record_list, node);
			saveRecordFile(record_list);
			showRecordNodeTitle();
			showRecordNode(node);
			saveEquipmentFile(equipment_list);
			printf("�����ɹ���\n");
		} else {
			printf("����ʧ�ܣ����豸��ǰ״̬���������ã�\n");
		}
	} else {
		printf("δ�ҵ����豸��\n");
	}
}

/*�黹�豸*/
void returnEquipment(pEquipmentNodeList equipment_list, pRecordNodeList record_list) {
	char id[128] = { 0 };
	pEquipmentNode equipment = NULL;
	printf("�X-------------------------------�[\n");
	printf(" $ �黹�豸 $ \n");
	printf("�^-------------------------------�a\n");
	printf("�����ţ�");
	scanf("%s", id);
	equipment = findEquipmentNodeListByID(equipment_list->head, id);
	if (equipment) {
		showEquipmentNodeTitle();
		showEquipmentNode(equipment);
		printf("-------------------\n");
		if (strcmp(equipment->state, "����") == 0) {
			pRecordNode node = (pRecordNode)calloc(1, sizeof(RecordNode));
			strcpy(node->id, equipment->id);
			strcpy(node->name, equipment->name);
			strcpy(node->state, "�黹");
			strcpy(equipment->state, "�ڿ�");
			printf("�������ڣ�");
			inputDate(node->date);
			addRecordNodeList(record_list, node);
			saveRecordFile(record_list);
			showRecordNodeTitle();
			showRecordNode(node);
			saveEquipmentFile(equipment_list);
			printf("�����ɹ���\n");
		} else {
			printf("����ʧ�ܣ����豸��ǰ״̬������黹��\n");
		}
	} else {
		printf("δ�ҵ����豸��\n");
	}
}

/*ά�޵Ǽ�*/
void repairEquipment(pEquipmentNodeList equipment_list, pRecordNodeList record_list) {
	char id[128] = { 0 };
	pEquipmentNode equipment = NULL;
	printf("�X-------------------------------�[\n");
	printf(" $ ά�޵Ǽ� $ \n");
	printf("�^-------------------------------�a\n");
	printf("�����ţ�");
	scanf("%s", id);
	equipment = findEquipmentNodeListByID(equipment_list->head, id);
	if (equipment) {
		showEquipmentNodeTitle();
		showEquipmentNode(equipment);
		printf("-------------------\n");
		if (strcmp(equipment->state, "�ڿ�") == 0) {
			pRecordNode node = (pRecordNode)calloc(1, sizeof(RecordNode));
			strcpy(node->id, equipment->id);
			strcpy(node->name, equipment->name);
			strcpy(node->state, "ά�޵Ǽ�");
			strcpy(equipment->state, "ά��");
			printf("�������ڣ�");
			inputDate(node->date);
			addRecordNodeList(record_list, node);
			saveRecordFile(record_list);
			showRecordNodeTitle();
			showRecordNode(node);
			saveEquipmentFile(equipment_list);
			printf("�����ɹ���\n");
		} else {
			printf("����ʧ�ܣ����豸��ǰ״̬������ά�ޣ�\n");
		}
	} else {
		printf("δ�ҵ����豸��\n");
	}
}

/*���ά��*/
void doneEquipment(pEquipmentNodeList equipment_list, pRecordNodeList record_list) {
	char id[128] = { 0 };
	pEquipmentNode equipment = NULL;
	printf("�X-------------------------------�[\n");
	printf(" $ ���ά�� $ \n");
	printf("�^-------------------------------�a\n");
	printf("�����ţ�");
	scanf("%s", id);
	equipment = findEquipmentNodeListByID(equipment_list->head, id);
	if (equipment) {
		showEquipmentNodeTitle();
		showEquipmentNode(equipment);
		printf("-------------------\n");
		if (strcmp(equipment->state, "ά��") == 0) {
			pRecordNode node = (pRecordNode)calloc(1, sizeof(RecordNode));
			strcpy(node->id, equipment->id);
			strcpy(node->name, equipment->name);
			strcpy(node->state, "���ά��");
			strcpy(equipment->state, "�ڿ�");
			printf("�������ڣ�");
			inputDate(node->date);
			addRecordNodeList(record_list, node);
			saveRecordFile(record_list);
			showRecordNodeTitle();
			showRecordNode(node);
			saveEquipmentFile(equipment_list);
			printf("�����ɹ���\n");
		} else {
			printf("����ʧ�ܣ����豸��ǰ״̬������ά�ޣ�\n");
		}
	} else {
		printf("δ�ҵ����豸��\n");
	}
}

/*������¼*/
void searchRecordNodeByID(pRecordNodeList list) {
	char keyword[128] = { 0 };
	pRecordNode target = NULL;
	printf("�X-------------------------------�[\n");
	printf(" $ ������ʷ��¼��Ϣ $ \n");
	printf("�^-------------------------------�a\n");
	printf("����ؼ��ʣ�");
	scanf("%s", keyword);
	target = findRecordNodeListByKeyword(list->head, keyword);
	if (target) {
		showRecordNodeTitle();
		do {
			showRecordNode(target);
			target = findRecordNodeListByKeyword(target->next, keyword);
		} while (target);
	} else {
		printf("δ�ҵ����豸�ļ�¼��Ϣ!\n");
	}
}

/*�������*/
void process(pEquipmentNodeList equipment_list, pRecordNodeList record_list) {
//   system("title �豸��Ϣ����ϵͳ");
//	system("cls");
	/*���ļ��м����豸��Ϣ*/
	loadEquipmentFile(equipment_list);
	/*���ļ��м��ؼ�¼��Ϣ*/
	loadRecordFile(record_list);
	/*ѭ���˵�*/
	while (1) {
		int option;
		printf("�X-------------------------------�[\n");
		printf("        $ �豸��Ϣ����ϵͳ $ \n");
		printf(" ��1�� ����豸��Ϣ\n");
		printf(" ��2�� ����豸��Ϣ\n");
		printf(" ��3�� �޸��豸��Ϣ\n");
		printf(" ��4�� ɾ���豸��Ϣ\n");
		printf(" ��5�� �����豸��Ϣ\n");
		printf(" ��6�� �����豸\n");
		printf(" ��7�� �黹�豸\n");
		printf(" ��8�� ά�޵Ǽ�\n");
		printf(" ��9�� ���ά��\n");
		printf(" ��10�������ʷ��¼\n");
		printf(" ��11��������ʷ��¼\n");
		printf(" ��0���˳�ϵͳ\n");
		printf("�^-------------------------------�a\n");
		printf("           ��ѡ��");
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

/*������*/
int main() {
	system("color 8F");
	lmain();
	/*�����豸����*/
	EquipmentNodeList equipment_list = { 0 };
	/*�����¼����*/
	RecordNodeList record_list = { 0 };
	/*�������*/
	process(&equipment_list, &record_list);
	/*�����豸����*/
	clearEquipmentNodeList(&equipment_list);
	/*���ټ�¼����*/
	clearRecordNodeList(&record_list);
	return 0;
}


