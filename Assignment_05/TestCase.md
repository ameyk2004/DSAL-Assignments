# Test Cases

<pre>
    //paste this in main
    Dictionary dict;

    // Test Case 1: Direct insertion
    dict.insert("apple", "fruit");

    // Test Case 2: Insertion in the same index where value is present
    dict.insert("orange", "fruit");
    dict.insert("banana", "fruit");

    // Test Case 3: Insertion of duplicate key
    dict.insert("banana", "fruit"); // This should print "key banana already present"

    // Test Case 4: Searching value present
    dict.searchKey("apple");

    // Test Case 5: Searching value not present
    dict.searchKey("grape"); // This should print "Key does not exist"
</pre>