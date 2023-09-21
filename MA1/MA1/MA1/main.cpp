/*
Suggested Improvments:
1. The queue size is hardcoded as 10 preventing dynamic size allocation limiting the fexibility of the queue class
2. The queue class uses std:cout to print error messages when undeflow or overflow is enounted however doesnt allow the calling code to handle errors in a more specific capacity
3. The queue implementation couldve hav eused a different data structure that would be more effecient for the project
4. Naming of variables isnt conssistant throughout the program
5. Could have been more comments explaining the purpose of classes, roles or eahc member, and expected behavior of each function
*/
#include "testQueue.h"

int main() {1
    testSize();
    testIsEmpty();
    testIsFull();
    testDequeue1();
    testDequeue2();
    testEnqueue1();
    testEnqueue2();
    testPeek1();
    testPeek2();

    return 0;
}
