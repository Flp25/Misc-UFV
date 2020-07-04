# -*- coding: UTF-8 -*-





import os #sys clear
import time # time.sleep
import random # rand, seed
import threading #threads
import numpy as np # n usei



class Banheiro:

	def __init__(self):
		
		self.t = -1
		self.box = 1 # Teste
		self.boxes = [ ]
		self.indices = -1
		self.historico = [ ]
		self.threadBox = threading.Condition() #Declaração de um objeto Condition()
		self.filaE = [ ] #FILA ESPERA FORA DO BANHEIRO
		self.filaB = [ ] #FILA ESPERA DO BANHEIRO
                self.esta_no_box = -1
		self.esta_usando_o_box = [ ]
	

	def init_tempo_box(self, usabox):

		for i in range(self.indices):
			usabox.append(0)

		return usabox


	def append_boxes(self, quantia):
		
		self.indices = quantia

		for i in range(quantia):
			self.boxes.append(True)
			self.esta_usando_o_box.append('-')



	def all_ocupied(self):
		
		if self.boxes[0] == False and self.boxes[1] == False and self.boxes[2] == False:
			return True

		return False

	def find_box(self):
		
		local = -1
		for i in range(self.indices):
			if self.boxes[i] == True:
				return i


		return local

	def lib_box(self):

		for i in range(self.indices):
			if self.boxes[self.indices] == False:
				return self.indices


	def tam_B(self):

		return len(self.filaB)

	def tam_H(self):

		return len(self.historico)

	def tam_E(self):
		
		return len(self.filaE)

	def disponibilidade_box(indice):
		
		return self.boxes[indice]


	def tempo_no_box(usabox):
		
		for i in range(3):
			if self.boxes[i] == False:
				usabox[i] += 1

		return usabox 

		
	

	def lb(self, indice):

		self.threadBox.acquire()

		if self.esta_no_box == 0:
			print "\n  > Homem saiu do banheiro...\n\n"

		else:
			print "\n  > Mulher saiu do banheiro...\n\n"
			

		
		
		self.esta_no_box = -1
		self.esta_usando_o_box[indice] = '-'
		self.boxes[indice] = True
		

		self.threadBox.notify()
		self.threadBox.release()


#*--------------------------*---------------------------*------------------------------*-----------------------------------*
		


	def usar_box(self):

		

		self.threadBox.acquire()

		

		while self.all_ocupied == True:
			self.threadBox.wait()


		
		if self.tam_B() == 1:
			self.t = -1


		self.box = self.find_box()


		if self.tam_B() > 0:
		
			
			self.esta_no_box = self.filaB.pop(0)
			#print self.filaB
			self.historico.append( self.esta_no_box)
			self.boxes[ self.box ] = False

			

			if self.esta_no_box == 0:
				print "\n  > H entrou no box..."
				self.esta_usando_o_box[self.box] = 'H'
				

			else:
				print "\n  > M entrou no box..."
				self.esta_usando_o_box[self.box] = 'M'

			
			

		self.threadBox.notify()
		self.threadBox.release()



			
#*--------------------------*---------------------------*------------------------------*-----------------------------------*

	def EntraBanheiro(self, pessoa):

                if pessoa == 0:
			print "\n\n> H chegou ..."

		else:
			print "\n\n> M chegou ..."


		if self.tam_H() == 0:
			
			self.filaB.append(pessoa)
			self.t = pessoa

		else:
			self.filaE.append(pessoa)
			


		if self.tam_B() == 0 and self.find_box() != -1 and self.tam_E() > 0:

			self.t = self.filaE[0]
		
		while True:
			
			if self.tam_E() > 0 and  self.filaE[0] == self.t:
				self.filaB.append(self.filaE.pop(0))

			else:
				break;



		return;

#*--------------------------*---------------------------*------------------------------*-----------------------------------*



	def imprime(self):
		
		
		print "\n\n\n\n________________________________________________"


		print " $ 0 = Homem, 1 = Mulher $\n"	

		print "FILA E = ", self.filaE
		print "FILA B = ", self.filaB
		
		print "\n"
		print "BOX = ", self.esta_usando_o_box
		print "BOX = ", self.boxes


                print "\nHISTORICO =", self.historico[0:10:1]
		#print "BOX >> ", self.box
		print "_________________________________________________\n"
				
#*--------------------------*---------------------------*------------------------------*--------------------------------*	

class Box(threading.Thread):

	def __init__(self, banheiro):

		threading.Thread.__init__(self)
		self.entrarbox = banheiro
	



	def run(self):
		self.entrarbox.usar_box()


#*--------------------------*---------------------------*------------------------------*-----------------------------------*


class B(threading.Thread):

	def __init__(self, banheiro, i):

		threading.Thread.__init__(self)
		self.liberarbox = banheiro
		self.indice_exclusao = i	



	def run(self):
		self.liberarbox.lb(self.indice_exclusao)

		


#*--------------------------*---------------------------*------------------------------*-----------------------------------*
def menu():

	print "___________________________________________"
	print "\nSIN - 142                  "
	print "Problema do Banheiro Unisex         " 
	print "\n$ Digite o numero de boxes $        "
	print "[ 1 ] = 50 pessoas"
	print "[ 3 ] = 150 pessoas"
	print "[ 5 ] = 250 pessoas \n\n"


def soma_tempo(boxes, indices, usabox):

	for i in range(indices):
		if  boxes[i] == False:
			usabox[i] += 1

	return usabox;

def main():

	chegou = 0
	usabox = [ ]
	b = Banheiro()

	menu()	

	while True:
		problema = int (raw_input())
		if problema > 0:
			break
		

	
	b.append_boxes(problema)
	usabox = b.init_tempo_box(usabox)
	
	limite = problema * 50

	''' limite equivale ao numero de pessoas que irão passar pelo
	    banheiro. Problema I   - 1 box   = 50  pessoas
			       II  - 3 boxes = 150 pessoas
			       III - 5 boxes = 250 pessoas
	'''
	
	
	travapessoa = False

   

	while len(b.historico) < limite:

		if travapessoa == False:

			random.seed() # "Semente" que controla o sorteio de números pseudo aleatórios
			pessoa_chegando = random.randrange(1, 8) # Sorteio de usuários - 0 Homen, 1 Mulher.
			sexo = random.randrange(0, 2)
			travapessoa = True


		time.sleep(1)
		chegou += 1

				
		usabox = soma_tempo(b.boxes, b.indices, usabox)

		


		if pessoa_chegando == chegou:

			chegou = 0
			travapessoa = False
			b.EntraBanheiro(sexo)


		t = Box(b)
		t.start()
                		

		

		
		for i in range (b.indices):
				
			if b.boxes[i] == False and usabox[i] == 5:
				
				u = B(b, i)
				u.start()
				usabox[i] = 0

		


		#os.system("clear")
		b.imprime()




		
			
#*--------------------------*---------------------------*------------------------------*-----------------------------------*

		
		

		

		

	
	

main() 
