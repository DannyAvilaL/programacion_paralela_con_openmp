#include <iostream>
#include <random>
#include <vector>
#include <omp.h>

#define mostrar 10
#define nHilos 2

// Funcion que genera un vector de numeros aleatorios con la cantidad indicada
std::vector<int> generarNumerosAleatorios(int cantidad)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 100);

	std::vector<int> numeros(cantidad);
	// Generando cada numero aleatorio
	for (int& num : numeros)
	{
		num = dist(gen);
	}

	return numeros;
}


void imprimerArreglo(std::vector<int> vector)
{
	// Iteracion por valor en el vector
	for (int x = 0; x < mostrar; x++)
	{
		std::cout << vector[x] << " ";
	}
	std::cout << std::endl;
}


int main()
{

	int cantidad;
	int pedazos;
	int i;

	// Pidiendo la cantidad de valores a generar en aleatorio para los dos vectores a sumar
	std::cout << "Ingresa la cantidad de valores en los vectores: ";
	std::cin >> cantidad;
	// Generando numeros aleatorios
	std::vector<int> vectorA = generarNumerosAleatorios(cantidad);
	std::vector<int> vectorB = generarNumerosAleatorios(cantidad);

	std::cout << "Imprimiendo los primeros " << mostrar << " valores del vector A: " << std::endl;
	imprimerArreglo(vectorA);
	std::cout << "Imprimiendo los primeros " << mostrar << " valores del vector B " << std::endl;
	imprimerArreglo(vectorB);

	// Creando el vectorC con 'cantidad' de espacios
	std::vector<int> vectorC(cantidad);

	//dividiendo la cantidad de valores por hilo
	pedazos = int(vectorA.size() / nHilos + vectorA.size() % nHilos);
	std::cout << "Cantidad de valores en cada hilo: " << pedazos << std::endl;

	// definiendo los vectores como variables compartidas. i como variable privada, dividiendo en pedazos de manera estatica en 2 hilos 
	#pragma omp parallel for shared(vectorA, vectorB, vectorC, pedazos) private(i) schedule(static, pedazos) num_threads(2)
	{
		for (i = 0; i < cantidad; i++)
		{
			vectorC[i] = vectorA[i] + vectorB[i];
		}

	}

	// Imprimiendo los primeros N valores del vector resultante
	std::cout << "Imprimiendo los primeros " << mostrar << " valores del vector C: " << std::endl;
	imprimerArreglo(vectorC);


}
