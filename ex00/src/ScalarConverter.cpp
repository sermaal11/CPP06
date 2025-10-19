/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:20:44 by sergio            #+#    #+#             */
/*   Updated: 2025/10/19 22:50:47 by sergio           ###   ########.fr       */
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

	// 2) Is Int Literal
	else if (isIntLit(input) == true)
	{
		errno = 0;
		long l = strtol(input.c_str(), nullptr, 10);
		if (errno != 0)
			fallback();
		else if (l < INT_MIN || l > INT_MAX)
			fallback();
		else
			printFromInt(static_cast<int>(l));
		return;
	}

	// 3) is Float Literal
	else if(isFloatLit(input) == true)
	{
		if (input == "nanf" || input == "+inff" || input == "-inff")
		{
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: " << input << std::endl;
			std::cout << "double: " << input.substr(0, input.length() - 1) << std::endl;
			return;
		}
		std::string core = input.substr(0, input.length() - 1); //quita la f
		errno = 0;
		char* endptr = nullptr;
		double d = strtod(core.c_str(), &endptr);
			
		if (errno != 0 || *endptr != '\0')
		    fallback();
		else if (d < -FLT_MAX || d > FLT_MAX)
		    fallback();
		else
			printFromFloat(static_cast<float>(d));
		return;
	}
	else if (isDoubleLit(input) == true)
	{
	    // Pseudoliterales de double
	    if (input == "nan" || input == "+inf" || input == "-inf")
	    {
	        std::cout << "char: impossible" << std::endl;
	        std::cout << "int: impossible" << std::endl;
	        std::cout << "float: " << input << "f" << std::endl;
	        std::cout << "double: " << input << std::endl;
	        return;
	    }
	    errno = 0;
	    char* endptr = nullptr;
	    double d = strtod(input.c_str(), &endptr);
	
	    if (errno != 0 || *endptr != '\0')
	        fallback();
	    else if (d < -DBL_MAX || d > DBL_MAX)
    		fallback();
		else
	        printFromDouble(d);
	    return;
	}
	else
		fallback();
	return;
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

// 2) Tipo int
bool isIntLit(const std::string& input)
{
	// Comprobacion si el imput esta vacio
	if (input.empty())
		return false;
	
	// Verificacion de primer caracter (+, -, o digito)
	size_t start = 0;
	if (input[0] == '+' || input[0] == '-')
	{
		start = 1;
		if (input.length() == 1)
			return false;
	}
	else if (input[0] >= '0' && input[0] <='9')
		start = 0;
	
	// Verificacion de cadena completa
	for (; start < input.length(); start++)
	{
		if (!isdigit(input[start]))
			return false;
	}
	return true;
}

// 3) Tipo float
bool isFloatLit(const std::string& input)
{
	if (input.empty())
		return false;

	size_t end = input.length() - 1;
	if (input[end] != 'f')
		return false;
	
	if (input == "nanf" || input == "+inff" || input == "-inff")
		return true;

	size_t start = 0;
	if (input[0] == '+' || input[0] == '-')
	{
		start = 1;
		if (input.length() == 1)
			return false;
	}
	else if (input[0] >= '0' && input[0] <='9')
		start = 0;
	
	std::string core = input.substr(start, input.length() - start - 1);
	
	size_t countDot = 0;
	size_t dotPosition = 0;
	for (size_t i = 0; i < core.length(); i++)
	{
		if (core[i] == '.')
		{
			dotPosition = i;
			countDot++;
		}
	}
	if (countDot != 1)
		return false;
	if (dotPosition == 0 || dotPosition == core.length() - 1)
    	return false;
	if (!(isdigit(static_cast<unsigned char>(core[dotPosition - 1]))) || !(isdigit(static_cast<unsigned char>(core[dotPosition + 1]))))
		return false;
	for (size_t i = 0; i < core.length(); i++)
	{
		if (!isdigit(static_cast<unsigned char>(core[i])) && core[i] != '.')
			return false;
	}
	return true;
}

// 4) Tipo double
bool isDoubleLit(const std::string& input)
{
	if (input.empty())
		return false;

	// No puede terminar en 'f' -> eso es un float
	if (input[input.length() - 1] == 'f')
		return false;

	// Pseudoliterales válidos
	if (input == "nan" || input == "+inf" || input == "-inf")
		return true;

	// Signo opcional
	size_t start = 0;
	if (input[0] == '+' || input[0] == '-')
	{
		start = 1;
		if (input.length() == 1)
			return false;
	}
	else if (input[0] >= '0' && input[0] <= '9')
		start = 0;

	// Extraemos el núcleo (sin signo)
	std::string core = input.substr(start, input.length() - start);

	// Verificación del punto decimal
	size_t countDot = 0;
	size_t dotPosition = 0;
	for (size_t i = 0; i < core.length(); i++)
	{
		if (core[i] == '.')
		{
			dotPosition = i;
			countDot++;
		}
	}
	if (countDot != 1)
		return false;
	if (dotPosition == 0 || dotPosition == core.length() - 1)
    	return false;
	if (!(isdigit(static_cast<unsigned char>(core[dotPosition - 1]))) || !(isdigit(static_cast<unsigned char>(core[dotPosition + 1]))))
		return false;

	// Verificación global de caracteres
	for (size_t i = 0; i < core.length(); i++)
	{
		if (!isdigit(static_cast<unsigned char>(core[i])) && core[i] != '.')
			return false;
	}
	return true;
}

// Funciones de impresión
// 1) From char
void printFromChar(char c)
{
	if (c >= 32 && c <= 126)
		std::cout << "char: " << "'" << c << "'" << std::endl;
	else
		std::cout << "char: " << "Non displayable" << std::endl;

	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(c) << 'f' << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(c) << std::endl;
}

// 2) From int
void printFromInt(int n)
{
	if (n >= 32 && n <= 126)
		std::cout << "char: " << "'" << static_cast<char>(n) << "'" << std::endl;
	else if ((n >= 0 && n <= 31) || n == 127)
		std::cout << "char: " << "Non displayable" << std::endl;
	else
		std::cout << "char: " << "impossible" << std::endl;
	std::cout << "int: " << n << std::endl;
	std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(n) << 'f' << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(n) << std::endl;
}

// 3) From float
void printFromFloat(float f)
{
	if (f >= 32 && f <= 126)
		std::cout << "char: " << "'" << static_cast<char>(f) << "'" << std::endl;
	else if ((f >= 0 && f <= 31) || f == 127)
		std::cout << "char: " << "Non displayable" << std::endl;
	else
		std::cout << "char: " << "impossible" << std::endl;
	std::cout << "int: " << static_cast<int>(f) << std::endl;
	std::cout << "float: " << std::fixed << std::setprecision(1) << f << 'f' << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(f) << std::endl;
}

// 4) From double
// 4) From double
void printFromDouble(double d)
{
	if (d >= 32 && d <= 126)
		std::cout << "char: " << "'" << static_cast<char>(d) << "'" << std::endl;
	else if ((d >= 0 && d <= 31) || d == 127)
		std::cout << "char: " << "Non displayable" << std::endl;
	else
		std::cout << "char: " << "impossible" << std::endl;
	std::cout << "int: " << static_cast<int>(d) << std::endl;
	std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(d) << 'f' << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
}
// Función de fallback
void fallback()
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
}