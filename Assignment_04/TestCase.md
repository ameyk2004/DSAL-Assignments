# Test Cases

## Test Case

<br>
<pre>
Index   Telephone Num   Client Name
0       5               e
1       2               b
2       9               i
3       6               f
4       3               c
5       10              j
6       7               g
7       4               d
8       1               a
9       8               h
</pre>

## Without Replacement
<pre>
    //copy this to and paste in main function
    TelephoneBook telBook(10, false);

    telBook.insert(12345, "amey");
    telBook.insert(1235, "vardhan");
    telBook.insert(1232, "tirthraj");

    telBook.printTable();
</pre>
## Output
<pre>
Index   Telephone Num   Client Name
0       12345           amey
1       1235            vardhan
2       1232            tirthraj
3       0
4       0
5       0
6       0
7       0
8       0
9       0
</pre>

<hr>
## With Replacement
<pre>
    //copy this to and paste in main function
    TelephoneBook telBook(10, true);

    telBook.insert(12345, "amey");
    telBook.insert(1235, "vardhan");
    telBook.insert(1232, "tirthraj");

    telBook.printTable();
</pre>
## Output
<pre>
Index   Telephone Num   Client Name
0       12345           amey
1       1232            tirthraj
2       1235            vardhan
3       0
4       0
5       0
6       0
7       0
8       0
9       0
</pre>




