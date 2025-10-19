/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:20:48 by sergio            #+#    #+#             */
/*   Updated: 2025/10/19 22:48:26 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# define RED "\033[31m"
# define CYAN "\033[36m"
# define MAGENTA "\033[35m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

# include <iostream>	// std::cout, std::cerr
# include <string>		// std::string, empty(), length(), c_str()
# include <cstdlib>		// strtol()
# include <cerrno>		// errno
# include <climits>		// INT_MAX, INT_MIN
# include <iomanip>		// std::setprecision, std::fixed
# include <cctype>		// isdigit()
# include <cfloat>		// FLT_MAX, DBL_MAX

class ScalarConverter
{
	private:
		//OCF
		ScalarConverter();
		ScalarConverter(const ScalarConverter&);
		ScalarConverter& operator=(const ScalarConverter&);
		~ScalarConverter();
	
	public:
		static void convert(const std::string& input);
};

// Funciones de deteccion de tipos.
bool isCharLit(const std::string& input);
bool isIntLit(const std::string& input);
bool isFloatLit(const std::string& input);
bool isDoubleLit(const std::string& input);
// bool isPseudoLit(const std::string& input);

// Funciones de conversión e impresión
void printFromChar(char c);
void printFromInt(int n);
void printFromFloat(float f);
void printFromDouble(double d);
// void printPseudo(const std::string& literal);

// Funcion de Fallback
void fallback();

#endif // SCALARCONVERTER_HPP
