#include"monitor.h"


// Обновляем аппаратный курсор.
static void move_cursor()
{
   // The screen is 80 characters wide...
   u16int cursorLocation = cursor_y * 80 + cursor_x;
   outb(0x3D4, 14);                  // Сообщаем плате VGA о том, что мы посылаем старший байт курсора.
   outb(0x3D5, cursorLocation >> 8); // Посылаем старший байт курсора.
   outb(0x3D4, 15);                  // Сообщаем плате VGA о том, что мы посылаем младший байт курсора.
   outb(0x3D5, cursorLocation);      // Посылаем младший байт курсора.
} 

// Скроллинг текста на экране на одну строку вверх.
static void scroll()
{

   // Берем символ пробела с атрибутами цвета, заданными по умолчанию.
   u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   u16int blank = 0x20 /* space */ | (attributeByte << 8);

   // Строка 25 находится внизу, это означает, что нам нужно выполнить скроллинг вверх
   if(cursor_y >= 25)
   {
       // Перемещаем кусок текста, отображаемого в текущий момент, 
       // обратно в буфер, сдвинув его на одну строку 
       int i;
       for (i = 0*80; i < 24*80; i++)
       {
           video_memory[i] = video_memory[i+80];
       }

       // Последняя строка должна теперь быть пустой. Это осуществляется 
       // записью в нее 80 символов пробела.
       for (i = 24*80; i < 25*80; i++)
       {
           video_memory[i] = blank;
       }
       // Теперь курсор должен находиться на последней строке.
       cursor_y = 24;
   }
} 

// Writes a single character out to the screen.
void monitor_put(char c)
{
   // Цвет фона - черный (0), цвет текста - белый (15).
   u8int backColour = 0;
   u8int foreColour = 15;

   // Байт атрибута состоит из двух полубайтов - младший является цветом, 
   // используемым для отображения текста, а старший - фоновым цветом.
   u8int  attributeByte = (backColour << 4) | (foreColour & 0x0F);
   // Байт атрибута представляет собой 8 старших битов слова, которое мы должны 
   // послать на плату VGA.

   u16int attribute = attributeByte << 8;
   u16int *location;

   // Обработка символа backspace - перемещаем курсор на одну позицию обратно
   if (c == 0x08 && cursor_x)
   {
       cursor_x--;
   }

   // Обработка символа табуляции - увеличиваем координату X курсора,
   // но так, чтобы она делилась на 8
   else if (c == 0x09)
   {
       cursor_x = (cursor_x+8) & ~(8-1);
   }

   // Обрабатываем возврат каретки
   else if (c == '\r')
   {
       cursor_x = 0;
   }

   // Обрабатываем переход на новую строку - перемещаем курсор обратно 
   // влево и увеличиваем номер строки
   else if (c == '\n')
   {
       cursor_x = 0;
       cursor_y++;
   }
   // Обрабатываем другие символы, которые можно выводить на экран.
   else if(c >= ' ')
   {
       location = video_memory + (cursor_y*80 + cursor_x);
       *location = c | attribute;
       cursor_x++;
   }

   // Проверяем, нужно ли нам добавлять новую строку из-за того, что
   // мы достигли конца экрана.
   if (cursor_x >= 80)
   {
       cursor_x = 0;
       cursor_y ++;
   }

   // Скроллинг экрана, если это необходимо.
   scroll();
   // Перемещение аппаратного курсора.
   move_cursor();
} 

// Очистка экрана - записываем пробелы во фреймбуфер.
void monitor_clear()
{
   // Устанавливаем в байте атрибутов значения цветов, используемые по умолчанию
   u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   u16int blank = 0x20 /* space */ | (attributeByte << 8);

   int i;
   for (i = 0; i < 80*25; i++)
   {
       video_memory[i] = blank;
   }

   // Перемещаем аппаратный курсор в начало.
   cursor_x = 0;
   cursor_y = 0;
   move_cursor();
} 

// Выдаем на монитор строку ASCII, завершающуюся символом null.
void monitor_write(char *c)
{
   int i = 0;
   while (c[i])
   {
       monitor_put(c[i++]);
   }
} 
