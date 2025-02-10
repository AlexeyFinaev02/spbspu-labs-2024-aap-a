#include "findMin.hpp"

void dirti::countSym(const char * str, char * symbols, size_t * sym_num, size_t & sym)
{
  symbols[0] = *str;
  sym_num[0] = 1;
  size_t k = 0;
  size_t i = 1;
  while (*(str + i) != '\0')
  {
    k = 0;
    for (size_t j = 0; j < sym; ++j)
    {
      if (*(str + i) == symbols[j])
      {
        sym_num[j] += 1;
        k++;
        break;
      }
    }
    if (k == 0)
    {
      symbols[sym] = *(str + i);
      sym_num[sym] = 1;
      sym++;
    }
    i++;
  }
}

char dirti::findMin(const char * str)
{
  if (*str == '\0')
  {
    return '\0';
  }
  char symbols[256] = {'0'};
  size_t sym_num[256] = {0};
  size_t sym = 1;
  dirti::countSym(str, symbols, sym_num, sym);
  size_t min = 0;
  char sym_out = 'a';
  for (size_t i = 0; i < sym; ++i)
  {
    if (sym_num[i] <= sym_num[min])
    {
      min = i;
      sym_out = symbols[min];
    }
  }
  return sym_out;
}
