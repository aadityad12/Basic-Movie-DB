# Basic-Movie-DB
C++ - CIS22B A3

This code reads and copies all the data about movies from a file called movies.txt, it allows the user to search for a movie which may or may not be in the file. If it is not in the file it will say so if it is in then it will display all the relevant data and ask if the user wants to save that movie in another seperate file called favorites.txt. The code will keep looping asking the user for a movie to search from the database until the user exits. the user can exit after each iteration when asked. After the user chooses to exit the list of saved movies will be displayed will all their details.

```
Please enter filename: test.txt
ERROR!! Please try again
Please enter filename: movies.txt
Enter a movie title to search: avaTAR

    Title: Avatar
    Gross Total: 2.788 billion dollars
    Director:  James Cameron
    Release date:  12/18/09
    Runtime: 161 minutes

Would you like to save the above movie? (Y or N): y
Would you like to exit? (Y/N): n
Enter a movie title to search: frozen

    Title: Frozen
    Gross Total: 1.276 billion dollars
    Director:  Chris Buck & Jennifer Lee
    Release date:  11/27/13
    Runtime: 102 minutes

Would you like to save the above movie? (Y or N): n
Would you like to exit? (Y/N): n
Enter a movie title to search: hello kitty
Error: 'hello kitty' not found in database. Please try again.
Would you like to exit? (Y/N): N
Enter a movie title to search: toy story 3

    Title: Toy Story 3
    Gross Total: 1.067 billion dollars
    Director:  Lee Unkrich
    Release date:  7/18/10
    Runtime: 103 minutes

Would you like to save the above movie? (Y or N): Y
Would you like to exit? (Y/N): Y

Your saved movies are:

    Title: Avatar
    Gross Total: 2.788 billion dollars
    Director:   James Cameron
    Release date:   12/18/09
    Runtime: 161 minutes


    Title: Toy Story 3
    Gross Total: 1.067 billion dollars
    Director:   Lee Unkrich
    Release date:   7/18/10
    Runtime: 103 minutes
```
