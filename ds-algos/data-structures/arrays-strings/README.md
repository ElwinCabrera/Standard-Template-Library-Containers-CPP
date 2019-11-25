# Arrays and Strings

## Arrays

Arrays are one of the most basic and simplest data structure in computer science. An array stores a fixed size collection of elements of the same data type. In memory arrays are usually continuos so that each element can easily be identified by an array index.

## Strings

A string is a just an array that only stores a specific data type. The data type that strings store are usually ascii characters (letters, numbers and a couple special symbols). You can think of a string as a special type of array.

## Time Complexity

### Inserting

Inserting elements to an array at the end of the array is O(1) time. However, inserting elements somewhere other than the end of the array will cost O(n) time since you would have to shift all elements to the right by one position.

### Deleting

The runtime for deleteing elements from an array is similar to that of inserting elements. If you delete an element form the end of the array it will cost you O(1) time. However, deleting elements from any point other than the end will cost you O(n) time since you would have to move all elements to the left by one position to keep the continuous property of an array (arrays need to be continuous so that it can be indexed an have O(1) access time).

### Access

Since arrays are continuous access time for any array is always O(1) and you can access an array element by its index.

## Space Complexity

Arrays start with a fixed size in the beggining so the space complexity would be O(n) where n is the initial size of the array.

## Resizable Arrays

In some programming languages arrays are resizable. This means that unlike a typical array where size is fixed at the start, with resizable arrays the array grows automatically as you add more items. An example of a resizable array in C++ is the Vector data structure. When you need an array like data structure that offers dynamic resizing you would use something like a Vector. In a typical implementation of an array access time is O(1). However, in an dynamically resizable array access is still O(1) unless the array is full at that point adding an element would cause the array to double in size. Each time the dynamic array doubles in size it takes O(n) time to copy all of the original elements to a new array with the new size. This doubling in size happens so rarely that the runtime of inserting a new element into a dynamic resizable array is amortized O(1) time.
