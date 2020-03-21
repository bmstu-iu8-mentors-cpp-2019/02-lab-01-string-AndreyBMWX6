// Copyright 2020 Andrey
#include <string.hpp>

String::~String()
{}

String::String()
{
 Data = nullptr;
}
String::String(const String& rhs) : Data(rhs.Data)
{}

String::String(const char* data):
Data(const_cast<char*>(data))
{}

String& String::operator=(const String& rhs)
{
 if (&rhs != this)
  this->Data = rhs.Data;
 return *this;
}

String& String::operator+=(const char* rhs)
{
 unsigned int a1, a2;
 a1 = sizeof(this->Data);
 a2 = sizeof(rhs);
 char* newStr;
 newStr = new char[a1 + a2];
 for (unsigned int i = 0; i < sizeof(newStr); i++)
 {
  if (i < a1) newStr[i] = this->Data[i];
  else
   newStr[i] = rhs[i - a1];
 }
 this->Data = newStr;
 return *this;
}

String& String::operator+=(const String& rhs)
{
 unsigned int a1, a2;
 a1 = sizeof(this->Data);
 a2 = sizeof(rhs.Data);
 char* newStr;
 newStr = new char[a1 + a2];
 for (unsigned int i = 0; i < sizeof(newStr); i++)
 {
  if (i < a1) newStr[i] = this->Data[i];
  else
   newStr[i] = rhs.Data[i - a1];
 }
 this->Data = newStr;
 return *this;
}


String& String::operator*=(unsigned int m)
{
 int a = sizeof(this->Data);
 char* newStr;
 newStr = new char[a*m];
 unsigned int i = 0;
 while (i < m - 1)
 {
  for (int j = 0; j < a; j++)
  {
   newStr[j + i * m] = this->Data[j];
  }
  i++;
 }
 this->Data = newStr;
 return *this;
}

bool String::operator==(const char* rhs) const
{
 if (sizeof(this->Data) != sizeof(rhs))
 {
  return false;
 } else {
  for (unsigned int i = 0; i < sizeof(this->Data); i++)
  {
   if (this->Data[i] != rhs[i])
    return false;
  }
 }
 return true;
}

bool String::operator==(const String& rhs) const
{
 if (sizeof(this->Data) != sizeof(rhs.Data))
 {
  return false;
 } else {
  for (unsigned int i = 0; i < sizeof(this->Data); i++)
  {
   if (this->Data[i] != rhs.Data[i])
    return false;
  }
 }
 return true;
}

bool String::operator<(const String& rhs) const
{
 unsigned int a = sizeof(this->Data);
 int i = 0;
 int min;
 if (a < sizeof(rhs.Data))
  min = a;
 else
  min = sizeof(rhs.Data);
 while (i < min)
 {
  if (this->Data[i] < rhs.Data[i])
   return true;
  else if (this->Data[i] > rhs.Data[i])
   return false;
  i++;
 }
 if (sizeof(rhs.Data) > a)
  return true;
 else
  return false;
}

size_t String::Find(const String& substr) const
{
 unsigned int a = sizeof(substr.Data);
 char* buff;
 buff = new char[a];
 for (unsigned int i = 0; i < a; i++)
  buff[i] = this->Data[i];
 unsigned int i = 0;
 bool flag = true;
 while (i + a < sizeof(this->Data))
 {
  for (unsigned int j = 0; j < a; j++)
  {
   if (substr.Data[i] != buff[i])
    flag = false;
  }
  if (flag)
   return i;
  else
  {
   for (unsigned int k = 0; k < a - 1; k++)
   {
    buff[k] = buff[k + 1];
   }
   buff[a - 1] = this->Data[i + a];
  }
   i++;
 }
 return -1;
}

size_t String::Find(const char* substr) const
{
 unsigned int a = sizeof(substr);
 char* buff;
 buff = new char[a];
 for (unsigned int i = 0; i < a; i++)
  buff[i] = this->Data[i];
 unsigned int i = 0;
 bool flag = true;
 while (i + a < sizeof(this->Data))
 {
  for (unsigned int j = 0; j < a; j++)
  {
   if (substr[i] != buff[i])
    flag = false;
  }
  if (flag)
   return i;
  else
  {
   for (unsigned int k = 0; k < a - 1; k++)
   {
    buff[k] = buff[k + 1];
   }
   buff[a - 1] = this->Data[i + a];
  }
   i++;
 }
 return -1;
}

void String::Replace(char oldSymbol, char newSymbol)
{
 for (unsigned int i = 0; i < sizeof(this->Data); i++)
  if (this->Data[i] == oldSymbol)
   this->Data[i] = newSymbol;
}

size_t String::Size() const
{
 int k = 0;
 for (unsigned int i = 0; i < sizeof(this->Data); i++)
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
 return this->Data[index];
}

char& String::operator[](size_t index)
{
 return this->Data[index];
}

void String::RTrim(char symbol)
{
 int a = sizeof(this->Data);
 int k = 0, index = sizeof(this->Data) - 1;
 while (this->Data[index] == symbol)
 {
  k++;
  index--;
 }
 char* buff;
 buff = new char[a - k];
 for (int i = 0; i < index + 1; i++)
  buff[i] = this->Data[i];
 this->Data = buff;
}

void String::LTrim(char symbol)
{
 int a = sizeof(this->Data);
 int index = 0;
 while (this->Data[index] == symbol)
 {
  index++;
 }
 char* buff;
 buff = new char[a - index];
 for (int i = index; i < a; i++)
  buff[i] = this->Data[i];
 this->Data = buff;
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
 a1 = sizeof(a.Data);
 a2 = sizeof(b.Data);
 char* newStr;
 newStr = new char[a1 + a2];
 for (unsigned int i = 0; i < sizeof(newStr); i++)
 {
  if (i < a1) newStr[i] = a.Data[i];
  else
   newStr[i] = b.Data[i - a1];
 }
 String str(newStr);
 return str;
}

String operator*(const String& a, unsigned int b)
{
 unsigned int asize = sizeof(a);
 char* newStr;
 newStr = new char[asize * b];
 unsigned int i = 0;
 while (i < b - 1)
 {
  for (unsigned int j = 0; j < asize; j++)
  {
   newStr[j + i * b] = a[j];
  }
  i++;
 }
 String str(newStr);
 return str;
}

bool operator!=(const String& a, const String& b)
{
 if (sizeof(a) != sizeof(b))
  return true;
 else
 {
  for (unsigned int i = 0; i < sizeof(a); i++)
   if (a.Data[i] != b.Data[i])
    return true;
  return false;
 }
}

bool operator>(const String& a, const String& b)
{
 unsigned int asize = sizeof(a);
 unsigned int bsize = sizeof(b);
 unsigned int i = 0;
 unsigned int min;
 if (asize < bsize)
  min = asize;
 else
  min = bsize;
 while (i < min)
 {
  if (a.Data[i] > b.Data[i])
   return true;
  else if (b.Data[i] > a.Data[i])
   return false;
  i++;
 }
 if (asize > bsize)
  return true;
 else
  return false;
}
