#include "str_min.hpp"

void dirti::sym_count(const char * str, char * symbols, size_t * sym_num, size_t size, size_t & sym)
{
  symbols[0] = str[0];
  sym_num[0] = 1;
  size_t k = 0;
  for (size_t i = 1; i < size; ++i)
  {
    k = 0;
    for (size_t j = 0; j < sym; ++j)
    {
      if (str[i] == symbols[j])
      {
        sym_num[j] += 1;
        k++;
        break;
      }
    }
    if (k == 0)
    {
      symbols[sym] = str[i];
      sym_num[sym] = 1;
      sym++;
    }
  }
}

char dirti::str_min(const char * str, size_t size)
{
  char symbols[256] = {'0'};
  size_t sym_num[256] = {0};
  size_t sym = 1;
  dirti::sym_count(str, symbols, sym_num, size, sym);
  size_t min = size + 1;
  size_t num = 0;
  char sym_out = 'a';
  for (size_t i = 0; i < sym; ++i)
  {
    if (sym_num[i] < min)
    {
      min = sym_num[i];
      sym_out = symbols[i];
      num = 1;
    }
    else if (sym_num[i] == min)
    {
      num++;
    }
  }
  if (num > 1)
  {
    return '\n';
  }
  return sym_out;
}
