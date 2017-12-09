Collaborators: Prikshet Sharma, Nathan McCloud

We implemented the function that creates a new tuple, and we call it newTuple. It looks like this:

newTuple(int index, int nAttr, ...);

-The first argument in newTuple is to specify the index of the array of attributes (attr) the key resides in. 
-The second argument of newTuple gives the number of arguments that'll follow in this function. We're using va_list from <stdarg.h>.
-We want to claim 20% extra credit as mentioned in extra credit requirement.



What we do in our program:
-insert all the tuples in their respective tables. 
-we also prevent insertions when the user tries to insert a tuple with a key that already exists in the relation. 
-print all the relations.
-perform some delete operations.
-print all the relations to show that the delete did after all work.
-do some lookups.
-read from file and add the tuples from the file readtest0.txt to the pre-existing database.
-write to file


to run the file, type the following command:
gcc mydatabase.c -g -o mydatabase

Then run using ./mydatabase


Thank you for grading our project!

