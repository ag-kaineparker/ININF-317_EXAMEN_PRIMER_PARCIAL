using System;
using System.Threading;

namespace SerieGeneradora
{
    class Program
    {
        static int[] valoresPares;
        static int[] valoresImpares;
        static int[] serie;

        static void CalcularValorSeriePar(object state)
        {
            int n = (int)state;
            valoresPares[n - 1] = n * n + 1;
        }

        static void CalcularValorSerieImpar(object state)
        {
            int n = (int)state;
            valoresImpares[n - 1] = n * 2;
        }

        static void Main(string[] args)
        {
            int n = 10000;
            valoresPares = new int[n / 2];
            valoresImpares = new int[n / 2];
            serie = new int[n];

            for (int i = 1; i <= n / 2; i++)
            {
                ThreadPool.QueueUserWorkItem(CalcularValorSeriePar, i);
                ThreadPool.QueueUserWorkItem(CalcularValorSerieImpar, i);
            }

            // Esperar a que se completen todas las tareas en segundo plano
            Thread.Sleep(5000);

            int j = 0;
            for (int i = 0; i < n / 2; i++)
            {
                serie[j++] = valoresPares[i];
                serie[j++] = valoresImpares[i];
            }

            // Imprimir la serie
            foreach (var num in serie)
            {
                Console.Write(num + " ");
            }
            Console.ReadKey();
        }
    }
}
