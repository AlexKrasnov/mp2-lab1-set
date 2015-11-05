// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define B_pMem (sizeof(TELEM) * 8)

TBitField::TBitField(int len)   
{
	if (len < 0)  throw out_of_range("out of range"); 
	MemLen = (len + B_pMem-1)/ B_pMem; 
	pMem = new TELEM[MemLen]; 
	if ( pMem != NULL ) 
		for ( int i=0; i < MemLen; i++ ) 
			pMem[i] = 0; 
	BitLen = len; 
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen; 
	MemLen = bf.MemLen; 
	pMem = new TELEM[MemLen]; 
	for (int i =0;i<MemLen; i++) 
		pMem[i] = bf.pMem[i]; 
}

TBitField::~TBitField()
{
	delete []pMem; 
	pMem = NULL; 
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / B_pMem; 
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % B_pMem); 
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen; 
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen)) 
		throw 
		out_of_range("Out of range"); 
	pMem[GetMemIndex(n)] |= GetMemMask(n); 
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ( (n <0) || (n >= BitLen) ) 
		throw out_of_range("Out of range"); 
	pMem[GetMemIndex(n)] &=~GetMemMask(n); 
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen)) 
		throw 
		out_of_range("out of range"); 
	return (((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0)? 0 : 1);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		BitLen = bf.BitLen; 
		MemLen = bf.MemLen; 
		delete []pMem; 
		pMem = new TELEM[MemLen]; 
		for (int i=0; i<MemLen; i++) 
			pMem[i] = bf.pMem[i];
	}
	return *this; 
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int f=1; 
	if (BitLen == bf.BitLen) 
	{ 
		for (int i = 0;i < MemLen;i++) 
			if (pMem[i] != bf.pMem[i]) 
			{ 
				f = 0; 
				break; 
			} 
	} 
	else 
		f=0;
	return f; 
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf); 
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int n = BitLen;
	if (n < bf.BitLen)
		n = bf.BitLen;
	TBitField tmp(n);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] |= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int n = BitLen;
	if (n < bf.BitLen)
		n = bf.BitLen;
	TBitField tmp(n);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] &= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int n = BitLen;
	TBitField tmp(n);
	TELEM f = 0;
	for (int i = 0; i < (BitLen % B_pMem); i++)
		f |= GetMemMask(i);
	pMem[MemLen - 1] |= (~f);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = ~pMem[i];
	return tmp;
}
// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i=0; char symbol; 
	do { istr >> symbol; } while (symbol !=' '); 
	while (1) 
	{ 
		istr >> symbol; 
		if ( symbol == '0' ) bf.ClrBit(i++); 
		else if ( symbol == '1' ) bf.SetBit(i++); 
		else break; 
	} 
	return istr; 
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i=0;i<bf.GetLength();i++)
		if (bf.GetBit(i)) ostr <<'1'; else ostr<<'0';
	return ostr;
}
