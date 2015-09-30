// main.c -- Определяется точка входа в ядро в коде на C, вызов процедур инициализации.
// Сделано для руководства James Molloy

int main(struct multiboot *mboot_ptr)
{
 	// Здесь должны находиться все вызовы инициализационных процедур.
	monitor_clear();
	monitor_write("Hello, world!");
	return 0xDEADBEAF;
} 

