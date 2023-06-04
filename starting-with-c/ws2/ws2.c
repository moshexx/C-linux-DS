#include <stdio.h>
#include <string.h>
#include <assert.h>


int IsPalindrome(const char *s)
{
	size_t i,j;
	int len = strlen(s);
	
	for (i=0 ;j=len-1 ,i<j ;++i ,--len)
	{
		if (s[i] != s[j])
		{
			return 0;
		}
	}
	return 1;	
}

int main()
{
	char str1[]="abcba";
	int check1;
	char str2[]="12321";
	int check2;
	
	char str3[]="abcaa";
	int check3;
	char str4[]="12311";
	int check4;
	
	printf("The polindromes check:\n");
	check1 = IsPalindrome(str1);
	check2 = IsPalindrome(str2);
	check3 = IsPalindrome(str3);
	check4 = IsPalindrome(str4);
	
	printf("%s: %s\n" ,str1 ,check1>0? "is palindrome":"NOT a palindrome");
	printf("%s: %s\n" ,str2 ,check2>0? "is palindrome":"NOT a palindrome");
	printf("%s: %s\n" ,str3 ,check3>0? "is palindrome":"NOT a palindrome");
	printf("%s: %s\n" ,str4 ,check4>0? "is palindrome":"NOT a palindrome");
	
	return 0;
}




