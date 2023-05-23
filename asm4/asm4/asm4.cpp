#include <iostream>

int main()
{
	setlocale(LC_ALL, "Russian");

	char a[] = "0111-";
	char sist; //системы счисления в которую переводим
	int num; 
	int b;
	int k;
	int s;
	char res[20];
	int n = strlen(a);
	bool f = false;
	if (a[n-1]=='-')
	{
		a[n - 1]='\0';
		f = true;
	}

	printf("Число %s в 4 \n", a);
	int col = strlen(a);
	_asm
	{
		mov sist, 4; //Заносим в переменную sist основание исходной системы счисления

		lea esi, a;

		mov ecx, [esi]
			mov eax, 0
			mov ebx, 0
			mov ecx, 0
			mov cl, sist;

		mov k, 0;
	to_Int: //перевод в число
		imul cx; //Умножение на си
		mov bl, [esi];
		cmp bl, 0;
		je endto_Int;
		sub bl, '0'; //Перевод символа в цифру
		mov[esi], bl;
		add ax, bx; //Добавление  цифры к числу
		mov num, eax;
		sub esi, 1;
		jmp to_Int;
	endto_Int:

		mov cx, 1;
		mov b, 0;

	tobin: //Перевод 10-тичного числа в 2-ичное
		mov eax, num;
		mov ebx, eax;
		cdq;
		mov si, 2;
		idiv si;
		imul ecx, 10;
		mov num, eax;
		imul edx, ecx;
		add b, edx;
		cmp num, 2;
		jge tobin;

		mov eax, 0;
		mov eax, b;
		cdq;
		mov ebx, 10;
		idiv ebx;
		mov ebx, num;
		imul ebx, ecx;
		add eax, ebx;
		mov num, eax;

		lea edi, res;
		mov ecx, 0;

		
	tostr:
		mov eax, num
			mov ebx, eax
			mov b, 10
			cdq
			idiv b
			mov num, eax
			mov bl, dl
			add bl, '0'; 
		push bl; 
		add ecx, 1; 
		cmp eax, 0;
		jne tostr;
		


	for_str: 
		pop eax;
		mov[edi], al;
		add edi, 1;
		sub k, 1;
		loop for_str;

		mov[edi], 0;
		jmp end;
	end:
	}
	n = strlen(res);

	for (int i = 0, j = n ; i < j; i++, j--) 
	{ 
		char ch = res[i]; 
		res[i] = res[j]; 
		res[j] = ch; 
	}
	if (f = true) 
	{
		res [n] ='-';
		res[n+1] = '\0';
	}
	printf("Число в 2 %s", res);

	getchar(); getchar();
}