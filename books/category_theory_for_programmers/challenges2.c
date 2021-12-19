#include <iostream>
#include <functional>
#include <cmath>
#include <random>
#include <cstdio>

// CTFP Challenges 2


int fib(int n) {
    if (n <= 1) return 1;
    return fib(n-1) + fib(n-2);
}

// 1. Define a memoization function
// https://tfetimes.com/c-function-composition/ 1st example
// functor class to be returned by memoize function
template <class Func>
class memoize_functor :
public std::unary_function<typename Func::argument_type,
typename Func::result_type>
{
protected:
 Func f;
 std::unordered_map<typename Func::argument_type, typename Func::result_type> mem;

public:
 memoize_functor(const Func& _f)
 : f(_f) { }

 typename Func::result_type
 operator()(const typename Func::argument_type& x) const {
     // check if x has been passed before
     // std::cout << "x = " << x << '\n';
     if (mem.find(x) != mem.end()) {
         return mem[x];
     }
     typename Func::result_type y = f(x);
     // memorize IO
     mem[x] = y;
     // std::cout << "mem[x] = " << mem[x] << '\n';

     return y;
 }
}; 

// we wrap it in a function so the compiler infers the template arguments
// whereas if we used the class directly we would have to specify them explicitly
template <class Func>
inline memoize_functor<Func>
memoize(const Func& f)
{ return memoize_functor<Func>(f); }


// 3. Implement a function that takes a seed ... and memoize it
float seedify(int seed) {
    std::uniform_real_distribution<float> uniform(0.0, 1.0);

    std::mt19937 generator(seed);

    return uniform(generator);

}



int main() {
    std::function f = fib;
    memoize_functor mem_fib = memoize(f);
    memoize_functor mem_fib = memoize_functor<std::function>(f);

    int big_int = 42; // try between 35-45
	std::cout << mem_fib(big_int) << std::endl;
	std::cout << mem_fib(big_int) << std::endl;


    // 3. Does it work? Yea
    std::function s = seedify;
    memoize_functor mem_seed = memoize(s);
    int seed = 5;

    float uni0 = seedify(seed);
	std::cout << uni0 << std::endl;

    float uni1 = mem_seed(seed);
	std::cout << uni1 << std::endl;

    float uni2 = mem_seed(seed);
	std::cout << uni2 << std::endl;

    float uni3 = seedify(seed);
	std::cout << uni3 << std::endl;

    /* 4. Which of these C++ functions are pure?
     * (a) factorial: yes
     * (b) std::getchar(): yes
     * (c) no
     * (d) yes
     */

    /* 5. How many functions are there from bool -> bool?
     * Ans: 4
     */

	return 0;
}
