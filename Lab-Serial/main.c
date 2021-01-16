/* main.c */
#include <main.h>
int main(void)
{
char c;
USART1_Init();
while(1)
{
if (USART1_Dequeue(&c) != 0)
{
USART1_SendChar(c);
}
}
}

