/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:20:48 by sergio            #+#    #+#             */
/*   Updated: 2025/10/19 14:13:15 by sergio           ###   ########.fr       */
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
# include <string>		// std::string

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
// bool isIntLiteral(const std::string&);
// bool isFloatLiteral(const std::string&);
// bool isDoubleLiteral(const std::string&);
// bool isPseudoLiteral(const std::string&);

// Funciones de conversión e impresión
void printFromChar(char c);
// void printFromInt(int n);
// void printFromFloat(float f);
// void printFromDouble(double d);
// void printPseudo(const std::string& literal);
// void printImpossible();

#endif // SCALARCONVERTER_HPP
