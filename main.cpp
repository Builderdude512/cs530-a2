// Your First C++ Program

#include <iostream>

bool first_pass();
bool second_pass();

int main() {
    first_pass();
    second_pass();
    return 0;
}

bool first_pass() 
{
    printf("first\n") ;
    return true;
}

bool second_pass() 
{
    printf("second\n") ;
    return true;
}
