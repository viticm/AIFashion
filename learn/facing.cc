#include <cstdio>
#include <iostream>
#include <memory.h>
#include <memory>
#include <cmath>

#define swap(a,b) \
{ \
  char temp[10]{0}; \
  memcpy(temp, &a, sizeof(a)); \
  memcpy(&a, &b, sizeof(b)); \
  memcpy(&b, temp, sizeof(a)); \
}

int add(int a, int b) {
  if (0 == b) return a;
  int sum, carry;
  sum = a ^ b;
  carry = (a & b) << 1;
  return add(sum, carry);
}

int max(int a, int b) {
  return ((a + b) + abs(a - b)) / 2;
}

int calc_score(int n, int *types, int *values) {
  if (nullptr == types || nullptr == values) return 0;
  int r{0}, c1{0}, c2{0}, sum1{0}, sum2{0};
  for (int i = 0; i < n; ++i) {
    // if (!types[i] || !values[i]) break;
    switch(types[i]) {
      case 1: sum1 += values[i]; c1 += 1; break;
      case 2: sum2 += values[i]; c2 += 1; break;
      default: break;
    }
  }
  double a1{0}, a2{0};
  if (c1) a1 = sum1 / c1;
  if (c2) a2 = sum2 / c2;
  r = a2 ? a1 * 0.6 + a2 * 0.4 : a1;
  return r;
}

#define SUB(x,y) x-y
#define ACCESS_BEFORE(e,a,b) *SUB(&e,a) = b // *&array[2]-3=b;
#define YEAR_SEC (24 * 60 * 60 * 365)UL

class A {
 public:
   void test() const {
     value_++;
     // value1_++; // value1_ in read only object.
   }
 private:
   mutable int value_;
   int value1_;
};

class B {

 public:
   int x;
   static int y;

 public:
   ~B();

};
// 析构函数可以是内联
inline B::~B() {
  std::cout << "B::~B() inline" << std::endl;
}

/*
// 这个c++11后不支持的，不知道为何面试宝典上会说是正确
std::unique_ptr<A> source() {
  return new A;
}
*/

struct a_t {
  char x;
  int y;
  char z;
};

struct b_t {
  char x;
  char y;
  int z;
};

class C {};

class D {
  public:
    virtual void foo() {}
};

class E : public D {};

class F : public D {
 
 virtual void foo() { std::cout << "xxx"; }

};

class C1 {
 
 public:
   C1(int a) : a_{a} {
     std::cout << "construct " << a_ << std::endl;
   }
   ~C1() {
     std::cout << "destruct" << std::endl;
   }
   C1(const C1 &o) { // 复制构造函数
     a_ = o.a_;
   }
   C1 & operator = (const C1 &o) { // 赋值函数
     a_ = o.a_;
     return *this;
   }

 private:
   int a_;

};

C1 play(C1 o) {
  return o;
}

class C2 {
 public:
  friend float calc_dis(const C2 &p1, const C2 &p2);

 private:
   float x_;
   float y_;
};

// ^是XOR运算符，面试宝典中直接当幂来使用其实不太正确(它两边的参数只能是整数)
float calc_dis(const C2 &p1, const C2 &p2) {
  return 
    std::pow((std::pow(p1.x_ - p2.x_, 2) + std::pow(p1.y_ - p2.y_, 2)), 0.5);
}

class A1 {
 public:
   A1() { a_ = 1; b_ = 2; }
   ~A1() {}
 public:
   void print() {
     printf("%d,%d\n", a_, b_);
   }
 private:
   int a_;
   int b_;

};

class A2 {
 public:
   A2() { c_ = 3; }
   ~A2() {}
 public:
   void print() {
     printf("%d\n", c_);
   }
 private:
   int c_;

};

int max1(int a, int b) {
  return a > b ? a : b;
}

int calc_angle(int n) {
  if (1 == n) return 1;
  return (n - 1) * 3 + calc_angle(n - 1);
}

void match_array(int a[], int b[], int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (a[i] == b[j]) {
        printf("a[%d] matched b[%d]\n", i, j);
        break;
      }
    }
  }
}

// 虚继承
class V1 {
 public:
   virtual void foo() {}
 private:
   char a_[3];
};

class V2 : public virtual V1 {
 public:
   virtual void foo() {}
 private:
   char a_[3];
};

class V3 : public virtual V2 {
 public:
   virtual void foo() {}
 private:
   char a_[3];
};

// 面试宝典上说这个规则应该是半圆的面积和对应以半径的正方形面积比较
// 即：3.14 * r * r / 4 和 r * r 的比值那么输出的数应当接近 (n / 4) * 3.14 
// 但实际上并不是这样，在n=1000时输出503，在n=1000时为5044
int calc_rand(int n) {
  int r{0};
  for (int i = 0; i < n; ++i) {
    int x = rand();
    int y = rand();
    if ((x * x + y * y) < (RAND_MAX * RAND_MAX)) ++r;
  }
  return r;
}

int sub(int x, int y) { return x + y; }
int dec(int x, int y) { return x - y; }
int judge(int x, int y) {
  if (x >= 0) {
    return y;
  } else if (0 == y) {
    return x;
  } else {
    return x / y;
  }
}

void test(int (*func)(int, int), int x, int y) {
  int r = (*func)(x, y);
  printf("x:%d|y:%d, result: %d\n", x, y, r);
}

template <class T>
class Funcs {
  public:
    static T sub(T x, T y) {
      return x + y;
    }
    static T dec(T x, T y) {
      return x - y;
    }
    static T judge(T x, T y) {
      if (x >= 0) {
        return y;
      } else if (0 == y) {
        return x;
      } else {
        return x / y;
      }
    }
};

typedef struct node_one_struct {
  int d;
  node_one_struct * next;
} node_one_t;

node_one_t *create_node_one(int v) {
  static node_one_t head;
  head.d = 0;
  head.next = nullptr;
  auto one = new node_one_t;
  one->d = v;
  one->next = nullptr;
  head.next = one;
  return one;
}

int count_node_one(node_one_t *node) {
  int r{0};
  auto head = node;
  for (;;) {
    ++r;
    if (!head->next) break;
    head = head->next;
  }
  return r;
}

void print_node_one(node_one_t *node) {
  auto head = node;
  for (;;) {
    std::cout << head->d;
    if (!head->next) break;
    head = head->next;
    std::cout << "\t";
  }
  std::cout << std::endl;
}

node_one_t *insert_node_one(node_one_t *head, int num) {
  node_one_t *p0, *p1, *p2;
  p1 = head;
  p0 = new node_one_t;
  p0->d = num;
  p0->next = nullptr;
  for (;p0->d > p1->d;) {
    p2 = p1;
    p1 = p1->next;
    if (p1 == nullptr) break;
  }
  if (p1 == head) {
    p0->next = p1;
    head = p0;
  } else {
    if (p1) {
      p2->next = p0;
      p0->next = p1;
    } else {
      p0->next = p2->next;
      p2->next = p0;
    }
  }
  return head;
}

void bubble(int *list, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      if (list[j] > list[j + 1]) {
        int temp = list[j];
        list[j] = list[j + 1];
        list[j + 1] = temp;
      }
    }
  }
}

void loop_move(char *str, int n) {
  int mn = strlen(str) - n;
  char tmp[128]{0};
  memcpy(tmp, str, mn);
  memcpy(str, str + mn, n);
  memcpy(str + n, tmp, mn);
}

const char *strstr1(const char *str, const char *sub) {
  
  for (int i = 0; str[i] != '\0'; ++i) {
    int temp = i;
    int j = 0;
    if (str[i] == sub[j]) {
      while (str[i++] == sub[j++]) {
        if ('\0' == sub[j]) return &str[temp];
      }
      i = temp;
    }
  }
  return nullptr;
}

double (*F1[10])(); // 函数指针double *()的数组
double *(*gh)[10]; // 指向double*数组的指针
float (**ah)[10]; // 指向元素为float数组的二级指针
int *aa[10]; // 指针数组
int (*ab)[10]; // 数组指针
               //
// RTTI -> Run time type information(运行时的类型信息).
// dynamic_cast typeinfo typeid 等，缺乏扩展和行为不可预期等缺点
// 在设计的时候应尽量避免使用

int main(int argc, char **argv) {
  unsigned char a = 0xa5; // 10100101
  unsigned char b = ~a >> 1 + 4; // ~a(01011010) >> 5 -> 00000010
  printf("b = %d|%d|%d\n", b, add(9, 100), max(9, 11));
  int m = 3;
  int n = 10;
  printf("before m = %d, n = %d\n", m, n);
  swap(m, n);
  printf("after m = %d, n = %d\n", m, n);
  int types[] = {1, 0, 2};
  int scores[] = {5, 1, 3};
  printf("avg: %d\n", calc_score(sizeof(types)/sizeof(int), types, scores));
  int array[] = {1, 2, 3, 4, 5, 6};
  int sec = 0; //YEAR_SEC;
  printf("test: %d|%d\n", *&array[3] - 1, sec);
  // ACCESS_BEFORE(array[2],3,1);
  printf("sizeof(a_t): %d, sizeof(b_t): %d\n", sizeof(a_t), sizeof(b_t));
  printf("sizeof(B): %d|%d|%d\n", sizeof(B), sizeof sec, sizeof(C));
  printf("sizeof(D): %d|%d|%d\n", sizeof(D), sizeof(E), sizeof(F));
  A1 a1;
  A2 *a2 = (A2 *)(&a1);
  a2->print();
  // int max1(int, int);
  int (*max1_p)(int, int) = &max1;
  printf("max1_p: %d\n", (*max1_p)(3, 6));
  int arr[] = {1, 2, 3, 4, 5};
  int *arr_ptr = (int *)(&arr + 1); // &arr是一个双指针(int **)，动一步为数组步长
                                    // 因此arr_ptr指向的是数组之后的内存单位
                                    // arr_ptr - 1则是将指针向前移动4字节所以为5
  printf("*(&arr_ptr - 1): %d\n", *(arr_ptr - 1));
  int arr1[2][5] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int *arr1_ptr = (int *)(&arr1 + 1);
  printf("arr1[1]:%d|%d\n", *arr1[1], *(arr1_ptr - 1));
  printf("angles: %d|%d|%d\n", calc_angle(100), sec, sec--);
  int m_a[] = {1, 2, 3, 4, 5, 6};
  int m_b[] = {5, 4, 3, 1, 2, 6};
  match_array(m_a, m_b, sizeof(m_a) / sizeof(int));
  printf("rand(1000): %d\n", calc_rand(1000));
  {
    B b;
    C1 c = play(1);
  }
  test(sub, 1, 3);
  test(judge, 100, -6);
  // 64位下是16 32 48，32位下8 16 24
  printf("sizeof(V): %d|%d|%d\n", sizeof(V1), sizeof(V2), sizeof(V3));
  int *p1 = nullptr;
  int *p2 = p1 + 15;
  printf("%x\n", p2);
  volatile int a3; // volatile 阻止编译器的优化，并表示该值随时可以改变
  return 0;
}
