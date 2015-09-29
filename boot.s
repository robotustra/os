;
; boot.s -- Место, откуда начинается ядро. Также определяет заголовок мультизагрузки multiboot.
; За основу взят файл start.asm из руководства по разработке ядра Brans kernel development tutorial
;

MBOOT_PAGE_ALIGN    equ 1<<0    ; Загружает ядро и модули на границу страницы
MBOOT_MEM_INFO      equ 1<<1    ; Предоставляет вашему ядру информацию о памяти
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; Магическое значение Multiboot Magic
; ЗАМЕЧАНИЕ: Мы не используем значение MBOOT_AOUT_KLUDGE. Это значит, что GRUB 
; не передает нам символьную таблицу.
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)


[BITS 32]                       ; Все инструкции должны быть 32-битовыми.

[GLOBAL mboot]                  ; Собираем 'mboot' из кода на C.
[EXTERN code]                   ; Начало секции '.text'.
[EXTERN bss]                    ; Начало секции .bss .
[EXTERN end]                    ; Конец последней загружаемой секции.

mboot:
  dd  MBOOT_HEADER_MAGIC        ; GRUB будет искать это значение для каждой 
                                ; 4-байтной границы в файле вашего ядра
  dd  MBOOT_HEADER_FLAGS        ; Указывает, как GRUB должен загружать   ваш файл / настройки
  dd  MBOOT_CHECKSUM            ; Чтобы обеспечить, чтобы приведенные выше значения были корректными
   
  dd  mboot                     ; Место размещения дескриптора
  dd  code                      ; Начало секции '.text' (код) ядра.
  dd  bss                       ; Начало секции '.data' ядра.
  dd  end                       ; Конец ядра.
  dd  start                     ; Точка входа в ядро (первоначальный EIP).

[GLOBAL start]                  ; Точка входа в ядро.
[EXTERN main]                   ; Это точка входа в ваш код на C

start:
  push    ebx                   ; Загрузка указателя на место размещения заголовка multiboot

  ; Выполнение ядра:
  cli                         ; Отключаем прерывания.
  call main                   ; вызываем нашу функцию main().
  jmp $                       ; Входом в бесконечный цикл, который останавливает работу
                              ; процессора всякий раз, в память обнаруживается мусор 
                              ; после работы нашего ядра! 
