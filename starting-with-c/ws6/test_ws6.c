#include <stdio.h>
#include <stdlib.h>
#include "ws6.h"


void TestPow2();
void TestCount();
void TestIsPow2();
void TestIsPow2NoLoop();
void TestAdd1();
void TestByteMirror();
void TestSwap();
void TestClosest();
void TestNotIf1();
void TestNotIf2();
void TestNotIf3();
void TestFloatAnalysis();

int main()
{    
	TestPow2();
	TestCount();
	TestIsPow2();
	TestIsPow2NoLoop();
	TestAdd1();
	TestByteMirror();
	TestSwap();
	TestClosest();
	TestNotIf1();
	TestNotIf2();
	TestNotIf3();
	TestFloatAnalysis();
	
	return 0;    
}

void TestPow2()
{    
	unsigned int x =2;
	unsigned int y =3;
	long int exercis1 = Pow2(x ,y);
	printf("TestPow2\n%ld \n" ,exercis1);
}

/* Program to test function count & CountNoLoop */
void TestCount()
{
	unsigned int n ,m ,t=30;
	n = CountNoLoop(t);
	m = Count(t);
	printf("CountNoLoop\nThe number:%d\ncount set bits: %d\n" ,t ,n);
	printf("Count	    \nThe number:%d\ncount set bits: %d\n" ,t ,m); 
}

void TestIsPow2()
{
	unsigned int n = 8; 
	printf("TestIsPow2\nIs n power of 2? 1/0: %d\n", IsPow2(n)); 
}

void TestIsPow2NoLoop()
{
	unsigned int num = 4;
	int count;
      
	count = IsPow2NoLoop(num);
	printf("TestIsPow2NoLoop\nIs n power of 2? 1/0: %d\n", count);
}

void TestAdd1()
{
	int n = 4;
	printf("TestAdd1\n %d\n", Add1(n)); 
}

void TestByteMirror()
{
	unsigned int n = 4;
	unsigned int m;
	
	m = ByteMirror(n);
	printf("the number: %d\nByte Mirror: %d\n" ,n ,m);
	m = ByteMirrorNoLoop(n);
	printf("the number: %d\nByte Mirror No Loop: %d\n" ,n ,m);
}

void TestSwap()
{
	int num1 = 10;
	int num2 = 2;
	
	printf("*n1=%d\n*n2=%d\n" ,num1 ,num2);
	Swap(&num1 ,&num2);
	printf("*n1=%d\n*n2=%d\n" ,num1 ,num2);
}

void TestClosest()
{
	unsigned int n = 20;
	
	n = Closest(n);
	printf("%d\n" ,n);
}

void TestNotIf1()
{
	unsigned char c = 68;
	unsigned int n;
	
	n = NotIf1(c);
	printf("%d %c\n" ,n ,c);
} 

void TestNotIf2()
{
	unsigned char c = 64;
	unsigned int n;
	
	n = NotIf2(c);
	printf("%d %c\n" ,n ,c);
} 

void TestNotIf3()
{
	unsigned int n ,t=54;
	n = NotIf3(t);
	printf("before:%d\nafter: %d\n" ,t ,n);
	PrintInBinary(t);
	PrintInBinary(n);
} 

void TestFloatAnalysis()
{
	float n = 3.14;
	
	FloatAnalysis(n);
} 
