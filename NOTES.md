[29.09.2015]

	Для того, чтобы скомпилировать main() для правильного кода надо было указать опцию -m32.

	А для линкера надо было добавить опцию -melf_i386

[28.09.2016]
	
	Идея ос Crystal:
	1) Используется только реальная физическая память.
	2) Первый процесс захватывает всю память, второй процесс занимает половину верхней памяти
	и так далее.
	Каждый последующий может делить пространство пополам 

	3) Адресация в программах локальная, порядок загрузки определяется обходом фрактала

[29.09.2016]

	Та же идея может использоваться и для файловой системы. Все что нужно знать это размер диска.

	Кластеризация будет использоваться по мере заполнения диска.

[3.10.2016]
	