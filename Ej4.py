from multiprocessing import Pool

def calcular_valor_serie_par(n):
    return n * n + 1
    
def calcular_valor_serie_impar(n):
    return n * 2 + 2

if __name__ == "__main__":
    n = 10000  # Puedes ajustar este valor para generar más términos de la serie
    pool = Pool()

    valores_pares = pool.map(calcular_valor_serie_par, range(1, n // 2 + 1))
    valores_impares = pool.map(calcular_valor_serie_impar, range(n // 2))

    serie = [valores_pares[i // 2] if i % 2 == 0 else valores_impares[i // 2] for i in range(n)]

    pool.close()
    pool.join()

    print(serie)
