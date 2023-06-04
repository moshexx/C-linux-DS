פסאודוקוד למיון מערך רנדומלי ע"י HeapSort
*****************************************
* סיבוכיות זמן:  O(nlog(n))
* סיבוכיות מקום: O(1) מבוצע in place


* להפוך את המערך הרנדומלי למערך שמסודר כheap 
  ******************************************
  סיבוכיות: O(nlog(n))
  * לבצע HeapifyDown לכל ההורים מלמטה עד לroot:
  	לולאה מהאלמנט האחרון שהוא לא עלה (i = size/2-1) עד השורש (i = 0)
		/*** בתרגום לשפת אם:         for(i = size / 2 - 1; 0 <= i; --i) */	


* לבצע HeapSort: מערך שמסודר כheap --> מערך ממוין
  ***********************************************
  סיבוכיות: O(nlog(n))
  * לשמור גודל המערך במשתנה נוסף. size = sizeof(arr)-1
  * לולאה מ i = 0 עד i <= sizeof(arr):
  	  * נבצע Swap בין arr[0] לבין arr[size - 1]
	  * לבצע HeapifyDown לroot עד size--.
	  	/**** המערך מחולק ל2:
	  		* חלק שמאלי שהוא מערך בתצורת heap
	  		* וחלק ימני שהוא המערך הממוין החדש (בסדר הופכי)
	  		בכל איטרציה המערך הימני גדל והשמאלי קטן */
	  
	  		
* לבצע reverse למערך:
  *******************
  סיבוכיות: O((n)). *אפשר לדלג !
  * להגדיר ולאתחל 2 אינדקסים: 
  	  * הראשון i = 0
  	  * השני j = size -1
  *	להגדיר משתנה זמני tmp
  * לולאה כל עוד i < j; קידום לאחר כל איטרציה i,--j++.
  	* השמה tmp = arr[j]
  	* השמה arr[j] = arr[i]
  	
  	
   /* **ניתן לבצע heap min / heap max -> 
		כדי לוותר על פעולת הreverse יש לסדר את המערך כheap *הפוך* 
		מהתוצאה הסופית שאנו רוצים - כך נוותר על הreverse.
		דוגמה: מערך --> max heap --> מערך ממוין מהקטן לגדול. */

	  	
  
  
  
