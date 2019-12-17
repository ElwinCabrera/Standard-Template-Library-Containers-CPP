# Concepts

### Big O

Usually when we talk about Big O we are talking about time/space complexity (The time it takes to run the program). There are 
three major cases that people look at when analyzing an algorithm. First, is the best case runtime, this runtime describes under what situation 
the current algorithm runs the fastest or has a low runtime most of the time. This case isn't very useful since technically you could say that any 
algorithm runs o(1) by giving some special input. Second, is the average case this is what most people look at and it describes how fast a program would 
run most of the time. Third, is the worst case and this describes what is the worst runtime that this algorithm can have. When dealing with runtime it is best to drop the non dominant terms for example if you have a runtime of O(2N) it would be considered O(N) or if you have a runtime of O(N^2 + N) you would simply say the runtime is O(N^2).
