/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:20:44 by sergio            #+#    #+#             */
/*   Updated: 2025/10/19 14:26:43 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScalarConverter.hpp"

//OCF
ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter&) {}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter&)
{
	return *this;
}

ScalarConverter::~ScalarConverter() {}

//Metodos Publicos
void ScalarConverter::convert(const std::string& input)
{	
	// 1) Is Char Literal
	if (isCharLit(input) == true)
	{
		// Extraemos el carácter real del input (pos 1 si 'x', pos 0 si x)
		char c = '\0';
		if (input.length() == 3)
			c = input[1];
		else
			c = input[0];
		printFromChar(c);
		return;
	}

	// Fallback: Si no ha entrado en ningún tipo válido
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
}

// Funciones de deteccion de tipo
// 1) Tipo char
bool isCharLit(const std::string& input)
{
	// Caso 1: formato con comillas simples -> 'x'
	if (input.length() == 3 && input[0] == '\'' && input[2] == '\'')
		return true;
	
	// Caso 2: un solo carácter no numérico -> x
	if (input.length() == 1)
	{
		char c = input[0];
		// Si el carácter no está entre '0' y '9', lo consideramos un char
		if (!(c >= '0' && c <= '9'))	
			return true;
	}
	
	return false;
}

// Funciones de conversión e impresión
// 1) From char
void printFromChar(char c)
{
	if (c >= 32 && c <= 126)
		std::cout << "char: " << "'" << c << "'" << std::endl;
	else
		std::cout << "char: " << "Non displayable" << std::endl;

	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}
