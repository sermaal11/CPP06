/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:02:43 by sergio            #+#    #+#             */
/*   Updated: 2025/10/20 11:02:28 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Serializer.hpp"

int main() 
{
    std::cout << MAGENTA << "[1] Crear objeto Data" << RESET << '\n';
    Data data;
    data.name = "Sergio";
    data.age  = 30;

    std::cout << "    Contenido inicial -> "
              << "name=\"" << data.name << "\", age=" << data.age << '\n';
    std::cout << "    Dirección (&data)  -> " << CYAN << &data << RESET << '\n';
    std::cout << '\n';

    std::cout << MAGENTA << "[2] Serializar la dirección con Serializer::serialize(&data)" << RESET << '\n';
    uintptr_t raw = Serializer::serialize(&data);
    std::cout << "    Valor entero (decimal) -> " << YELLOW << raw << RESET << '\n';
    std::cout << "    Valor entero (hex)     -> "
              << YELLOW << "0x" << std::hex << raw << std::dec << RESET << '\n';
	std::cout << '\n';

    std::cout << MAGENTA << "[3] Deserializar el entero con Serializer::deserialize(raw)" << RESET << '\n';
    Data* back = Serializer::deserialize(raw);
    std::cout << "    Puntero recuperado -> " << CYAN << back << RESET << '\n';
    std::cout << '\n';

    std::cout << MAGENTA << "[4] Comprobar igualdad de punteros" << RESET << '\n';
    std::cout << "    &data              -> " << CYAN << &data << RESET << '\n';
    std::cout << "    deserialize(raw)   -> " << CYAN << back   << RESET << '\n';

    if (back == &data) 
	{
        std::cout << GREEN << "    OK: Son la misma dirección" << RESET << '\n';
    } 
	else 
	{
        std::cout << RED   << "    ERROR: Direcciones distintas" << RESET << '\n';
        return 1;
    }
    std::cout << '\n';

    std::cout << MAGENTA << "[5] Acceder a los datos a través del puntero deserializado" << RESET << '\n';
    std::cout << "    back->name -> " << back->name << '\n';
    std::cout << "    back->age  -> "  << back->age  << '\n';

    std::cout << GREEN << "\nFin: serialización/deserialización verificada correctamente.\n" << RESET;
    return 0;
}



