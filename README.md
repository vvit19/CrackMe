# CrackMe
## Описание
В данном репозитории собраны программы из учебного проекта CrackMe, в рамках которого мы с [@OgKisque](https://github.com/ogkisque/hacking) перекрестно взламывали программы друг друга, написанные на TAsm, в которые изначально заложили по 1 уязвимости, связанные с переполнением буффера (то есть программа не проверяет число введенных символов). Программы запрашивают пароль, в случае совпадения выдают сообщение по типу: "Доступ разрешен", в противном случае - "Доступ отклонен". Наша задача, не зная паролей друг друга, заставить программу "разрешить доступ".
## Взлом через ввод пароля
В программе easy.com (исходник - easy.asm) находится код, который должен был взломать [@OgKisque](https://github.com/ogkisque/hacking). Буффер лежит в месте в памяти, где находится код самой программы, таким образом, переполняя его, можно было подменить байт-код и просто сделать jmp на место, которое печатает, что доступ разрешен. Программа [@OgKisque](https://github.com/ogkisque/hacking) (buffer_crack/ogkisque.com) имела такую же уязвимость, которую я использовал аналогичным образом (подаваемый на вход файл: buffer_crack/ogkisque.txt).

![pic1](https://github.com/vvit19/CrackMe/blob/main/pictures/pic1.png)

## Взлом через бинарный патч (таблетку)
Немного проще совершить взлом через бинарный патч (binpatch/binpatch.cpp), данная программа просто меняет offset в самом первом jmp из байт-кода (binpatch/arseasy.com) на offset в место, которое печатает, что доступ разрешен.

![pic2](https://github.com/vvit19/CrackMe/blob/main/pictures/pic2.png)
