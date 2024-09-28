#include <iostream>
#include <ostream>
#include <string>
#include <cmath>
#include "Plane.hpp"

int main () {
	Set_points a;
	std::cout << "Вывод множества A: "<< a << std::endl;
	try { a.p_delete(1, 0); }
	catch (Exception ex){ ex.print_message(); }

	a(100, 200);
	a.p_delete(100, 200);

	a.p_add(0, 0);
	std::cout << "Вывод множества A (добавдение элемента (0, 0)): " << a;
	a.p_delete(0,0);
	std::cout << "Вывод множества A (удаление элемента (0, 0)): "<< a << std::endl;

	a.p_add(12, 124);
	a.p_add(34, 32);
	a.p_add(154, 65);
	std::cout << "Добавление элементов (12, 124), (34, 32), (154, 65) в A: " << a << std::endl;

	a.p_delete(34,32);
	std::cout << "Удаление элемента (34, 32) из A: " << a;
	a.p_delete(12, 124);
	std::cout << "Удаление элемента (12, 124) из A: " << a << std::endl;

	try { a.p_delete(1, 0); }
	catch (Exception ex){ ex.print_message(); }

	try { a.p_add(0, 0); }
	catch (Exception ex){ ex.print_message(); }

	Set_points b = a;
	std::cout << "A: " << a;
	std::cout << "B: " << b << std::endl;

	try { b.p_add(154, 65); }
	catch (Exception ex){ ex.print_message(); }

	b.p_delete(154, 65);
	std::cout << "Удаление элемента (154, 65) из B: " << b;
	b.p_delete(0, 0);
	std::cout << "Удаление элемента (0, 0) из B: " << b << std::endl;

	Set_points c;
	c.p_add(23, 43);
	c.p_add(50, 50);
	c.p_add(0, 0);
	c.p_add(50, 51);
	std::cout << "Сравнение множеств A и C: " << std::endl << "A: " << a << "C: " << c << std::endl;

	c = a;
	a = a;
	std::cout << "Присваивание C A: " << std::endl << "A: " << a << "C: " << c << std::endl;

	a.p_delete(0, 0);
	a.p_delete(154, 65);
	a = c;
	std::cout << "Присваивание A C (A пусто): " << std::endl << "A: " << a << "C: " << c << std::endl;

	if (a == b) { std::cout << "Множество A совпадает с множеством B." << std::endl; }
	else { std::cout << "Множество A не совпадает с множеством B." << std::endl; }
	std::cout << std::endl << "A: " << a << "B: " << b << std::endl;


	if (c != b) { std::cout << "Множество C не совпадает с множеством B." << std::endl; }
	else { std::cout << "Множество C совпадает с множеством B." << std::endl; }
	std::cout << std::endl << "C: " << c << "B: " << b << std::endl;


	if (a == c) { std::cout << "Множество A совпадает с множеством C." << std::endl; }
	else { std::cout << "Множество A не совпадает с множеством C." << std::endl; }
	std::cout << std::endl << "A: " << a << "C: " << c << std::endl;


	Set_points d;
	d.p_add(100, 300);
	Set_points e;
	e.p_add(100, 300);
	e.p_add(1000, 3000);

	if (d == e) { std::cout << "D = E" << std::endl; }
	else { std::cout << "D != E" << std::endl; }
	std::cout << std::endl << "D: " << d << "E: " << e << std::endl;

	if (a == d) { std::cout << "Множество A совпадает с множеством D." << std::endl; }
	else { std::cout << "Множество A не совпадает с множеством D." << std::endl; }
	std::cout << std::endl << "A: " << a << "D: " << d << std::endl;

	Set_points big_1;
	Set_points big_2;
	if (big_1 == big_2) { std::cout << "Равенство пустых множеств." << std::endl; }
	for (int i = 0; i < 100; i++) {	big_1.p_add(std::sqrt(i), i*(i/2)); }
	for (int i = 0; i < 99; i++) { big_2.p_add(std::sqrt(i), i*(i/2)); }
	big_2.p_add(-100, -200);

	if (big_1 != big_2) { std::cout << "Два больших множества не совпали." << std::endl; }
	else { std::cout << "Два больших множества совпали." << std::endl; }
	std::cout << "BIG1: "<< std::endl << big_1 << "BIG2: " << std::endl << big_2 << std::endl;

	Set_points big_3 = big_1|big_2;
	std::cout << "Объединение множеств BIG_1 и BIG_2: " << big_3 << std::endl;

	if (big_3 == big_1 || big_3 == big_2) { std::cout << "Одно из множеств BIG_1 или BIG_2 полностью совпадает с объединением этих двух множеств."<< std::endl; }
	else { std::cout << "Множества все-таки отличаются." << std::endl; }

	Set_points set = big_3|a;
	std::cout << "Объединение множеств BIG_1 и BIG_2 и A: " << set << std::endl;
	if (set == big_3 || set == a) { std::cout << "Одно из множеств BIG_1 и BIG_2 или A полностью совпадает с объединением этих двух множеств."<< std::endl; }

	Set_points empty;
	Set_points un_empty = empty|big_3;
	std::cout << "Объединение пустого множества и объединения множеств BIG_1 и BIG_2: " << un_empty << std::endl;

	big_3 = big_1&big_2;
	std::cout << "Пересечение множеств BIG_1 и BIG_2:" << big_3 << std::endl;

	if (big_3 == big_1 || big_3 == big_2) { std::cout << "Одно из множеств BIG_1 или BIG_2 полностью совпадает с пересечением этих двух множеств."<< std::endl; }
	else { std::cout << "Множества все-таки отличаются." << std::endl; }

	set = big_3&a;
	std::cout << "Пересечение множеств BIG_1 и BIG_2 и A: " << set << std::endl;
	if (set == big_3 || set == a) { std::cout << "Одно из множеств BIG_1 и BIG_2 или A полностью совпадает с пересечением этих двух множеств."<< std::endl; }

	if ((big_1&big_2) != (big_1|big_2)) { std::cout << "Объединение и пересечение множеств не совпадают." << std::endl; }

	std::cout << "Пересечение пустого множества с некоторым множеством, содержащим элементы: " << (empty&big_3) << std::endl;
	std::cout << "Пересечение множеств BIG_2 и BIG_2: " << (big_2&big_2) << std::endl;

	std::cout << "Разность множеств BIG_1 и BIG_2: " << (big_1-big_2) << std::endl;
	std::cout << "Разность множеств BIG_2 и BIG_1: " << (big_2-big_1) << std::endl;
	std::cout << "Разность множеств BIG_2 и BIG_2: " << (big_2-big_2) << std::endl;
	std::cout << "Разность множеств BIG_2 и BIG_2: " << (empty-big_2) << std::endl;
	std::cout << "Разность множеств BIG_2 и BIG_2: " << (big_2-empty) << std::endl;
	if (big_2 == (big_2-empty)) { std::cout << "Множества BIG2 и BIG2 без пустого множества совпадают." << std::endl; }

	a |= big_1;
	std::cout << "Множество A (измененное), объединенное с множеством BIG1: " << a << std::endl;
	if (a != big_1) { std::cout << "Множества BIG2 и A не совпадают." << std::endl; }
	a |= empty;

	a &= big_2;
	std::cout << "Множество A (измененное), пересеченное с множеством BIG2: " << a << std::endl;
	
	a -= empty;

	Rectangle rect(Point(-10, 0), Point(10, 0), Point(0,-10), Point(0, 10));
	try { big_3.print_in_rectangle(rect); }
	catch (Exception ex){ ex.print_message(); }

	std::cout << std::endl;

	Rectangle Rect(Point(-100, 0), Point(0, -100), Point(100, 0), Point(0, 100));
	big_3.print_in_rectangle(Rect);
	std::cout << std::endl;

	std::cout << big_3;
	std::cout << std::endl;

	Rectangle REct(Point(-1, -1), Point(-3, -1), Point(-3, -2), Point(-1, -2));
	big_3.print_in_rectangle(REct);
	std::cout << std::endl;

	Rectangle RECt(Point(-1, -1), Point(-100, -200), Point(-3, -2), Point(-1, -10));
	try { big_3.print_in_rectangle(RECt); }
	catch (Exception ex){ ex.print_message(); }

	Rectangle RECT(Point(-1, -1), Point(-100, -200), Point(-1, -1), Point(-1, -10));
	try { big_3.print_in_rectangle(RECT); }
	catch (Exception ex){ ex.print_message(); }

	return 0;
}
