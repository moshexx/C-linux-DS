#include <stdlib.h>


	int g1;		/* 0000000000000004 C g1 */
	static int g2;	/* 0000000000000000 b g2 */
	static int g3 = 0;	/* 0000000000000004 b g3 */
	static int g4 = 8;	/* 0000000000000000 d g4	s */
	
	static void foo1()	/* 0000000000000000 t foo1 */
	{
		static int g5; /* 0000000000000008 b g5.2500 */
		int l1 = 9;
	}
	
	void foo2()	/* 0000000000000012 T foo2 */
	{
		static int g6 = 0; /* 000000000000000c b g6.2504 */
		static int g7 = 7; /* 0000000000000004 d g7.2505 */
		
		void *p = malloc(10);
		free(p); p = 0;
	}
	
	extern void bar();
	
/*                  U _GLOBAL_OFFSET_TABLE_
                	U malloc 
*/

/*
b - BSS. uninitialized data section
The symbol is in the uninitialized data section (known as BSS ). 

C - Common - uninitialized 
The symbol is common. Common symbols are uninitialized data. When linking, multiple common symbols may appear with the same name. If the symbol is defined anywhere, the common symbols are treated as undefined references. 

d - initialized data
The symbol is in the initialized data section. 

T /t - text (code) section

U
The symbol is undefined.

u
The symbol is a unique global symbol. This is a GNU extension to the standard set of ELF symbol bindings. For such a symbol the dynamic linker will make sure that in the entire process there is just one symbol with this name and type in use. 

 
