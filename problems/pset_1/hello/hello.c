#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Getting String
    string name = get_string("What's your name? "); 
    
    // Pint String
    printf("hello, %s\n", name); 
}