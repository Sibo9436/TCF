#ifndef DATE1_H
#define DATE1_H

class Date {
    public:
	Date(int = 1, int = 1, int = 1900);
	void print() const;
	~Date();
    private:
	int month;
	int day;
	int year;
	int checkDay(int) const;
};
#endif
