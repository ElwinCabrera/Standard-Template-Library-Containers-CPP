/*

Original : https://www.hackerrank.com/challenges/dynamic-array/problem

*Create a list, seqList, of N empty sequences, where each sequence is indexed from 0 to N-1. The elements within each of the sequences also use 0 indexing.
*Create an integer, lastAnswer, and initialize it to 0.
The 2 types of queries that can be performed on your list of sequences (seqList) are described below:

    1. Query: 1 x y
        1. Find the sequence, seq, at index ((x ^ lastAnswer)% N) in seqList.
        2. Append integer y to sequence seq.

    2. Query: 2 x y
        1. Find the sequence, seq, at index ((x ^ lastAnswer)% N) in seqList.
        2. Find the value of element y % size in seq (where size is the size of seq) and assign it to lastAnswer.
        3. Store the new value of lastAnswer in an array.

Task
Given
N, Q, and Q queries, execute each query.

Input Format

The first line contains two space-separated integers, N (the number of sequences) and Q (the number of queries), respectively.

Each of the Q subsequent lines contains a query in the format defined above.

Constraints

It is guaranteed that query type 2 will never query an empty sequence or index.

Output Format

For each type 2 query, save the updated value of lastAnswer in an array.

Sample Input

2 5
1 0 5
1 1 7
1 0 3
2 1 0
2 1 1

Sample Output

[7, 3]

Explanation

Initial Values:
N = 2 
lastAnswer = 0 

s0 = [ ]

s1 = [ ]

Query 0: Append 5 to sequence ((0^0) %2) =0.
lastAnswer = 0

s0 = [5]

s1 = [ ]

Query 1: Append 7 to sequence ((1^0) %2) =1.
lastAnswer = 0
s0 = [5]

s1 = [7]

Query 2: Append 3 to sequence ((0^0) %2) =0.
lastAnswer = 0

s0 = [5, 3]

s1 = [7]

Query 3: Assign the value at index 0 of sequence ((1^0) %2) =1 to lastAnswer, store lastAnswer in array.
lastAnswer = 7

s0 = [5, 3]

s1 = [7]

 Result: [7]

Query 4: Assign the value at index 1 of sequence ((1^7) %2) =0 to lastAnswer, print store lastAnswer in array.
lastAnswer = 3

s0 = [5, 3]

s1 = [7]

  Result: [7, 3]


*/

#include <iostream>
#include <vector>

using std::vector;

/*
 * Complete the 'dynamicArray' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY queries
 */

/*
First we need to create an 2D array with a size of n to create our sequences.

Then for any query we need to get the corresponding sequence by using this formula
((x ^ lastAnswer) % N) where x is queries.at(i).at(1), N is the total number of sequences, and lastAnswer is a variable initally 0 an only changed on a type 2 query.

In a type 1 query we simply get the corresponding sequence using the formula mentioned above and append queries.at(i).at(2) to that sequence.

In a type 2 query we also get the corresponding sequence using th formula mentioned above and then we find a value in that sequence using (queries.at(i).at(2) % sequence size) to compute the index and assign lastValue to the value in the computed index. then we store that value in an array. 

*/
vector<int> dynamicArray(int n, vector<vector<int>> queries) {
    vector<vector<int>> sequences(n);
    vector<int> result;
    int lastValue = 0;
    for(int q = 0; q < queries.size(); q++){
        int x = queries.at(q).at(1);
        int y = queries.at(q).at(2);
        int seqIdx = ((x ^ lastValue) % n);

        if(queries.at(q).at(0) == 1){
            sequences.at(seqIdx).push_back(y);
        } else {
            int seqValIdx = y % sequences.at(seqIdx).size();
            lastValue = sequences.at(seqIdx).at(seqValIdx);
            result.push_back(lastValue);
        }
    }
    return result;
}