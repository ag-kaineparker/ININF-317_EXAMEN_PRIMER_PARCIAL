using System;
using System.Threading;

namespace CalculoPi
{
    class Program
    {
        static decimal CalcularPi(int inicio, int fin)
        {
            decimal pi = 0;
            for (int i = inicio; i <= fin; i++)
            {
                if (i % 2 == 0)
                {
                    pi += 1.0m / ((2 * i) + 1);
                }
                else
                {
                    pi -= 1.0m / ((2 * i) + 1);
                }
            }
            return pi * 4;
        }

        static void Main(string[] args)
        {
            int n = 100000;
            int procesadores = Environment.ProcessorCount;

            decimal resultadoFinal = 0;
            object lockObj = new object();

            ThreadPool.SetMinThreads(procesadores, procesadores);

            ManualResetEvent[] eventos = new ManualResetEvent[procesadores];

            for (int i = 0; i < procesadores; i++)
            {
                eventos[i] = new ManualResetEvent(false);
                int inicio = i * (n / procesadores);
                int fin = (i + 1) * (n / procesadores) - 1;

                ThreadPool.QueueUserWorkItem((state) =>
                {
                    int[] indices = (int[])state;
                    decimal resultadoParcial = CalcularPi(indices[0], indices[1]);
                    lock (lockObj)
                    {
                        resultadoFinal += resultadoParcial;
                    }
                    eventos[indices[2]].Set();
                }, new int[] { inicio, fin, i });
            }

            WaitHandle.WaitAll(eventos);

            Console.WriteLine($"Resultado: {resultadoFinal}");
            Console.ReadKey();
        }
    }
}
