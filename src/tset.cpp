// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(-1)
{
	MaxPower = mp; 
	BitField = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(-1)
{
	BitField = s.BitField; 
	MaxPower = s.MaxPower; 
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(-1)
{
	MaxPower = bf.GetLength(); 
	BitField = bf; 
}

TSet::operator TBitField()
{
	TBitField BP (this->BitField); 
	return BP; 
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower; 
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem); 
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem); 
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField; 
	MaxPower = s.MaxPower; 
	return *this; 
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet set1 (BitField | s.BitField ); 
	return set1; 
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet set1 (BitField); 
	set1.BitField.SetBit (Elem); 
	return set1; 
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet set1 (BitField); 
	set1.BitField.ClrBit(Elem); 
	return set1; 
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet set1 (BitField & s.BitField); 
	return set1; 
}

TSet TSet::operator~(void) // дополнение
{
	TSet set1 (~BitField); 
	return set1; 
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int a; 
	for (int i=0;i<s.GetMaxPower();i++) 
	{ 
		istr >> a; 
		s.InsElem (a); 
	} 
	return istr; 
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i=0; i < s.GetMaxPower(); i++) 
		ostr << s.IsMember(i); 
	return ostr; 
}
