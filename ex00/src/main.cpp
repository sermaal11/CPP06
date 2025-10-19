/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:20:37 by sergio            #+#    #+#             */
/*   Updated: 2025/10/19 12:52:28 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScalarConverter.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << RED << "Usage: ./conversion_of_scalar_types <literal>\n" << RESET;
		return 1;
	}
	ScalarConverter::convert(argv[1]);
	return 0;
}

