// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	if (mp <= 0)
		throw "Error Power";
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem < 0 || Elem >= MaxPower)
		throw "Error element";
	if (BitField.GetBit(Elem))
		return 1;
	else
		return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0 || Elem >= MaxPower)
		throw "Error element";
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0 || Elem >= MaxPower)
		throw "Error element";
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
	if (MaxPower != s.MaxPower)
		return 0;
	if (BitField != s.BitField)
		return 0;
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return 1;
	else
		if (BitField != s.BitField)
			return 1;
	return 0;
}

TSet TSet::operator+(const TSet& s) // объединение
{
	return TSet(BitField | s.BitField);

}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet NewTSet(*this);
	NewTSet.BitField.SetBit(Elem);
	return NewTSet;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	return TSet(BitField | ~Elem);
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
	return TSet(~BitField);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int tmp;
	istr >> tmp;
	while ((tmp >= 0) && (tmp < s.MaxPower))
	{
		s.InsElem(tmp);
		istr >> tmp;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField << ' ';
	return ostr;
}
