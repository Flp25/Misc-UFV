#K means
import numpy as np
import matplotlib.pylab as plt
from scipy.spatial import distance
from sklearn import datasets
from sklearn import cluster

def kmeans_simple(F, P):
    # N : Numero total de objetos
    # M : Numero de caracteristicas
    N, M = F.shape
    # Critério de parada
    m = np.Inf
    m_min = 0.01
    # Contador
    i=0
    while m > m_min:
        print '----------'
        print 'Iteracao ', i, 

        # Calcula a matriz de distancias inicial (D):
        D = distance.cdist(F, P, metric='euclidean')

        print '\nMatriz de distancias(D):'
        print D

        # Objetos mais proximos do vetor 1
        L1 = F[ D[:,0] <= D[:,1] ]
        # Objetos mais proximos do vetor 2
        L2 = F[ D[:,0] > D[:,1] ]
        
        # --- Print ---
        print '\nPontos em #1:'
        print L1
        print '\nPontos em #1:'
        print L2
        
        # Armazena valores dos vetores na ultima iteracao
        P_old = P.copy()
        
        # Move os vetores de prototipo
        P = np.zeros([2,M])
        P[0,:] = L1.mean()
        P[1,:] = L2.mean()

        # --- PRINT ---
        print '\nP_old:'
        print P_old
        print '\nP: '
        print P
        
        # Distancia entre a posicao dos vetores atual e anterior.
        m = np.max( np.sqrt( ((P_old - P)**2).sum(0) ) )
        print 'm: '
        print m

        # Pepara para plotar
        class_C1 = L1
        class_C2 = L2

        title = 'K-means. Iteracao ' + str(i)

        plt.figure()
        plt.subplot(111)
        plt.axis('equal')
        plt.scatter(class_C1[:,0], class_C1[:,1], c='red')
        plt.scatter(class_C2[:,0], class_C2[:,1], c='blue')

        plt.scatter(P_old[0,0], P_old[0,1], marker='x', c='red')
        plt.scatter(P_old[1,0], P_old[1,1], marker='x', c='blue')

        ax = plt.gca()
        ax.add_patch(plt.Arrow(P_old[0,0], P_old[0,1], P[0,0]-P_old[0,0], P[0,1]-P_old[0,1]))
        ax.add_patch(plt.Arrow(P_old[1,0], P_old[1,1], P[1,0]-P_old[1,0], P[1,1]-P_old[1,1]))       

        plt.scatter(P[0,0], P[0,1], marker='x', c='red')
        plt.scatter(P[1,0], P[1,1], marker='x', c='blue')
        plt.title(title)
        plt.xlabel('Caracteristica 0')
        plt.ylabel('Caracteristica 1')
        # Mostra as figuras na tela.
        plt.show()

        i = i+1
        # ---------------------------------------------------------------------

    # Calcula a matriz de distancias inicial (D):
    D = distance.cdist(F, P, metric='euclidean')

    # Gera valores para o retorno
    CLASS = np.zeros(N)
    # Objetos mais proximos do vetor 1
    CLASS[ D[:,0] <= D[:,1] ] = 0
    # Objetos mais proximos do vetor 2
    CLASS[ D[:,0] > D[:,1] ] = 1

    # Pepara para plotar
    class_C1 = F[CLASS==0,:]
    class_C2 = F[CLASS==1,:]

    plt.figure()
    plt.subplot(111)
    plt.axis('equal')
    plt.scatter(class_C1[:,0], class_C1[:,1], c='red')
    plt.scatter(class_C2[:,0], class_C2[:,1], c='blue')
    plt.scatter(P[0,0], P[0,1], marker='x', c='red')
    plt.scatter(P[1,0], P[1,1], marker='x', c='blue')
    plt.title('K-means. Final.')
    plt.xlabel('Caracteristica 0')
    plt.ylabel('Caracteristica 1')
    # Mostra as figuras na tela.
    plt.show()

    return [CLASS, P]
    # =========================================================================



# -----------------------------------------------------------------------------
# Conjunto de dados IRIS:
# -----------------------------------------------------------------------------
# Carrega o conjunto de dados
iris = datasets.load_iris()

# Separa um subconjunto do conjunto de dados. Considera apenas as duas classes,
# C1 e C2.
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

'''
# -----------------------------------------------------------------------------
# Conjunto de dados artificial:
# -----------------------------------------------------------------------------
F = np.array([[1.2, 2.0],
              [3.0, 3.7],
              [1.5, 2.7],
              [2.3, 2.0],
              [3.1, 3.3]])

T = [0, 1, 0, 0, 1]

# Classes:
C1 = 0 # Classe 1
C2 = 1 # Classe 2

# Caracteristicas das classes C1 e C2
F_C1 = F[T==C1]
F_C2 = F[T==C2]
'''

# k-means simples
# ===============
# Vetores prototipos iniciais
P_ = np.random.uniform(low=F.min(), high=F.max(), size=(2,2))
#P_ = np.array([[F.min(), F.min()], [F.max(), F.max()]])
[classificacao, P] = kmeans_simple(F, P_)

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

# Mostra as figuras na tela.
plt.show()