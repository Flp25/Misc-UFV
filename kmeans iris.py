#K means usando o iris dataset
import numpy as np
import matplotlib.pylab as plt
from scipy.spatial import distance
from sklearn import datasets
from sklearn import cluster

# Carrega o conjunto de dados
iris = datasets.load_iris()
# Separa um subconjunto do conjunto de dados.
# Considera apenas as duas classes, C1 e C2.
# Classes:
C1 = 1 # Versicolor
C2 = 2 # Virginica

# Considera apenas as caracteristicas largura (0) e comprimento (1) das Sepalas.
F = iris.data[(iris.target==C1) | (iris.target==C2), ::2]
T = iris.target[(iris.target==C1) | (iris.target==C2)]
# Caracteristicas das classes C1 e C2
F_C1 = F[T==C1]
F_C2 = F[T==C2]
# ----- TESTE -----
print T.shape
print T

# SKLEARN Classificadores
classificador = cluster.KMeans(n_clusters=2)
# Etapa de Treinamento
classificador.fit(F)
# Etapa de classificacao
classificacao = classificador.labels_
P = classificador.cluster_centers_

# Mostra resultados:
print 'Verdade: '
print T
print 'Classificacao: '
print classificacao
# Pepara para plotar
class_C1 = F[classificacao==0,:]
class_C2 = F[classificacao==1,:]

# Plota o conjunto de dados.
plt.figure()
plt.subplot(111)
plt.axis('equal')
plt.scatter(F_C1[:,0], F_C1[:,1], c='red')
plt.scatter(F_C2[:,0], F_C2[:,1], c='blue')
plt.title('Conjunto de dados original')
plt.xlabel('Comprimento da PETALA')
plt.ylabel('Largura da PETALA')

# Plota a classificação.
plt.figure()
plt.subplot(111)
plt.axis('equal')
plt.scatter(class_C1[:,0], class_C1[:,1], c='red')
plt.scatter(class_C2[:,0], class_C2[:,1], c='blue')
# plt.scatter(P_[0,0], P_[0,1], marker='s', c='red')
# plt.scatter(P_[1,0], P_[1,1], marker='s', c='blue')
plt.scatter(P[0,0], P[0,1], marker='x', c='red')
plt.scatter(P[1,0], P[1,1], marker='x', c='blue')
plt.title('Classificacao k-means')
plt.xlabel('Comprimento da PETALA')
plt.ylabel('Largura da PETALA')
# Mostra as figuras na tela.
plt.show()