#include <fstream>
double eps = 0;

int cmp (int* a, int* b) {
	if (&a > &b) return 1;
	else if (&a < &b) return -1;
	return 0;
}

void randomTest () {
	int quantity = 10000;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0,100);
	Rectangle* parr = new Rectangle[quantity];
	for (int i = 0; i < quantity; i++) {
		double x1 = dist(gen);
		double y1 = dist(gen);
		parr[i] = Rectangle(Point(x1, y1), Point(x1+dist(gen)+eps, y1+dist(gen)+eps));
	}
	parr->print("Рандомные прямоугольники.txt", quantity);
	List<Edge*>* edges = findContour (parr, quantity);
	edges->print("Рандомные прямоугольники.txt");

	delete [] parr;
	delete edges;
}

void randomTest2 () {
	int quantity = 1000;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0,100);
	std::random_device rd2;
	std::mt19937 gen2(rd2());
	std::uniform_int_distribution<> dist2(0,10);
	Rectangle* parr = new Rectangle[quantity];
	for (int i = 0; i < quantity; i++) {
		double x1 = dist(gen);
		double y1 = dist(gen);
		parr[i] = Rectangle(Point(x1, y1), Point(x1+dist2(gen2)+eps, y1+dist2(gen2)+eps));
	}
	parr->print("Рандомные прямоугольники 2.txt", quantity);
	List<Edge*>* edges = findContour (parr, quantity);
	edges->print("Рандомные прямоугольники 2.txt");

	delete [] parr;
	delete edges;
}

void randomTest3 () {
	int quantity = 1000;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0,1000);
	std::random_device rd2;
	std::mt19937 gen2(rd2());
	std::uniform_int_distribution<> dist2(0,10);
	Rectangle* parr = new Rectangle[quantity];
	for (int i = 0; i < quantity; i++) {
		double x1 = dist(gen);
		double y1 = dist(gen);
		parr[i] = Rectangle(Point(x1, y1), Point(x1+dist2(gen2)+eps, y1+dist2(gen2)+eps));
	}
	parr->print("Рандомные прямоугольники 3.txt", quantity);
	List<Edge*>* edges = findContour (parr, quantity);
	edges->print("Рандомные прямоугольники 3.txt");

	delete [] parr;
	delete edges;
}

void diagonalTest () {
	int quantity = 7;
	Rectangle* parr = new Rectangle[quantity];
	for (int i = 0; i < quantity-1; i++) { parr[i] = Rectangle(Point(i, i), Point(i+1, i+1)); }
	parr[quantity-1] = Rectangle(Point(3, 3), Point(4, 4));
	parr->print("Прямоугольники по диагонали.txt", quantity);
	List<Edge*>* edges = findContour (parr, quantity);
	edges->print("Прямоугольники по диагонали.txt");

	delete [] parr;
	delete edges;
}

void shrinkTest () {
	int quantity = 3;
	Rectangle* parr = new Rectangle[quantity];
	for (int i = 0; i < quantity; i++) { parr[i] = Rectangle(Point(0, 0), Point(quantity-i, quantity-i)); }
	parr->print("Сжимающиеся прямоугольники.txt", quantity);
	List<Edge*>* edges = findContour (parr, quantity);
	edges->print("Сжимающиеся прямоугольники.txt");

	delete [] parr;
	delete edges;
}

void latticeTest () {
	int quantity = 10000;
	Rectangle* parr = new Rectangle[quantity];
	for (int i = 0; i < sqrt(quantity); i++) {
		for (int j = 0; j < static_cast<int>(sqrt(quantity)); j++) { parr[i*static_cast<int>(sqrt(quantity)) + j] = Rectangle(Point(i, j), Point(i+1, j+1)); }
	}
	parr->print("Решетка.txt", quantity);
	List<Edge*>* edges = findContour (parr, quantity);
	edges->print("Решетка.txt");

	delete [] parr;
	delete edges;
}

void ladderTest () {
	int quantity = 100;
	Rectangle* parr = new Rectangle[quantity];
	for (int i = 0; i < quantity/2; i++) { parr[i] = Rectangle(Point(i, i), Point(i+2, i+2)); }
	for (int i = 0; i < quantity/2; i++) { parr[quantity/2+i] = Rectangle(Point(quantity/2-i, i), Point(quantity/2-i+2, i+2)); }
	parr->print("Объединение лесенок.txt", quantity);
	List<Edge*>* edges = findContour (parr, quantity);
	edges->print("Объединение лесенок.txt");

	delete [] parr;
	delete edges;
}

void embeddedTest () {
	int quantity = 1000;
	Rectangle* parr = new Rectangle[quantity];
	for (int i = 1; i < quantity+1; i++) { parr[i] = Rectangle(Point(quantity/2-i, quantity/2-i), Point(quantity/2+i, quantity/2+i)); }
	parr->print("Вложенные квадраты.txt", quantity);
	List<Edge*>* edges = findContour (parr, quantity);
	edges->print("Вложенные квадраты.txt");

	delete [] parr;
	delete edges;
}
