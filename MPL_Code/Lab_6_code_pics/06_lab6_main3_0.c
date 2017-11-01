//These functions inside the asm file
extern void GPIO_init();
extern void MAX7219_init();
extern void MAX7219Send(unsigned char address, unsigned char data);
/**
* TODO: Show data on 7-seg via max7219_send
* Input:
* data: decimal value
* num_digs: number of digits will show on 7-seg
* Return:
* 0: success
* -1: illegal data range(out of 8 digits range)
*/
void display(int data, int num_digs)
{
	int remainder, i;
	for(i=0;i<num_digs-1;i++)
	{
		remainder = data%10;
		MAX7219Send(i+1, remainder);
		data/=10;
	}
	MAX7219Send(i+1,0);
}

int main()
{
	int student_id = 416005;
	GPIO_init();
	MAX7219_init();
	display(student_id, 7);
	return 0;
}
