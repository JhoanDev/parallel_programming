import numpy as np

# Dados fornecidos: n, p, tempo medido
data = [
    (2e9, 1, 5.197017),
    (2e9, 2, 2.663708),
    (2e9, 4, 1.810460),
    (4e9, 1, 10.464022),
    (4e9, 2, 5.401646),
    (4e9, 4, 3.697336),
    (6e9, 1, 15.635705),
    (6e9, 2, 8.573146),
    (6e9, 4, 5.586796),
    (8e9, 1, 20.917419),
    (8e9, 2, 11.451473),
    (8e9, 4, 7.568115),
]

X = [] 
y = []  

for n, p, time in data:
    x1 = n / p            
    x2 = np.log2(p)       
    X.append([x1, x2])    
    y.append(time)        

X = np.array(X)  
y = np.array(y)

X = np.c_[X, np.ones(X.shape[0])]

coefficients = np.linalg.lstsq(X, y, rcond=None)[0]

a, b, c = coefficients

print("Coeficientes estimados:")
print(f"a (n/p)     = {a:.6e}")
print(f"b (log2(p)) = {b:.6e}")

print("\nComparação entre tempos medidos e estimados:")
print("n/p\t\tlog2(p)\t\tTempo Medido\tTempo Estimado")
for (n, p, time), (x1, x2) in zip(data, X[:, :-1]):
    tempo_estimado = a * x1 + b * x2 + c
    print(f"{x1:.2e}\t{x2:.2f}\t\t{time:.6f}\t{tempo_estimado:.6f}")
