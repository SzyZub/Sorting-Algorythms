A program about sorting algorithms made in c++ with the use of "raylib" graphical library.

Demonstration at:

https://www.youtube.com/watch?v=n2OfB4Zg9cE

It includes these sorting algorithms:

![ScreenShots](https://github.com/SzyZub/Sorting-Algorythms/blob/master/ScreenShots/1.png)

Every sorting algorithm has explanations and a demonstration of it in action.

![Explanation](https://github.com/SzyZub/Sorting-Algorythms/blob/master/ScreenShots/2.png)
![Demonstration](https://github.com/SzyZub/Sorting-Algorythms/blob/master/ScreenShots/3.png)



Sidenotes:

All explanations were made by me including the pictures

All demonstrations are done on random integer array with 100 fields, with each field having a number from 0 to 99(no duplicates)

Speed of the algorithm in demonstrations isn't equivalent to its real speed, even comparably to other algorithms, because:

1.function showing array representation on screen was placed manually in each sorting function, so as to show the best how they work(some algorithms even have them be called multiple times in one run through), there can be other ways to place them.

2.function showing array representation on screen has inbuilt sleep for 12ms so it can be seen easier how these sorting algorithms work.
      
If pressing left mouse button to exit a demonstration doesn't work, holding should to the trick.

Stalin sort is done by making any "discarded" field have a value of -1, which means it doesn't show up on the screen.

Counting sort demonstration is a bit incomprehensible, so

first it shows array counting all instances of a certain number 

then it shows that same array being changed so as to show where a certain number should be placed

and lastly it shows the output array being filled.  

The reason why the two last things show the same result is because each value shows up one time, if it wasn't so, they would be different. Also, the reason that there are random "lines" during the last part is because the created output array isn't initiated with any values, they are random.
