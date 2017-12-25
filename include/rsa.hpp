#include <cstdlib>
#include <ctime>
typedef struct key
{
    long pub;
    long exp;
    long dkey;
} Key;

class Rsa
{
public:
    Rsa();
    virtual ~Rsa();

public:
    Key getKeys();
    long endecrypt(const long mess, const long key, const long publ);

private:
    long getPub(const long p1, const long p2);
    long getExp(const long euler);
    long getDKey(const long exp, const long euler);
    long getPrime();
    long getEuler(const long p1, const long p2);
    long getGCD(const long a, const long b);
    bool isPrime(const long num);
};
