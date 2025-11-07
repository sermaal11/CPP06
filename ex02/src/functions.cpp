/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:47:50 by sergio            #+#    #+#             */
/*   Updated: 2025/11/07 11:55:34 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// functions.cpp
#include <iostream>
#include <cstdlib> // std::rand, std::srand
#include <ctime>   // std::time
#include "../include/Base.hpp"
#include "../include/A.hpp"
#include "../include/B.hpp"
#include "../include/C.hpp"

// -----------------------------------------------------------------------------
// Base* generate()
//  - Crea aleatoriamente una instancia de A, B o C y la devuelve como Base*
//  - Usa dynamic_cast de forma indirecta porque devolvemos Base*
// -----------------------------------------------------------------------------
Base* generate(void)
{
    // Semilla única la primera vez que se llama
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        seeded = true;
    }

    int r = std::rand() % 3;
    switch (r) {
        case 0:
            std::cout << "[generate] -> A\n";
            return new A();
        case 1:
            std::cout << "[generate] -> B\n";
            return new B();
        default:
            std::cout << "[generate] -> C\n";
            return new C();
    }
}

// -----------------------------------------------------------------------------
// void identify(Base* p)
//  - Imprime "A", "B" o "C" según el tipo real.
//  - Si p == NULL, informa y retorna.
//  - Usa dynamic_cast a puntero (devuelve NULL si falla).
// -----------------------------------------------------------------------------
void identify(Base* p)
{
    if (!p) {
        std::cout << "identify(Base*): null pointer\n";
        return;
    }
    if (dynamic_cast<A*>(p)) { std::cout << "A\n"; return; }
    if (dynamic_cast<B*>(p)) { std::cout << "B\n"; return; }
    if (dynamic_cast<C*>(p)) { std::cout << "C\n"; return; }
    std::cout << "identify(Base*): unknown type\n";
}

// -----------------------------------------------------------------------------
// void identify(Base& p)
//  - Imprime "A", "B" o "C" según el tipo real.
//  - PROHIBIDO usar punteros dentro de esta función (subject).
//  - Usa dynamic_cast a referencia, que lanza std::bad_cast si falla.
// -----------------------------------------------------------------------------
void identify(Base& p)
{
    try { (void)dynamic_cast<A&>(p); std::cout << "A\n"; return; }
    catch (std::bad_cast&) {}

    try { (void)dynamic_cast<B&>(p); std::cout << "B\n"; return; }
    catch (std::bad_cast&) {}

    try { (void)dynamic_cast<C&>(p); std::cout << "C\n"; return; }
    catch (std::bad_cast&) {}

    std::cout << "identify(Base&): unknown type\n";
}