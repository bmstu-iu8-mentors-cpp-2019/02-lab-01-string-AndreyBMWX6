// Copyright 2020 Andrey/
#include <string.hpp>
#include <cstring>

String::~String()
{
 delete[] Data;
}

String::String()
{
 Data = nullptr;
}

String::String(const String& rhs): String(rhs.Data)
{}

String::String(const char* data)
{
 size_t k = std::strlen(data);
 Data = new char[k+1];
 std::copy(data, data + k, Data);
 Data[k] = '\0';
 }

String& String::operator=(const String& rhs)
{
 if (&rhs != this)
 {
  unsigned int k = std::strlen(rhs.Data);
  delete[] Data;
  Data = new char[k+1];
  std::copy(rhs.Data, rhs.Data + k, Data);
  Data[k] = '\0';
 }
 return *this;
}

String& String::operator+=(const char* rhs)
{
 unsigned int a1, a2;
 a1 = this->Size();
 a2 = std::strlen(rhs);
 char* newStr;
 newStr = new char[a1 + a2 + 1];
 std::copy(this->Data, this->Data + a1, newStr);
 std::copy(rhs, rhs + a2, newStr + a1);
 newStr[a1+a2] = '\0';
 delete[] Data;
 Data = newStr;
 return *this;
}

String& String::operator+=(const String& rhs)
{
 return *this += rhs.Data;
}


String& String::operator*=(unsigned int m)
{
 unsigned int a = this->Size();
 char* newStr;
 newStr = new char[a * m + 1];
 unsigned int i = 0;
 while (i < m)
 {
  for (unsigned int j = 0; j < a; j++)
  {
   newStr[j + i * m] = this->Data[j];
  }
  i++;
 }
 newStr[a * m] = '\0';
 delete[] Data;
 Data = newStr;
 return *this;
}

bool String::operator==(const char* rhs) const
{
 if (this->Size() != std::strlen(rhs))
 {
  return false;
 } else {
  for (unsigned int i = 0; i < this->Size(); i++)
  {
   if (this->Data[i] != rhs[i])
    return false;
  }
 }
 return true;
}

bool String::operator==(const String& rhs) const
{
 return *this == rhs.Data;
}

bool String::operator<(const String& rhs) const
{
 unsigned int a = this->Size();
 unsigned int i = 0;
 unsigned int min;
 if (a < rhs.Size())
  min = a;
 else
  min = rhs.Size();
 while (i < min)
 {
  if (this->Data[i] < rhs.Data[i])
   return true;
  else if (this->Data[i] > rhs.Data[i])
   return false;
  i++;
 }
 if (rhs.Size() > a)
  return true;
 else
  return false;
}

size_t String::Find(const String& substr) const
{
 unsigned int a = substr.Size();
 char* buff;
 buff = new char[a + 1];
 for (unsigned int i = 0; i < a; i++)
  buff[i] = this->Data[i];
 buff[a] = '\0';
 unsigned int i = 0;
 bool flag = true;
 while (i + a <= this->Size())
 {
  for (unsigned int j = 0; j < a; j++)
  {
   if (substr.Data[j] != buff[j])
    flag = false;
  }
  if (flag)
  {
   delete[] buff;
   return i;
  } else {
   for (unsigned int k = 0; k < a - 1; k++)
   {
    buff[k] = buff[k + 1];
   }
   buff[a - 1] = this->Data[i + a];
   buff[a] = '\0';
   flag = true;
  }
   i++;
 }
 delete[] buff;
 return -1;
}

size_t String::Find(const char* substr) const
{
 unsigned int a = std::strlen(substr);
 char* buff;
 buff = new char[a + 1];
 for (unsigned int i = 0; i < a; i++)
  buff[i] = this->Data[i];
 buff[a] = '\0';
 unsigned int i = 0;
 bool flag = true;
 while (i + a < this->Size())
 {
  for (unsigned int j = 0; j < a; j++)
  {
   if (substr[j] != buff[j])
    flag = false;
  }
  if (flag)
  {
   delete[] buff;
   return i;
  } else {
   for (unsigned int k = 0; k < a - 1; k++)
   {
    buff[k] = buff[k + 1];
   }
   buff[a - 1] = this->Data[i + a];
   buff[a] = '\0';
   flag = true;
  }
   i++;
 }
 delete[] buff;
 return -1;
}

void String::Replace(char oldSymbol, char newSymbol)
{
 for (unsigned int i = 0; i < this->Size(); i++)
  if (this->Data[i] == oldSymbol)
   this->Data[i] = newSymbol;
}

size_t String::Size() const
{
 unsigned int k = 0;
 for (int i = 0; this->Data[i]; i++)
 {
  k++;
 }
 return k;
}

bool String::Empty() const
{
 if (this->Data == nullptr)
  return true;
 return false;
}

char String::operator[](size_t index) const
{
 return Data[index];
}

char& String::operator[](size_t index)
{
 return Data[index];
}

void String::RTrim(char symbol)
{
 unsigned int a = this->Size();
 unsigned int k = 0, index = this->Size() - 1;
 while (this->Data[index] == symbol)
 {
  k++;
  index--;
 }
 char* buff;
 buff = new char[a - k + 1];
 for (unsigned int i = 0; i < index + 1; i++)
 {
  buff[i] = this->Data[i];
 }
  buff[a - k] = '\0';
 delete[] Data;
 Data = buff;
 
}

void String::LTrim(char symbol)
{
 unsigned int a = this->Size();
 unsigned int index = 0;
 while (this->Data[index] == symbol)
 {
  index++;
 }
 char* buff;
 buff = new char[a - index + 1];
 for (unsigned int i = index; i < a; i++)
  buff[i - index] = this->Data[i];
 buff[a - index] = '\0';
 delete[] Data;
 Data = buff;
 
}

void String::swap(String& oth)
{
 char* buff = this->Data;
 this->Data = oth.Data;
 oth.Data = buff;
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
 out << str.Data;
 return out;
}

String operator+(const String& a, const String& b)
{
 unsigned int a1, a2;
 a1 = a.Size();
 a2 = b.Size();
 char* newStr;
 newStr = new char[a1 + a2 + 1];
 for (unsigned int i = 0; i < a1+a2; i++)
 {
  if (i < a1) newStr[i] = a.Data[i];
  else
   newStr[i] = b.Data[i - a1];
 }
 newStr[a1+a2] = '\0';
 String str = String(newStr);
 delete[] newStr;
 return str;
}

String operator*(const String& a, unsigned int b)
{
 return String{a} *= b;
}

bool operator!=(const String& a, const String& b)
{
 return !(a == b);
}

bool operator>(const String& a, const String& b)
{
 return b < a;
}

bool operator==(const char* a, const String& b)
{
 return b == a;
}
