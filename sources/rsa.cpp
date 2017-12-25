#include "rsa.hpp"
using namespace std;

Rsa::Rsa(){}

Rsa::~Rsa(){}


/************************************
 * Шифрование/дешифрование сообщения (числа)
 * *********************************/
long Rsa::endecrypt(const long mess, const long key, const long publ)
{
    long getMess = 1;
    long root = mess;
    long index = key;
    while (index)
    {
        if (index & 1)
            getMess = (getMess * root) % publ;
        index >>= 1;
        root = (root * root) % publ;
    }
    return getMess;
}

/************************************
 * Генерация ключей
 * *********************************/
Key Rsa::getKeys()
{
	long prime1 = getPrime();
    long prime2 = getPrime();
    while (prime2 == prime1)
        prime2 = getPrime();

    Key key;
    long euler = getEuler(prime1, prime2);
    key.pub = getPub(prime1, prime2);
    key.exp = getExp(euler);
    key.dkey = getDKey(key.exp, euler);
    return key;
}

/************************************
 * Генерация публичного ключа
 * *********************************/
long Rsa::getPub(const long p1, const long p2)
{
    return p1 * p2;
}

/************************************
 * Генерация значения функции Эйлера
 * *********************************/
long Rsa::getEuler(const long p1, const long p2)
{
    return (p1 - 1) * (p2 - 1);
}

/************************************
 *	Генерация открытой экспоненты
 * *********************************/
long Rsa::getExp(const long euler)
{
    long exp;
    while (true)
    {
        exp = rand() % euler;
        if (exp >= 2 && getGCD(exp, euler) == 1)
            break;
    }
    return exp;
}

/************************************
 * Генерация приватного ключа (декриптора)
 * *********************************/
long Rsa::getDKey(const long exp, const long euler)
{
    long dkey = euler / exp;
    while (true)
    {
        if (((dkey * exp) % euler) == 1)
            break;
        else
            ++dkey;
    }
    return dkey;
}

/************************************
 * Генерация случайных чисел в промежутке
 * от 100 включительно до 200
 * *********************************/
long Rsa::getPrime()
{
    long prime = 0;
    srand(time(0));
    while (true)
    {
        prime = rand() % 100 + 100;
        if (isPrime(prime))
            break;
    }
    return prime;
}

/************************************
 * Вычисление НОД
 * *********************************/
long Rsa::getGCD(const long a, const long b)
{
    long dividend = a;
    long divisor = b;
    long residual = dividend % divisor;
    while (residual)
    {
        dividend = divisor;
        divisor = residual;
        residual = dividend % divisor;
    }
    return divisor;
}

/************************************
 * проверка числа на простоту
 * *********************************/
bool Rsa::isPrime(const long num)
{
    int tmp = 2;
    while (tmp < num)
        if (num % tmp++ == 0)
            break;

    if (tmp == num)
        return true;
    return false;
}