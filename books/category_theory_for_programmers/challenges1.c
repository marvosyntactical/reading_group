#include <iostream>
#include <functional>
#include <cmath>
#include <assert.h>

// CTFP Challenges 1

// 1. Implement Identity
template <typename T>
T identity(T x) {
    return x;
}

// 2. Implement Composition
// from https://tfetimes.com/c-function-composition/
template <typename A, typename B, typename C>
std::function<C(A)> compose(std::function<C(B)> f, std::function<B(A)> g) {
	return [f,g](A x) { return f(g(x)); };
}





int main() {

    std::function<double(double)> id = identity<double>;
	std::function<double(double)> f = sin;
	std::function<double(double)> g = asin;
	std::cout << compose(f, g)(0.5) << std::endl;

	std::cout << identity(0.5) << std::endl;

    // 3. Write a program that tries to test whether 
    // composition respects identity
    double c = 0.5;
    assert(compose(id, f)(c) == f(c));
    assert(compose(f, id)(c) == f(c));

    /*
     * 4. Is the WWW a category in any sense? Are links morphisms?
     * Links cant be morphisms since they dont respect composition or identity.
     * 
     * You could still define a category using the WWW, for example
     * by letting sites be points and drawing an arrow between points a, b
     * if b can be reached from a by following 0-N links.
     * This respects identity and composition.
     *
     *
     * The morphisms existing in any category are elements of a relation between
     * the points and the points, 
     * which is reflexive (identity) and transitive (composition).
     *
     * 5. Facebook isnt a category as defined for the same reason
     * (neither composition nor identity hold)
     *
     * 6. When is a directed graph a category?
     * When each node has a self link
     * (the diagonal of the transition matrix A has only non-zero entries Aii > 0)
     * and Aij != 0, Ajk != 0 => Aik != 0
     */

	return 0;
}
